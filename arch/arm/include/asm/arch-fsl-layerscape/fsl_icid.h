/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2018 NXP
 */

#ifndef _FSL_ICID_H_
#define _FSL_ICID_H_

#include <asm/types.h>
#include <fsl_qbman.h>

struct icid_id_table {
	const char *compat;
	u32 id;
	u32 reg;
	phys_addr_t compat_addr;
	phys_addr_t reg_addr;
};

struct fman_icid_id_table {
	u32 port_id;
	u32 icid;
};

u32 get_ppid_icid(int ppid_tbl_idx, int ppid);
int fdt_get_smmu_phandle(void *blob);
int fdt_set_iommu_prop(void *blob, int off, int smmu_ph, u32 *ids, int num_ids);
void set_icids(void);
void fdt_fixup_icid(void *blob);

#define SET_ICID_ENTRY(name, idA, regA, addr, compataddr) \
	{ .compat = name, \
	  .id = idA, \
	  .reg = regA, \
	  .compat_addr = compataddr, \
	  .reg_addr = addr, \
	}

#define SET_SCFG_ICID(compat, streamid, name, compataddr) \
	SET_ICID_ENTRY(compat, streamid, (((streamid) << 24) | (1 << 23)), \
		offsetof(struct ccsr_scfg, name) + CONFIG_SYS_FSL_SCFG_ADDR, \
		compataddr)

#define SET_USB_ICID(usb_num, compat, streamid) \
	SET_SCFG_ICID(compat, streamid, usb##usb_num##_icid,\
		CONFIG_SYS_XHCI_USB##usb_num##_ADDR)

#define SET_SATA_ICID(compat, streamid) \
	SET_SCFG_ICID(compat, streamid, sata_icid,\
		AHCI_BASE_ADDR)

#define SET_SDHC_ICID(streamid) \
	SET_SCFG_ICID("fsl,esdhc", streamid, sdhc_icid,\
		CONFIG_SYS_FSL_ESDHC_ADDR)

#define SET_QDMA_ICID(compat, streamid) \
	SET_SCFG_ICID(compat, streamid, dma_icid,\
		QDMA_BASE_ADDR)

#define SET_EDMA_ICID(streamid) \
	SET_SCFG_ICID("fsl,vf610-edma", streamid, edma_icid,\
		EDMA_BASE_ADDR)

#define SET_ETR_ICID(streamid) \
	SET_SCFG_ICID(NULL, streamid, etr_icid, 0)

#define SET_DEBUG_ICID(streamid) \
	SET_SCFG_ICID(NULL, streamid, debug_icid, 0)

#define SET_QMAN_ICID(streamid) \
	SET_ICID_ENTRY("fsl,qman", streamid, streamid, \
		offsetof(struct ccsr_qman, liodnr) + \
		CONFIG_SYS_FSL_QMAN_ADDR, \
		CONFIG_SYS_FSL_QMAN_ADDR)

#define SET_BMAN_ICID(streamid) \
	SET_ICID_ENTRY("fsl,bman", streamid, streamid, \
		offsetof(struct ccsr_bman, liodnr) + \
		CONFIG_SYS_FSL_BMAN_ADDR, \
		CONFIG_SYS_FSL_BMAN_ADDR)

#define SET_FMAN_ICID_ENTRY(_port_id, streamid) \
	{ .port_id = (_port_id), .icid = (streamid) }

extern struct icid_id_table icid_tbl[];
extern struct fman_icid_id_table fman_icid_tbl[];
extern int icid_tbl_sz;
extern int fman_icid_tbl_sz;

#endif
