/*
 * USB armory MkI board initialization
 * http://inversepath.com/usbarmory
 *
 * Copyright (C) 2015, Inverse Path
 * Andrej Rosano <andrej@inversepath.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/io.h>
#include <asm/arch/imx-regs.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/crm_regs.h>
#include <asm/arch/clock.h>
#include <asm/arch/iomux-mx53.h>
#include <asm/errno.h>
#include <i2c.h>
#include <mmc.h>
#include <fsl_esdhc.h>
#include <asm/gpio.h>

DECLARE_GLOBAL_DATA_PTR;

u32 get_board_rev(void)
{
	struct iim_regs *iim = (struct iim_regs *)IMX_IIM_BASE;
	struct fuse_bank *bank = &iim->bank[0];
	struct fuse_bank0_regs *fuse =
		(struct fuse_bank0_regs *)bank->fuse_regs;

	int rev = readl(&fuse->gp[6]);

	return (get_cpu_rev() & ~(0xF << 8)) | (rev & 0xF) << 8;
}

struct fsl_esdhc_cfg esdhc_cfg[1] = {
	{MMC_SDHC1_BASE_ADDR}
};

int board_mmc_getcd(struct mmc *mmc)
{
	/* CD not present */
	return 1;
}

int board_mmc_init(bd_t *bis)
{
	int ret = 0;

	esdhc_cfg[0].sdhc_clk = mxc_get_clock(MXC_ESDHC_CLK);
	ret = fsl_esdhc_initialize(bis, &esdhc_cfg[0]);

	return ret;
}

#define SD_CMD_PAD_CTRL	(PAD_CTL_HYS | PAD_CTL_DSE_HIGH | \
			PAD_CTL_PUS_100K_UP)
#define I2C_PAD_CTRL	(PAD_CTL_SRE_FAST | PAD_CTL_DSE_HIGH | \
			PAD_CTL_PUS_100K_UP | PAD_CTL_ODE)
#define PAD_CTRL_UP	PAD_CTL_PUS_100K_UP
#define PAD_CTRL_GND	PAD_CTL_PUS_100K_DOWN

static void setup_iomux_sd(void)
{
	static const iomux_v3_cfg_t pads[] = {
		NEW_PAD_CTRL(MX53_PAD_SD1_CMD__ESDHC1_CMD, SD_CMD_PAD_CTRL),
		NEW_PAD_CTRL(MX53_PAD_SD1_CLK__ESDHC1_CLK, MX53_SDHC_PAD_CTRL),
		NEW_PAD_CTRL(MX53_PAD_SD1_DATA0__ESDHC1_DAT0,
			     MX53_SDHC_PAD_CTRL),
		NEW_PAD_CTRL(MX53_PAD_SD1_DATA1__ESDHC1_DAT1,
			     MX53_SDHC_PAD_CTRL),
		NEW_PAD_CTRL(MX53_PAD_SD1_DATA2__ESDHC1_DAT2,
			     MX53_SDHC_PAD_CTRL),
		NEW_PAD_CTRL(MX53_PAD_SD1_DATA3__ESDHC1_DAT3,
			     MX53_SDHC_PAD_CTRL),
		MX53_PAD_EIM_DA13__GPIO3_13,
	};

	imx_iomux_v3_setup_multiple_pads(pads, ARRAY_SIZE(pads));
}

static void setup_iomux_led(void)
{
	static const iomux_v3_cfg_t pads[] = {
		NEW_PAD_CTRL(MX53_PAD_DISP0_DAT6__GPIO4_27,
			     PAD_CTL_PUS_100K_DOWN),
	};

	imx_iomux_v3_setup_multiple_pads(pads, ARRAY_SIZE(pads));
}

static void setup_iomux_i2c(void)
{
	static const iomux_v3_cfg_t pads[] = {
		NEW_PAD_CTRL(MX53_PAD_EIM_D28__I2C1_SDA, I2C_PAD_CTRL),
		NEW_PAD_CTRL(MX53_PAD_EIM_D21__I2C1_SCL, I2C_PAD_CTRL),
	};

	imx_iomux_v3_setup_multiple_pads(pads, ARRAY_SIZE(pads));
}

static void setup_iomux_pinheader(void)
{
	static const iomux_v3_cfg_t pads[] = {
		NEW_PAD_CTRL(MX53_PAD_CSI0_DAT8__GPIO5_26, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_CSI0_DAT9__GPIO5_27, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_CSI0_DAT10__UART1_TXD_MUX,
			     MX53_UART_PAD_CTRL),
		NEW_PAD_CTRL(MX53_PAD_CSI0_DAT11__UART1_RXD_MUX,
			     MX53_UART_PAD_CTRL),
		NEW_PAD_CTRL(MX53_PAD_CSI0_DAT12__GPIO5_30, PAD_CTRL_UP),
	};

	imx_iomux_v3_setup_multiple_pads(pads, ARRAY_SIZE(pads));
}

static void setup_iomux_unused_boot(void)
{
	static const iomux_v3_cfg_t pads[] = {
		/* Pulled-up pads */
		NEW_PAD_CTRL(MX53_PAD_EIM_A21__GPIO2_17, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_EIM_DA0__GPIO3_0, PAD_CTRL_UP),

		/* Grounded pads */
		NEW_PAD_CTRL(MX53_PAD_EIM_LBA__GPIO2_27, PAD_CTRL_GND),
		NEW_PAD_CTRL(MX53_PAD_EIM_EB0__GPIO2_28, PAD_CTRL_GND),
		NEW_PAD_CTRL(MX53_PAD_EIM_EB1__GPIO2_29, PAD_CTRL_GND),
		NEW_PAD_CTRL(MX53_PAD_EIM_A16__GPIO2_22, PAD_CTRL_GND),
		NEW_PAD_CTRL(MX53_PAD_EIM_A17__GPIO2_21, PAD_CTRL_GND),
		NEW_PAD_CTRL(MX53_PAD_EIM_A18__GPIO2_20, PAD_CTRL_GND),
		NEW_PAD_CTRL(MX53_PAD_EIM_A19__GPIO2_19, PAD_CTRL_GND),
		NEW_PAD_CTRL(MX53_PAD_EIM_A20__GPIO2_18, PAD_CTRL_GND),
		NEW_PAD_CTRL(MX53_PAD_EIM_A22__GPIO2_16, PAD_CTRL_GND),
		NEW_PAD_CTRL(MX53_PAD_EIM_DA1__GPIO3_1, PAD_CTRL_GND),
		NEW_PAD_CTRL(MX53_PAD_EIM_DA2__GPIO3_2, PAD_CTRL_GND),
		NEW_PAD_CTRL(MX53_PAD_EIM_DA3__GPIO3_3, PAD_CTRL_GND),
		NEW_PAD_CTRL(MX53_PAD_EIM_DA4__GPIO3_4, PAD_CTRL_GND),
		NEW_PAD_CTRL(MX53_PAD_EIM_DA5__GPIO3_5, PAD_CTRL_GND),
		NEW_PAD_CTRL(MX53_PAD_EIM_DA6__GPIO3_6, PAD_CTRL_GND),
		NEW_PAD_CTRL(MX53_PAD_EIM_DA7__GPIO3_7, PAD_CTRL_GND),
		NEW_PAD_CTRL(MX53_PAD_EIM_DA8__GPIO3_8, PAD_CTRL_GND),
		NEW_PAD_CTRL(MX53_PAD_EIM_DA9__GPIO3_9, PAD_CTRL_GND),
		NEW_PAD_CTRL(MX53_PAD_EIM_DA10__GPIO3_10, PAD_CTRL_GND),
	};

	imx_iomux_v3_setup_multiple_pads(pads, ARRAY_SIZE(pads));
}

static void setup_iomux_unused_nc(void)
{
	/* Out of reset values define the pin values before the
	   ROM is executed so we force all the not connected pins
	   to a known state */
	static const iomux_v3_cfg_t pads[] = {
		/* CONTROL PINS block */
		NEW_PAD_CTRL(MX53_PAD_GPIO_0__GPIO1_0, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_GPIO_1__GPIO1_1, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_GPIO_2__GPIO1_2, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_GPIO_3__GPIO1_3, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_GPIO_4__GPIO1_4, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_GPIO_5__GPIO1_5, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_GPIO_6__GPIO1_6, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_GPIO_7__GPIO1_7, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_GPIO_8__GPIO1_8, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_GPIO_9__GPIO1_9, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_GPIO_10__GPIO4_0, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_GPIO_11__GPIO4_1, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_GPIO_12__GPIO4_2, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_GPIO_13__GPIO4_3, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_GPIO_14__GPIO4_4, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_GPIO_16__GPIO7_11, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_GPIO_17__GPIO7_12, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_GPIO_18__GPIO7_13, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_GPIO_19__GPIO4_5, PAD_CTRL_UP),

		/* EIM block */
		NEW_PAD_CTRL(MX53_PAD_EIM_OE__GPIO2_25, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_EIM_WAIT__GPIO5_0, PAD_CTRL_UP),
		/* EIM_LBA: setup_iomux_unused_boot() */
		NEW_PAD_CTRL(MX53_PAD_EIM_RW__GPIO2_26, PAD_CTRL_UP),
		/* EIM_EB0: setup_iomux_unused_boot() */
		/* EIM_EB1: setup_iomux_unused_boot() */
		NEW_PAD_CTRL(MX53_PAD_EIM_EB2__GPIO2_30, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_EIM_EB3__GPIO2_31, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_EIM_CS0__GPIO2_23, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_EIM_CS1__GPIO2_24, PAD_CTRL_UP),
		/* EIM_A16: setup_iomux_unused_boot() */
		/* EIM_A17: setup_iomux_unused_boot() */
		/* EIM_A18: setup_iomux_unused_boot() */
		/* EIM_A19: setup_iomux_unused_boot() */
		/* EIM_A20: setup_iomux_unused_boot() */
		/* EIM_A21: setup_iomux_unused_boot() */
		/* EIM_A22: setup_iomux_unused_boot() */
		NEW_PAD_CTRL(MX53_PAD_EIM_A23__GPIO6_6, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_EIM_A24__GPIO5_4, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_EIM_A25__GPIO5_2, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_EIM_D16__GPIO3_16, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_EIM_D17__GPIO3_17, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_EIM_D18__GPIO3_18, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_EIM_D19__GPIO3_19, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_EIM_D20__GPIO3_20, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_EIM_D21__GPIO3_21, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_EIM_D22__GPIO3_22, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_EIM_D23__GPIO3_23, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_EIM_D24__GPIO3_24, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_EIM_D25__GPIO3_25, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_EIM_D26__GPIO3_26, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_EIM_D27__GPIO3_27, PAD_CTRL_UP),
		/* EIM_D28: setup_iomux_unused_boot() */
		/* EIM_D29: setup_iomux_unused_boot() */
		NEW_PAD_CTRL(MX53_PAD_EIM_D30__GPIO3_30, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_EIM_D31__GPIO3_31, PAD_CTRL_UP),
		/* EIM_DA0: setup_iomux_unused_boot() */
		/* EIM_DA1: setup_iomux_unused_boot() */
		/* EIM_DA2: setup_iomux_unused_boot() */
		/* EIM_DA3: setup_iomux_unused_boot() */
		/* EIM_DA4: setup_iomux_unused_boot() */
		/* EIM_DA5: setup_iomux_unused_boot() */
		/* EIM_DA6: setup_iomux_unused_boot() */
		/* EIM_DA7: setup_iomux_unused_boot() */
		/* EIM_DA8: setup_iomux_unused_boot() */
		/* EIM_DA9: setup_iomux_unused_boot() */
		/* EIM_DA10: setup_iomux_unused_boot() */
		NEW_PAD_CTRL(MX53_PAD_EIM_DA11__GPIO3_11, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_EIM_DA12__GPIO3_12, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_EIM_DA13__GPIO3_13, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_EIM_DA14__GPIO3_14, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_EIM_DA15__GPIO3_15, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_NANDF_WE_B__GPIO6_12, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_NANDF_RE_B__GPIO6_13, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_NANDF_ALE__GPIO6_8, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_NANDF_CLE__GPIO6_7, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_NANDF_WP_B__GPIO6_9, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_NANDF_RB0__GPIO6_10, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_NANDF_CS0__GPIO6_11, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_NANDF_CS1__GPIO6_14, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_NANDF_CS2__GPIO6_15, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_NANDF_CS3__GPIO6_16, PAD_CTRL_UP),

		/* MISC block */
		NEW_PAD_CTRL(MX53_PAD_FEC_MDC__GPIO1_31, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_FEC_MDIO__GPIO1_22, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_FEC_CRS_DV__GPIO1_25, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_FEC_REF_CLK__GPIO1_23, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_FEC_RX_ER__GPIO1_24, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_FEC_TX_EN__GPIO1_28, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_FEC_RXD0__GPIO1_27, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_FEC_RXD1__GPIO1_26, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_FEC_TXD0__GPIO1_30, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_FEC_TXD1__GPIO1_29, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_KEY_COL0__GPIO4_6, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_KEY_ROW0__GPIO4_7, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_KEY_COL1__GPIO4_8, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_KEY_ROW1__GPIO4_9, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_KEY_COL2__GPIO4_10, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_KEY_ROW2__GPIO4_11, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_KEY_COL3__GPIO4_12, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_KEY_ROW3__GPIO4_13, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_KEY_COL4__GPIO4_14, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_KEY_ROW4__GPIO4_15, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_SD2_CMD__GPIO1_11, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_SD2_CLK__GPIO1_10, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_SD2_DATA0__GPIO1_15, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_SD2_DATA1__GPIO1_14, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_SD2_DATA2__GPIO1_13, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_SD2_DATA3__GPIO1_12, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_BUFFER_EN__GPIO7_1, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_CS_0__GPIO7_9, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_CS_1__GPIO7_10, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_DA_0__GPIO7_6, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_DA_1__GPIO7_7, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_DA_2__GPIO7_8, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_DATA0__GPIO2_0, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_DATA1__GPIO2_1, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_DATA2__GPIO2_2, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_DATA3__GPIO2_3, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_DATA4__GPIO2_4, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_DATA5__GPIO2_5, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_DATA6__GPIO2_6, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_DATA7__GPIO2_7, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_DATA8__GPIO2_8, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_DATA9__GPIO2_9, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_DATA10__GPIO2_10, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_DATA11__GPIO2_11, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_DATA12__GPIO2_12, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_DATA13__GPIO2_13, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_DATA14__GPIO2_14, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_DATA15__GPIO2_15, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_DIOR__GPIO7_3, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_DIOW__GPIO6_17, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_DMACK__GPIO6_18, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_DMARQ__GPIO7_0, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_INTRQ__GPIO7_2, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_IORDY__GPIO7_5, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_PATA_RESET_B__GPIO7_4, PAD_CTRL_UP),

		/* IPU block */
		NEW_PAD_CTRL(MX53_PAD_CSI0_DAT4__GPIO5_22, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_CSI0_DAT5__GPIO5_23, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_CSI0_DAT6__GPIO5_24, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_CSI0_DAT7__GPIO5_25, PAD_CTRL_UP),
		/* CSI0_DAT8: setup_iomux_pinheader() */
		/* CSI0_DAT9: setup_iomux_pinheader() */
		/* CSI0_DAT10: setup_iomux_pinheader() */
		/* CSI0_DAT11: setup_iomux_pinheader() */
		/* CSI0_DAT12: setup_iomux_pinheader() */
		NEW_PAD_CTRL(MX53_PAD_CSI0_DAT13__GPIO5_31, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_CSI0_DAT14__GPIO6_0, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_CSI0_DAT15__GPIO6_1, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_CSI0_DAT16__GPIO6_2, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_CSI0_DAT17__GPIO6_3, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_CSI0_DAT18__GPIO6_4, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_CSI0_DAT19__GPIO6_5, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_CSI0_VSYNC__GPIO5_21, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_CSI0_PIXCLK__GPIO5_18, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_CSI0_MCLK__GPIO5_19, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_CSI0_DATA_EN__GPIO5_20, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_DI0_PIN2__GPIO4_18, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_DI0_PIN3__GPIO4_19, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_DI0_PIN4__GPIO4_20, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_DI0_PIN15__GPIO4_17, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_DISP0_DAT0__GPIO4_21, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_DISP0_DAT1__GPIO4_22, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_DISP0_DAT2__GPIO4_23, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_DISP0_DAT3__GPIO4_24, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_DISP0_DAT4__GPIO4_25, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_DISP0_DAT5__GPIO4_26, PAD_CTRL_UP),
		/* DISP0_DAT6: setup_iomux_led() */
		NEW_PAD_CTRL(MX53_PAD_DISP0_DAT7__GPIO4_28, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_DISP0_DAT8__GPIO4_29, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_DISP0_DAT9__GPIO4_30, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_DISP0_DAT10__GPIO4_31, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_DISP0_DAT11__GPIO5_5, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_DISP0_DAT12__GPIO5_6, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_DISP0_DAT13__GPIO5_7, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_DISP0_DAT14__GPIO5_8, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_DISP0_DAT15__GPIO5_9, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_DISP0_DAT16__GPIO5_10, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_DISP0_DAT17__GPIO5_11, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_DISP0_DAT18__GPIO5_12, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_DISP0_DAT19__GPIO5_13, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_DISP0_DAT20__GPIO5_14, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_DISP0_DAT21__GPIO5_15, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_DISP0_DAT22__GPIO5_16, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_DISP0_DAT23__GPIO5_17, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_DI0_DISP_CLK__GPIO4_16, PAD_CTRL_UP),

		/* LVDS block */
		NEW_PAD_CTRL(MX53_PAD_LVDS0_TX0_P__GPIO7_30, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_LVDS0_TX1_P__GPIO7_28, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_LVDS0_TX2_P__GPIO7_26, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_LVDS0_TX3_P__GPIO7_22, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_LVDS1_TX0_P__GPIO6_30, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_LVDS1_TX1_P__GPIO6_28, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_LVDS1_TX2_P__GPIO6_24, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_LVDS1_TX3_P__GPIO6_22, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_LVDS0_CLK_P__GPIO7_24, PAD_CTRL_UP),
		NEW_PAD_CTRL(MX53_PAD_LVDS1_CLK_P__GPIO6_26, PAD_CTRL_UP),
	};

	imx_iomux_v3_setup_multiple_pads(pads, ARRAY_SIZE(pads));
}

#define CPU_CLOCK 800

static void set_clock(void)
{
	u32 ref_clk = MXC_HCLK;
	const uint32_t cpuclk = CPU_CLOCK;
	const uint32_t dramclk = 400;
	int ret;

	ret = mxc_set_clock(ref_clk, cpuclk, MXC_ARM_CLK);
	if (ret)
		printf("CPU:   Switch CPU clock to %dMHZ failed\n", cpuclk);

	ret = mxc_set_clock(ref_clk, dramclk, MXC_PERIPH_CLK);
	if (ret)
		printf("CPU:   Switch peripheral clock to %dMHz failed\n",
		       dramclk);

	ret = mxc_set_clock(ref_clk, dramclk, MXC_DDR_CLK);
	if (ret)
		printf("CPU:   Switch DDR clock to %dMHz failed\n", dramclk);
}

int board_early_init_f(void)
{
	setup_iomux_unused_nc();
	setup_iomux_unused_boot();
	setup_iomux_sd();
	setup_iomux_led();
	setup_iomux_pinheader();
	set_clock();
	return 0;
}

int board_init(void)
{
	gd->bd->bi_boot_params = PHYS_SDRAM + 0x100;
	setup_iomux_i2c();
	return 0;
}

int dram_init(void)
{
	gd->ram_size = get_ram_size((void *)CONFIG_SYS_SDRAM_BASE, 1 << 30);
	return 0;
}

int checkboard(void)
{
	puts("Board: Inverse Path USB armory MkI\n");
	return 0;
}

#ifndef CONFIG_CMDLINE
static char *ext2_argv[] = {
	"ext2load",
	"mmc",
	"0:1",
	USBARMORY_FIT_ADDR,
	USBARMORY_FIT_PATH
};

static char *bootm_argv[] = {
	"bootm",
	USBARMORY_FIT_ADDR
};

int board_run_command(const char *cmdline)
{
	printf("%s %s %s %s %s\n", ext2_argv[0], ext2_argv[1], ext2_argv[2],
	       ext2_argv[3], ext2_argv[4]);

	if (do_ext2load(NULL, 0, 5, ext2_argv) != 0) {
		udelay(5*1000*1000);
		return 1;
	}

	printf("%s %s\n", bootm_argv[0], bootm_argv[1]);
	do_bootm(NULL, 0, 2, bootm_argv);

	return 1;
}
#endif
