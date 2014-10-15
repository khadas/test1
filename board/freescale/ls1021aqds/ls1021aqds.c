/*
 * Copyright 2014 Freescale Semiconductor, Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <i2c.h>
#include <asm/io.h>
#include <asm/arch/immap_ls102xa.h>
#include <asm/arch/clock.h>
#include <asm/arch/fsl_serdes.h>
#include <mmc.h>
#include <fsl_esdhc.h>
#include <fsl_ifc.h>
#include <fsl_sec.h>

#include "../common/qixis.h"
#include "ls1021aqds_qixis.h"

DECLARE_GLOBAL_DATA_PTR;

enum {
	MUX_TYPE_SD_PCI4,
	MUX_TYPE_SD_PC_SA_SG_SG,
	MUX_TYPE_SD_PC_SA_PC_SG,
	MUX_TYPE_SD_PC_SG_SG,
};

int checkboard(void)
{
	char buf[64];
	u8 sw;

	puts("Board: LS1021AQDS\n");

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

	printf("Sys ID:0x%02x, Sys Ver: 0x%02x\n",
	       QIXIS_READ(id), QIXIS_READ(arch));

	printf("FPGA:  v%d (%s), build %d\n",
	       (int)QIXIS_READ(scver), qixis_read_tag(buf),
	       (int)qixis_read_minor());

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

int dram_init(void)
{
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

int board_early_init_f(void)
{
	struct ccsr_scfg *scfg = (struct ccsr_scfg *)CONFIG_SYS_FSL_SCFG_ADDR;
	struct ccsr_cci400 *cci = (struct ccsr_cci400 *)CONFIG_SYS_CCI400_ADDR;

#ifdef CONFIG_TSEC_ENET
	out_be32(&scfg->scfgrevcr, SCFG_SCFGREVCR_REV);
	out_be32(&scfg->etsecdmamcr, SCFG_ETSECDMAMCR_LE_BD_FR);
	out_be32(&scfg->scfgrevcr, SCFG_SCFGREVCR_NOREV);
#endif

#ifdef CONFIG_FSL_IFC
	init_early_memctl_regs();
#endif

	/* Workaround for the issue that DDR could not respond to
	 * barrier transaction which is generated by executing DSB/ISB
	 * instruction. Set CCI-400 control override register to
	 * terminate the barrier transaction. After DDR is initialized,
	 * allow barrier transaction to DDR again */
	out_le32(&cci->ctrl_ord, CCI400_CTRLORD_TERM_BARRIER);

	return 0;
}

int config_board_mux(int ctrl_type)
{
	u8 reg12;

	reg12 = QIXIS_READ(brdcfg[12]);

	switch (ctrl_type) {
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

#if defined(CONFIG_MISC_INIT_R)
int misc_init_r(void)
{
#ifdef CONFIG_FSL_CAAM
	return sec_init();
#endif
}
#endif

int board_init(void)
{
	struct ccsr_cci400 *cci = (struct ccsr_cci400 *)CONFIG_SYS_CCI400_ADDR;

	/* Set CCI-400 control override register to
	 * enable barrier transaction */
	out_le32(&cci->ctrl_ord, CCI400_CTRLORD_EN_BARRIER);

	select_i2c_ch_pca9547(I2C_MUX_CH_DEFAULT);

#ifndef CONFIG_SYS_FSL_NO_SERDES
	fsl_serdes_init();
	config_serdes_mux();
#endif
	return 0;
}

void ft_board_setup(void *blob, bd_t *bd)
{
	ft_cpu_setup(blob, bd);
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
