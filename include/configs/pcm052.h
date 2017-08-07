/*
 * Copyright 2013 Freescale Semiconductor, Inc.
 *
 * Configuration settings for the phytec PCM-052 SoM.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <asm/arch/imx-regs.h>

#define CONFIG_SKIP_LOWLEVEL_INIT

/* Enable passing of ATAGs */
#define CONFIG_CMDLINE_TAG

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + 2 * 1024 * 1024)

/* Allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

/* NAND support */
#define CONFIG_SYS_NAND_ONFI_DETECTION

#ifdef CONFIG_CMD_NAND
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_BASE		NFC_BASE_ADDR

#define CONFIG_JFFS2_NAND

/* Dynamic MTD partition support */
#define CONFIG_MTD_PARTITIONS
#define CONFIG_MTD_DEVICE

#ifndef MTDIDS_DEFAULT
#define MTDIDS_DEFAULT			"nand0=NAND"
#endif

#ifndef MTDPARTS_DEFAULT
#define MTDPARTS_DEFAULT		"mtdparts=NAND:640k(bootloader)"\
					",128k(env1)"\
					",128k(env2)"\
					",128k(dtb)"\
					",6144k(kernel)"\
					",-(root)"
#endif

#endif

#define CONFIG_FSL_ESDHC
#define CONFIG_SYS_FSL_ESDHC_ADDR	0
#define CONFIG_SYS_FSL_ESDHC_NUM	1

/*#define CONFIG_ESDHC_DETECT_USE_EXTERN_IRQ1*/

#define CONFIG_FEC_MXC
#define CONFIG_MII
#define IMX_FEC_BASE			ENET_BASE_ADDR
#define CONFIG_FEC_XCV_TYPE		RMII
#define CONFIG_FEC_MXC_PHYADDR          0

/* QSPI Configs*/

#ifdef CONFIG_FSL_QSPI
#define FSL_QSPI_FLASH_SIZE		(1 << 24)
#define FSL_QSPI_FLASH_NUM		2
#define CONFIG_SYS_FSL_QSPI_LE
#endif

/* I2C Configs */
#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_MXC_I2C3
#define CONFIG_SYS_I2C_MXC

/* RTC (actually an RV-4162 but M41T62-compatible) */
#define CONFIG_RTC_M41T62
#define CONFIG_SYS_I2C_RTC_ADDR 0x68
#define CONFIG_SYS_RTC_BUS_NUM 2

/* EEPROM (24FC256) */
#define CONFIG_SYS_I2C_EEPROM_ADDR 0x50
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN 2
#define CONFIG_SYS_I2C_EEPROM_BUS 2


#define CONFIG_LOADADDR			0x82000000

/* We boot from the gfxRAM area of the OCRAM. */
#define CONFIG_SYS_TEXT_BASE		0x3f408000
#define CONFIG_BOARD_SIZE_LIMIT		524288

/* if no target-specific extra environment settings were defined by the
   target, define an empty one */
#ifndef PCM052_EXTRA_ENV_SETTINGS
#define PCM052_EXTRA_ENV_SETTINGS
#endif

/* if no target-specific boot command was defined by the target,
   define an empty one */
#ifndef PCM052_BOOTCOMMAND
#define PCM052_BOOTCOMMAND
#endif

/* if no target-specific extra environment settings were defined by the
   target, define an empty one */
#ifndef PCM052_NET_INIT
#define PCM052_NET_INIT
#endif

/* boot command, including the target-defined one if any */
#define CONFIG_BOOTCOMMAND	PCM052_BOOTCOMMAND "run bootcmd_nand"

/* Extra env settings (including the target-defined ones if any) */
#define CONFIG_EXTRA_ENV_SETTINGS \
	PCM052_EXTRA_ENV_SETTINGS \
	"autoload=no\0" \
	"fdt_high=0xffffffff\0" \
	"initrd_high=0xffffffff\0" \
	"blimg_file=u-boot.vyb\0" \
	"blimg_addr=0x81000000\0" \
	"kernel_file=zImage\0" \
	"kernel_addr=0x82000000\0" \
	"fdt_file=zImage.dtb\0" \
	"fdt_addr=0x81000000\0" \
	"ram_file=uRamdisk\0" \
	"ram_addr=0x83000000\0" \
	"filesys=rootfs.ubifs\0" \
	"sys_addr=0x81000000\0" \
	"tftploc=/path/to/tftp/directory/\0" \
	"nfs_root=/path/to/nfs/root\0" \
	"tftptimeout=1000\0" \
	"tftptimeoutcountmax=1000000\0" \
	"mtdparts=" MTDPARTS_DEFAULT "\0" \
	"bootargs_base=setenv bootargs rw " \
		" mem=" __stringify(CONFIG_PCM052_DDR_SIZE) "M " \
		"console=ttyLP1,115200n8\0" \
	"bootargs_sd=setenv bootargs ${bootargs} " \
		"root=/dev/mmcblk0p2 rootwait\0" \
	"bootargs_net=setenv bootargs ${bootargs} root=/dev/nfs ip=dhcp " \
		"nfsroot=${serverip}:${nfs_root},v3,tcp\0" \
	"bootargs_nand=setenv bootargs ${bootargs} " \
		"ubi.mtd=5 rootfstype=ubifs root=ubi0:rootfs\0" \
	"bootargs_ram=setenv bootargs ${bootargs} " \
		"root=/dev/ram rw initrd=${ram_addr}\0" \
	"bootargs_mtd=setenv bootargs ${bootargs} ${mtdparts}\0" \
	"bootcmd_sd=run bootargs_base bootargs_sd bootargs_mtd; " \
		"fatload mmc 0:1 ${kernel_addr} ${kernel_file}; " \
		"fatload mmc 0:1 ${fdt_addr} ${fdt_file}; " \
		"bootz ${kernel_addr} - ${fdt_addr}\0" \
	"bootcmd_net=run bootargs_base bootargs_net bootargs_mtd; " \
		"tftpboot ${kernel_addr} ${tftpdir}${kernel_file}; " \
		"tftpboot ${fdt_addr} ${tftpdir}${fdt_file}; " \
		"bootz ${kernel_addr} - ${fdt_addr}\0" \
	"bootcmd_nand=run bootargs_base bootargs_nand bootargs_mtd; " \
		"nand read ${fdt_addr} dtb; " \
		"nand read ${kernel_addr} kernel; " \
		"bootz ${kernel_addr} - ${fdt_addr}\0" \
	"bootcmd_ram=run bootargs_base bootargs_ram bootargs_mtd; " \
		"nand read ${fdt_addr} dtb; " \
		"nand read ${kernel_addr} kernel; " \
		"nand read ${ram_addr} root; " \
		"bootz ${kernel_addr} ${ram_addr} ${fdt_addr}\0" \
	"update_bootloader_from_tftp=" PCM052_NET_INIT \
		"if tftp ${blimg_addr} "\
		"${tftpdir}${blimg_file}; then " \
		"mtdparts default; " \
		"nand erase.part bootloader; " \
		"nand write ${blimg_addr} bootloader ${filesize}; fi\0" \
	"update_kernel_from_sd=if fatload mmc 0:2 ${kernel_addr} " \
		"${kernel_file}; " \
		"then mtdparts default; " \
		"nand erase.part kernel; " \
		"nand write ${kernel_addr} kernel ${filesize}; " \
		"if fatload mmc 0:2 ${fdt_addr} ${fdt_file}; then " \
		"nand erase.part dtb; " \
		"nand write ${fdt_addr} dtb ${filesize}; fi\0" \
	"update_kernel_from_tftp=" PCM052_NET_INIT \
		"if tftp ${fdt_addr} ${tftpdir}${fdt_file}; " \
		"then setenv fdtsize ${filesize}; " \
		"if tftp ${kernel_addr} ${tftpdir}${kernel_file}; then " \
		"mtdparts default; " \
		"nand erase.part dtb; " \
		"nand write ${fdt_addr} dtb ${fdtsize}; " \
		"nand erase.part kernel; " \
		"nand write ${kernel_addr} kernel ${filesize}; fi; fi\0" \
	"update_rootfs_from_tftp=" PCM052_NET_INIT \
		"if tftp ${sys_addr} ${tftpdir}${filesys}; " \
		"then mtdparts default; " \
		"nand erase.part root; " \
		"ubi part root; " \
		"ubi create rootfs; " \
		"ubi write ${sys_addr} rootfs ${filesize}; fi\0" \
	"update_ramdisk_from_tftp=" PCM052_NET_INIT \
		"if tftp ${ram_addr} ${tftpdir}${ram_file}; " \
		"then mtdparts default; " \
		"nand erase.part root; " \
		"nand write ${ram_addr} root ${filesize}; fi\0"

/* Miscellaneous configurable options */
#define CONFIG_SYS_LONGHELP		/* undef to save memory */
#define CONFIG_AUTO_COMPLETE
#define CONFIG_CMDLINE_EDITING
#define CONFIG_SYS_CBSIZE		256	/* Console I/O Buffer Size */
#define CONFIG_SYS_PBSIZE		\
			(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS		16	/* max number of command args */
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE

#define CONFIG_SYS_MEMTEST_START	0x80010000
#define CONFIG_SYS_MEMTEST_END		0x87C00000

#define CONFIG_SYS_LOAD_ADDR		CONFIG_LOADADDR

/* Physical memory map */
#define CONFIG_NR_DRAM_BANKS		1
#define PHYS_SDRAM			(0x80000000)
#define PHYS_SDRAM_SIZE			(CONFIG_PCM052_DDR_SIZE * 1024 * 1024)

#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE	IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* environment organization */
#ifdef CONFIG_ENV_IS_IN_MMC
#define CONFIG_ENV_SIZE			(8 * 1024)

#define CONFIG_ENV_OFFSET		(12 * 64 * 1024)
#define CONFIG_SYS_MMC_ENV_DEV		0
#endif

#ifdef CONFIG_ENV_IS_IN_NAND
#define CONFIG_ENV_SECT_SIZE		(128 * 1024)
#define CONFIG_ENV_SIZE			(8 * 1024)
#define CONFIG_ENV_OFFSET		0xA0000
#define CONFIG_ENV_SIZE_REDUND		(8 * 1024)
#define CONFIG_ENV_OFFSET_REDUND	0xC0000
#endif

#endif
