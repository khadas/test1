/*
 * Copyright 2014 Freescale Semiconductor, Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <i2c.h>
#include <asm/io.h>
#include <asm/arch/immap_ls102xa.h>
#include <asm/arch/ns_access.h>
#include <asm/arch/clock.h>
#include <asm/arch/fsl_serdes.h>
#include <asm/arch/ls102xa_stream_id.h>
#include <hwconfig.h>
#include <mmc.h>
#include <fsl_esdhc.h>
#include <fsl_ifc.h>
#include <fsl_sec.h>
#include <spl.h>

#include "../common/sleep.h"
#include "../common/qixis.h"
#include "ls1021aqds_qixis.h"
#ifdef CONFIG_U_QE
#include "../../../drivers/qe/qe.h"
#endif

#define PIN_MUX_SEL_CAN		0x03
#define PIN_MUX_SEL_IIC2	0xa0
#define PIN_MUX_SEL_RGMII	0x00
#define PIN_MUX_SEL_SAI		0x0c
#define PIN_MUX_SEL_SDHC	0x00

#define SET_SDHC_MUX_SEL(reg, value)	((reg & 0x0f) | value)
#define SET_EC_MUX_SEL(reg, value)	((reg & 0xf0) | value)
DECLARE_GLOBAL_DATA_PTR;

enum {
	MUX_TYPE_CAN,
	MUX_TYPE_IIC2,
	MUX_TYPE_RGMII,
	MUX_TYPE_SAI,
	MUX_TYPE_SDHC,
	MUX_TYPE_SD_PCI4,
	MUX_TYPE_SD_PC_SA_SG_SG,
	MUX_TYPE_SD_PC_SA_PC_SG,
	MUX_TYPE_SD_PC_SG_SG,
};

enum {
	GE0_CLK125,
	GE2_CLK125,
	GE1_CLK125,
};

#ifdef CONFIG_LS102XA_NS_ACCESS
static struct csu_ns_dev ns_dev[] = {
	{ CSU_CSLX_PCIE2_IO, CSU_ALL_RW },
	{ CSU_CSLX_PCIE1_IO, CSU_ALL_RW },
	{ CSU_CSLX_MG2TPR_IP, CSU_ALL_RW },
	{ CSU_CSLX_IFC_MEM, CSU_ALL_RW },
	{ CSU_CSLX_OCRAM, CSU_ALL_RW },
	{ CSU_CSLX_GIC, CSU_ALL_RW },
	{ CSU_CSLX_PCIE1, CSU_ALL_RW },
	{ CSU_CSLX_OCRAM2, CSU_ALL_RW },
	{ CSU_CSLX_QSPI_MEM, CSU_ALL_RW },
	{ CSU_CSLX_PCIE2, CSU_ALL_RW },
	{ CSU_CSLX_SATA, CSU_ALL_RW },
	{ CSU_CSLX_USB3, CSU_ALL_RW },
	{ CSU_CSLX_SERDES, CSU_ALL_RW },
	{ CSU_CSLX_QDMA, CSU_ALL_RW },
	{ CSU_CSLX_LPUART2, CSU_ALL_RW },
	{ CSU_CSLX_LPUART1, CSU_ALL_RW },
	{ CSU_CSLX_LPUART4, CSU_ALL_RW },
	{ CSU_CSLX_LPUART3, CSU_ALL_RW },
	{ CSU_CSLX_LPUART6, CSU_ALL_RW },
	{ CSU_CSLX_LPUART5, CSU_ALL_RW },
	{ CSU_CSLX_DSPI2, CSU_ALL_RW },
	{ CSU_CSLX_DSPI1, CSU_ALL_RW },
	{ CSU_CSLX_QSPI, CSU_ALL_RW },
	{ CSU_CSLX_ESDHC, CSU_ALL_RW },
	{ CSU_CSLX_2D_ACE, CSU_ALL_RW },
	{ CSU_CSLX_IFC, CSU_ALL_RW },
	{ CSU_CSLX_I2C1, CSU_ALL_RW },
	{ CSU_CSLX_USB2, CSU_ALL_RW },
	{ CSU_CSLX_I2C3, CSU_ALL_RW },
	{ CSU_CSLX_I2C2, CSU_ALL_RW },
	{ CSU_CSLX_DUART2, CSU_ALL_RW },
	{ CSU_CSLX_DUART1, CSU_ALL_RW },
	{ CSU_CSLX_WDT2, CSU_ALL_RW },
	{ CSU_CSLX_WDT1, CSU_ALL_RW },
	{ CSU_CSLX_EDMA, CSU_ALL_RW },
	{ CSU_CSLX_SYS_CNT, CSU_ALL_RW },
	{ CSU_CSLX_DMA_MUX2, CSU_ALL_RW },
	{ CSU_CSLX_DMA_MUX1, CSU_ALL_RW },
	{ CSU_CSLX_DDR, CSU_ALL_RW },
	{ CSU_CSLX_QUICC, CSU_ALL_RW },
	{ CSU_CSLX_DCFG_CCU_RCPM, CSU_ALL_RW },
	{ CSU_CSLX_SECURE_BOOTROM, CSU_ALL_RW },
	{ CSU_CSLX_SFP, CSU_ALL_RW },
	{ CSU_CSLX_TMU, CSU_ALL_RW },
	{ CSU_CSLX_SECURE_MONITOR, CSU_ALL_RW },
	{ CSU_CSLX_RESERVED0, CSU_ALL_RW },
	{ CSU_CSLX_ETSEC1, CSU_ALL_RW },
	{ CSU_CSLX_SEC5_5, CSU_ALL_RW },
	{ CSU_CSLX_ETSEC3, CSU_ALL_RW },
	{ CSU_CSLX_ETSEC2, CSU_ALL_RW },
	{ CSU_CSLX_GPIO2, CSU_ALL_RW },
	{ CSU_CSLX_GPIO1, CSU_ALL_RW },
	{ CSU_CSLX_GPIO4, CSU_ALL_RW },
	{ CSU_CSLX_GPIO3, CSU_ALL_RW },
	{ CSU_CSLX_PLATFORM_CONT, CSU_ALL_RW },
	{ CSU_CSLX_CSU, CSU_ALL_RW },
	{ CSU_CSLX_ASRC, CSU_ALL_RW },
	{ CSU_CSLX_SPDIF, CSU_ALL_RW },
	{ CSU_CSLX_FLEXCAN2, CSU_ALL_RW },
	{ CSU_CSLX_FLEXCAN1, CSU_ALL_RW },
	{ CSU_CSLX_FLEXCAN4, CSU_ALL_RW },
	{ CSU_CSLX_FLEXCAN3, CSU_ALL_RW },
	{ CSU_CSLX_SAI2, CSU_ALL_RW },
	{ CSU_CSLX_SAI1, CSU_ALL_RW },
	{ CSU_CSLX_SAI4, CSU_ALL_RW },
	{ CSU_CSLX_SAI3, CSU_ALL_RW },
	{ CSU_CSLX_FTM2, CSU_ALL_RW },
	{ CSU_CSLX_FTM1, CSU_ALL_RW },
	{ CSU_CSLX_FTM4, CSU_ALL_RW },
	{ CSU_CSLX_FTM3, CSU_ALL_RW },
	{ CSU_CSLX_FTM6, CSU_ALL_RW },
	{ CSU_CSLX_FTM5, CSU_ALL_RW },
	{ CSU_CSLX_FTM8, CSU_ALL_RW },
	{ CSU_CSLX_FTM7, CSU_ALL_RW },
	{ CSU_CSLX_COP_DCSR, CSU_ALL_RW },
	{ CSU_CSLX_EPU, CSU_ALL_RW },
	{ CSU_CSLX_GDI, CSU_ALL_RW },
	{ CSU_CSLX_DDI, CSU_ALL_RW },
	{ CSU_CSLX_RESERVED1, CSU_ALL_RW },
	{ CSU_CSLX_USB3_PHY, CSU_ALL_RW },
	{ CSU_CSLX_RESERVED2, CSU_ALL_RW },
};
#endif

int checkboard(void)
{
#ifndef CONFIG_QSPI_BOOT
	char buf[64];
#endif
#if !defined(CONFIG_SD_BOOT) && !defined(CONFIG_QSPI_BOOT)
	u8 sw;
#endif

	puts("Board: LS1021AQDS\n");

#ifdef CONFIG_SD_BOOT
	puts("SD\n");
#elif CONFIG_QSPI_BOOT
	puts("QSPI\n");
#else
	sw = QIXIS_READ(brdcfg[0]);
	sw = (sw & QIXIS_LBMAP_MASK) >> QIXIS_LBMAP_SHIFT;

	if (sw < 0x8)
		printf("vBank: %d\n", sw);
	else if (sw == 0x8)
		puts("PromJet\n");
	else if (sw == 0x9)
		puts("NAND\n");
	else if (sw == 0x15)
		printf("IFCCard\n");
	else
		printf("invalid setting of SW%u\n", QIXIS_LBMAP_SWITCH);
#endif

#ifndef CONFIG_QSPI_BOOT
	printf("Sys ID:0x%02x, Sys Ver: 0x%02x\n",
	       QIXIS_READ(id), QIXIS_READ(arch));

	printf("FPGA:  v%d (%s), build %d\n",
	       (int)QIXIS_READ(scver), qixis_read_tag(buf),
	       (int)qixis_read_minor());
#endif

	return 0;
}

unsigned long get_board_sys_clk(void)
{
	u8 sysclk_conf = QIXIS_READ(brdcfg[1]);

	switch (sysclk_conf & 0x0f) {
	case QIXIS_SYSCLK_64:
		return 64000000;
	case QIXIS_SYSCLK_83:
		return 83333333;
	case QIXIS_SYSCLK_100:
		return 100000000;
	case QIXIS_SYSCLK_125:
		return 125000000;
	case QIXIS_SYSCLK_133:
		return 133333333;
	case QIXIS_SYSCLK_150:
		return 150000000;
	case QIXIS_SYSCLK_160:
		return 160000000;
	case QIXIS_SYSCLK_166:
		return 166666666;
	}
	return 66666666;
}

unsigned long get_board_ddr_clk(void)
{
	u8 ddrclk_conf = QIXIS_READ(brdcfg[1]);

	switch ((ddrclk_conf & 0x30) >> 4) {
	case QIXIS_DDRCLK_100:
		return 100000000;
	case QIXIS_DDRCLK_125:
		return 125000000;
	case QIXIS_DDRCLK_133:
		return 133333333;
	}
	return 66666666;
}

unsigned int get_soc_major_rev(void)
{
	struct ccsr_gur __iomem *gur = (void *)(CONFIG_SYS_FSL_GUTS_ADDR);
	unsigned int svr, major;

	svr = in_be32(&gur->svr);
	major = SVR_MAJ(svr);

	return major;
}

int select_i2c_ch_pca9547(u8 ch)
{
	int ret;

	ret = i2c_write(I2C_MUX_PCA_ADDR_PRI, 0, 1, &ch, 1);
	if (ret) {
		puts("PCA: failed to select proper channel\n");
		return ret;
	}

	return 0;
}

int dram_init(void)
{
	/*
	 * When resuming from deep sleep, the I2C channel may not be
	 * in the default channel. So, switch to the default channel
	 * before accessing DDR SPD.
	 */
	select_i2c_ch_pca9547(I2C_MUX_CH_DEFAULT);
	gd->ram_size = initdram(0);

	return 0;
}

#ifdef CONFIG_FSL_ESDHC
struct fsl_esdhc_cfg esdhc_cfg[1] = {
	{CONFIG_SYS_FSL_ESDHC_ADDR},
};

int board_mmc_init(bd_t *bis)
{
	esdhc_cfg[0].sdhc_clk = mxc_get_clock(MXC_ESDHC_CLK);

	return fsl_esdhc_initialize(bis, &esdhc_cfg[0]);
}
#endif

int board_early_init_f(void)
{
	struct ccsr_scfg *scfg = (struct ccsr_scfg *)CONFIG_SYS_FSL_SCFG_ADDR;
	struct ccsr_cci400 *cci = (struct ccsr_cci400 *)CONFIG_SYS_CCI400_ADDR;
	unsigned int major;

#ifdef CONFIG_TSEC_ENET
	/* clear BD & FR bits for BE BD's and frame data */
	clrbits_be32(&scfg->etsecdmamcr, SCFG_ETSECDMAMCR_LE_BD_FR);
#endif

#ifdef CONFIG_FSL_IFC
	init_early_memctl_regs();
#endif

#ifdef CONFIG_FSL_QSPI
	out_be32(&scfg->qspi_cfg, SCFG_QSPI_CLKSEL);
#endif

#ifdef CONFIG_FSL_DCU_FB
	out_be32(&scfg->pixclkcr, SCFG_PIXCLKCR_PXCKEN);
#endif

	/* Configure Little endian for SAI, ASRC and SPDIF */
	out_be32(&scfg->endiancr, SCFG_ENDIANCR_LE);

	/*
	 * Enable snoop requests and DVM message requests for
	 * Slave insterface S4 (A7 core cluster)
	 */
	out_le32(&cci->slave[4].snoop_ctrl,
		 CCI400_DVM_MESSAGE_REQ_EN | CCI400_SNOOP_REQ_EN);

	major = get_soc_major_rev();
	if (major == SOC_MAJOR_VER_1_0) {
		/*
		 * Set CCI-400 Slave interface S1, S2 Shareable Override
		 * Register All transactions are treated as non-shareable
		 */
		out_le32(&cci->slave[1].sha_ord, CCI400_SHAORD_NON_SHAREABLE);
		out_le32(&cci->slave[2].sha_ord, CCI400_SHAORD_NON_SHAREABLE);

		/* Workaround for the issue that DDR could not respond to
		 * barrier transaction which is generated by executing DSB/ISB
		 * instruction. Set CCI-400 control override register to
		 * terminate the barrier transaction. After DDR is initialized,
		 * allow barrier transaction to DDR again */
		out_le32(&cci->ctrl_ord, CCI400_CTRLORD_TERM_BARRIER);
	}

#if defined(CONFIG_DEEP_SLEEP)
	if (is_warm_boot())
		fsl_dp_disable_console();
#endif

	return 0;
}

#ifdef CONFIG_SPL_BUILD
void board_init_f(ulong dummy)
{
	struct ccsr_cci400 *cci = (struct ccsr_cci400 *)CONFIG_SYS_CCI400_ADDR;
	unsigned int major;

#ifdef CONFIG_NAND_BOOT
	struct ccsr_gur __iomem *gur = (void *)CONFIG_SYS_FSL_GUTS_ADDR;
	u32 porsr1, pinctl;

	/*
	 * There is LS1 SoC issue where NOR, FPGA are inaccessible during
	 * NAND boot because IFC signals > IFC_AD7 are not enabled.
	 * This workaround changes RCW source to make all signals enabled.
	 */
	porsr1 = in_be32(&gur->porsr1);
	pinctl = ((porsr1 & ~(DCFG_CCSR_PORSR1_RCW_MASK)) |
		 DCFG_CCSR_PORSR1_RCW_SRC_I2C);
	out_be32((unsigned int *)(CONFIG_SYS_DCSR_DCFG_ADDR + DCFG_DCSR_PORCR1),
		 pinctl);
#endif

	/* Clear the BSS */
	memset(__bss_start, 0, __bss_end - __bss_start);

#ifdef CONFIG_FSL_IFC
	init_early_memctl_regs();
#endif

	get_clocks();

#if defined(CONFIG_DEEP_SLEEP)
	if (is_warm_boot())
		fsl_dp_disable_console();
#endif

	preloader_console_init();

#ifdef CONFIG_SPL_I2C_SUPPORT
	i2c_init_all();
#endif

	major = get_soc_major_rev();
	if (major == SOC_MAJOR_VER_1_0)
		out_le32(&cci->ctrl_ord, CCI400_CTRLORD_TERM_BARRIER);

	dram_init();

	/* Allow OCRAM access permission as R/W */
#ifdef CONFIG_LS102XA_NS_ACCESS
	enable_devices_ns_access(&ns_dev[4], 1);
	enable_devices_ns_access(&ns_dev[7], 1);
#endif

	board_init_r(NULL, 0);
}
#endif

void config_etseccm_source(int etsec_gtx_125_mux)
{
	struct ccsr_scfg *scfg = (struct ccsr_scfg *)CONFIG_SYS_FSL_SCFG_ADDR;

	switch (etsec_gtx_125_mux) {
	case GE0_CLK125:
		out_be32(&scfg->etsecmcr, SCFG_ETSECCMCR_GE0_CLK125);
		debug("etseccm set to GE0_CLK125\n");
		break;

	case GE2_CLK125:
		out_be32(&scfg->etsecmcr, SCFG_ETSECCMCR_GE2_CLK125);
		debug("etseccm set to GE2_CLK125\n");
		break;

	case GE1_CLK125:
		out_be32(&scfg->etsecmcr, SCFG_ETSECCMCR_GE1_CLK125);
		debug("etseccm set to GE1_CLK125\n");
		break;

	default:
		printf("Error! trying to set etseccm to invalid value\n");
		break;
	}
}

int config_board_mux(int ctrl_type)
{
	u8 reg12, reg14;

	reg12 = QIXIS_READ(brdcfg[12]);
	reg14 = QIXIS_READ(brdcfg[14]);

	switch (ctrl_type) {
	case MUX_TYPE_CAN:
		config_etseccm_source(GE2_CLK125);
		reg14 = SET_EC_MUX_SEL(reg14, PIN_MUX_SEL_CAN);
		break;
	case MUX_TYPE_IIC2:
		reg14 = SET_SDHC_MUX_SEL(reg14, PIN_MUX_SEL_IIC2);
		break;
	case MUX_TYPE_RGMII:
		reg14 = SET_EC_MUX_SEL(reg14, PIN_MUX_SEL_RGMII);
		break;
	case MUX_TYPE_SAI:
		config_etseccm_source(GE2_CLK125);
		reg14 = SET_EC_MUX_SEL(reg14, PIN_MUX_SEL_SAI);
		break;
	case MUX_TYPE_SDHC:
		reg14 = SET_SDHC_MUX_SEL(reg14, PIN_MUX_SEL_SDHC);
		break;
	case MUX_TYPE_SD_PCI4:
		reg12 = 0x38;
		break;
	case MUX_TYPE_SD_PC_SA_SG_SG:
		reg12 = 0x01;
		break;
	case MUX_TYPE_SD_PC_SA_PC_SG:
		reg12 = 0x01;
		break;
	case MUX_TYPE_SD_PC_SG_SG:
		reg12 = 0x21;
		break;
	default:
		printf("Wrong mux interface type\n");
		return -1;
	}

	QIXIS_WRITE(brdcfg[12], reg12);
	QIXIS_WRITE(brdcfg[14], reg14);

	return 0;
}

int config_serdes_mux(void)
{
	struct ccsr_gur *gur = (struct ccsr_gur *)CONFIG_SYS_FSL_GUTS_ADDR;
	u32 cfg;

	cfg = in_be32(&gur->rcwsr[4]) & RCWSR4_SRDS1_PRTCL_MASK;
	cfg >>= RCWSR4_SRDS1_PRTCL_SHIFT;

	switch (cfg) {
	case 0x0:
		config_board_mux(MUX_TYPE_SD_PCI4);
		break;
	case 0x30:
		config_board_mux(MUX_TYPE_SD_PC_SA_SG_SG);
		break;
	case 0x60:
		config_board_mux(MUX_TYPE_SD_PC_SG_SG);
		break;
	case 0x70:
		config_board_mux(MUX_TYPE_SD_PC_SA_PC_SG);
		break;
	default:
		printf("SRDS1 prtcl:0x%x\n", cfg);
		break;
	}

	return 0;
}

int misc_init_r(void)
{
	int conflict_flag;

	/* some signals can not enable simultaneous*/
	conflict_flag = 0;
	if (hwconfig("sdhc"))
		conflict_flag++;
	if (hwconfig("iic2"))
		conflict_flag++;
	if (conflict_flag > 1) {
		printf("WARNING: pin conflict !\n");
		return 0;
	}

	conflict_flag = 0;
	if (hwconfig("rgmii"))
		conflict_flag++;
	if (hwconfig("can"))
		conflict_flag++;
	if (hwconfig("sai"))
		conflict_flag++;
	if (conflict_flag > 1) {
		printf("WARNING: pin conflict !\n");
		return 0;
	}

	if (hwconfig("can"))
		config_board_mux(MUX_TYPE_CAN);
	else if (hwconfig("rgmii"))
		config_board_mux(MUX_TYPE_RGMII);
	else if (hwconfig("sai"))
		config_board_mux(MUX_TYPE_SAI);

	if (hwconfig("iic2"))
		config_board_mux(MUX_TYPE_IIC2);
	else if (hwconfig("sdhc"))
		config_board_mux(MUX_TYPE_SDHC);

#ifdef CONFIG_FSL_CAAM
	return sec_init();
#endif
	return 0;
}

struct liodn_id_table sec_liodn_tbl[] = {
	SET_SEC_JR_LIODN_ENTRY(0, 0x10, 0x10),
	SET_SEC_JR_LIODN_ENTRY(1, 0x10, 0x10),
	SET_SEC_JR_LIODN_ENTRY(2, 0x10, 0x10),
	SET_SEC_JR_LIODN_ENTRY(3, 0x10, 0x10),
	SET_SEC_RTIC_LIODN_ENTRY(a, 0x10),
	SET_SEC_RTIC_LIODN_ENTRY(b, 0x10),
	SET_SEC_RTIC_LIODN_ENTRY(c, 0x10),
	SET_SEC_RTIC_LIODN_ENTRY(d, 0x10),
	SET_SEC_DECO_LIODN_ENTRY(0, 0x10, 0x10),
	SET_SEC_DECO_LIODN_ENTRY(1, 0x10, 0x10),
	SET_SEC_DECO_LIODN_ENTRY(2, 0x10, 0x10),
	SET_SEC_DECO_LIODN_ENTRY(3, 0x10, 0x10),
	SET_SEC_DECO_LIODN_ENTRY(4, 0x10, 0x10),
	SET_SEC_DECO_LIODN_ENTRY(5, 0x10, 0x10),
	SET_SEC_DECO_LIODN_ENTRY(6, 0x10, 0x10),
	SET_SEC_DECO_LIODN_ENTRY(7, 0x10, 0x10),
};

struct smmu_stream_id dev_stream_id[] = {
	{ 0x100, 0x01, "ETSEC MAC1" },
	{ 0x104, 0x02, "ETSEC MAC2" },
	{ 0x108, 0x03, "ETSEC MAC3" },
	{ 0x10c, 0x04, "PEX1" },
	{ 0x110, 0x05, "PEX2" },
	{ 0x114, 0x06, "qDMA" },
	{ 0x118, 0x07, "SATA" },
	{ 0x11c, 0x08, "USB3" },
	{ 0x120, 0x09, "QE" },
	{ 0x124, 0x0a, "eSDHC" },
	{ 0x128, 0x0b, "eMA" },
	{ 0x14c, 0x0c, "2D-ACE" },
	{ 0x150, 0x0d, "USB2" },
	{ 0x18c, 0x0e, "DEBUG" },
};

int board_init(void)
{
	struct ccsr_cci400 *cci = (struct ccsr_cci400 *)CONFIG_SYS_CCI400_ADDR;
	unsigned int major;

	major = get_soc_major_rev();
	if (major == SOC_MAJOR_VER_1_0) {
		/* Set CCI-400 control override register to
		 * enable barrier transaction */
		out_le32(&cci->ctrl_ord, CCI400_CTRLORD_EN_BARRIER);
	}

	select_i2c_ch_pca9547(I2C_MUX_CH_DEFAULT);

#ifndef CONFIG_SYS_FSL_NO_SERDES
	fsl_serdes_init();
	config_serdes_mux();
#endif

	ls1021x_config_caam_stream_id(sec_liodn_tbl,
				      ARRAY_SIZE(sec_liodn_tbl));
	ls102xa_config_smmu_stream_id(dev_stream_id,
				      ARRAY_SIZE(dev_stream_id));

#ifdef CONFIG_LS102XA_NS_ACCESS
	enable_devices_ns_access(ns_dev, ARRAY_SIZE(ns_dev));
#endif

#ifdef CONFIG_U_QE
	u_qe_init();
#endif

	return 0;
}

#if defined(CONFIG_DEEP_SLEEP)
void board_sleep_prepare(void)
{
	struct ccsr_cci400 __iomem *cci = (void *)CONFIG_SYS_CCI400_ADDR;
	unsigned int major;

	major = get_soc_major_rev();
	if (major == SOC_MAJOR_VER_1_0) {
		/* Set CCI-400 control override register to
		 * enable barrier transaction */
		out_le32(&cci->ctrl_ord, CCI400_CTRLORD_EN_BARRIER);
	}


#ifdef CONFIG_LS102XA_NS_ACCESS
	enable_devices_ns_access(ns_dev, ARRAY_SIZE(ns_dev));
#endif
}
#endif

int ft_board_setup(void *blob, bd_t *bd)
{
	ft_cpu_setup(blob, bd);

#ifdef CONFIG_PCI
	ft_pci_setup(blob, bd);
#endif

	return 0;
}

u8 flash_read8(void *addr)
{
	return __raw_readb(addr + 1);
}

void flash_write16(u16 val, void *addr)
{
	u16 shftval = (((val >> 8) & 0xff) | ((val << 8) & 0xff00));

	__raw_writew(shftval, addr);
}

u16 flash_read16(void *addr)
{
	u16 val = __raw_readw(addr);

	return (((val) >> 8) & 0x00ff) | (((val) << 8) & 0xff00);
}
