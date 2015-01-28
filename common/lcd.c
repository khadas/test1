/*
 * Common LCD routines for supported CPUs
 *
 * (C) Copyright 2001-2002
 * Wolfgang Denk, DENX Software Engineering -- wd@denx.de
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

/************************************************************************/
/* ** HEADER FILES							*/
/************************************************************************/

/* #define DEBUG */

#include <config.h>
#include <common.h>
#include <command.h>
#include <stdarg.h>
#include <search.h>
#include <env_callback.h>
#include <linux/types.h>
#include <stdio_dev.h>
#if defined(CONFIG_POST)
#include <post.h>
#endif
#include <lcd.h>
#include <watchdog.h>
#include <asm/unaligned.h>
#include <splash.h>
#include <asm/io.h>
#include <asm/unaligned.h>
#include <fdt_support.h>

#if defined(CONFIG_CPU_PXA25X) || defined(CONFIG_CPU_PXA27X) || \
	defined(CONFIG_CPU_MONAHANS)
#include <asm/byteorder.h>
#endif

#if defined(CONFIG_MPC823)
#include <lcdvideo.h>
#endif

#if defined(CONFIG_ATMEL_LCD)
#include <atmel_lcdc.h>
#endif

#if defined(CONFIG_LCD_DT_SIMPLEFB)
#include <libfdt.h>
#endif

/************************************************************************/
/* ** FONT DATA								*/
/************************************************************************/
#include <video_font.h>		/* Get font data, width and height	*/

/************************************************************************/
/* ** LOGO DATA								*/
/************************************************************************/
#ifdef CONFIG_LCD_LOGO
# include <bmp_logo.h>		/* Get logo data, width and height	*/
# include <bmp_logo_data.h>
# if (CONSOLE_COLOR_WHITE >= BMP_LOGO_OFFSET) && (LCD_BPP != LCD_COLOR16)
#  error Default Color Map overlaps with Logo Color Map
# endif
#endif

#ifdef CONFIG_SANDBOX
#include <asm/sdl.h>
#endif

#ifndef CONFIG_LCD_ALIGNMENT
#define CONFIG_LCD_ALIGNMENT PAGE_SIZE
#endif

#if (LCD_BPP != LCD_COLOR8) && (LCD_BPP != LCD_COLOR16) && \
	(LCD_BPP != LCD_COLOR32)
# error Unsupported LCD BPP.
#endif

DECLARE_GLOBAL_DATA_PTR;

static int lcd_init(void *lcdbase);

static void *lcd_logo(void);

static void lcd_setfgcolor(int color);
static void lcd_setbgcolor(int color);

static int lcd_color_fg;
static int lcd_color_bg;
int lcd_line_length;

char lcd_is_enabled = 0;

static void *lcd_base;			/* Start of framebuffer memory	*/

static char lcd_flush_dcache;	/* 1 to flush dcache after each lcd update */

/************************************************************************/

/* Flush LCD activity to the caches */
void lcd_sync(void)
{
	/*
	 * flush_dcache_range() is declared in common.h but it seems that some
	 * architectures do not actually implement it. Is there a way to find
	 * out whether it exists? For now, ARM is safe.
	 */
#if defined(CONFIG_ARM) && !defined(CONFIG_SYS_DCACHE_OFF)
	int line_length;

	if (lcd_flush_dcache)
		flush_dcache_range((u32)lcd_base,
			(u32)(lcd_base + lcd_get_size(&line_length)));
#elif defined(CONFIG_SANDBOX) && defined(CONFIG_VIDEO_SANDBOX_SDL)
	static ulong last_sync;

	if (get_timer(last_sync) > 10) {
		sandbox_sdl_sync(lcd_base);
		last_sync = get_timer(0);
	}
#endif
}

void lcd_set_flush_dcache(int flush)
{
	lcd_flush_dcache = (flush != 0);
}

/*----------------------------------------------------------------------*/

static void lcd_stub_putc(struct stdio_dev *dev, const char c)
{
	lcd_putc(c);
}

static void lcd_stub_puts(struct stdio_dev *dev, const char *s)
{
	lcd_puts(s);
}

/************************************************************************/
/**  Small utility to check that you got the colours right		*/
/************************************************************************/
#ifdef LCD_TEST_PATTERN

#define	N_BLK_VERT	2
#define	N_BLK_HOR	3

static int test_colors[N_BLK_HOR * N_BLK_VERT] = {
	CONSOLE_COLOR_RED,	CONSOLE_COLOR_GREEN,	CONSOLE_COLOR_YELLOW,
	CONSOLE_COLOR_BLUE,	CONSOLE_COLOR_MAGENTA,	CONSOLE_COLOR_CYAN,
};

static void test_pattern(void)
{
	ushort v_max  = panel_info.vl_row;
	ushort h_max  = panel_info.vl_col;
	ushort v_step = (v_max + N_BLK_VERT - 1) / N_BLK_VERT;
	ushort h_step = (h_max + N_BLK_HOR  - 1) / N_BLK_HOR;
	ushort v, h;
	uchar *pix = (uchar *)lcd_base;

	printf("[LCD] Test Pattern: %d x %d [%d x %d]\n",
		h_max, v_max, h_step, v_step);

	/* WARNING: Code silently assumes 8bit/pixel */
	for (v = 0; v < v_max; ++v) {
		uchar iy = v / v_step;
		for (h = 0; h < h_max; ++h) {
			uchar ix = N_BLK_HOR * iy + h / h_step;
			*pix++ = test_colors[ix];
		}
	}
}
#endif /* LCD_TEST_PATTERN */


/************************************************************************/
/* ** GENERIC Initialization Routines					*/
/************************************************************************/
/*
 * With most lcd drivers the line length is set up
 * by calculating it from panel_info parameters. Some
 * drivers need to calculate the line length differently,
 * so make the function weak to allow overriding it.
 */
__weak int lcd_get_size(int *line_length)
{
	*line_length = (panel_info.vl_col * NBITS(panel_info.vl_bpix)) / 8;
	return *line_length * panel_info.vl_row;
}

int drv_lcd_init(void)
{
	struct stdio_dev lcddev;
	int rc;

	lcd_base = map_sysmem(gd->fb_base, 0);

	lcd_init(lcd_base);		/* LCD initialization */

	/* Device initialization */
	memset(&lcddev, 0, sizeof(lcddev));

	strcpy(lcddev.name, "lcd");
	lcddev.ext   = 0;			/* No extensions */
	lcddev.flags = DEV_FLAGS_OUTPUT;	/* Output only */
	lcddev.putc  = lcd_stub_putc;		/* 'putc' function */
	lcddev.puts  = lcd_stub_puts;		/* 'puts' function */

	rc = stdio_register(&lcddev);

	return (rc == 0) ? 1 : rc;
}

/*----------------------------------------------------------------------*/
void lcd_clear(void)
{
	short console_rows, console_cols;
	int bg_color;
#if LCD_BPP == LCD_COLOR8
	/* Setting the palette */
	lcd_setcolreg(CONSOLE_COLOR_BLACK, 0, 0, 0);
	lcd_setcolreg(CONSOLE_COLOR_RED, 0xFF, 0, 0);
	lcd_setcolreg(CONSOLE_COLOR_GREEN, 0, 0xFF, 0);
	lcd_setcolreg(CONSOLE_COLOR_YELLOW, 0xFF, 0xFF, 0);
	lcd_setcolreg(CONSOLE_COLOR_BLUE, 0, 0, 0xFF);
	lcd_setcolreg(CONSOLE_COLOR_MAGENTA, 0xFF, 0, 0xFF);
	lcd_setcolreg(CONSOLE_COLOR_CYAN, 0, 0xFF, 0xFF);
	lcd_setcolreg(CONSOLE_COLOR_GREY, 0xAA, 0xAA, 0xAA);
	lcd_setcolreg(CONSOLE_COLOR_WHITE, 0xFF, 0xFF, 0xFF);
#endif

#ifndef CONFIG_SYS_WHITE_ON_BLACK
	lcd_setfgcolor(CONSOLE_COLOR_BLACK);
	lcd_setbgcolor(CONSOLE_COLOR_WHITE);
	bg_color = CONSOLE_COLOR_WHITE;
#else
	lcd_setfgcolor(CONSOLE_COLOR_WHITE);
	lcd_setbgcolor(CONSOLE_COLOR_BLACK);
	bg_color = CONSOLE_COLOR_BLACK;
#endif	/* CONFIG_SYS_WHITE_ON_BLACK */

#ifdef	LCD_TEST_PATTERN
	test_pattern();
#else
	/* set framebuffer to background color */
#if (LCD_BPP != LCD_COLOR32)
	memset((char *)lcd_base, bg_color, lcd_line_length * panel_info.vl_row);
#else
	u32 *ppix = lcd_base;
	u32 i;
	for (i = 0;
	   i < (lcd_line_length * panel_info.vl_row)/NBYTES(panel_info.vl_bpix);
	   i++) {
		*ppix++ = bg_color;
	}
#endif
#endif
	/* Paint the logo and retrieve LCD base address */
	debug("[LCD] Drawing the logo...\n");
#if defined(CONFIG_LCD_LOGO) && !defined(CONFIG_LCD_INFO_BELOW_LOGO)
	console_rows = (panel_info.vl_row - BMP_LOGO_HEIGHT);
	console_rows /= VIDEO_FONT_HEIGHT;
#else
	console_rows = panel_info.vl_row / VIDEO_FONT_HEIGHT;
#endif
	console_cols = panel_info.vl_col / VIDEO_FONT_WIDTH;
	lcd_init_console(lcd_base, console_rows, console_cols);
	lcd_init_console(lcd_logo(), console_rows, console_cols);
	lcd_sync();
}

static int do_lcd_clear(cmd_tbl_t *cmdtp, int flag, int argc,
			char *const argv[])
{
	lcd_clear();
	return 0;
}

U_BOOT_CMD(
	cls,	1,	1,	do_lcd_clear,
	"clear screen",
	""
);

/*----------------------------------------------------------------------*/

static int lcd_init(void *lcdbase)
{
	/* Initialize the lcd controller */
	debug("[LCD] Initializing LCD frambuffer at %p\n", lcdbase);

	lcd_ctrl_init(lcdbase);

	/*
	 * lcd_ctrl_init() of some drivers (i.e. bcm2835 on rpi) ignores
	 * the 'lcdbase' argument and uses custom lcd base address
	 * by setting up gd->fb_base. Check for this condition and fixup
	 * 'lcd_base' address.
	 */
	if (map_to_sysmem(lcdbase) != gd->fb_base)
		lcd_base = map_sysmem(gd->fb_base, 0);

	debug("[LCD] Using LCD frambuffer at %p\n", lcd_base);

	lcd_get_size(&lcd_line_length);
	lcd_is_enabled = 1;
	lcd_clear();
	lcd_enable();

	/* Initialize the console */
	lcd_set_col(0);
#ifdef CONFIG_LCD_INFO_BELOW_LOGO
	lcd_set_row(7 + BMP_LOGO_HEIGHT / VIDEO_FONT_HEIGHT);
#else
	lcd_set_row(1);	/* leave 1 blank line below logo */
#endif

	return 0;
}


/************************************************************************/
/* ** ROM capable initialization part - needed to reserve FB memory	*/
/************************************************************************/
/*
 * This is called early in the system initialization to grab memory
 * for the LCD controller.
 * Returns new address for monitor, after reserving LCD buffer memory
 *
 * Note that this is running from ROM, so no write access to global data.
 */
ulong lcd_setmem(ulong addr)
{
	ulong size;
	int line_length;

	debug("LCD panel info: %d x %d, %d bit/pix\n", panel_info.vl_col,
		panel_info.vl_row, NBITS(panel_info.vl_bpix));

	size = lcd_get_size(&line_length);

	/* Round up to nearest full page, or MMU section if defined */
	size = ALIGN(size, CONFIG_LCD_ALIGNMENT);
	addr = ALIGN(addr - CONFIG_LCD_ALIGNMENT + 1, CONFIG_LCD_ALIGNMENT);

	/* Allocate pages for the frame buffer. */
	addr -= size;

	debug("Reserving %ldk for LCD Framebuffer at: %08lx\n",
	      size >> 10, addr);

	return addr;
}

/*----------------------------------------------------------------------*/

static void lcd_setfgcolor(int color)
{
	lcd_color_fg = color;
}

int lcd_getfgcolor(void)
{
	return lcd_color_fg;
}

/*----------------------------------------------------------------------*/

static void lcd_setbgcolor(int color)
{
	lcd_color_bg = color;
}

int lcd_getbgcolor(void)
{
	return lcd_color_bg;
}

/************************************************************************/
/* ** Chipset depending Bitmap / Logo stuff...                          */
/************************************************************************/
static inline ushort *configuration_get_cmap(void)
{
#if defined CONFIG_CPU_PXA
	struct pxafb_info *fbi = &panel_info.pxa;
	return (ushort *)fbi->palette;
#elif defined(CONFIG_MPC823)
	immap_t *immr = (immap_t *) CONFIG_SYS_IMMR;
	cpm8xx_t *cp = &(immr->im_cpm);
	return (ushort *)&(cp->lcd_cmap[255 * sizeof(ushort)]);
#elif defined(CONFIG_ATMEL_LCD)
	return (ushort *)(panel_info.mmio + ATMEL_LCDC_LUT(0));
#elif !defined(CONFIG_ATMEL_HLCD) && !defined(CONFIG_EXYNOS_FB)
	return panel_info.cmap;
#elif defined(CONFIG_LCD_LOGO)
	return bmp_logo_palette;
#else
	return NULL;
#endif
}

#ifdef CONFIG_LCD_LOGO
void bitmap_plot(int x, int y)
{
#ifdef CONFIG_ATMEL_LCD
	uint *cmap = (uint *)bmp_logo_palette;
#else
	ushort *cmap = (ushort *)bmp_logo_palette;
#endif
	ushort i, j;
	uchar *bmap;
	uchar *fb;
	ushort *fb16;
#if defined(CONFIG_MPC823)
	immap_t *immr = (immap_t *) CONFIG_SYS_IMMR;
	cpm8xx_t *cp = &(immr->im_cpm);
#endif
	unsigned bpix = NBITS(panel_info.vl_bpix);

	debug("Logo: width %d  height %d  colors %d  cmap %d\n",
		BMP_LOGO_WIDTH, BMP_LOGO_HEIGHT, BMP_LOGO_COLORS,
		ARRAY_SIZE(bmp_logo_palette));

	bmap = &bmp_logo_bitmap[0];
	fb   = (uchar *)(lcd_base + y * lcd_line_length + x * bpix / 8);

	if (bpix < 12) {
		/* Leave room for default color map
		 * default case: generic system with no cmap (most likely 16bpp)
		 * cmap was set to the source palette, so no change is done.
		 * This avoids even more ifdefs in the next stanza
		 */
#if defined(CONFIG_MPC823)
		cmap = (ushort *) &(cp->lcd_cmap[BMP_LOGO_OFFSET * sizeof(ushort)]);
#elif defined(CONFIG_ATMEL_LCD)
		cmap = (uint *)configuration_get_cmap();
#else
		cmap = configuration_get_cmap();
#endif

		WATCHDOG_RESET();

		/* Set color map */
		for (i = 0; i < ARRAY_SIZE(bmp_logo_palette); ++i) {
			ushort colreg = bmp_logo_palette[i];
#ifdef CONFIG_ATMEL_LCD
			uint lut_entry;
#ifdef CONFIG_ATMEL_LCD_BGR555
			lut_entry = ((colreg & 0x000F) << 11) |
					((colreg & 0x00F0) <<  2) |
					((colreg & 0x0F00) >>  7);
#else /* CONFIG_ATMEL_LCD_RGB565 */
			lut_entry = ((colreg & 0x000F) << 1) |
					((colreg & 0x00F0) << 3) |
					((colreg & 0x0F00) << 4);
#endif
			*(cmap + BMP_LOGO_OFFSET) = lut_entry;
			cmap++;
#else /* !CONFIG_ATMEL_LCD */
			*cmap++ = colreg;
#endif /* CONFIG_ATMEL_LCD */
		}

		WATCHDOG_RESET();

		for (i = 0; i < BMP_LOGO_HEIGHT; ++i) {
			memcpy(fb, bmap, BMP_LOGO_WIDTH);
			bmap += BMP_LOGO_WIDTH;
			fb += panel_info.vl_col;
		}
	}
	else { /* true color mode */
		u16 col16;
		fb16 = (ushort *)fb;
		for (i = 0; i < BMP_LOGO_HEIGHT; ++i) {
			for (j = 0; j < BMP_LOGO_WIDTH; j++) {
				col16 = bmp_logo_palette[(bmap[j]-16)];
				fb16[j] =
					((col16 & 0x000F) << 1) |
					((col16 & 0x00F0) << 3) |
					((col16 & 0x0F00) << 4);
				}
			bmap += BMP_LOGO_WIDTH;
			fb16 += panel_info.vl_col;
		}
	}

	WATCHDOG_RESET();
	lcd_sync();
}
#else
static inline void bitmap_plot(int x, int y) {}
#endif /* CONFIG_LCD_LOGO */

/*----------------------------------------------------------------------*/
#if defined(CONFIG_CMD_BMP) || defined(CONFIG_SPLASH_SCREEN)
/*
 * Display the BMP file located at address bmp_image.
 * Only uncompressed.
 */

#ifdef CONFIG_SPLASH_SCREEN_ALIGN
#define BMP_ALIGN_CENTER	0x7FFF

static void splash_align_axis(int *axis, unsigned long panel_size,
					unsigned long picture_size)
{
	unsigned long panel_picture_delta = panel_size - picture_size;
	unsigned long axis_alignment;

	if (*axis == BMP_ALIGN_CENTER)
		axis_alignment = panel_picture_delta / 2;
	else if (*axis < 0)
		axis_alignment = panel_picture_delta + *axis + 1;
	else
		return;

	*axis = max(0, (int)axis_alignment);
}
#endif


#ifdef CONFIG_LCD_BMP_RLE8

#define BMP_RLE8_ESCAPE		0
#define BMP_RLE8_EOL		0
#define BMP_RLE8_EOBMP		1
#define BMP_RLE8_DELTA		2

static void draw_unencoded_bitmap(ushort **fbp, uchar *bmap, ushort *cmap,
				  int cnt)
{
	while (cnt > 0) {
		*(*fbp)++ = cmap[*bmap++];
		cnt--;
	}
}

static void draw_encoded_bitmap(ushort **fbp, ushort c, int cnt)
{
	ushort *fb = *fbp;
	int cnt_8copy = cnt >> 3;

	cnt -= cnt_8copy << 3;
	while (cnt_8copy > 0) {
		*fb++ = c;
		*fb++ = c;
		*fb++ = c;
		*fb++ = c;
		*fb++ = c;
		*fb++ = c;
		*fb++ = c;
		*fb++ = c;
		cnt_8copy--;
	}
	while (cnt > 0) {
		*fb++ = c;
		cnt--;
	}
	*fbp = fb;
}

/*
 * Do not call this function directly, must be called from lcd_display_bitmap.
 */
static void lcd_display_rle8_bitmap(bmp_image_t *bmp, ushort *cmap, uchar *fb,
				    int x_off, int y_off)
{
	uchar *bmap;
	ulong width, height;
	ulong cnt, runlen;
	int x, y;
	int decode = 1;

	width = get_unaligned_le32(&bmp->header.width);
	height = get_unaligned_le32(&bmp->header.height);
	bmap = (uchar *)bmp + get_unaligned_le32(&bmp->header.data_offset);

	x = 0;
	y = height - 1;

	while (decode) {
		if (bmap[0] == BMP_RLE8_ESCAPE) {
			switch (bmap[1]) {
			case BMP_RLE8_EOL:
				/* end of line */
				bmap += 2;
				x = 0;
				y--;
				/* 16bpix, 2-byte per pixel, width should *2 */
				fb -= (width * 2 + lcd_line_length);
				break;
			case BMP_RLE8_EOBMP:
				/* end of bitmap */
				decode = 0;
				break;
			case BMP_RLE8_DELTA:
				/* delta run */
				x += bmap[2];
				y -= bmap[3];
				/* 16bpix, 2-byte per pixel, x should *2 */
				fb = (uchar *) (lcd_base + (y + y_off - 1)
					* lcd_line_length + (x + x_off) * 2);
				bmap += 4;
				break;
			default:
				/* unencoded run */
				runlen = bmap[1];
				bmap += 2;
				if (y < height) {
					if (x < width) {
						if (x + runlen > width)
							cnt = width - x;
						else
							cnt = runlen;
						draw_unencoded_bitmap(
							(ushort **)&fb,
							bmap, cmap, cnt);
					}
					x += runlen;
				}
				bmap += runlen;
				if (runlen & 1)
					bmap++;
			}
		} else {
			/* encoded run */
			if (y < height) {
				runlen = bmap[0];
				if (x < width) {
					/* aggregate the same code */
					while (bmap[0] == 0xff &&
					       bmap[2] != BMP_RLE8_ESCAPE &&
					       bmap[1] == bmap[3]) {
						runlen += bmap[2];
						bmap += 2;
					}
					if (x + runlen > width)
						cnt = width - x;
					else
						cnt = runlen;
					draw_encoded_bitmap((ushort **)&fb,
						cmap[bmap[1]], cnt);
				}
				x += runlen;
			}
			bmap += 2;
		}
	}
}
#endif

#if defined(CONFIG_MPC823)
#define FB_PUT_BYTE(fb, from) *(fb)++ = (255 - *(from)++)
#else
#define FB_PUT_BYTE(fb, from) *(fb)++ = *(from)++
#endif

#if defined(CONFIG_BMP_16BPP)
#if defined(CONFIG_ATMEL_LCD_BGR555)
static inline void fb_put_word(uchar **fb, uchar **from)
{
	*(*fb)++ = (((*from)[0] & 0x1f) << 2) | ((*from)[1] & 0x03);
	*(*fb)++ = ((*from)[0] & 0xe0) | (((*from)[1] & 0x7c) >> 2);
	*from += 2;
}
#else
static inline void fb_put_word(uchar **fb, uchar **from)
{
	*(*fb)++ = *(*from)++;
	*(*fb)++ = *(*from)++;
}
#endif
#endif /* CONFIG_BMP_16BPP */

int lcd_display_bitmap(ulong bmp_image, int x, int y)
{
	ushort *cmap = NULL;
	ushort *cmap_base = NULL;
	ushort i, j;
	uchar *fb;
	bmp_image_t *bmp = (bmp_image_t *)map_sysmem(bmp_image, 0);
	uchar *bmap;
	ushort padded_width;
	unsigned long width, height, byte_width;
	unsigned long pwidth = panel_info.vl_col;
	unsigned colors, bpix, bmp_bpix;

	if (!bmp || !(bmp->header.signature[0] == 'B' &&
		bmp->header.signature[1] == 'M')) {
		printf("Error: no valid bmp image at %lx\n", bmp_image);

		return 1;
	}

	width = get_unaligned_le32(&bmp->header.width);
	height = get_unaligned_le32(&bmp->header.height);
	bmp_bpix = get_unaligned_le16(&bmp->header.bit_count);

	colors = 1 << bmp_bpix;

	bpix = NBITS(panel_info.vl_bpix);

	if (bpix != 1 && bpix != 8 && bpix != 16 && bpix != 32) {
		printf ("Error: %d bit/pixel mode, but BMP has %d bit/pixel\n",
			bpix, bmp_bpix);

		return 1;
	}

	/*
	 * We support displaying 8bpp BMPs on 16bpp LCDs
	 * and displaying 24bpp BMPs on 32bpp LCDs
	 * */
	if (bpix != bmp_bpix &&
	    !(bmp_bpix == 8 && bpix == 16) &&
	    !(bmp_bpix == 24 && bpix == 32)) {
		printf ("Error: %d bit/pixel mode, but BMP has %d bit/pixel\n",
			bpix, get_unaligned_le16(&bmp->header.bit_count));
		return 1;
	}

	debug("Display-bmp: %d x %d  with %d colors\n",
		(int)width, (int)height, (int)colors);

	if (bmp_bpix == 8) {
		cmap = configuration_get_cmap();
		cmap_base = cmap;

		/* Set color map */
		for (i = 0; i < colors; ++i) {
			bmp_color_table_entry_t cte = bmp->color_table[i];
#if !defined(CONFIG_ATMEL_LCD)
			ushort colreg =
				( ((cte.red)   << 8) & 0xf800) |
				( ((cte.green) << 3) & 0x07e0) |
				( ((cte.blue)  >> 3) & 0x001f) ;
			*cmap = colreg;
#if defined(CONFIG_MPC823)
			cmap--;
#else
			cmap++;
#endif
#else /* CONFIG_ATMEL_LCD */
			lcd_setcolreg(i, cte.red, cte.green, cte.blue);
#endif
		}
	}

	padded_width = (width & 0x3 ? (width & ~0x3) + 4 : width);

#ifdef CONFIG_SPLASH_SCREEN_ALIGN
	splash_align_axis(&x, pwidth, width);
	splash_align_axis(&y, panel_info.vl_row, height);
#endif /* CONFIG_SPLASH_SCREEN_ALIGN */

	if ((x + width) > pwidth)
		width = pwidth - x;
	if ((y + height) > panel_info.vl_row)
		height = panel_info.vl_row - y;

	bmap = (uchar *)bmp + get_unaligned_le32(&bmp->header.data_offset);
	fb   = (uchar *)(lcd_base +
		(y + height - 1) * lcd_line_length + x * bpix / 8);

	switch (bmp_bpix) {
	case 1: /* pass through */
	case 8: {
#ifdef CONFIG_LCD_BMP_RLE8
		u32 compression = get_unaligned_le32(&bmp->header.compression);
		if (compression == BMP_BI_RLE8) {
			if (bpix != 16) {
				/* TODO implement render code for bpix != 16 */
				printf("Error: only support 16 bpix");
				return 1;
			}
			lcd_display_rle8_bitmap(bmp, cmap_base, fb, x, y);
			break;
		}
#endif

		if (bpix != 16)
			byte_width = width;
		else
			byte_width = width * 2;

		for (i = 0; i < height; ++i) {
			WATCHDOG_RESET();
			for (j = 0; j < width; j++) {
				if (bpix != 16) {
					FB_PUT_BYTE(fb, bmap);
				} else {
					*(uint16_t *)fb = cmap_base[*(bmap++)];
					fb += sizeof(uint16_t) / sizeof(*fb);
				}
			}
			bmap += (padded_width - width);
			fb -= byte_width + lcd_line_length;
		}
		break;
	}
#if defined(CONFIG_BMP_16BPP)
	case 16:
		for (i = 0; i < height; ++i) {
			WATCHDOG_RESET();
			for (j = 0; j < width; j++)
				fb_put_word(&fb, &bmap);

			bmap += (padded_width - width) * 2;
			fb -= width * 2 + lcd_line_length;
		}
		break;
#endif /* CONFIG_BMP_16BPP */
#if defined(CONFIG_BMP_24BMP)
	case 24:
		for (i = 0; i < height; ++i) {
			for (j = 0; j < width; j++) {
				*(fb++) = *(bmap++);
				*(fb++) = *(bmap++);
				*(fb++) = *(bmap++);
				*(fb++) = 0;
			}
			fb -= lcd_line_length + width * (bpix / 8);
		}
		break;
#endif /* CONFIG_BMP_24BMP */
#if defined(CONFIG_BMP_32BPP)
	case 32:
		for (i = 0; i < height; ++i) {
			for (j = 0; j < width; j++) {
				*(fb++) = *(bmap++);
				*(fb++) = *(bmap++);
				*(fb++) = *(bmap++);
				*(fb++) = *(bmap++);
			}
			fb -= lcd_line_length + width * (bpix / 8);
		}
		break;
#endif /* CONFIG_BMP_32BPP */
	default:
		break;
	};

	lcd_sync();
	return 0;
}
#endif

static void *lcd_logo(void)
{
#ifdef CONFIG_SPLASH_SCREEN
	char *s;
	ulong addr;
	static int do_splash = 1;

	if (do_splash && (s = getenv("splashimage")) != NULL) {
		int x = 0, y = 0;
		do_splash = 0;

		if (splash_screen_prepare())
			return (void *)lcd_base;

		addr = simple_strtoul (s, NULL, 16);

		splash_get_pos(&x, &y);

		if (bmp_display(addr, x, y) == 0)
			return (void *)lcd_base;
	}
#endif /* CONFIG_SPLASH_SCREEN */

	bitmap_plot(0, 0);

#ifdef CONFIG_LCD_INFO
	lcd_set_col(LCD_INFO_X / VIDEO_FONT_WIDTH);
	lcd_set_row(LCD_INFO_Y / VIDEO_FONT_HEIGHT);
	lcd_show_board_info();
#endif /* CONFIG_LCD_INFO */

#if defined(CONFIG_LCD_LOGO) && !defined(CONFIG_LCD_INFO_BELOW_LOGO)
	return (void *)((ulong)lcd_base + BMP_LOGO_HEIGHT * lcd_line_length);
#else
	return (void *)lcd_base;
#endif /* CONFIG_LCD_LOGO && !defined(CONFIG_LCD_INFO_BELOW_LOGO) */
}

#ifdef CONFIG_SPLASHIMAGE_GUARD
static int on_splashimage(const char *name, const char *value, enum env_op op,
	int flags)
{
	ulong addr;
	int aligned;

	if (op == env_op_delete)
		return 0;

	addr = simple_strtoul(value, NULL, 16);
	/* See README.displaying-bmps */
	aligned = (addr % 4 == 2);
	if (!aligned) {
		printf("Invalid splashimage value. Value must be 16 bit aligned, but not 32 bit aligned\n");
		return -1;
	}

	return 0;
}

U_BOOT_ENV_CALLBACK(splashimage, on_splashimage);
#endif

int lcd_get_pixel_width(void)
{
	return panel_info.vl_col;
}

int lcd_get_pixel_height(void)
{
	return panel_info.vl_row;
}

#if defined(CONFIG_LCD_DT_SIMPLEFB)
static int lcd_dt_simplefb_configure_node(void *blob, int off)
{
#if LCD_BPP == LCD_COLOR16
	return fdt_setup_simplefb_node(blob, off, gd->fb_base,
				       panel_info.vl_col, panel_info.vl_row,
				       panel_info.vl_col * 2, "r5g6b5");
#else
	return -1;
#endif
}

int lcd_dt_simplefb_add_node(void *blob)
{
	static const char compat[] = "simple-framebuffer";
	static const char disabled[] = "disabled";
	int off, ret;

	off = fdt_add_subnode(blob, 0, "framebuffer");
	if (off < 0)
		return -1;

	ret = fdt_setprop(blob, off, "status", disabled, sizeof(disabled));
	if (ret < 0)
		return -1;

	ret = fdt_setprop(blob, off, "compatible", compat, sizeof(compat));
	if (ret < 0)
		return -1;

	return lcd_dt_simplefb_configure_node(blob, off);
}

int lcd_dt_simplefb_enable_existing_node(void *blob)
{
	int off;

	off = fdt_node_offset_by_compatible(blob, -1, "simple-framebuffer");
	if (off < 0)
		return -1;

	return lcd_dt_simplefb_configure_node(blob, off);
}
#endif
