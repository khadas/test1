/*
 * Copyright (c) 2010-2012, NVIDIA CORPORATION.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <asm/io.h>
#include <asm/arch/clock.h>
#include <asm/arch/gp_padctrl.h>
#include <asm/arch/pinmux.h>
#include <asm/arch/tegra.h>
#include <asm/arch-tegra/clk_rst.h>
#include <asm/arch-tegra/pmc.h>
#include <asm/arch-tegra/scu.h>
#include "cpu.h"

enum tegra_family_t {
	TEGRA_FAMILY_T2x,
	TEGRA_FAMILY_T3x,
};


enum tegra_family_t get_family(void)
{
	u32 reg, chip_id;

	reg = readl(NV_PA_APB_MISC_BASE + GP_HIDREV);

	chip_id = reg >> 8;
	chip_id &= 0xff;
	debug("  tegra_get_family: chip_id = %x\n", chip_id);
	if (chip_id == 0x30)
		return TEGRA_FAMILY_T3x;
	else
		return TEGRA_FAMILY_T2x;
}

int get_num_cpus(void)
{
	return get_family() == TEGRA_FAMILY_T3x ? 4 : 2;
}

/*
 * Timing tables for each SOC for all four oscillator options.
 */
struct clk_pll_table tegra_pll_x_table[TEGRA_SOC_CNT][CLOCK_OSC_FREQ_COUNT] = {
	/* T20: 1 GHz */
	{{ 1000, 13, 0, 12},	/* OSC 13M */
	 { 625,  12, 0, 8},	/* OSC 19.2M */
	 { 1000, 12, 0, 12},	/* OSC 12M */
	 { 1000, 26, 0, 12},	/* OSC 26M */
	},

	/* T25: 1.2 GHz */
	{{ 923, 10, 0, 12},
	 { 750, 12, 0, 8},
	 { 600,  6, 0, 12},
	 { 600, 13, 0, 12},
	},

	/* T30: 1.4 GHz */
	{{ 862, 8, 0, 8},
	 { 583, 8, 0, 4},
	 { 700, 6, 0, 8},
	 { 700, 13, 0, 8},
	},
};

void adjust_pllp_out_freqs(void)
{
	struct clk_rst_ctlr *clkrst = (struct clk_rst_ctlr *)NV_PA_CLK_RST_BASE;
	struct clk_pll *pll = &clkrst->crc_pll[CLOCK_ID_PERIPH];
	u32 reg;

	/* Set T30 PLLP_OUT1, 2, 3 & 4 freqs to 9.6, 48, 102 & 204MHz */
	reg = readl(&pll->pll_out[0]);	/* OUTA, contains OUT2 / OUT1 */
	reg |= (IN_408_OUT_48_DIVISOR << PLLP_OUT2_RATIO) | PLLP_OUT2_OVR
		| (IN_408_OUT_9_6_DIVISOR << PLLP_OUT1_RATIO) | PLLP_OUT1_OVR;
	writel(reg, &pll->pll_out[0]);

	reg = readl(&pll->pll_out[1]);   /* OUTB, contains OUT4 / OUT3 */
	reg |= (IN_408_OUT_204_DIVISOR << PLLP_OUT4_RATIO) | PLLP_OUT4_OVR
		| (IN_408_OUT_102_DIVISOR << PLLP_OUT3_RATIO) | PLLP_OUT3_OVR;
	writel(reg, &pll->pll_out[1]);
}

int pllx_set_rate(struct clk_pll_simple *pll , u32 divn, u32 divm,
		u32 divp, u32 cpcon)
{
	u32 reg;

	/* If PLLX is already enabled, just return */
	if (readl(&pll->pll_base) & PLL_ENABLE_MASK) {
		debug("pllx_set_rate: PLLX already enabled, returning\n");
		return 0;
	}

	debug(" pllx_set_rate entry\n");

	/* Set BYPASS, m, n and p to PLLX_BASE */
	reg = PLL_BYPASS_MASK | (divm << PLL_DIVM_SHIFT);
	reg |= ((divn << PLL_DIVN_SHIFT) | (divp << PLL_DIVP_SHIFT));
	writel(reg, &pll->pll_base);

	/* Set cpcon to PLLX_MISC */
	reg = (cpcon << PLL_CPCON_SHIFT);

	/* Set dccon to PLLX_MISC if freq > 600MHz */
	if (divn > 600)
		reg |= (1 << PLL_DCCON_SHIFT);
	writel(reg, &pll->pll_misc);

	/* Enable PLLX */
	reg = readl(&pll->pll_base);
	reg |= PLL_ENABLE_MASK;

	/* Disable BYPASS */
	reg &= ~PLL_BYPASS_MASK;
	writel(reg, &pll->pll_base);

	/* Set lock_enable to PLLX_MISC */
	reg = readl(&pll->pll_misc);
	reg |= PLL_LOCK_ENABLE_MASK;
	writel(reg, &pll->pll_misc);

	return 0;
}

void init_pllx(void)
{
	struct clk_rst_ctlr *clkrst = (struct clk_rst_ctlr *)NV_PA_CLK_RST_BASE;
	struct clk_pll_simple *pll = &clkrst->crc_pll_simple[SIMPLE_PLLX];
	int chip_type;
	enum clock_osc_freq osc;
	struct clk_pll_table *sel;

	debug("init_pllx entry\n");

	/* get chip type */
	chip_type = tegra_get_chip_type();
	debug(" init_pllx: chip_type = %d\n", chip_type);

	/* get osc freq */
	osc = clock_get_osc_freq();
	debug("  init_pllx: osc = %d\n", osc);

	/* set pllx */
	sel = &tegra_pll_x_table[chip_type][osc];
	pllx_set_rate(pll, sel->n, sel->m, sel->p, sel->cpcon);

	/* adjust PLLP_out1-4 on T30 */
	if (chip_type == TEGRA_SOC_T30) {
		debug("  init_pllx: adjusting PLLP out freqs\n");
		adjust_pllp_out_freqs();
	}
}

void enable_cpu_clock(int enable)
{
	struct clk_rst_ctlr *clkrst = (struct clk_rst_ctlr *)NV_PA_CLK_RST_BASE;
	u32 clk;

	/*
	 * NOTE:
	 * Regardless of whether the request is to enable or disable the CPU
	 * clock, every processor in the CPU complex except the master (CPU 0)
	 * will have it's clock stopped because the AVP only talks to the
	 * master.
	 */

	if (enable) {
		/* Initialize PLLX */
		init_pllx();

		/* Wait until all clocks are stable */
		udelay(PLL_STABILIZATION_DELAY);

		writel(CCLK_BURST_POLICY, &clkrst->crc_cclk_brst_pol);
		writel(SUPER_CCLK_DIVIDER, &clkrst->crc_super_cclk_div);
	}

	/*
	 * Read the register containing the individual CPU clock enables and
	 * always stop the clocks to CPUs > 0.
	 */
	clk = readl(&clkrst->crc_clk_cpu_cmplx);
	clk |= 1 << CPU1_CLK_STP_SHIFT;
#if defined(CONFIG_TEGRA30)
	clk |= 1 << CPU2_CLK_STP_SHIFT;
	clk |= 1 << CPU3_CLK_STP_SHIFT;
#endif
	/* Stop/Unstop the CPU clock */
	clk &= ~CPU0_CLK_STP_MASK;
	clk |= !enable << CPU0_CLK_STP_SHIFT;
	writel(clk, &clkrst->crc_clk_cpu_cmplx);

	clock_enable(PERIPH_ID_CPU);
}

static int is_cpu_powered(void)
{
	struct pmc_ctlr *pmc = (struct pmc_ctlr *)NV_PA_PMC_BASE;

	return (readl(&pmc->pmc_pwrgate_status) & CPU_PWRED) ? 1 : 0;
}

static void remove_cpu_io_clamps(void)
{
	struct pmc_ctlr *pmc = (struct pmc_ctlr *)NV_PA_PMC_BASE;
	u32 reg;

	/* Remove the clamps on the CPU I/O signals */
	reg = readl(&pmc->pmc_remove_clamping);
	reg |= CPU_CLMP;
	writel(reg, &pmc->pmc_remove_clamping);

	/* Give I/O signals time to stabilize */
	udelay(IO_STABILIZATION_DELAY);
}

void powerup_cpu(void)
{
	struct pmc_ctlr *pmc = (struct pmc_ctlr *)NV_PA_PMC_BASE;
	u32 reg;
	int timeout = IO_STABILIZATION_DELAY;

	if (!is_cpu_powered()) {
		/* Toggle the CPU power state (OFF -> ON) */
		reg = readl(&pmc->pmc_pwrgate_toggle);
		reg &= PARTID_CP;
		reg |= START_CP;
		writel(reg, &pmc->pmc_pwrgate_toggle);

		/* Wait for the power to come up */
		while (!is_cpu_powered()) {
			if (timeout-- == 0)
				printf("CPU failed to power up!\n");
			else
				udelay(10);
		}

		/*
		 * Remove the I/O clamps from CPU power partition.
		 * Recommended only on a Warm boot, if the CPU partition gets
		 * power gated. Shouldn't cause any harm when called after a
		 * cold boot according to HW, probably just redundant.
		 */
		remove_cpu_io_clamps();
	}
}

void reset_A9_cpu(int reset)
{
	/*
	* NOTE:  Regardless of whether the request is to hold the CPU in reset
	*        or take it out of reset, every processor in the CPU complex
	*        except the master (CPU 0) will be held in reset because the
	*        AVP only talks to the master. The AVP does not know that there
	*        are multiple processors in the CPU complex.
	*/
	int mask = crc_rst_cpu | crc_rst_de | crc_rst_debug;
	int num_cpus = get_num_cpus();
	int cpu;

	debug("reset_a9_cpu entry\n");
	/* Hold CPUs 1 onwards in reset, and CPU 0 if asked */
	for (cpu = 1; cpu < num_cpus; cpu++)
		reset_cmplx_set_enable(cpu, mask, 1);
	reset_cmplx_set_enable(0, mask, reset);

	/* Enable/Disable master CPU reset */
	reset_set_enable(PERIPH_ID_CPU, reset);
}

void clock_enable_coresight(int enable)
{
	u32 rst, src;

	debug("clock_enable_coresight entry\n");
	clock_set_enable(PERIPH_ID_CORESIGHT, enable);
	reset_set_enable(PERIPH_ID_CORESIGHT, !enable);

	if (enable) {
		/*
		 * Put CoreSight on PLLP_OUT0 (216 MHz) and divide it down by
		 *  1.5, giving an effective frequency of 144MHz.
		 * Set PLLP_OUT0 [bits31:30 = 00], and use a 7.1 divisor
		 *  (bits 7:0), so 00000001b == 1.5 (n+1 + .5)
		 *
		 * Clock divider request for 204MHz would setup CSITE clock as
		 * 144MHz for PLLP base 216MHz and 204MHz for PLLP base 408MHz
		 */
		if (tegra_get_chip_type() == TEGRA_SOC_T30)
			src = CLK_DIVIDER(NVBL_PLLP_KHZ, 204000);
		else
			src = CLK_DIVIDER(NVBL_PLLP_KHZ, 144000);
		clock_ll_set_source_divisor(PERIPH_ID_CSI, 0, src);

		/* Unlock the CPU CoreSight interfaces */
		rst = CORESIGHT_UNLOCK;
		writel(rst, CSITE_CPU_DBG0_LAR);
		writel(rst, CSITE_CPU_DBG1_LAR);
#if defined(CONFIG_TEGRA30)
		writel(rst, CSITE_CPU_DBG2_LAR);
		writel(rst, CSITE_CPU_DBG3_LAR);
#endif
	}
}

void halt_avp(void)
{
	for (;;) {
		writel((HALT_COP_EVENT_JTAG | HALT_COP_EVENT_IRQ_1 \
			| HALT_COP_EVENT_FIQ_1 | (FLOW_MODE_STOP<<29)),
			FLOW_CTLR_HALT_COP_EVENTS);
	}
}
