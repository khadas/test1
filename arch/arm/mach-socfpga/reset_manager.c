/*
 *  Copyright (C) 2013 Altera Corporation <www.altera.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */


#include <common.h>
#include <asm/io.h>
#include <asm/arch/reset_manager.h>
#include <asm/arch/fpga_manager.h>

DECLARE_GLOBAL_DATA_PTR;

static const struct socfpga_reset_manager *reset_manager_base =
		(void *)SOCFPGA_RSTMGR_ADDRESS;

/* Assert or de-assert SoCFPGA reset manager reset. */
void socfpga_per_reset(u32 reset, int set)
{
	const void *reg;

	if (RSTMGR_BANK(reset) == 0)
		reg = &reset_manager_base->mpu_mod_reset;
	else if (RSTMGR_BANK(reset) == 1)
		reg = &reset_manager_base->per_mod_reset;
	else if (RSTMGR_BANK(reset) == 2)
		reg = &reset_manager_base->per2_mod_reset;
	else if (RSTMGR_BANK(reset) == 3)
		reg = &reset_manager_base->brg_mod_reset;
	else if (RSTMGR_BANK(reset) == 4)
		reg = &reset_manager_base->misc_mod_reset;
	else	/* Invalid reset register, do nothing */
		return;

	if (set)
		setbits_le32(reg, 1 << RSTMGR_RESET(reset));
	else
		clrbits_le32(reg, 1 << RSTMGR_RESET(reset));
}

/* Toggle reset signal to watchdog (WDT is disabled after this operation!) */
void socfpga_watchdog_reset(void)
{
	/* assert reset for watchdog */
	socfpga_per_reset(SOCFPGA_RESET(L4WD0), 1);

	/* deassert watchdog from reset (watchdog in not running state) */
	socfpga_per_reset(SOCFPGA_RESET(L4WD0), 0);
}

/*
 * Write the reset manager register to cause reset
 */
void reset_cpu(ulong addr)
{
	/* request a warm reset */
	writel((1 << RSTMGR_CTRL_SWWARMRSTREQ_LSB),
		&reset_manager_base->ctrl);
	/*
	 * infinite loop here as watchdog will trigger and reset
	 * the processor
	 */
	while (1)
		;
}

/*
 * Release peripherals from reset based on handoff
 */
void reset_deassert_peripherals_handoff(void)
{
	writel(0, &reset_manager_base->per_mod_reset);
}

#if defined(CONFIG_SOCFPGA_VIRTUAL_TARGET)
void socfpga_bridges_reset(int enable)
{
	/* For SoCFPGA-VT, this is NOP. */
}
#else

#define L3REGS_REMAP_LWHPS2FPGA_MASK	0x10
#define L3REGS_REMAP_HPS2FPGA_MASK	0x08
#define L3REGS_REMAP_OCRAM_MASK		0x01

void socfpga_bridges_reset(int enable)
{
	const uint32_t l3mask = L3REGS_REMAP_LWHPS2FPGA_MASK |
				L3REGS_REMAP_HPS2FPGA_MASK |
				L3REGS_REMAP_OCRAM_MASK;

	if (enable) {
		/* brdmodrst */
		writel(0xffffffff, &reset_manager_base->brg_mod_reset);
	} else {
		/* Check signal from FPGA. */
		if (fpgamgr_poll_fpga_ready()) {
			/* FPGA not ready. Wait for watchdog timeout. */
			printf("%s: fpga not ready, hanging.\n", __func__);
			hang();
		}

		/* brdmodrst */
		writel(0, &reset_manager_base->brg_mod_reset);

		/* Remap the bridges into memory map */
		writel(l3mask, SOCFPGA_L3REGS_ADDRESS);
	}
}
#endif

/* Change the reset state for EMAC 0 and EMAC 1 */
void socfpga_emac_reset(int enable)
{
	if (enable) {
		socfpga_per_reset(SOCFPGA_RESET(EMAC0), 1);
		socfpga_per_reset(SOCFPGA_RESET(EMAC1), 1);
	} else {
#if (CONFIG_EMAC_BASE == SOCFPGA_EMAC0_ADDRESS)
		socfpga_per_reset(SOCFPGA_RESET(EMAC0), 0);
#elif (CONFIG_EMAC_BASE == SOCFPGA_EMAC1_ADDRESS)
		socfpga_per_reset(SOCFPGA_RESET(EMAC1), 0);
#endif
	}
}

/* SPI Master enable (its held in reset by the preloader) */
void socfpga_spim_enable(void)
{
	socfpga_per_reset(SOCFPGA_RESET(SPIM0), 0);
	socfpga_per_reset(SOCFPGA_RESET(SPIM1), 0);
}

/* Bring UART0 out of reset. */
void socfpga_uart0_enable(void)
{
	socfpga_per_reset(SOCFPGA_RESET(UART0), 0);
}

/* Bring SDRAM controller out of reset. */
void socfpga_sdram_enable(void)
{
	socfpga_per_reset(SOCFPGA_RESET(SDR), 0);
}

/* Bring OSC1 timer out of reset. */
void socfpga_osc1timer_enable(void)
{
	socfpga_per_reset(SOCFPGA_RESET(OSC1TIMER0), 0);
}
