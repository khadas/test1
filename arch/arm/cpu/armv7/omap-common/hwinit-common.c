/*
 *
 * Common functions for OMAP4/5 based boards
 *
 * (C) Copyright 2010
 * Texas Instruments, <www.ti.com>
 *
 * Author :
 *	Aneesh V	<aneesh@ti.com>
 *	Steve Sakoman	<steve@sakoman.com>
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */
#include <common.h>
#include <spl.h>
#include <asm/arch/sys_proto.h>
#include <asm/sizes.h>
#include <asm/emif.h>
#include <asm/omap_common.h>
#include <linux/compiler.h>
#include <asm/cache.h>
#include <asm/system.h>

#define ARMV7_DCACHE_WRITEBACK  0xe
#define	ARMV7_DOMAIN_CLIENT	1
#define ARMV7_DOMAIN_MASK	(0x3 << 0)

DECLARE_GLOBAL_DATA_PTR;

void do_set_mux(u32 base, struct pad_conf_entry const *array, int size)
{
	int i;
	struct pad_conf_entry *pad = (struct pad_conf_entry *) array;

	for (i = 0; i < size; i++, pad++)
		writew(pad->val, base + pad->offset);
}

static void set_mux_conf_regs(void)
{
	switch (omap_hw_init_context()) {
	case OMAP_INIT_CONTEXT_SPL:
		set_muxconf_regs_essential();
		break;
	case OMAP_INIT_CONTEXT_UBOOT_AFTER_SPL:
#ifdef CONFIG_SYS_ENABLE_PADS_ALL
		set_muxconf_regs_non_essential();
#endif
		break;
	case OMAP_INIT_CONTEXT_UBOOT_FROM_NOR:
	case OMAP_INIT_CONTEXT_UBOOT_AFTER_CH:
		set_muxconf_regs_essential();
#ifdef CONFIG_SYS_ENABLE_PADS_ALL
		set_muxconf_regs_non_essential();
#endif
		break;
	}
}

u32 cortex_rev(void)
{

	unsigned int rev;

	/* Read Main ID Register (MIDR) */
	asm ("mrc p15, 0, %0, c0, c0, 0" : "=r" (rev));

	return rev;
}

void omap_rev_string(void)
{
	u32 omap_rev = omap_revision();
	u32 soc_variant	= (omap_rev & 0xF0000000) >> 28;
	u32 omap_variant = (omap_rev & 0xFFFF0000) >> 16;
	u32 major_rev = (omap_rev & 0x00000F00) >> 8;
	u32 minor_rev = (omap_rev & 0x000000F0) >> 4;

	if (soc_variant)
		printf("OMAP");
	else
		printf("DRA");
	printf("%x ES%x.%x\n", omap_variant, major_rev,
	       minor_rev);
}

#ifdef CONFIG_SPL_BUILD
void spl_display_print(void)
{
	omap_rev_string();
}
#endif

void __weak srcomp_enable(void)
{
}

static void save_omap_boot_params(void)
{
	u32 rom_params = *((u32 *)OMAP_SRAM_SCRATCH_BOOT_PARAMS);
	u8 boot_device;
	u32 dev_desc, dev_data;

	if ((rom_params <  NON_SECURE_SRAM_START) ||
	    (rom_params > NON_SECURE_SRAM_END))
		return;

	/*
	 * rom_params can be type casted to omap_boot_parameters and
	 * used. But it not correct to assume that romcode structure
	 * encoding would be same as u-boot. So use the defined offsets.
	 */
	gd->arch.omap_boot_params.omap_bootdevice = boot_device =
				   *((u8 *)(rom_params + BOOT_DEVICE_OFFSET));

	gd->arch.omap_boot_params.ch_flags =
				*((u8 *)(rom_params + CH_FLAGS_OFFSET));

	if ((boot_device >= MMC_BOOT_DEVICES_START) &&
	    (boot_device <= MMC_BOOT_DEVICES_END)) {
		if ((omap_hw_init_context() ==
				      OMAP_INIT_CONTEXT_UBOOT_AFTER_SPL)) {
			gd->arch.omap_boot_params.omap_bootmode =
			*((u8 *)(rom_params + BOOT_MODE_OFFSET));
		} else {
			dev_desc = *((u32 *)(rom_params + DEV_DESC_PTR_OFFSET));
			dev_data = *((u32 *)(dev_desc + DEV_DATA_PTR_OFFSET));
			gd->arch.omap_boot_params.omap_bootmode =
					*((u32 *)(dev_data + BOOT_MODE_OFFSET));
		}
	}
}

#ifdef CONFIG_ARCH_CPU_INIT
/*
 * SOC specific cpu init
 */
int arch_cpu_init(void)
{
	save_omap_boot_params();
	return 0;
}
#endif /* CONFIG_ARCH_CPU_INIT */

/*
 * Routine: s_init
 * Description: Does early system init of watchdog, muxing,  andclocks
 * Watchdog disable is done always. For the rest what gets done
 * depends on the boot mode in which this function is executed
 *   1. s_init of SPL running from SRAM
 *   2. s_init of U-Boot running from FLASH
 *   3. s_init of U-Boot loaded to SDRAM by SPL
 *   4. s_init of U-Boot loaded to SDRAM by ROM code using the
 *	Configuration Header feature
 * Please have a look at the respective functions to see what gets
 * done in each of these cases
 * This function is called with SRAM stack.
 */
void s_init(void)
{
	/*
	 * Save the boot parameters passed from romcode.
	 * We cannot delay the saving further than this,
	 * to prevent overwrites.
	 */
#ifdef CONFIG_SPL_BUILD
	save_omap_boot_params();
#endif
	init_omap_revision();
	hw_data_init();

#ifdef CONFIG_SPL_BUILD
	if (warm_reset() && (omap_revision() <= OMAP5430_ES1_0))
		force_emif_self_refresh();
#endif
	watchdog_init();
	set_mux_conf_regs();
#ifdef CONFIG_SPL_BUILD
	srcomp_enable();
	setup_clocks_for_console();

	gd = &gdata;

	preloader_console_init();
	do_io_settings();
#endif
	prcm_init();
#ifdef CONFIG_SPL_BUILD
	timer_init();

	/* For regular u-boot sdram_init() is called from dram_init() */
	sdram_init();
#endif
}

/*
 * Routine: wait_for_command_complete
 * Description: Wait for posting to finish on watchdog
 */
void wait_for_command_complete(struct watchdog *wd_base)
{
	int pending = 1;
	do {
		pending = readl(&wd_base->wwps);
	} while (pending);
}

/*
 * Routine: watchdog_init
 * Description: Shut down watch dogs
 */
void watchdog_init(void)
{
	struct watchdog *wd2_base = (struct watchdog *)WDT2_BASE;

	writel(WD_UNLOCK1, &wd2_base->wspr);
	wait_for_command_complete(wd2_base);
	writel(WD_UNLOCK2, &wd2_base->wspr);
}


/*
 * This function finds the SDRAM size available in the system
 * based on DMM section configurations
 * This is needed because the size of memory installed may be
 * different on different versions of the board
 */
u32 omap_sdram_size(void)
{
	u32 section, i, valid;
	u64 sdram_start = 0, sdram_end = 0, addr,
	    size, total_size = 0, trap_size = 0;

	for (i = 0; i < 4; i++) {
		section	= __raw_readl(DMM_BASE + i*4);
		valid = (section & EMIF_SDRC_ADDRSPC_MASK) >>
			(EMIF_SDRC_ADDRSPC_SHIFT);
		addr = section & EMIF_SYS_ADDR_MASK;

		/* See if the address is valid */
		if ((addr >= DRAM_ADDR_SPACE_START) &&
		    (addr < DRAM_ADDR_SPACE_END)) {
			size = ((section & EMIF_SYS_SIZE_MASK) >>
				   EMIF_SYS_SIZE_SHIFT);
			size = 1 << size;
			size *= SZ_16M;

			if (valid != DMM_SDRC_ADDR_SPC_INVALID) {
				if (!sdram_start || (addr < sdram_start))
					sdram_start = addr;
				if (!sdram_end || ((addr + size) > sdram_end))
					sdram_end = addr + size;
			} else {
				trap_size = size;
			}

		}

	}
	total_size = (sdram_end - sdram_start) - (trap_size);

	return total_size;
}


/*
 * Routine: dram_init
 * Description: sets uboots idea of sdram size
 */
int dram_init(void)
{
	sdram_init();
	gd->ram_size = omap_sdram_size();
	return 0;
}

/*
 * Print board information
 */
int checkboard(void)
{
	puts(sysinfo.board_string);
	return 0;
}

/*
 *  get_device_type(): tell if GP/HS/EMU/TST
 */
u32 get_device_type(void)
{
	return (readl((*ctrl)->control_status) &
				      (DEVICE_TYPE_MASK)) >> DEVICE_TYPE_SHIFT;
}

/*
 * Print CPU information
 */
int print_cpuinfo(void)
{
	puts("CPU  : ");
	omap_rev_string();

	return 0;
}
#ifndef CONFIG_SYS_DCACHE_OFF
void enable_caches(void)
{
	/* Enable D-cache. I-cache is already enabled in start.S */
	dcache_enable();
}

void dram_bank_mmu_setup(int bank)
{
	bd_t *bd = gd->bd;
	int	i;

	u32 start = bd->bi_dram[bank].start >> 20;
	u32 size = bd->bi_dram[bank].size >> 20;
	u32 end = start + size;

	debug("%s: bank: %d\n", __func__, bank);
	for (i = start; i < end; i++)
		set_section_dcache(i, ARMV7_DCACHE_WRITEBACK);

}

void arm_init_domains(void)
{
	u32 reg;

	reg = get_dacr();
	/*
	* Set DOMAIN to client access so that all permissions
	* set in pagetables are validated by the mmu.
	*/
	reg &= ~ARMV7_DOMAIN_MASK;
	reg |= ARMV7_DOMAIN_CLIENT;
	set_dacr(reg);
}
#endif
