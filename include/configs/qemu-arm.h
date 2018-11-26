/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2017 Tuomas Tynkkynen
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <linux/sizes.h>

/* Physical memory map */

#define CONFIG_SYS_SDRAM_BASE		0x40000000

/* The DTB generated by QEMU is placed at start of RAM, stay away from there */
#define CONFIG_SYS_INIT_SP_ADDR         (CONFIG_SYS_SDRAM_BASE + SZ_2M)
#define CONFIG_SYS_LOAD_ADDR		(CONFIG_SYS_SDRAM_BASE + SZ_2M)
#define CONFIG_SYS_MALLOC_LEN		SZ_16M

/* For timer, QEMU emulates an ARMv7/ARMv8 architected timer */
#define CONFIG_SYS_HZ                       1000

/* Environment options */
#define CONFIG_ENV_ADDR			0x4000000
#define CONFIG_ENV_SIZE			SZ_256K

#define BOOT_TARGET_DEVICES(func) \
	func(SCSI, scsi, 0) \
	func(VIRTIO, virtio, 0) \
	func(DHCP, dhcp, na)

#include <config_distro_bootcmd.h>

#define CONFIG_PREBOOT "pci enum"
#define CONFIG_EXTRA_ENV_SETTINGS \
	"fdt_high=0xffffffff\0" \
	"initrd_high=0xffffffff\0" \
	"fdt_addr=0x40000000\0" \
	"scriptaddr=0x40200000\0" \
	"pxefile_addr_r=0x40300000\0" \
	"kernel_addr_r=0x40400000\0" \
	"ramdisk_addr_r=0x44000000\0" \
	BOOTENV

#define CONFIG_SYS_CBSIZE 512

#define CONFIG_SYS_MONITOR_BASE		CONFIG_SYS_TEXT_BASE
#define CONFIG_SYS_FLASH_BASE		0x0
#define CONFIG_SYS_MAX_FLASH_BANKS	2
#define CONFIG_SYS_MAX_FLASH_SECT	256 /* Sector: 256K, Bank: 64M */

#endif /* __CONFIG_H */
