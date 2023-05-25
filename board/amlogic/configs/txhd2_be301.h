/* SPDX-License-Identifier: (GPL-2.0+ OR MIT) */
/*
 * board/amlogic/configs/txhd2_be301.h
 *
 * Copyright (C) 2020 Amlogic, Inc. All rights reserved.
 *
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <asm/arch/cpu.h>

#define CONFIG_SYS_GENERIC_BOARD  1
#ifndef CONFIG_AML_MESON
#warning "include warning"
#endif

/*
 * platform power init config
 */
#define CONFIG_PLATFORM_POWER_INIT
#define CONFIG_VCCK_INIT_VOLTAGE	960		// VCCK power up voltage
#define CONFIG_VDDEE_INIT_VOLTAGE	840		// VDDEE power up voltage
#define CONFIG_VDDEE_SLEEP_VOLTAGE	770		// VDDEE suspend voltage

/* configs for CEC */
#define CONFIG_CEC_OSD_NAME		"AML_TV"
#define CONFIG_CEC_WAKEUP
/*if use bt-wakeup,open it*/
#define CONFIG_BT_WAKEUP
/*if use wifi-wakeup,open it*/
//#define CONFIG_WIFI_WAKEUP
/* SMP Definitions */
#define CPU_RELEASE_ADDR		secondary_boot_func

/* config saradc*/
//#define CONFIG_CMD_SARADC 1
//#define CONFIG_SARADC_CH  2

/*dsp boot*/
//#define CONFIG_CMD_STARTDSP 1
//#define CONFIG_CMD_DSPJTAGRESET 1

#define CONFIG_FAT_WRITE 1
//#define CONFIG_AML_FACTORY_PROVISION 1

#define CONFIG_AML_WATERMARK 1

/* Bootloader Control Block function
   That is used for recovery and the bootloader to talk to each other
  */
//#define CONFIG_BOOTLOADER_CONTROL_BLOCK

/*a/b update */
//#define CONFIG_CMD_BOOTCTOL_AVB

/* Serial config */
#define CONFIG_CONS_INDEX 2
#define CONFIG_BAUDRATE  115200
#define CONFIG_AML_MESON_SERIAL   1
#define CONFIG_SERIAL_MULTI		1

//Enable ir remote wake up for bl30
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL1 0xef10fe01 //amlogic tv ir --- power
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL2 0XBB44FB04 //amlogic tv ir --- ch+
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL3 0xF20DFE01 //amlogic tv ir --- ch-
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL4 0XBA45BD02 //amlogic small ir--- power
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL5 0xe51afb04
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL6 0xFFFFFFFF
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL7 0xFFFFFFFF
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL8 0xFFFFFFFF
#define CONFIG_IR_REMOTE_POWER_UP_KEY_VAL9 0xFFFFFFFF

/*config the default parameters for adc power key*/
#define CONFIG_ADC_POWER_KEY_CHAN   2  /*channel range: 0-7*/
#define CONFIG_ADC_POWER_KEY_VAL    0  /*sample value range: 0-1023*/

#define CONFIG_SILENT_CONSOLE
/* args/envs */
#define CONFIG_SYS_MAXARGS  64
#define CONFIG_EXTRA_ENV_SETTINGS \
        "firstboot=1\0"\
        "upgrade_step=0\0"\
        "jtag=disable\0"\
        "loadaddr=1080000\0"\
		"model_name=FHD2HDMI\0" \
		"panel_type=mipi_0\0" \
		"panel_name=null\0" \
		"lcd_ctrl=0x00000000\0" \
		"outputmode=panel\0" \
        "hdmimode=1080p60hz\0" \
        "cvbsmode=576cvbs\0" \
	"vout_init=disable\0" \
	"connector_type=LVDS-A\0" \
        "display_width=1920\0" \
        "display_height=1080\0" \
        "display_bpp=16\0" \
        "display_color_index=16\0" \
        "display_layer=osd0\0" \
        "display_color_fg=0xffff\0" \
        "display_color_bg=0\0" \
	"dtb_mem_addr=0x1000000\0" \
        "fb_addr=0x1f800000\0" \
        "fb_width=1920\0" \
        "fb_height=1080\0" \
        "frac_rate_policy=1\0" \
        "usb_burning=adnl 2000\0" \
        "otg_device=1\0"\
        "fdt_high=0x20000000\0"\
        "try_auto_burn=adnl 1000 1500;\0"\
        "sdcburncfg=aml_sdc_burn.ini\0"\
        "sdc_burning=sdc_burn ${sdcburncfg}\0"\
        "wipe_data=successful\0"\
        "wipe_cache=successful\0"\
        "EnableSelinux=enforcing\0" \
        "recovery_part=recovery\0"\
        "recovery_offset=0\0"\
        "cvbs_drv=0\0"\
	"lock=10101000\0"\
        "osd_reverse=0\0"\
        "video_reverse=0\0"\
        "active_slot=normal\0"\
        "boot_part=boot\0"\
	"rollback_flag=0\0"\
	"boot_flag=0\0"\
        "vendor_boot_part=vendor_boot\0"\
        "suspend=off\0"\
        "powermode=on\0"\
        "ffv_wake=off\0"\
        "ffv_freeze=off\0"\
        "edid_14_dir=/odm/etc/tvconfig/hdmi/port_14.bin\0" \
        "edid_20_dir=/odm/etc/tvconfig/hdmi/port_20.bin\0" \
        "edid_14_dir_dynamic=/odm_ext/etc/tvconfig/hdmi/port_14.bin\0" \
        "edid_20_dir_dynamic=/odm_ext/etc/tvconfig/hdmi/port_20.bin\0" \
        "edid_select=0\0" \
        "port_map=0x4321\0" \
        "cec_fun=0x2F\0" \
        "logic_addr=0x0\0" \
        "cec_ac_wakeup=1\0" \
        "Irq_check_en=0\0"\
        "fs_type=""rootfstype=ramfs""\0"\
	"disable_ir=0\0"\
	"check_connector_type="\
		"setenv bootconfig ${bootconfig} androidboot.connector_type=${connector_type};"\
		"\0"\
        "initargs="\
			"init=/init console=ttyS0,115200 no_console_suspend earlycon=aml-uart,0xffd23000 "\
			"printk.devkmsg=on ramoops.pstore_en=1 ramoops.record_size=0x8000 "\
			"ramoops.console_size=0x4000 loop.max_part=4 scramble_reg=0xff6345c4 "\
            "\0"\
        "upgrade_check="\
            "echo upgrade_step=${upgrade_step}; "\
            "if itest ${upgrade_step} == 3; then "\
                "run init_display; run storeargs; run update;"\
            "else fi;"\
            "\0"\
        "storeargs="\
            "get_bootloaderversion;" \
			"setenv bootargs ${initargs} otg_device=${otg_device} logo=${display_layer},loaded,${fb_addr} powermode=${powermode} fb_width=${fb_width} fb_height=${fb_height} display_bpp=${display_bpp} outputmode=${outputmode} vout=${outputmode},${vout_init} panel_name=${panel_name} panel_type=${panel_type} lcd_ctrl=${lcd_ctrl} hdmimode=${hdmimode} cvbsmode=${cvbsmode} osd_reverse=${osd_reverse} video_reverse=${video_reverse} androidboot.selinux=${EnableSelinux} androidboot.firstboot=${firstboot} jtag=${jtag} mem_size=${mem_size} disable_ir=${disable_ir};"\
	"setenv bootargs ${bootargs} androidboot.hardware=amlogic androidboot.bootloader=${bootloader_version} androidboot.build.expect.baseband=N/A;"\
	"setenv bootargs ${bootargs} androidboot.memsize=${memsize};"\
		"run check_connector_type; "\
            "run cmdline_keys;"\
            "\0"\
        "cec_init="\
            "echo cec_ac_wakeup=${cec_ac_wakeup}; "\
            "if test ${cec_ac_wakeup} = 1; then "\
                "cec ${logic_addr} ${cec_fun}; "\
                "if test ${edid_select} = 1111; then "\
					"if test ${partition_mode} = dynamic; then " \
                        "hdmirx init ${port_map} ${edid_20_dir_dynamic}; "\
                    "else "\
                        "hdmirx init ${port_map} ${edid_20_dir}; "\
                    "fi;"\
                "else "\
                    "if test ${vendor_boot_mode} = true; then " \
                        "hdmirx init ${port_map} ${edid_14_dir_dynamic}; "\
                    "else "\
                        "hdmirx init ${port_map} ${edid_14_dir}; "\
                    "fi;"\
                "fi;"\
            "fi;"\
            "\0"\
        "ffv_freeze_action="\
            "run cec_init;"\
            "setenv ffv_freeze on;"\
            "setenv bootargs ${bootargs} ffv_freeze=on"\
            "\0"\
        "cold_boot_normal_check="\
            "setenv bootargs ${bootargs} ffv_freeze=off; "\
            /*"run try_auto_burn;uboot wake up "*/\
            "if test ${powermode} = on; then "\
                /*"run try_auto_burn; "*/\
            "else if test ${powermode} = standby; then "\
                "run cec_init;"\
                "systemoff; "\
            "else if test ${powermode} = last; then "\
               "echo suspend=${suspend}; "\
                "if test ${suspend} = off; then "\
                    /*"run try_auto_burn; "*/\
                "else if test ${suspend} = on; then "\
                    "run cec_init;"\
                    "systemoff; "\
                "else if test ${suspend} = shutdown; then "\
                    "run cec_init;"\
                    "systemoff; "\
                "fi; fi; fi; "\
            "fi; fi; fi; "\
            "\0"\
        "switch_bootmode="\
            "get_rebootmode;"\
            "setenv ffv_freeze off;"\
            "if test ${reboot_mode} = factory_reset; then "\
                    "run recovery_from_flash;"\
            "else if test ${reboot_mode} = update; then "\
                    "run update;"\
            "else if test ${reboot_mode} = quiescent; then "\
                    "setenv bootargs ${bootargs} androidboot.quiescent=1;"\
            "else if test ${reboot_mode} = recovery_quiescent; then "\
                    "setenv bootargs ${bootargs} androidboot.quiescent=1;"\
                    "run recovery_from_flash;"\
            "else if test ${reboot_mode} = cold_boot; then "\
                "echo cold boot: ffv_wake=${ffv_wake} powermode=${powermode} suspend=${suspend};"\
                "if test ${ffv_wake} = on; then "\
                    "if test ${powermode} = on; then "\
                        "setenv bootargs ${bootargs} ffv_freeze=off; "\
                    "else if test ${powermode} = standby; then "\
                        "run ffv_freeze_action; "\
                    "else if test ${powermode} = last; then "\
                        "if test ${suspend} = off; then "\
                            "setenv bootargs ${bootargs} ffv_freeze=off; "\
                        "else if test ${suspend} = on; then "\
                            "run ffv_freeze_action; "\
                        "else if test ${suspend} = shutdown; then "\
                            "run ffv_freeze_action; "\
                        "fi; fi; fi; "\
                    "fi; fi; fi; "\
                "else "\
                    "run cold_boot_normal_check;"\
                "fi; "\
            "else if test ${reboot_mode} = ffv_reboot; then "\
                "if test ${ffv_wake} = on; then "\
                    "run ffv_freeze_action; "\
                "fi; "\
            "else if test ${reboot_mode} = fastboot; then "\
                "fastboot;"\
            "fi;fi;fi;fi;fi;fi;fi;"\
            "\0" \
        "reset_suspend="\
            "if test ${ffv_freeze} != on; then "\
                "if test ${suspend} = on || test ${suspend} = shutdown; then "\
                    "setenv ""suspend off"";"\
                    "saveenv;"\
                "fi;"\
            "fi;"\
            "\0" \
        "enter_fastboot="\
            "fastboot 0;"\
            "\0"\
        "storeboot="\
            "if test ${reboot_mode} = normal; then "\
            "else if test ${reboot_mode} = cold_boot; then "\
            "else "\
                "boot_cooling;"\
            "fi;fi;"\
            "get_system_as_root_mode;"\
            "echo system_mode: ${system_mode};"\
            "get_avb_mode;"\
            "echo active_slot: ${active_slot};"\
            "if test ${system_mode} = 1; then "\
                "setenv bootargs ${bootargs} ro rootwait skip_initramfs;"\
            "else "\
                "setenv bootargs ${bootargs} androidboot.force_normal_boot=1;"\
            "fi;"\
            "if test ${active_slot} != normal; then "\
                    "setenv bootargs ${bootargs} androidboot.slot_suffix=${active_slot};"\
            "fi;"\
            "if test ${avb2} = 0; then "\
                "if test ${active_slot} = _a; then "\
                    "setenv bootargs ${bootargs} root=/dev/mmcblk0p23;"\
                "else if test ${active_slot} = _b; then "\
                    "setenv bootargs ${bootargs} root=/dev/mmcblk0p24;"\
                "fi;fi;"\
            "fi;"\
	    "setenv bootargs ${bootargs} androidboot.rollback=${rollback_flag};"\
            "if imgread kernel ${boot_part} ${loadaddr}; then bootm ${loadaddr}; fi;"\
            "run update;"\
            "\0"\
        "factory_reset_poweroff_protect="\
            "echo wipe_data=${wipe_data}; echo wipe_cache=${wipe_cache};"\
            "if test ${wipe_data} = failed; then "\
                "run init_display; run storeargs;"\
                "if mmcinfo; then "\
                    "run recovery_from_sdcard;"\
                "fi;"\
                "if usb start 0; then "\
                    "run recovery_from_udisk;"\
                "fi;"\
                "run recovery_from_flash;"\
            "fi; "\
            "if test ${wipe_cache} = failed; then "\
                "run init_display; run storeargs;"\
                "if mmcinfo; then "\
                    "run recovery_from_sdcard;"\
                "fi;"\
                "if usb start 0; then "\
                    "run recovery_from_udisk;"\
                "fi;"\
                "run recovery_from_flash;"\
            "fi; \0" \
         "update="\
            /*first usb burning, second sdc_burn, third ext-sd autoscr/recovery, last udisk autoscr/recovery*/\
            "run usb_burning; "\
            "run sdc_burning; "\
            "if mmcinfo; then "\
                "run recovery_from_sdcard;"\
            "fi;"\
            "if usb start 0; then "\
                "run recovery_from_udisk;"\
            "fi;"\
            "run recovery_from_flash;"\
            "\0"\
        "recovery_from_sdcard="\
            "if fatload mmc 0 ${loadaddr} aml_autoscript; then autoscr ${loadaddr}; fi;"\
            "if fatload mmc 0 ${loadaddr} recovery.img; then "\
                    "if fatload mmc 0 ${dtb_mem_addr} dtb.img; then echo sd dtb.img loaded; fi;"\
                    "wipeisb; "\
                    "bootm ${loadaddr};fi;"\
            "\0"\
        "recovery_from_udisk="\
            "if fatload usb 0 ${loadaddr} aml_autoscript; then autoscr ${loadaddr}; fi;"\
            "if fatload usb 0 ${loadaddr} recovery.img; then "\
                "if fatload usb 0 ${dtb_mem_addr} dtb.img; then echo udisk dtb.img loaded; fi;"\
                "wipeisb; "\
                "bootm ${loadaddr};fi;"\
            "\0"\
        "recovery_from_flash="\
            "echo active_slot: ${active_slot};"\
            "if test ${active_slot} = normal; then "\
                "setenv bootargs ${bootargs} ${fs_type} aml_dt=${aml_dt} recovery_part=${recovery_part} recovery_offset=${recovery_offset};"\
				"if test ${upgrade_step} = 3; then "\
                    "if ext4load mmc 1:2 ${dtb_mem_addr} /recovery/dtb.img; then echo cache dtb.img loaded; fi;"\
					"if test ${vendor_boot_mode} = true; then "\
						"if imgread kernel ${recovery_part} ${loadaddr} ${recovery_offset}; then bootm ${loadaddr}; fi;"\
					"else "\
                    "if ext4load mmc 1:2 ${loadaddr} /recovery/recovery.img; then echo cache recovery.img loaded; wipeisb; bootm ${loadaddr}; fi;"\
					"fi;"\
                "else fi;"\
                "if imgread kernel ${recovery_part} ${loadaddr} ${recovery_offset}; then wipeisb; bootm ${loadaddr}; fi;"\
            "else "\
				"if test ${partition_mode} = normal; then "\
                    "setenv bootargs ${bootargs} ${fs_type} aml_dt=${aml_dt} recovery_part=${boot_part} recovery_offset=${recovery_offset};"\
                    "if imgread kernel ${boot_part} ${loadaddr}; then bootm ${loadaddr}; fi;"\
                "else "\
                    "if test ${vendor_boot_mode} = true; then "\
                        "setenv bootargs ${bootargs} ${fs_type} aml_dt=${aml_dt} recovery_part=${boot_part} recovery_offset=${recovery_offset} androidboot.slot_suffix=${active_slot};"\
                        "if imgread kernel ${boot_part} ${loadaddr}; then bootm ${loadaddr}; fi;"\
                    "else "\
                        "setenv bootargs ${bootargs} ${fs_type} aml_dt=${aml_dt} recovery_part=${recovery_part} recovery_offset=${recovery_offset} androidboot.slot_suffix=${active_slot};"\
                    "if imgread kernel ${recovery_part} ${loadaddr} ${recovery_offset}; then wipeisb; bootm ${loadaddr}; fi;"\
                    "fi;"\
                "fi;"\
            "fi;"\
            "\0"\
        "init_display="\
		"watermark_init;osd open;osd clear;imgread pic logo bootup $loadaddr;bmp display $bootup_offset;bmp scale;vout output ${outputmode}"\
            "\0"\
        "check_display="\
            "if test ${reboot_mode} = cold_boot; then "\
                "if test ${powermode} = standby; then "\
                    "echo not init_display; "\
                "else if test ${powermode} = last; then "\
                    "echo suspend=${suspend}; "\
                    "if test ${suspend} = off; then "\
                        "run init_display; "\
                    "else if test ${suspend} = on; then "\
                        "echo not init_display; "\
                    "else if test ${suspend} = shutdown; then "\
                        "echo not init_display; "\
                    "fi; fi; fi; "\
                "else "\
                    "run init_display; "\
                "fi; fi; "\
            "else if test ${reboot_mode} = ffv_reboot; then "\
                "if test ${ffv_wake} = on; then "\
                    "echo ffv reboot no display; "\
                "else "\
                    "run init_display; "\
                "fi; "\
            "else "\
                "run init_display; "\
            "fi;fi; "\
            "\0"\
        "cmdline_keys="\
            "if keyman init 0x1234; then "\
                "if keyman read usid ${loadaddr} str; then "\
                    "setenv bootargs ${bootargs} androidboot.serialno=${usid};"\
                    "setenv serial ${usid};"\
                "else "\
                    "setenv bootargs ${bootargs} androidboot.serialno=at301${cpu_id};"\
                    "setenv serial at301${cpu_id};"\
                "fi;"\
                "if keyman read mac ${loadaddr} str; then "\
                    "setenv bootargs ${bootargs} mac=${mac} androidboot.mac=${mac};"\
                "fi;"\
                "if keyman read deviceid ${loadaddr} str; then "\
                    "setenv bootargs ${bootargs} androidboot.deviceid=${deviceid};"\
                "fi;"\
                "if keyman read oemkey ${loadaddr} str; then "\
                    "setenv bootargs ${bootargs} androidboot.oem.key1=${oemkey};"\
                "fi;"\
            "else "\
                "setenv bootargs ${bootargs} androidboot.serialno=at301${cpu_id};"\
                "setenv serial at301${cpu_id};"\
            "fi;"\
	    "factory_provision init;"\
            "\0"\
        "bcb_cmd="\
            "get_rebootmode;"\
            "get_valid_slot;"\
            "if test ${vendor_boot_mode} = true; then "\
		"setenv loadaddr 2080000;"\
		"setenv dtb_mem_addr 0x1000000;"\
            "fi;"\
            "\0"\
        "upgrade_key="\
            "if gpio input GPIOAO_3; then "\
			"echo detect upgrade key;"\
			"if test ${boot_flag} = 0; then "\
				"echo enter fastboot; setenv boot_flag 1; saveenv; fastboot;"\
			"else if test ${boot_flag} = 1; then "\
				"echo enter update; setenv boot_flag 2; saveenv; run update;"\
			"else "\
				"echo enter recovery; setenv boot_flag 0; saveenv; run recovery_from_flash;"\
			"fi;fi;"\
            "fi;"\
            "\0"\
	"irremote_update="\
		"if irkey 2500000 0xe31cfb04 0xb748fb04; then "\
			"echo read irkey ok!; " \
		"if itest ${irkey_value} == 0xe31cfb04; then " \
			"run update;" \
		"else if itest ${irkey_value} == 0xb748fb04; then " \
			"run update;\n" \
			"fi;fi;" \
		"fi;\0" \

#ifndef CONFIG_PXP_EMULATOR
#define CONFIG_PREBOOT  \
	"run bcb_cmd;"\
	"run factory_reset_poweroff_protect;"\
	"run upgrade_check;"\
	/* "run init_display;"\ */\
	"run check_display;"\
	"run storeargs;"\
	"bcb uboot-command;"\
	"run switch_bootmode;"\
	"run reset_suspend;"
//#define CONFIG_BOOTCOMMAND "run storeboot"
#else
#define CONFIG_PREBOOT  "echo preboot"
//#define CONFIG_BOOTCOMMAND "echo bootcomand"
#endif //CONFIG_PXP_EMULATOR

#define CONFIG_ENV_IS_NOWHERE  1

#ifndef CONFIG_PXP_EMULATOR
//#define CONFIG_ENV_IS_NOWHERE  1
#endif //CONFIG_PXP_EMULATOR
#define CONFIG_ENV_SIZE   (64*1024)
#define CONFIG_FIT 1
//#define CONFIG_OF_LIBFDT 1
#define CONFIG_ANDROID_BOOT_IMAGE 1
#define CONFIG_ANDROID_IMG 1
#define CONFIG_SYS_BOOTM_LEN (64<<20) /* Increase max gunzip size*/

/* cpu */
#define CONFIG_CPU_CLK					1512 //MHz. Range: 360-2000, should be multiple of 24

/*low console baudrate*/
#define CONFIG_LOW_CONSOLE_BAUD			0

/* ATTENTION */
/* DDR configs move to board/amlogic/[board]/firmware/timing.c */

//#define CONFIG_NR_DRAM_BANKS			1
/* ddr functions */
#if 0
//#define CONFIG_CMD_DDR_D2PLL			0 //0:disable, 1:enable. d2pll cmd
//#define CONFIG_CMD_DDR_TEST				0 //0:disable, 1:enable. ddrtest cmd
#define CONFIG_DDR_FULL_TEST			0 //0:disable, 1:enable. ddr full test
#define CONFIG_CMD_DDR_D2PLL			0 //0:disable, 1:enable. d2pll cmd
#define CONFIG_CMD_DDR_TEST				0 //0:disable, 1:enable. ddrtest cmd
#define CONFIG_DDR_LOW_POWER			0 //0:disable, 1:enable. ddr clk gate for lp
#define CONFIG_DDR_ZQ_PD				0 //0:disable, 1:enable. ddr zq power down
#define CONFIG_DDR_USE_EXT_VREF			0 //0:disable, 1:enable. ddr use external vref
#define CONFIG_DDR4_TIMING_TEST			0 //0:disable, 1:enable. ddr4 timing test function
#define CONFIG_DDR_PLL_BYPASS			0 //0:disable, 1:enable. ddr pll bypass function

#define DDR_FULL_TEST            0 //0:disable, 1:enable. ddr full test
#define DDR_LOW_POWER            0 //0:disable, 1:enable. ddr clk gate for lp
#define DDR_ZQ_PD                0 //0:disable, 1:enable. ddr zq power down
#define DDR_USE_EXT_VREF         0 //0:disable, 1:enable. ddr use external vref
#define DDR4_TIMING_TEST         0 //0:disable, 1:enable. ddr4 timing test function
#define DDR_PLL_BYPASS           0 //0:disable, 1:enable. ddr pll bypass function

#endif //CONFIG_PXP_EMULATOR

/* storage: emmc/nand/sd */
#if 0
#define		CONFIG_STORE_COMPATIBLE 1
#endif
#define 	CONFIG_ENV_OVERWRITE
//#define 	CONFIG_CMD_SAVEENV

#if (defined(CONFIG_ENV_IS_IN_AMLNAND) || defined(CONFIG_ENV_IS_IN_MMC)) && defined(CONFIG_STORE_COMPATIBLE)
#error env in amlnand/mmc already be compatible;
#endif

/*
*				storage
*		|---------|---------|
*		|					|
*		emmc<--Compatible-->nand
*					|-------|-------|
*					|				|
*					MTD<-Exclusive->NFTL
*/
/* axg only support slc nand */
/* swither for mtd nand which is for slc only. */
/* support for mtd */
/* support for nftl */
//#define CONFIG_AML_NAND	1

#if defined(CONFIG_AML_NAND) && defined(CONFIG_MESON_NFC)
#error CONFIG_AML_NAND/CONFIG_MESON_NFC can not support at the sametime;
#endif

#if (defined(CONFIG_AML_NAND) || defined(CONFIG_MESON_NFC)) && defined(CONFIG_MESON_FBOOT)
#error CONFIG_AML_NAND/CONFIG_MESON_NFC CONFIG _MESON_FBOOT can not support at the sametime;
/* bootloader is construct by bl2 and fip
 * when DISCRETE_BOOTLOADER is enabled, bl2 & fip
 * will not be stored continuously, and nand layout
 * would be bl2|rsv|fip|normal, but not
 * bl2|fip|rsv|normal anymore
 */

/* for bl2, restricted by romboot */
//#define CONFIG_BL2_COPY_NUM               4
#endif /* CONFIG_DISCRETE_BOOTLOADER */

//#define CONFIG_MTD_DEVICE y
/* mtd parts of ourown.*/
/* mtd parts by env default way.*/
/*
#define MTDIDS_NAME_STR		"aml_nand.0"
#define MTDIDS_DEFAULT		"nand1=" MTDIDS_NAME_STR
#define MTDPARTS_DEFAULT	"mtdparts=" MTDIDS_NAME_STR ":" \
					"3M@8192K(logo),"	\
					"10M(recovery),"	\
					"8M(kernel),"	\
					"40M(rootfs),"	\
					"-(data)"
*/
#if defined(CONFIG_SPI_NAND) && defined(CONFIG_MESON_NFC)
#error CONFIG_SPI_NAND/CONFIG_MESON_NFC can not support at the sametime;
#endif
/* endof CONFIG_AML_MTD */
/* #define		CONFIG_AML_SD_EMMC 1 */
#ifdef		CONFIG_AML_SD_EMMC
	#define 	CONFIG_GENERIC_MMC 1
	#define 	CONFIG_CMD_MMC 1
	#define CONFIG_CMD_GPT 1
	#define	CONFIG_SYS_MMC_ENV_DEV 1
	#define CONFIG_EMMC_DDR52_EN 0
	#define CONFIG_EMMC_DDR52_CLK 35000000

#endif
#define		CONFIG_PARTITIONS 1

#if 0
#define 	CONFIG_SYS_NO_FLASH  1

/* meson SPI */
//#define CONFIG_AML_SPIFC
//#define CONFIG_SPICC_SPINOR
#endif

	//#define CONFIG_DM_SPI
	//#define CONFIG_CMD_SPI
/* SPI flash config */
	//#define CONFIG_DM_SPI_FLASH
	//#define CONFIG_CMD_SF
	/* SPI flash support list */
	/* SPI nand flash support */
//	#define CONFIG_SPI_NAND
//	#define CONFIG_BL2_SIZE (64 * 1024)

#if defined CONFIG_MESON_NFC || defined CONFIG_SPI_NAND
	//#define CONFIG_MTD_DEVICE y
	#define CONFIG_SYS_MAX_NAND_DEVICE  2
#endif

/* vpu */
#define AML_VPU_CLK_LEVEL_DFT 5

/* VPP */
#define OSD_SCALE_ENABLE
#define AML_OSD_HIGH_VERSION

/* DISPLAY */
//#define CONFIG_AML_VOUT 1
#if 0
#define CONFIG_AML_CANVAS 1
#define CONFIG_AML_OSD 1
#define CONFIG_OSD_SCALE_ENABLE 1
#endif

/* USB
 * Enable CONFIG_MUSB_HCD for Host functionalities MSC, keyboard
 * Enable CONFIG_MUSB_UDD for Device functionalities.
 */
/* #define CONFIG_MUSB_UDC		1 */
/* #define CONFIG_CMD_USB 1 */
	//#define CONFIG_USB_XHCI_AMLOGIC_V2 1
	//#define CONFIG_USB_XHCI_AMLOGIC_USB3_V2		1

#define USB_PHY2_PLL_PARAMETER_1	0x09400414
#define USB_PHY2_PLL_PARAMETER_2	0x927e0000
#define USB_PHY2_PLL_PARAMETER_3	0xAC5F49E5

#define USB_G12x_PHY_PLL_SETTING_1	(0xfe18)
#define USB_G12x_PHY_PLL_SETTING_2	(0xfff)
#define USB_G12x_PHY_PLL_SETTING_3	(0x78000)
#define USB_G12x_PHY_PLL_SETTING_4	(0xe0004)
#define USB_G12x_PHY_PLL_SETTING_5	(0xe000c)
#define AML_TXLX_USB        1
//UBOOT fastboot config
#if 0
#define CONFIG_CMD_FASTBOOT 1
#define CONFIG_FASTBOOT_FLASH_MMC_DEV 1
#define CONFIG_FASTBOOT_FLASH 1
#define CONFIG_USB_GADGET 1
#define CONFIG_USBDOWNLOAD_GADGET 1

#define CONFIG_SYS_CACHELINE_SIZE 64
#define CONFIG_FASTBOOT_MAX_DOWN_SIZE	0x8000000
#define CONFIG_DEVICE_PRODUCT	"u200"
#endif

//UBOOT Factory usb/sdcard burning config
/* #define CONFIG_AML_V2_FACTORY_BURN              1       //support factory usb burning */
#if 0
#define CONFIG_AML_FACTORY_BURN_LOCAL_UPGRADE   1       //support factory sdcard burning
#define CONFIG_POWER_KEY_NOT_SUPPORTED_FOR_BURN 1       //There isn't power-key for factory sdcard burning
#define CONFIG_SD_BURNING_SUPPORT_UI            1       //Displaying upgrading progress bar when sdcard/udisk burning
#endif

#define CONFIG_AML_SECURITY_KEY                 1
#define CONFIG_UNIFY_KEY_MANAGE                 1

/* net */
/* #define CONFIG_CMD_NET   1 */
//#define CONFIG_ETH_DESIGNWARE
#if defined(CONFIG_CMD_NET)
	#define CONFIG_DESIGNWARE_ETH 1
	#define CONFIG_PHYLIB	1
	#define CONFIG_NET_MULTI 1
	#define CONFIG_CMD_PING 1
	#define CONFIG_CMD_DHCP 1
	#define CONFIG_CMD_RARP 1
	#define CONFIG_HOSTNAME        "arm_gxbb"
#if 0
	#define CONFIG_RANDOM_ETHADDR  1				   /* use random eth addr, or default */
#endif
	#define CONFIG_ETHADDR         00:15:18:01:81:31   /* Ethernet address */
	#define CONFIG_IPADDR          10.18.9.97          /* Our ip address */
	#define CONFIG_GATEWAYIP       10.18.9.1           /* Our getway ip address */
	#define CONFIG_SERVERIP        10.18.9.113         /* Tftp server ip address */
	#define CONFIG_NETMASK         255.255.255.0
#endif /* (CONFIG_CMD_NET) */

#define CONFIG_SHA1 1
#define CONFIG_MD5 1
#define CONFIG_AML_HW_SHA2

/* commands */
#if 0
#define CONFIG_CMD_CACHE 1
#define CONFIG_CMD_BOOTI 1
#define CONFIG_CMD_EFUSE 1
#define CONFIG_CMD_MEMORY 1
#define CONFIG_CMD_FAT 1
#define CONFIG_CMD_GPIO 1
//#define CONFIG_CMD_RUN
#define CONFIG_CMD_REBOOT 1
#define CONFIG_CMD_ECHO 1
#define CONFIG_CMD_JTAG	1
#define CONFIG_CMD_AUTOSCRIPT 1
#define CONFIG_CMD_MISC 1
#endif //CONFIG_PXP_EMULATOR

/*file system*/
#define CONFIG_DOS_PARTITION 1
#define CONFIG_EFI_PARTITION 1

#if 0
#define CONFIG_AML_PARTITION 1
#endif

//#define CONFIG_MMC 1
#define CONFIG_FS_FAT 1
#define CONFIG_FS_EXT4 1
#define CONFIG_LZO 1

#if 0
#define CONFIG_MDUMP_COMPRESS 1
//#define CONFIG_EXT4_WRITE 1
#endif //CONFIG_PXP_EMULATOR
//#define CONFIG_CMD_EXT4_WRITE 1

/* Cache Definitions */
//#define CONFIG_SYS_DCACHE_OFF
//#define CONFIG_SYS_ICACHE_OFF

/* other functions */
#if 0
#define CONFIG_NEED_BL301	1
#define CONFIG_NEED_BL32	1
#define CONFIG_CMD_RSVMEM	1
#define CONFIG_FIP_IMG_SUPPORT	1
//#define CONFIG_BOOTDELAY	0 //delay 0s
#define CONFIG_SYS_LONGHELP 1
#define CONFIG_CMD_MISC     1
#define CONFIG_CMD_ITEST    1
#define CONFIG_CMD_CPU_TEMP 1
#define CONFIG_CMD_LOADB    1
#endif

#define CONFIG_FIP_IMG_SUPPORT  1
#define CONFIG_CMD_INI 1
#define CONFIG_CMD_CEC 1
#define CONFIG_CMD_HDMIRX 1
//#define CONFIG_RX_RTERM		1
#define CONFIG_SYS_MEM_TOP_HIDE 0x08000000 //hide 128MB for kernel reserve
#define CONFIG_LIBAVB		1

#define CONFIG_CPU_ARMV8
#define CONFIG_MULTI_DTB    1

/* debug mode defines */
//#define CONFIG_DEBUG_MODE           1

//support secure boot
#define CONFIG_AML_SECURE_UBOOT   1

#if defined(CONFIG_AML_SECURE_UBOOT)

//for SRAM size limitation just disable NAND
//as the socket board default has no NAND
//#undef CONFIG_AML_NAND

//unify build for generate encrypted bootloader "u-boot.bin.encrypt"
#define CONFIG_AML_CRYPTO_UBOOT   1
//#define CONFIG_AML_SIGNED_UBOOT   1
//unify build for generate encrypted kernel image
//SRC : "board/amlogic/(board)/boot.img"
//DST : "fip/boot.img.encrypt"
//#define CONFIG_AML_CRYPTO_IMG       1

#endif //CONFIG_AML_SECURE_UBOOT

#define CONFIG_SECURE_STORAGE 1

/* USB port for MT7668. */

//build with uboot auto test
//#define CONFIG_AML_UBOOT_AUTO_TEST 1

//board customer ID
//#define CONFIG_CUSTOMER_ID  (0x6472616F624C4D41)

#if 0
#if defined(CONFIG_CUSTOMER_ID)
  #undef CONFIG_AML_CUSTOMER_ID
  #define CONFIG_AML_CUSTOMER_ID  CONFIG_CUSTOMER_ID
#endif
#endif

/* Choose One of Ethernet Type */
#undef CONFIG_ETHERNET_NONE
#define ETHERNET_INTERNAL_PHY
#undef ETHERNET_EXTERNAL_PHY

#if 0
#define CONFIG_CMD_AML_MTEST 1
#endif

#if defined(CONFIG_CMD_AML_MTEST)
#if !defined(CONFIG_SYS_MEM_TOP_HIDE)
#error CONFIG_CMD_AML_MTEST depends on CONFIG_SYS_MEM_TOP_HIDE;
#endif
#if !(CONFIG_SYS_MEM_TOP_HIDE)
#error CONFIG_SYS_MEM_TOP_HIDE should not be zero;
#endif
#endif

//to support TLV which can support to transfer info from BL2 to BL3X
//#define CONFIG_AML_SUPPORT_TLV

//DDR address to contain info from BL2 to BL3X
//#define  AML_BL2_TMASTER_DDR_ADDR  (0x3000000)

/* config ramdump to debug kernel panic */
#define CONFIG_FULL_RAMDUMP

#define CONFIG_AML_KASLR_SEED
#endif
