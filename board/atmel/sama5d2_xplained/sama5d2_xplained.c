/*
 * Copyright (C) 2015 Atmel Corporation
 *		      Wenyou.Yang <wenyou.yang@atmel.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <atmel_hlcdc.h>
#include <lcd.h>
#include <mmc.h>
#include <net.h>
#include <netdev.h>
#include <spi.h>
#include <version.h>
#include <asm/io.h>
#include <asm/arch/at91_common.h>
#include <asm/arch/at91_pmc.h>
#include <asm/arch/atmel_pio4.h>
#include <asm/arch/atmel_mpddrc.h>
#include <asm/arch/atmel_usba_udc.h>
#include <asm/arch/atmel_sdhci.h>
#include <asm/arch/clk.h>
#include <asm/arch/gpio.h>
#include <asm/arch/sama5d2.h>

DECLARE_GLOBAL_DATA_PTR;

int spi_cs_is_valid(unsigned int bus, unsigned int cs)
{
	return bus == 0 && cs == 0;
}

void spi_cs_activate(struct spi_slave *slave)
{
	atmel_pio4_set_pio_output(AT91_PIO_PORTA, 17, 0);
}

void spi_cs_deactivate(struct spi_slave *slave)
{
	atmel_pio4_set_pio_output(AT91_PIO_PORTA, 17, 1);
}

static void board_spi0_hw_init(void)
{
	atmel_pio4_set_a_periph(AT91_PIO_PORTA, 14, 0);
	atmel_pio4_set_a_periph(AT91_PIO_PORTA, 15, 0);
	atmel_pio4_set_a_periph(AT91_PIO_PORTA, 16, 0);

	atmel_pio4_set_pio_output(AT91_PIO_PORTA, 17, 1);

	at91_periph_clk_enable(ATMEL_ID_SPI0);
}

static void board_usb_hw_init(void)
{
	atmel_pio4_set_pio_output(AT91_PIO_PORTB, 10, 1);
}

#ifdef CONFIG_LCD
vidinfo_t panel_info = {
	.vl_col = 480,
	.vl_row = 272,
	.vl_clk = 9000000,
	.vl_bpix = LCD_BPP,
	.vl_tft = 1,
	.vl_hsync_len = 41,
	.vl_left_margin = 2,
	.vl_right_margin = 2,
	.vl_vsync_len = 11,
	.vl_upper_margin = 2,
	.vl_lower_margin = 2,
	.mmio = ATMEL_BASE_LCDC,
};

/* No power up/down pin for the LCD pannel */
void lcd_enable(void)	{ /* Empty! */ }
void lcd_disable(void)	{ /* Empty! */ }

unsigned int has_lcdc(void)
{
	return 1;
}

static void board_lcd_hw_init(void)
{
	atmel_pio4_set_a_periph(AT91_PIO_PORTC, 28, 0);	/* LCDPWM */
	atmel_pio4_set_a_periph(AT91_PIO_PORTC, 29, 0);	/* LCDDISP */
	atmel_pio4_set_a_periph(AT91_PIO_PORTC, 30, 0);	/* LCDVSYNC */
	atmel_pio4_set_a_periph(AT91_PIO_PORTC, 31, 0);	/* LCDHSYNC */
	atmel_pio4_set_a_periph(AT91_PIO_PORTD,  0, 0);	/* LCDPCK */
	atmel_pio4_set_a_periph(AT91_PIO_PORTD,  1, 0);	/* LCDDEN */

	/* LCDDAT0 */
	/* LCDDAT1 */
	atmel_pio4_set_a_periph(AT91_PIO_PORTC, 10, 0);	/* LCDDAT2 */
	atmel_pio4_set_a_periph(AT91_PIO_PORTC, 11, 0);	/* LCDDAT3 */
	atmel_pio4_set_a_periph(AT91_PIO_PORTC, 12, 0);	/* LCDDAT4 */
	atmel_pio4_set_a_periph(AT91_PIO_PORTC, 13, 0);	/* LCDDAT5 */
	atmel_pio4_set_a_periph(AT91_PIO_PORTC, 14, 0);	/* LCDDAT6 */
	atmel_pio4_set_a_periph(AT91_PIO_PORTC, 15, 0);	/* LCDDAT7 */

	/* LCDDAT8 */
	/* LCDDAT9 */
	atmel_pio4_set_a_periph(AT91_PIO_PORTC, 16, 0);	/* LCDDAT10 */
	atmel_pio4_set_a_periph(AT91_PIO_PORTC, 17, 0);	/* LCDDAT11 */
	atmel_pio4_set_a_periph(AT91_PIO_PORTC, 18, 0);	/* LCDDAT12 */
	atmel_pio4_set_a_periph(AT91_PIO_PORTC, 19, 0);	/* LCDDAT13 */
	atmel_pio4_set_a_periph(AT91_PIO_PORTC, 20, 0);	/* LCDDAT14 */
	atmel_pio4_set_a_periph(AT91_PIO_PORTC, 21, 0);	/* LCDDAT15 */

	/* LCDD16 */
	/* LCDD17 */
	atmel_pio4_set_a_periph(AT91_PIO_PORTC, 22, 0);	/* LCDDAT18 */
	atmel_pio4_set_a_periph(AT91_PIO_PORTC, 23, 0);	/* LCDDAT19 */
	atmel_pio4_set_a_periph(AT91_PIO_PORTC, 24, 0);	/* LCDDAT20 */
	atmel_pio4_set_a_periph(AT91_PIO_PORTC, 25, 0);	/* LCDDAT21 */
	atmel_pio4_set_a_periph(AT91_PIO_PORTC, 26, 0);	/* LCDDAT22 */
	atmel_pio4_set_a_periph(AT91_PIO_PORTC, 27, 0);	/* LCDDAT23 */

	at91_periph_clk_enable(ATMEL_ID_LCDC);
}

#ifdef CONFIG_LCD_INFO
void lcd_show_board_info(void)
{
	ulong dram_size;
	int i;
	char temp[32];

	lcd_printf("%s\n", U_BOOT_VERSION);
	lcd_printf("2015 ATMEL Corp\n");
	lcd_printf("%s CPU at %s MHz\n", get_cpu_name(),
		   strmhz(temp, get_cpu_clk_rate()));

	dram_size = 0;
	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++)
		dram_size += gd->bd->bi_dram[i].size;

	lcd_printf("%ld MB SDRAM\n", dram_size >> 20);
}
#endif /* CONFIG_LCD_INFO */
#endif /* CONFIG_LCD */

static void board_gmac_hw_init(void)
{
	atmel_pio4_set_f_periph(AT91_PIO_PORTB, 14, 0);	/* GTXCK */
	atmel_pio4_set_f_periph(AT91_PIO_PORTB, 15, 0);	/* GTXEN */
	atmel_pio4_set_f_periph(AT91_PIO_PORTB, 16, 0);	/* GRXDV */
	atmel_pio4_set_f_periph(AT91_PIO_PORTB, 17, 0);	/* GRXER */
	atmel_pio4_set_f_periph(AT91_PIO_PORTB, 18, 0);	/* GRX0 */
	atmel_pio4_set_f_periph(AT91_PIO_PORTB, 19, 0);	/* GRX1 */
	atmel_pio4_set_f_periph(AT91_PIO_PORTB, 20, 0);	/* GTX0 */
	atmel_pio4_set_f_periph(AT91_PIO_PORTB, 21, 0);	/* GTX1 */
	atmel_pio4_set_f_periph(AT91_PIO_PORTB, 22, 0);	/* GMDC */
	atmel_pio4_set_f_periph(AT91_PIO_PORTB, 23, 0);	/* GMDIO */

	at91_periph_clk_enable(ATMEL_ID_GMAC);
}

static void board_sdhci0_hw_init(void)
{
	atmel_pio4_set_a_periph(AT91_PIO_PORTA, 0, 0);	/* SDMMC0_CK */
	atmel_pio4_set_a_periph(AT91_PIO_PORTA, 1, 0);	/* SDMMC0_CMD */
	atmel_pio4_set_a_periph(AT91_PIO_PORTA, 2, 0);	/* SDMMC0_DAT0 */
	atmel_pio4_set_a_periph(AT91_PIO_PORTA, 3, 0);	/* SDMMC0_DAT1 */
	atmel_pio4_set_a_periph(AT91_PIO_PORTA, 4, 0);	/* SDMMC0_DAT2 */
	atmel_pio4_set_a_periph(AT91_PIO_PORTA, 5, 0);	/* SDMMC0_DAT3 */
	atmel_pio4_set_a_periph(AT91_PIO_PORTA, 6, 0);	/* SDMMC0_DAT4 */
	atmel_pio4_set_a_periph(AT91_PIO_PORTA, 7, 0);	/* SDMMC0_DAT5 */
	atmel_pio4_set_a_periph(AT91_PIO_PORTA, 8, 0);	/* SDMMC0_DAT6 */
	atmel_pio4_set_a_periph(AT91_PIO_PORTA, 9, 0);	/* SDMMC0_DAT7 */
	atmel_pio4_set_a_periph(AT91_PIO_PORTA, 10, 0);	/* SDMMC0_RSTN */
	atmel_pio4_set_a_periph(AT91_PIO_PORTA, 11, 0);	/* SDMMC0_VDDSEL */

	at91_periph_clk_enable(ATMEL_ID_SDMMC0);
	at91_enable_periph_generated_clk(ATMEL_ID_SDMMC0,
					 GCK_CSS_PLLA_CLK, 1);
}

static void board_sdhci1_hw_init(void)
{
	atmel_pio4_set_e_periph(AT91_PIO_PORTA, 18, 0);	/* SDMMC1_DAT0 */
	atmel_pio4_set_e_periph(AT91_PIO_PORTA, 19, 0);	/* SDMMC1_DAT1 */
	atmel_pio4_set_e_periph(AT91_PIO_PORTA, 20, 0);	/* SDMMC1_DAT2 */
	atmel_pio4_set_e_periph(AT91_PIO_PORTA, 21, 0);	/* SDMMC1_DAT3 */
	atmel_pio4_set_e_periph(AT91_PIO_PORTA, 22, 0);	/* SDMMC1_CK */
	atmel_pio4_set_e_periph(AT91_PIO_PORTA, 27, 0);	/* SDMMC1_RSTN */
	atmel_pio4_set_e_periph(AT91_PIO_PORTA, 28, 0);	/* SDMMC1_CMD */
	atmel_pio4_set_e_periph(AT91_PIO_PORTA, 30, 0);	/* SDMMC1_CD */

	at91_periph_clk_enable(ATMEL_ID_SDMMC1);
	at91_enable_periph_generated_clk(ATMEL_ID_SDMMC1,
					 GCK_CSS_PLLA_CLK, 1);
}

int board_mmc_init(bd_t *bis)
{
#ifdef CONFIG_ATMEL_SDHCI0
	atmel_sdhci_init((void *)ATMEL_BASE_SDMMC0, ATMEL_ID_SDMMC0);
#endif
#ifdef CONFIG_ATMEL_SDHCI1
	atmel_sdhci_init((void *)ATMEL_BASE_SDMMC1, ATMEL_ID_SDMMC1);
#endif

	return 0;
}

static void board_uart1_hw_init(void)
{
	atmel_pio4_set_a_periph(AT91_PIO_PORTD, 2, 1);	/* URXD1 */
	atmel_pio4_set_a_periph(AT91_PIO_PORTD, 3, 0);	/* UTXD1 */

	at91_periph_clk_enable(ATMEL_ID_UART1);
}

int board_early_init_f(void)
{
	at91_periph_clk_enable(ATMEL_ID_PIOA);
	at91_periph_clk_enable(ATMEL_ID_PIOB);
	at91_periph_clk_enable(ATMEL_ID_PIOC);
	at91_periph_clk_enable(ATMEL_ID_PIOD);

	board_uart1_hw_init();

	return 0;
}

int board_init(void)
{
	/* address of boot parameters */
	gd->bd->bi_boot_params = CONFIG_SYS_SDRAM_BASE + 0x100;

#ifdef CONFIG_ATMEL_SPI
	board_spi0_hw_init();
#endif
#ifdef CONFIG_ATMEL_SDHCI
#ifdef CONFIG_ATMEL_SDHCI0
	board_sdhci0_hw_init();
#endif
#ifdef CONFIG_ATMEL_SDHCI1
	board_sdhci1_hw_init();
#endif
#endif
#ifdef CONFIG_MACB
	board_gmac_hw_init();
#endif
#ifdef CONFIG_LCD
	board_lcd_hw_init();
#endif
#ifdef CONFIG_CMD_USB
	board_usb_hw_init();
#endif
#ifdef CONFIG_USB_GADGET_ATMEL_USBA
	at91_udp_hw_init();
#endif

	return 0;
}

int dram_init(void)
{
	gd->ram_size = get_ram_size((void *)CONFIG_SYS_SDRAM_BASE,
				    CONFIG_SYS_SDRAM_SIZE);
	return 0;
}

int board_eth_init(bd_t *bis)
{
	int rc = 0;

#ifdef CONFIG_MACB
	rc = macb_eth_initialize(0, (void *)ATMEL_BASE_GMAC, 0x00);
#endif

#ifdef CONFIG_USB_GADGET_ATMEL_USBA
	usba_udc_probe(&pdata);
#ifdef CONFIG_USB_ETH_RNDIS
	usb_eth_initialize(bis);
#endif
#endif

	return rc;
}

/* SPL */
#ifdef CONFIG_SPL_BUILD
void spl_board_init(void)
{
#ifdef CONFIG_SYS_USE_SERIALFLASH
	board_spi0_hw_init();
#endif
#ifdef CONFIG_ATMEL_SDHCI
#ifdef CONFIG_ATMEL_SDHCI0
	board_sdhci0_hw_init();
#endif
#ifdef CONFIG_ATMEL_SDHCI1
	board_sdhci1_hw_init();
#endif
#endif
}

static void ddrc_conf(struct atmel_mpddrc_config *ddrc)
{
	ddrc->md = (ATMEL_MPDDRC_MD_DBW_32_BITS | ATMEL_MPDDRC_MD_DDR3_SDRAM);

	ddrc->cr = (ATMEL_MPDDRC_CR_NC_COL_10 |
		    ATMEL_MPDDRC_CR_NR_ROW_14 |
		    ATMEL_MPDDRC_CR_CAS_DDR_CAS5 |
		    ATMEL_MPDDRC_CR_DIC_DS |
		    ATMEL_MPDDRC_CR_DIS_DLL |
		    ATMEL_MPDDRC_CR_NB_8BANKS |
		    ATMEL_MPDDRC_CR_DECOD_INTERLEAVED |
		    ATMEL_MPDDRC_CR_UNAL_SUPPORTED);

	ddrc->rtr = 0x511;

	ddrc->tpr0 = (6 << ATMEL_MPDDRC_TPR0_TRAS_OFFSET |
		      3 << ATMEL_MPDDRC_TPR0_TRCD_OFFSET |
		      4 << ATMEL_MPDDRC_TPR0_TWR_OFFSET |
		      9 << ATMEL_MPDDRC_TPR0_TRC_OFFSET |
		      3 << ATMEL_MPDDRC_TPR0_TRP_OFFSET |
		      4 << ATMEL_MPDDRC_TPR0_TRRD_OFFSET |
		      4 << ATMEL_MPDDRC_TPR0_TWTR_OFFSET |
		      4 << ATMEL_MPDDRC_TPR0_TMRD_OFFSET);

	ddrc->tpr1 = (27 << ATMEL_MPDDRC_TPR1_TRFC_OFFSET |
		      29 << ATMEL_MPDDRC_TPR1_TXSNR_OFFSET |
		      0 << ATMEL_MPDDRC_TPR1_TXSRD_OFFSET |
		      3 << ATMEL_MPDDRC_TPR1_TXP_OFFSET);

	ddrc->tpr2 = (0 << ATMEL_MPDDRC_TPR2_TXARD_OFFSET |
		      0 << ATMEL_MPDDRC_TPR2_TXARDS_OFFSET |
		      0 << ATMEL_MPDDRC_TPR2_TRPA_OFFSET |
		      4 << ATMEL_MPDDRC_TPR2_TRTP_OFFSET |
		      7 << ATMEL_MPDDRC_TPR2_TFAW_OFFSET);
}

void mem_init(void)
{
	struct at91_pmc *pmc = (struct at91_pmc *)ATMEL_BASE_PMC;
	struct atmel_mpddr *mpddrc = (struct atmel_mpddr *)ATMEL_BASE_MPDDRC;
	struct atmel_mpddrc_config ddrc_config;
	u32 reg;

	ddrc_conf(&ddrc_config);

	at91_periph_clk_enable(ATMEL_ID_MPDDRC);
	writel(AT91_PMC_DDR, &pmc->scer);

	reg = readl(&mpddrc->io_calibr);
	reg &= ~ATMEL_MPDDRC_IO_CALIBR_RDIV;
	reg |= ATMEL_MPDDRC_IO_CALIBR_DDR3_RZQ_55;
	reg &= ~ATMEL_MPDDRC_IO_CALIBR_TZQIO;
	reg |= ATMEL_MPDDRC_IO_CALIBR_TZQIO_(100);
	writel(reg, &mpddrc->io_calibr);

	writel(ATMEL_MPDDRC_RD_DATA_PATH_SHIFT_TWO_CYCLE,
	       &mpddrc->rd_data_path);

	ddr3_init(ATMEL_BASE_MPDDRC, ATMEL_BASE_DDRCS, &ddrc_config);

	writel(0x3, &mpddrc->cal_mr4);
	writel(64, &mpddrc->tim_cal);
}

void at91_pmc_init(void)
{
	struct at91_pmc *pmc = (struct at91_pmc *)ATMEL_BASE_PMC;
	u32 tmp;

	tmp = AT91_PMC_PLLAR_29 |
	      AT91_PMC_PLLXR_PLLCOUNT(0x3f) |
	      AT91_PMC_PLLXR_MUL(82) |
	      AT91_PMC_PLLXR_DIV(1);
	at91_plla_init(tmp);

	writel(0x0 << 8, &pmc->pllicpr);

	tmp = AT91_PMC_MCKR_H32MXDIV |
	      AT91_PMC_MCKR_PLLADIV_2 |
	      AT91_PMC_MCKR_MDIV_3 |
	      AT91_PMC_MCKR_CSS_PLLA;
	at91_mck_init(tmp);
}
#endif
