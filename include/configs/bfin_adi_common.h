/*
 * U-Boot - Common settings for Analog Devices boards
 */

#ifndef __CONFIG_BFIN_ADI_COMMON_H__
#define __CONFIG_BFIN_ADI_COMMON_H__

/*
 * Command Settings
 */
#ifndef _CONFIG_CMD_DEFAULT_H
# ifdef ADI_CMDS_NETWORK
#  define CONFIG_BOOTP_SUBNETMASK
#  define CONFIG_BOOTP_GATEWAY
#  define CONFIG_BOOTP_DNS
#  define CONFIG_BOOTP_NTPSERVER
#  define CONFIG_BOOTP_RANDOM_DELAY
#  define CONFIG_KEEP_SERVERADDR
#  ifdef CONFIG_BFIN_MAC
#   define CONFIG_CMD_MII
#  endif
# endif
# ifdef CONFIG_LIBATA
#  define CONFIG_CMD_FAT
#  define CONFIG_CMD_SATA
#  define CONFIG_DOS_PARTITION
# endif
# ifdef CONFIG_MMC
#  define CONFIG_CMD_EXT2
#  define CONFIG_CMD_FAT
#  define CONFIG_CMD_MMC
#  define CONFIG_DOS_PARTITION
#  define CONFIG_SYS_MMC_MAX_BLK_COUNT 127
# endif
# ifdef CONFIG_MMC_SPI
#  define CONFIG_CMD_MMC_SPI
# endif
# ifdef CONFIG_USB
#  define CONFIG_CMD_EXT2
#  define CONFIG_CMD_FAT
#  define CONFIG_CMD_USB_STORAGE
#  define CONFIG_DOS_PARTITION
# endif
# if defined(CONFIG_NAND_PLAT) || defined(CONFIG_DRIVER_NAND_BFIN)
#  define CONFIG_CMD_NAND
#  define CONFIG_CMD_NAND_LOCK_UNLOCK
# endif
# ifdef CONFIG_POST
#  define CONFIG_CMD_DIAG
# endif
# ifdef CONFIG_RTC_BFIN
#  define CONFIG_CMD_DATE
#  ifdef ADI_CMDS_NETWORK
#  endif
# endif
# ifdef CONFIG_SPI
#  define CONFIG_CMD_EEPROM
# endif
# if defined(CONFIG_SYS_I2C) || defined(CONFIG_SYS_I2C_SOFT)
#  define CONFIG_SOFT_I2C_READ_REPEATED_START
# endif
# ifndef CONFIG_SYS_NO_FLASH
#  define CONFIG_CMD_JFFS2
# endif
# ifdef CONFIG_CMD_JFFS2
#  define CONFIG_JFFS2_SUMMARY
# endif
# define CONFIG_CMD_BOOTLDR
# define CONFIG_CMD_CACHE
# define CONFIG_CMD_CPLBINFO
# define CONFIG_CMD_KGDB
# define CONFIG_CMD_LDRINFO
# define CONFIG_CMD_REGINFO
# define CONFIG_CMD_STRINGS
# if defined(__ADSPBF51x__) || defined(__ADSPBF52x__) || defined(__ADSPBF54x__)
#  define CONFIG_CMD_OTP
#  define CONFIG_CMD_SPIBOOTLDR
# endif
#endif

/*
 * Console Settings
 */
#define CONFIG_SYS_LONGHELP	1
#define CONFIG_CMDLINE_EDITING	1
#define CONFIG_AUTO_COMPLETE	1
#define CONFIG_LOADS_ECHO	1
#define CONFIG_JTAG_CONSOLE
#define CONFIG_SILENT_CONSOLE
#ifndef CONFIG_BAUDRATE
# define CONFIG_BAUDRATE	57600
#endif
#ifdef CONFIG_UART_CONSOLE
# define CONFIG_BFIN_SERIAL
#endif

/*
 * Debug Settings
 */
#define CONFIG_ENV_OVERWRITE	1
#define CONFIG_DEBUG_DUMP	1
#define CONFIG_KALLSYMS		1
#define CONFIG_PANIC_HANG	1

/*
 * Env Settings
 */
#ifndef CONFIG_BOOTDELAY
# if (CONFIG_BFIN_BOOT_MODE == BFIN_BOOT_UART)
#  define CONFIG_BOOTDELAY	-1
# else
#  define CONFIG_BOOTDELAY	5
# endif
#endif
#ifndef CONFIG_BOOTCOMMAND
# define CONFIG_BOOTCOMMAND	"run ramboot"
#endif
#ifdef CONFIG_VIDEO
# define CONFIG_BOOTARGS_VIDEO "console=tty0 "
#else
# define CONFIG_BOOTARGS_VIDEO ""
#endif
#ifndef CONFIG_BOOTARGS_ROOT
# define CONFIG_BOOTARGS_ROOT "/dev/mtdblock0 rw"
#endif
#ifndef FLASHBOOT_ENV_SETTINGS
# define FLASHBOOT_ENV_SETTINGS "flashboot=bootm 0x20100000\0"
#endif
#define CONFIG_BOOTARGS	\
	"root=" CONFIG_BOOTARGS_ROOT " " \
	"clkin_hz=" __stringify(CONFIG_CLKIN_HZ) " " \
	"earlyprintk=" \
		"serial," \
		"uart" __stringify(CONFIG_UART_CONSOLE) "," \
		__stringify(CONFIG_BAUDRATE) " " \
	CONFIG_BOOTARGS_VIDEO \
	"console=ttyBF" __stringify(CONFIG_UART_CONSOLE) "," \
			__stringify(CONFIG_BAUDRATE)
#if defined(CONFIG_CMD_NAND)
# define NAND_ENV_SETTINGS \
	"nandargs=set bootargs " CONFIG_BOOTARGS "\0" \
	"nandboot=" \
		"nand read $(loadaddr) 0x20000 0x100000;" \
		"run nandargs;" \
		"bootm" \
		"\0"
#else
# define NAND_ENV_SETTINGS
#endif
#if defined(CONFIG_CMD_NET)
# if (CONFIG_BFIN_BOOT_MODE == BFIN_BOOT_BYPASS)
#  define UBOOT_ENV_FILE "u-boot.bin"
# else
#  define UBOOT_ENV_FILE "u-boot.ldr"
# endif
# if (CONFIG_BFIN_BOOT_MODE == BFIN_BOOT_SPI_MASTER)
#  ifdef CONFIG_SPI
#   define UBOOT_ENV_UPDATE \
		"eeprom write $(loadaddr) 0x0 $(filesize)"
#  else
#   ifndef CONFIG_BFIN_SPI_IMG_SIZE
#    define CONFIG_BFIN_SPI_IMG_SIZE 0x40000
#   endif
#   define UBOOT_ENV_UPDATE \
		"sf probe " __stringify(BFIN_BOOT_SPI_SSEL) ";" \
		"sf erase 0 " __stringify(CONFIG_BFIN_SPI_IMG_SIZE) ";" \
		"sf write $(loadaddr) 0 $(filesize)"
#  endif
# elif (CONFIG_BFIN_BOOT_MODE == BFIN_BOOT_NAND)
#  define UBOOT_ENV_UPDATE \
		"nand unlock 0 0x40000;" \
		"nand erase 0 0x40000;" \
		"nand write $(loadaddr) 0 0x40000"
# else
#  ifndef UBOOT_ENV_UPDATE
#   define UBOOT_ENV_UPDATE \
		"protect off 0x20000000 +$(filesize);" \
		"erase 0x20000000 +$(filesize);" \
		"cp.b $(loadaddr) 0x20000000 $(filesize)"
#  endif
# endif
# ifdef CONFIG_NETCONSOLE
#  define NETCONSOLE_ENV \
	"nc=" \
		"set ncip ${serverip};" \
		"set stdin nc;" \
		"set stdout nc;" \
		"set stderr nc" \
		"\0"
# else
#  define NETCONSOLE_ENV
# endif
# define NETWORK_ENV_SETTINGS \
	NETCONSOLE_ENV \
	\
	"ubootfile=" UBOOT_ENV_FILE "\0" \
	"update=" \
		"tftp $(loadaddr) $(ubootfile);" \
		UBOOT_ENV_UPDATE \
		"\0" \
	"addip=set bootargs $(bootargs) " \
		"ip=$(ipaddr):$(serverip):$(gatewayip):$(netmask):" \
		   "$(hostname):eth0:off" \
		"\0" \
	\
	"ramfile=uImage\0" \
	"ramargs=set bootargs " CONFIG_BOOTARGS "\0" \
	"ramboot=" \
		"tftp $(loadaddr) $(ramfile);" \
		"run ramargs;" \
		"run addip;" \
		"bootm" \
		"\0" \
	\
	"nfsfile=vmImage\0" \
	"nfsargs=set bootargs " \
		"root=/dev/nfs rw " \
		"nfsroot=$(serverip):$(rootpath),tcp,nfsvers=3" \
		"\0" \
	"nfsboot=" \
		"tftp $(loadaddr) $(nfsfile);" \
		"run nfsargs;" \
		"run addip;" \
		"bootm" \
		"\0"
#else
# define NETWORK_ENV_SETTINGS
#endif
#ifndef BOARD_ENV_SETTINGS
# define BOARD_ENV_SETTINGS
#endif
#define CONFIG_EXTRA_ENV_SETTINGS \
	NAND_ENV_SETTINGS \
	NETWORK_ENV_SETTINGS \
	FLASHBOOT_ENV_SETTINGS \
	BOARD_ENV_SETTINGS

/*
 * Network Settings
 */
#ifdef CONFIG_CMD_NET
# define CONFIG_NETMASK		255.255.255.0
# ifndef CONFIG_IPADDR
#  define CONFIG_IPADDR		192.168.0.15
#  define CONFIG_GATEWAYIP	192.168.0.1
#  define CONFIG_SERVERIP	192.168.0.2
# endif
# ifndef CONFIG_ROOTPATH
#  define CONFIG_ROOTPATH	"/romfs"
# endif
# ifdef CONFIG_CMD_DHCP
#  ifndef CONFIG_SYS_AUTOLOAD
#   define CONFIG_SYS_AUTOLOAD "no"
#  endif
# endif
# define CONFIG_IP_DEFRAG
# define CONFIG_NET_RETRY_COUNT 20
#endif

/*
 * Flash Settings
 */
#define CONFIG_FLASH_SHOW_PROGRESS 45

/*
 * SPI Settings
 */
#ifdef CONFIG_SPI_FLASH_ALL
#endif

/*
 * I2C Settings
 */
#if defined(CONFIG_SYS_I2C) || defined(CONFIG_SYS_I2C_SOFT)
# ifndef CONFIG_SYS_I2C_SPEED
#  define CONFIG_SYS_I2C_SPEED 50000
# endif
# ifndef CONFIG_SYS_I2C_SLAVE
#  define CONFIG_SYS_I2C_SLAVE 0
# endif
#endif

/*
 * Misc Settings
 */
#ifndef CONFIG_BOARD_SIZE_LIMIT
# define CONFIG_BOARD_SIZE_LIMIT $$(( 256 * 1024 ))
#endif
#define CONFIG_BFIN_SPI_GPIO_CS /* Only matters if BFIN_SPI is enabled */
#define CONFIG_LZMA
#define CONFIG_MONITOR_IS_IN_RAM
#ifdef CONFIG_HW_WATCHDOG
# define CONFIG_BFIN_WATCHDOG
# ifndef CONFIG_WATCHDOG_TIMEOUT_MSECS
#  define CONFIG_WATCHDOG_TIMEOUT_MSECS 5000
# endif
#endif
#ifndef CONFIG_ADI_GPIO2
# define CONFIG_ADI_GPIO1
#endif
#endif
