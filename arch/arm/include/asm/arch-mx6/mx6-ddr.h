/*
 * Copyright (C) 2013 Boundary Devices Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef __ASM_ARCH_MX6_DDR_H__
#define __ASM_ARCH_MX6_DDR_H__

#ifndef CONFIG_SPL_BUILD
#ifdef CONFIG_MX6Q
#include "mx6q-ddr.h"
#else
#if defined(CONFIG_MX6DL) || defined(CONFIG_MX6S)
#include "mx6dl-ddr.h"
#else
#error "Please select cpu"
#endif	/* CONFIG_MX6DL or CONFIG_MX6S */
#endif	/* CONFIG_MX6Q */
#else

/* MMDC P0/P1 Registers */
struct mmdc_p_regs {
	u32 mdctl;
	u32 mdpdc;
	u32 mdotc;
	u32 mdcfg0;
	u32 mdcfg1;
	u32 mdcfg2;
	u32 mdmisc;
	u32 mdscr;
	u32 mdref;
	u32 res1[2];
	u32 mdrwd;
	u32 mdor;
	u32 res2[3];
	u32 mdasp;
	u32 res3[240];
	u32 mapsr;
	u32 res4[254];
	u32 mpzqhwctrl;
	u32 res5[2];
	u32 mpwldectrl0;
	u32 mpwldectrl1;
	u32 res6;
	u32 mpodtctrl;
	u32 mprddqby0dl;
	u32 mprddqby1dl;
	u32 mprddqby2dl;
	u32 mprddqby3dl;
	u32 res7[4];
	u32 mpdgctrl0;
	u32 mpdgctrl1;
	u32 res8;
	u32 mprddlctl;
	u32 res9;
	u32 mpwrdlctl;
	u32 res10[25];
	u32 mpmur0;
};

/*
 * MMDC iomux registers (pinctl/padctl) - (different for IMX6DQ vs IMX6SDL)
 */
#define MX6DQ_IOM_DDR_BASE      0x020e0500
struct mx6dq_iomux_ddr_regs {
	u32 res1[3];
	u32 dram_sdqs5;
	u32 dram_dqm5;
	u32 dram_dqm4;
	u32 dram_sdqs4;
	u32 dram_sdqs3;
	u32 dram_dqm3;
	u32 dram_sdqs2;
	u32 dram_dqm2;
	u32 res2[16];
	u32 dram_cas;
	u32 res3[2];
	u32 dram_ras;
	u32 dram_reset;
	u32 res4[2];
	u32 dram_sdclk_0;
	u32 dram_sdba2;
	u32 dram_sdcke0;
	u32 dram_sdclk_1;
	u32 dram_sdcke1;
	u32 dram_sdodt0;
	u32 dram_sdodt1;
	u32 res5;
	u32 dram_sdqs0;
	u32 dram_dqm0;
	u32 dram_sdqs1;
	u32 dram_dqm1;
	u32 dram_sdqs6;
	u32 dram_dqm6;
	u32 dram_sdqs7;
	u32 dram_dqm7;
};

#define MX6DQ_IOM_GRP_BASE      0x020e0700
struct mx6dq_iomux_grp_regs {
	u32 res1[18];
	u32 grp_b7ds;
	u32 grp_addds;
	u32 grp_ddrmode_ctl;
	u32 res2;
	u32 grp_ddrpke;
	u32 res3[6];
	u32 grp_ddrmode;
	u32 res4[3];
	u32 grp_b0ds;
	u32 grp_b1ds;
	u32 grp_ctlds;
	u32 res5;
	u32 grp_b2ds;
	u32 grp_ddr_type;
	u32 grp_b3ds;
	u32 grp_b4ds;
	u32 grp_b5ds;
	u32 grp_b6ds;
};

#define MX6SDL_IOM_DDR_BASE     0x020e0400
struct mx6sdl_iomux_ddr_regs {
	u32 res1[25];
	u32 dram_cas;
	u32 res2[2];
	u32 dram_dqm0;
	u32 dram_dqm1;
	u32 dram_dqm2;
	u32 dram_dqm3;
	u32 dram_dqm4;
	u32 dram_dqm5;
	u32 dram_dqm6;
	u32 dram_dqm7;
	u32 dram_ras;
	u32 dram_reset;
	u32 res3[2];
	u32 dram_sdba2;
	u32 dram_sdcke0;
	u32 dram_sdcke1;
	u32 dram_sdclk_0;
	u32 dram_sdclk_1;
	u32 dram_sdodt0;
	u32 dram_sdodt1;
	u32 dram_sdqs0;
	u32 dram_sdqs1;
	u32 dram_sdqs2;
	u32 dram_sdqs3;
	u32 dram_sdqs4;
	u32 dram_sdqs5;
	u32 dram_sdqs6;
	u32 dram_sdqs7;
};

#define MX6SDL_IOM_GRP_BASE     0x020e0700
struct mx6sdl_iomux_grp_regs {
	u32 res1[18];
	u32 grp_b7ds;
	u32 grp_addds;
	u32 grp_ddrmode_ctl;
	u32 grp_ddrpke;
	u32 res2[2];
	u32 grp_ddrmode;
	u32 grp_b0ds;
	u32 res3;
	u32 grp_ctlds;
	u32 grp_b1ds;
	u32 grp_ddr_type;
	u32 grp_b2ds;
	u32 grp_b3ds;
	u32 grp_b4ds;
	u32 grp_b5ds;
	u32 res4;
	u32 grp_b6ds;
};

/* Device Information: Varies per DDR3 part number and speed grade */
struct mx6_ddr3_cfg {
	u16 mem_speed;	/* ie 1600 for DDR3-1600 (800,1066,1333,1600) */
	u8 density;	/* chip density (Gb) (1,2,4,8) */
	u8 width;	/* bus width (bits) (4,8,16) */
	u8 banks;	/* number of banks */
	u8 rowaddr;	/* row address bits (11-16)*/
	u8 coladdr;	/* col address bits (9-12) */
	u8 pagesz;	/* page size (K) (1-2) */
	u16 trcd;	/* tRCD=tRP=CL (ns*100) */
	u16 trcmin;	/* tRC min (ns*100) */
	u16 trasmin;	/* tRAS min (ns*100) */
	u8 SRT;		/* self-refresh temperature: 0=normal, 1=extended */
};

/* System Information: Varies per board design, layout, and term choices */
struct mx6_ddr_sysinfo {
	u8 dsize;	/* size of bus (in dwords: 0=16bit,1=32bit,2=64bit) */
	u8 cs_density;	/* density per chip select (Gb) */
	u8 ncs;		/* number chip selects used (1|2) */
	char cs1_mirror;/* enable address mirror (0|1) */
	char bi_on;	/* Bank interleaving enable */
	u8 rtt_nom;	/* Rtt_Nom (DDR3_RTT_*) */
	u8 rtt_wr;	/* Rtt_Wr (DDR3_RTT_*) */
	u8 ralat;	/* Read Additional Latency (0-7) */
	u8 walat;	/* Write Additional Latency (0-3) */
	u8 mif3_mode;	/* Command prediction working mode */
	u8 rst_to_cke;	/* Time from SDE enable to CKE rise */
	u8 sde_to_rst;	/* Time from SDE enable until DDR reset# is high */
};

/*
 * Board specific calibration:
 *   This includes write leveling calibration values as well as DQS gating
 *   and read/write delays. These values are board/layout/device specific.
 *   Freescale recommends using the i.MX6 DDR Stress Test Tool V1.0.2
 *   (DOC-96412) to determine these values over a range of boards and
 *   temperatures.
 */
struct mx6_mmdc_calibration {
	/* write leveling calibration */
	u32 p0_mpwldectrl0;
	u32 p0_mpwldectrl1;
	u32 p1_mpwldectrl0;
	u32 p1_mpwldectrl1;
	/* read DQS gating */
	u32 p0_mpdgctrl0;
	u32 p0_mpdgctrl1;
	u32 p1_mpdgctrl0;
	u32 p1_mpdgctrl1;
	/* read delay */
	u32 p0_mprddlctl;
	u32 p1_mprddlctl;
	/* write delay */
	u32 p0_mpwrdlctl;
	u32 p1_mpwrdlctl;
};

/* configure iomux (pinctl/padctl) */
void mx6dq_dram_iocfg(unsigned width,
		      const struct mx6dq_iomux_ddr_regs *,
		      const struct mx6dq_iomux_grp_regs *);
void mx6sdl_dram_iocfg(unsigned width,
		       const struct mx6sdl_iomux_ddr_regs *,
		       const struct mx6sdl_iomux_grp_regs *);

/* configure mx6 mmdc registers */
void mx6_dram_cfg(const struct mx6_ddr_sysinfo *,
		  const struct mx6_mmdc_calibration *,
		  const struct mx6_ddr3_cfg *);

#endif /* CONFIG_SPL_BUILD */

#define MX6_MMDC_P0_MDCTL	0x021b0000
#define MX6_MMDC_P0_MDPDC	0x021b0004
#define MX6_MMDC_P0_MDOTC	0x021b0008
#define MX6_MMDC_P0_MDCFG0	0x021b000c
#define MX6_MMDC_P0_MDCFG1	0x021b0010
#define MX6_MMDC_P0_MDCFG2	0x021b0014
#define MX6_MMDC_P0_MDMISC	0x021b0018
#define MX6_MMDC_P0_MDSCR	0x021b001c
#define MX6_MMDC_P0_MDREF	0x021b0020
#define MX6_MMDC_P0_MDRWD	0x021b002c
#define MX6_MMDC_P0_MDOR	0x021b0030
#define MX6_MMDC_P0_MDASP	0x021b0040
#define MX6_MMDC_P0_MAPSR	0x021b0404
#define MX6_MMDC_P0_MPZQHWCTRL	0x021b0800
#define MX6_MMDC_P0_MPWLDECTRL0	0x021b080c
#define MX6_MMDC_P0_MPWLDECTRL1	0x021b0810
#define MX6_MMDC_P0_MPODTCTRL	0x021b0818
#define MX6_MMDC_P0_MPRDDQBY0DL	0x021b081c
#define MX6_MMDC_P0_MPRDDQBY1DL	0x021b0820
#define MX6_MMDC_P0_MPRDDQBY2DL	0x021b0824
#define MX6_MMDC_P0_MPRDDQBY3DL	0x021b0828
#define MX6_MMDC_P0_MPDGCTRL0	0x021b083c
#define MX6_MMDC_P0_MPDGCTRL1	0x021b0840
#define MX6_MMDC_P0_MPRDDLCTL	0x021b0848
#define MX6_MMDC_P0_MPWRDLCTL	0x021b0850
#define MX6_MMDC_P0_MPMUR0	0x021b08b8

#define MX6_MMDC_P1_MDCTL	0x021b4000
#define MX6_MMDC_P1_MDPDC	0x021b4004
#define MX6_MMDC_P1_MDOTC	0x021b4008
#define MX6_MMDC_P1_MDCFG0	0x021b400c
#define MX6_MMDC_P1_MDCFG1	0x021b4010
#define MX6_MMDC_P1_MDCFG2	0x021b4014
#define MX6_MMDC_P1_MDMISC	0x021b4018
#define MX6_MMDC_P1_MDSCR	0x021b401c
#define MX6_MMDC_P1_MDREF	0x021b4020
#define MX6_MMDC_P1_MDRWD	0x021b402c
#define MX6_MMDC_P1_MDOR	0x021b4030
#define MX6_MMDC_P1_MDASP	0x021b4040
#define MX6_MMDC_P1_MAPSR	0x021b4404
#define MX6_MMDC_P1_MPZQHWCTRL	0x021b4800
#define MX6_MMDC_P1_MPWLDECTRL0	0x021b480c
#define MX6_MMDC_P1_MPWLDECTRL1	0x021b4810
#define MX6_MMDC_P1_MPODTCTRL	0x021b4818
#define MX6_MMDC_P1_MPRDDQBY0DL	0x021b481c
#define MX6_MMDC_P1_MPRDDQBY1DL	0x021b4820
#define MX6_MMDC_P1_MPRDDQBY2DL	0x021b4824
#define MX6_MMDC_P1_MPRDDQBY3DL	0x021b4828
#define MX6_MMDC_P1_MPDGCTRL0	0x021b483c
#define MX6_MMDC_P1_MPDGCTRL1	0x021b4840
#define MX6_MMDC_P1_MPRDDLCTL	0x021b4848
#define MX6_MMDC_P1_MPWRDLCTL	0x021b4850
#define MX6_MMDC_P1_MPMUR0	0x021b48b8

#endif	/*__ASM_ARCH_MX6_DDR_H__ */
