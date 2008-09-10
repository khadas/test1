/*
 * (C) Copyright 2005
 * Heiko Schocher, DENX Software Engineering, <hs@denx.de>
 *
 * (C) Copyright 2001
 * Kyle Harris, Nexus Technologies, Inc. kharris@nexus-tech.net
 *
 * (C) Copyright 2001-2005
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#undef DEBUG

#include <common.h>

flash_info_t flash_info[CFG_MAX_FLASH_BANKS];	/* info for FLASH chips    */

#if defined(CONFIG_ENV_IS_IN_FLASH)
# ifndef  CFG_ENV_ADDR
#  define CFG_ENV_ADDR	(CFG_FLASH_BASE + CFG_ENV_OFFSET)
# endif
# ifndef  CFG_ENV_SIZE
#  define CFG_ENV_SIZE	CFG_ENV_SECT_SIZE
# endif
# ifndef  CFG_ENV_SECT_SIZE
#  define CFG_ENV_SECT_SIZE  CFG_ENV_SIZE
# endif
#endif

/*-----------------------------------------------------------------------
 * Protection Flags:
 */
#define FLAG_PROTECT_SET	0x01
#define FLAG_PROTECT_CLEAR	0x02

/* Board support for 1 or 2 flash devices */
#undef FLASH_PORT_WIDTH32
#undef FLASH_PORT_WIDTH16
#define FLASH_PORT_WIDTH8

#ifdef FLASH_PORT_WIDTH16
#define FLASH_PORT_WIDTH	ushort
#define FLASH_PORT_WIDTHV	vu_short
#elif FLASH_PORT_WIDTH32
#define FLASH_PORT_WIDTH	ulong
#define FLASH_PORT_WIDTHV	vu_long
#else /* FLASH_PORT_WIDTH8 */
#define FLASH_PORT_WIDTH	uchar
#define FLASH_PORT_WIDTHV	vu_char
#endif

#define FPW			FLASH_PORT_WIDTH
#define FPWV			FLASH_PORT_WIDTHV

/*-----------------------------------------------------------------------
 * Functions
 */
static ulong flash_get_size (FPWV * addr, flash_info_t * info);
static int write_data (flash_info_t * info, ulong dest, FPW data);
static void flash_get_offsets (ulong base, flash_info_t * info);

/*-----------------------------------------------------------------------
 */

unsigned long flash_init (void)
{
	unsigned long size_b0;
	int i;
	volatile immap_t * immr = (immap_t *)CFG_IMMR;
	volatile memctl8260_t *memctl = &immr->im_memctl;

	/* Init: no FLASHes known */
	for (i = 0; i < CFG_MAX_FLASH_BANKS; ++i) {
		flash_info[i].flash_id = FLASH_UNKNOWN;
	}

	/* Static FLASH Bank configuration here - FIXME XXX */
	size_b0 = flash_get_size ((FPW *) CFG_FLASH0_BASE, &flash_info[0]);

	if (flash_info[0].flash_id == FLASH_UNKNOWN) {
		printf ("## Unknown FLASH on Bank 0 - Size = 0x%08lx = %ld MB\n",
			size_b0, size_b0 << 20);
	}

	memctl->memc_or0 = 0xff800060;
	memctl->memc_br0 = 0xff800801;

	flash_get_offsets (0xff800000, &flash_info[0]);

#if CFG_MONITOR_BASE >= CFG_FLASH_BASE
	/* monitor protection ON by default */
	(void) flash_protect (FLAG_PROTECT_SET,
				CFG_MONITOR_BASE,
				CFG_MONITOR_BASE + monitor_flash_len - 1,
				&flash_info[0]);
#endif

#ifdef	CONFIG_ENV_IS_IN_FLASH
	/* ENV protection ON by default */
	flash_protect (FLAG_PROTECT_SET,
			CFG_ENV_ADDR,
			CFG_ENV_ADDR + CFG_ENV_SIZE - 1,
			&flash_info[0]);
#endif

	flash_info[0].size = size_b0;

	return (size_b0);
}

/*-----------------------------------------------------------------------
 */
static void flash_get_offsets (ulong base, flash_info_t * info)
{
	int i;

	if (info->flash_id == FLASH_UNKNOWN) {
		return;
	}

	if ((info->flash_id & FLASH_VENDMASK) == FLASH_MAN_INTEL) {
		for (i = 0; i < info->sector_count; i++) {
			info->start[i] = base + (i * 0x00020000);
		}
	}
}

/*-----------------------------------------------------------------------
 */
void flash_print_info (flash_info_t * info)
{
	int i;

	if (info->flash_id == FLASH_UNKNOWN) {
		printf ("missing or unknown FLASH type\n");
		return;
	}

	switch (info->flash_id & FLASH_VENDMASK) {
	case FLASH_MAN_INTEL:
		printf ("INTEL ");
		break;
	default:
		printf ("Unknown Vendor ");
		break;
	}

	switch (info->flash_id & FLASH_TYPEMASK) {
	case FLASH_28F320J3A:
		printf ("28F320J3A\n");
		break;
	case FLASH_28F640J3A:
		printf ("28F640J3A\n");
		break;
	case FLASH_28F128J3A:
		printf ("28F128J3A\n");
		break;
	default:
		printf ("Unknown Chip Type\n");
		break;
	}

	printf ("  Size: %ld MB in %d Sectors\n",
			info->size >> 20, info->sector_count);

	printf ("  Sector Start Addresses:");
	for (i = 0; i < info->sector_count; ++i) {
		if ((i % 5) == 0)
			printf ("\n   ");
		printf (" %08lX%s",
			info->start[i],
			info->protect[i] ? " (RO)" : "     ");
	}
	printf ("\n");
	return;
}

/*-----------------------------------------------------------------------
 */


/*-----------------------------------------------------------------------
 */

/*
 * The following code cannot be run from FLASH!
 */

static ulong flash_get_size (FPWV * addr, flash_info_t * info)
{
	FPW value;

	addr[0] = (FPW) 0x00900090;

	value = addr[0];

	debug ("Manuf. ID @ 0x%08lx: 0x%08lx\n", (ulong)addr, value);

	switch (value) {
	case (FPW) INTEL_MANUFACT:
		info->flash_id = FLASH_MAN_INTEL;
		break;
	default:
		info->flash_id = FLASH_UNKNOWN;
		info->sector_count = 0;
		info->size = 0;
		addr[0] = (FPW) 0x00FF00FF;	/* restore read mode */
		return (0);			/* no or unknown flash  */
	}

#ifdef FLASH_PORT_WIDTH8
	value = addr[2];			/* device ID        */
#else
	value = addr[1];			/* device ID        */
#endif

	debug ("Device ID @ 0x%08lx: 0x%08lx\n", (ulong)(&addr[1]), value);

	switch (value) {
	case (FPW) INTEL_ID_28F320J3A:
		info->flash_id += FLASH_28F320J3A;
		info->sector_count = 32;
		info->size = 0x00400000;
		break;				/* => 4 MB     */

	case (FPW) INTEL_ID_28F640J3A:
		info->flash_id += FLASH_28F640J3A;
		info->sector_count = 64;
		info->size = 0x00800000;
		break;				/* => 8 MB     */

	case (FPW) INTEL_ID_28F128J3A:
		info->flash_id += FLASH_28F128J3A;
		info->sector_count = 128;
		info->size = 0x01000000;
		break;				/* => 16 MB     */

	default:
		info->flash_id = FLASH_UNKNOWN;
		break;
	}

	if (info->sector_count > CFG_MAX_FLASH_SECT) {
		printf ("** ERROR: sector count %d > max (%d) **\n",
				info->sector_count, CFG_MAX_FLASH_SECT);
		info->sector_count = CFG_MAX_FLASH_SECT;
	}

	addr[0] = (FPW) 0x00FF00FF;	/* restore read mode */

	return (info->size);
}


/*-----------------------------------------------------------------------
 */

int flash_erase (flash_info_t * info, int s_first, int s_last)
{
	int flag, prot, sect;
	ulong type, start, now, last;
	int rcode = 0;

	if ((s_first < 0) || (s_first > s_last)) {
		if (info->flash_id == FLASH_UNKNOWN) {
			printf ("- missing\n");
		} else {
			printf ("- no sectors to erase\n");
		}
		return 1;
	}

	type = (info->flash_id & FLASH_VENDMASK);
	if ((type != FLASH_MAN_INTEL)) {
		printf ("Can't erase unknown flash type %08lx - aborted\n",
			info->flash_id);
		return 1;
	}

	prot = 0;
	for (sect = s_first; sect <= s_last; ++sect) {
		if (info->protect[sect]) {
			prot++;
		}
	}

	if (prot) {
		printf ("- Warning: %d protected sectors will not be erased!\n",
			prot);
	} else {
		printf ("\n");
	}

	start = get_timer (0);
	last = start;
	/* Start erase on unprotected sectors */
	for (sect = s_first; sect <= s_last; sect++) {
		if (info->protect[sect] == 0) {	/* not protected */
			FPWV *addr = (FPWV *) (info->start[sect]);
			FPW status;

			/* Disable interrupts which might cause a timeout here */
			flag = disable_interrupts ();

			*addr = (FPW) 0x00500050;	/* clear status register */
			*addr = (FPW) 0x00200020;	/* erase setup */
			*addr = (FPW) 0x00D000D0;	/* erase confirm */

			/* re-enable interrupts if necessary */
			if (flag)
				enable_interrupts ();

			/* wait at least 80us - let's wait 1 ms */
			udelay (1000);

			while (((status = *addr) & (FPW) 0x00800080) != (FPW) 0x00800080) {
			    if ((now = get_timer (start)) > CFG_FLASH_ERASE_TOUT) {
				printf ("Timeout\n");
				*addr = (FPW) 0x00B000B0;	/* suspend erase     */
				*addr = (FPW) 0x00FF00FF;	/* reset to read mode */
				rcode = 1;
				break;
			    }

			    /* show that we're waiting */
			    if ((now - last) > 1000) {	/* every second */
				putc ('.');
				last = now;
			    }
			}

			*addr = (FPW) 0x00FF00FF;	/* reset to read mode */
		}
	}
	printf (" done\n");
	return rcode;
}

/*-----------------------------------------------------------------------
 * Copy memory to flash, returns:
 * 0 - OK
 * 1 - write timeout
 * 2 - Flash not erased
 * 4 - Flash not identified
 */

int write_buff (flash_info_t * info, uchar * src, ulong addr, ulong cnt)
{
	ulong cp, wp;
	FPW data;

	int i, l, rc, port_width;

	if (info->flash_id == FLASH_UNKNOWN) {
		return 4;
	}
/* get lower word aligned address */
#ifdef FLASH_PORT_WIDTH16
	wp = (addr & ~1);
	port_width = 2;
#elif defined(FLASH_PORT_WIDTH32)
	wp = (addr & ~3);
	port_width = 4;
#else
	wp = addr;
	port_width = 1;
#endif

	/*
	 * handle unaligned start bytes
	 */
	if ((l = addr - wp) != 0) {
		data = 0;
		for (i = 0, cp = wp; i < l; ++i, ++cp) {
			data = (data << 8) | (*(uchar *) cp);
		}
		for (; i < port_width && cnt > 0; ++i) {
			data = (data << 8) | *src++;
			--cnt;
			++cp;
		}
		for (; cnt == 0 && i < port_width; ++i, ++cp) {
			data = (data << 8) | (*(uchar *) cp);
		}

		if ((rc = write_data (info, wp, data)) != 0) {
			return (rc);
		}
		wp += port_width;
	}

	/*
	 * handle word aligned part
	 */
	while (cnt >= port_width) {
		data = 0;
		for (i = 0; i < port_width; ++i) {
			data = (data << 8) | *src++;
		}
		if ((rc = write_data (info, wp, data)) != 0) {
			return (rc);
		}
		wp += port_width;
		cnt -= port_width;
	}

	if (cnt == 0) {
		return (0);
	}

	/*
	 * handle unaligned tail bytes
	 */
	data = 0;
	for (i = 0, cp = wp; i < port_width && cnt > 0; ++i, ++cp) {
		data = (data << 8) | *src++;
		--cnt;
	}
	for (; i < port_width; ++i, ++cp) {
		data = (data << 8) | (*(uchar *) cp);
	}

	return (write_data (info, wp, data));
}

/*-----------------------------------------------------------------------
 * Write a word or halfword to Flash, returns:
 * 0 - OK
 * 1 - write timeout
 * 2 - Flash not erased
 */
static int write_data (flash_info_t * info, ulong dest, FPW data)
{
	FPWV *addr = (FPWV *) dest;
	ulong status;
	ulong start;
	int flag;

	/* Check if Flash is (sufficiently) erased */
	if ((*addr & data) != data) {
		printf ("not erased at %08lx (%x)\n", (ulong) addr, *addr);
		return (2);
	}
	/* Disable interrupts which might cause a timeout here */
	flag = disable_interrupts ();

	*addr = (FPW) 0x00400040;	/* write setup */
	*addr = data;

	/* re-enable interrupts if necessary */
	if (flag)
		enable_interrupts ();

	start = get_timer (0);

	while (((status = *addr) & (FPW) 0x00800080) != (FPW) 0x00800080) {
		if (get_timer (start) > CFG_FLASH_WRITE_TOUT) {
			*addr = (FPW) 0x00FF00FF;	/* restore read mode */
			return (1);
		}
	}

	*addr = (FPW) 0x00FF00FF;	/* restore read mode */

	return (0);
}
