/*
 * (C) Copyright 2014
 * Vikas Manocha, ST Micoelectronics, vikas.manocha@st.com
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _STV0991_CGU_H
#define _STV0991_CGU_H

struct stv0991_cgu_regs {
	u32 cpu_freq;		/* offset 0x0 */
	u32 icn2_freq;		/* offset 0x4 */
	u32 dma_freq;		/* offset 0x8 */
	u32 isp_freq;		/* offset 0xc */
	u32 h264_freq;		/* offset 0x10 */
	u32 osif_freq;		/* offset 0x14 */
	u32 ren_freq;		/* offset 0x18 */
	u32 tim_freq;		/* offset 0x1c */
	u32 sai_freq;		/* offset 0x20 */
	u32 eth_freq;		/* offset 0x24 */
	u32 i2c_freq;		/* offset 0x28 */
	u32 spi_freq;		/* offset 0x2c */
	u32 uart_freq;		/* offset 0x30 */
	u32 qspi_freq;		/* offset 0x34 */
	u32 sdio_freq;		/* offset 0x38 */
	u32 usi_freq;		/* offset 0x3c */
	u32 can_line_freq;	/* offset 0x40 */
	u32 debug_freq;		/* offset 0x44 */
	u32 trace_freq;		/* offset 0x48 */
	u32 stm_freq;		/* offset 0x4c */
	u32 eth_ctrl;		/* offset 0x50 */
	u32 reserved[3];	/* offset 0x54 */
	u32 osc_ctrl;		/* offset 0x60 */
	u32 pll1_ctrl;		/* offset 0x64 */
	u32 pll1_freq;		/* offset 0x68 */
	u32 pll1_fract;		/* offset 0x6c */
	u32 pll1_spread;	/* offset 0x70 */
	u32 pll1_status;	/* offset 0x74 */
	u32 pll2_ctrl;		/* offset 0x78 */
	u32 pll2_freq;		/* offset 0x7c */
	u32 pll2_fract;		/* offset 0x80 */
	u32 pll2_spread;	/* offset 0x84 */
	u32 pll2_status;	/* offset 0x88 */
	u32 cgu_enable_1;	/* offset 0x8c */
	u32 cgu_enable_2;	/* offset 0x90 */
	u32 cgu_isp_pulse;	/* offset 0x94 */
	u32 cgu_h264_pulse;	/* offset 0x98 */
	u32 cgu_osif_pulse;	/* offset 0x9c */
	u32 cgu_ren_pulse;	/* offset 0xa0 */

};

/* CGU Timer */
#define CLK_TMR_OSC			0
#define CLK_TMR_MCLK			1
#define CLK_TMR_PLL1			2
#define CLK_TMR_PLL2			3
#define MDIV_SHIFT_TMR			3
#define DIV_SHIFT_TMR			6

#define TIMER1_CLK_CFG			(0 << DIV_SHIFT_TMR \
					| 0 << MDIV_SHIFT_TMR | CLK_TMR_MCLK)

/* Clock Enable/Disable */

#define TIMER1_CLK_EN			(1 << 15)

/* CGU Uart config */
#define CLK_UART_MCLK			0
#define CLK_UART_PLL1			1
#define CLK_UART_PLL2			2

#define MDIV_SHIFT_UART			3
#define DIV_SHIFT_UART			6

#define UART_CLK_CFG			(4 << DIV_SHIFT_UART \
					| 1 << MDIV_SHIFT_UART | CLK_UART_MCLK)

#endif
