/*
 * Copyright 2014-2015 Freescale Semiconductor, Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <efi_loader.h>
#include <libfdt.h>
#include <fdt_support.h>
#include <phy.h>
#ifdef CONFIG_FSL_LSCH3
#include <asm/arch/fdt.h>
#endif
#ifdef CONFIG_FSL_ESDHC
#include <fsl_esdhc.h>
#endif
#ifdef CONFIG_SYS_DPAA_FMAN
#include <fsl_fman.h>
#endif
#ifdef CONFIG_MP
#include <asm/arch/mp.h>
#endif
#include <fsl_sec.h>
#include <asm/arch-fsl-layerscape/soc.h>
#ifdef CONFIG_ARMV8_SEC_FIRMWARE_SUPPORT
#include <asm/armv8/sec_firmware.h>
#endif

int fdt_fixup_phy_connection(void *blob, int offset, phy_interface_t phyc)
{
	return fdt_setprop_string(blob, offset, "phy-connection-type",
					 phy_string_for_interface(phyc));
}

#ifdef CONFIG_MP
void ft_fixup_cpu(void *blob)
{
	int off;
	__maybe_unused u64 spin_tbl_addr = (u64)get_spin_tbl_addr();
	fdt32_t *reg;
	int addr_cells;
	u64 val, core_id;
	size_t *boot_code_size = &(__secondary_boot_code_size);
#if defined(CONFIG_ARMV8_SEC_FIRMWARE_SUPPORT) && \
	defined(CONFIG_FSL_PPA_ARMV8_PSCI)
	int node;
	u32 psci_ver;

	/* Check the psci version to determine if the psci is supported */
	psci_ver = sec_firmware_support_psci_version();
	if (psci_ver == 0xffffffff) {
		/* remove psci DT node */
		node = fdt_path_offset(blob, "/psci");
		if (node >= 0)
			goto remove_psci_node;

		node = fdt_node_offset_by_compatible(blob, -1, "arm,psci");
		if (node >= 0)
			goto remove_psci_node;

		node = fdt_node_offset_by_compatible(blob, -1, "arm,psci-0.2");
		if (node >= 0)
			goto remove_psci_node;

		node = fdt_node_offset_by_compatible(blob, -1, "arm,psci-1.0");
		if (node >= 0)
			goto remove_psci_node;

remove_psci_node:
		if (node >= 0)
			fdt_del_node(blob, node);
	} else {
		return;
	}
#endif
	off = fdt_path_offset(blob, "/cpus");
	if (off < 0) {
		puts("couldn't find /cpus node\n");
		return;
	}
	of_bus_default_count_cells(blob, off, &addr_cells, NULL);

	off = fdt_node_offset_by_prop_value(blob, -1, "device_type", "cpu", 4);
	while (off != -FDT_ERR_NOTFOUND) {
		reg = (fdt32_t *)fdt_getprop(blob, off, "reg", 0);
		if (reg) {
			core_id = of_read_number(reg, addr_cells);
			if (core_id  == 0 || (is_core_online(core_id))) {
				val = spin_tbl_addr;
				val += id_to_core(core_id) *
				       SPIN_TABLE_ELEM_SIZE;
				val = cpu_to_fdt64(val);
				fdt_setprop_string(blob, off, "enable-method",
						   "spin-table");
				fdt_setprop(blob, off, "cpu-release-addr",
					    &val, sizeof(val));
			} else {
				debug("skipping offline core\n");
			}
		} else {
			puts("Warning: found cpu node without reg property\n");
		}
		off = fdt_node_offset_by_prop_value(blob, off, "device_type",
						    "cpu", 4);
	}

	fdt_add_mem_rsv(blob, (uintptr_t)&secondary_boot_code,
			*boot_code_size);
#if defined(CONFIG_EFI_LOADER) && !defined(CONFIG_SPL_BUILD)
	efi_add_memory_map((uintptr_t)&secondary_boot_code,
			   ALIGN(*boot_code_size, EFI_PAGE_SIZE) >> EFI_PAGE_SHIFT,
			   EFI_RESERVED_MEMORY_TYPE, false);
#endif
}
#endif

void fsl_fdt_disable_usb(void *blob)
{
	int off;
	/*
	 * SYSCLK is used as a reference clock for USB. When the USB
	 * controller is used, SYSCLK must meet the additional requirement
	 * of 100 MHz.
	 */
	if (CONFIG_SYS_CLK_FREQ != 100000000) {
		off = fdt_node_offset_by_compatible(blob, -1, "snps,dwc3");
		while (off != -FDT_ERR_NOTFOUND) {
			fdt_status_disabled(blob, off);
			off = fdt_node_offset_by_compatible(blob, off,
							    "snps,dwc3");
		}
	}
}

void ft_cpu_setup(void *blob, bd_t *bd)
{
#ifdef CONFIG_FSL_LSCH2
	struct ccsr_gur __iomem *gur = (void *)(CONFIG_SYS_FSL_GUTS_ADDR);
	unsigned int svr = in_be32(&gur->svr);

	/* delete crypto node if not on an E-processor */
	if (!IS_E_PROCESSOR(svr))
		fdt_fixup_crypto_node(blob, 0);
#if CONFIG_SYS_FSL_SEC_COMPAT >= 4
	else {
		ccsr_sec_t __iomem *sec;

		sec = (void __iomem *)CONFIG_SYS_FSL_SEC_ADDR;
		fdt_fixup_crypto_node(blob, sec_in32(&sec->secvid_ms));
	}
#endif
#endif

#ifdef CONFIG_MP
	ft_fixup_cpu(blob);
#endif

#ifdef CONFIG_SYS_NS16550
	do_fixup_by_compat_u32(blob, "fsl,ns16550",
			       "clock-frequency", CONFIG_SYS_NS16550_CLK, 1);
#endif

	do_fixup_by_compat_u32(blob, "fixed-clock",
			       "clock-frequency", CONFIG_SYS_CLK_FREQ, 1);

#ifdef CONFIG_PCI
	ft_pci_setup(blob, bd);
#endif

#ifdef CONFIG_FSL_ESDHC
	fdt_fixup_esdhc(blob, bd);
#endif

#ifdef CONFIG_SYS_DPAA_FMAN
	fdt_fixup_fman_firmware(blob);
#endif
	fsl_fdt_disable_usb(blob);

}
