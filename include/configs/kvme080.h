/*
 * (C) Copyright 2005
 * Sangmoon Kim, dogoil@etinsys.com.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_MPC824X		1
#define CONFIG_MPC8245		1
#define CONFIG_KVME080		1

#define	CONFIG_SYS_TEXT_BASE	0xFFF00000

#define CONFIG_CONS_INDEX	1

#define CONFIG_BAUDRATE		115200

#define CONFIG_BOOTDELAY	5

#define CONFIG_IPADDR		192.168.0.2
#define CONFIG_NETMASK		255.255.255.0
#define CONFIG_SERVERIP		192.168.0.1

#define CONFIG_BOOTARGS \
	"console=ttyS0,115200 " \
	"root=/dev/nfs rw nfsroot=192.168.0.1:/opt/eldk/ppc_82xx " \
	"ip=192.168.0.2:192.168.0.1:192.168.0.1:255.255.255.0:" \
	"kvme080:eth0:none " \
	"mtdparts=phys_mapped_flash:12m(root),-(kernel)"

#define CONFIG_BOOTCOMMAND \
	"tftp 800000 kvme080/uImage; " \
	"bootm 800000"

#define CONFIG_LOADADDR		800000

#define CONFIG_BOARD_EARLY_INIT_F
#define CONFIG_BOARD_EARLY_INIT_R
#define CONFIG_MISC_INIT_R

#define CONFIG_LOADS_ECHO	1
#undef	CONFIG_SYS_LOADS_BAUD_CHANGE

#undef	CONFIG_WATCHDOG

/*
 * BOOTP options
 */
#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_BOOTFILESIZE


#define CONFIG_MAC_PARTITION
#define CONFIG_DOS_PARTITION

#define CONFIG_RTC_DS164x


/*
 * Command line configuration.
 */
#include <config_cmd_default.h>

#define CONFIG_CMD_ASKENV
#define CONFIG_CMD_CACHE
#define CONFIG_CMD_DATE
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_DIAG
#define CONFIG_CMD_EEPROM
#define CONFIG_CMD_ELF
#define CONFIG_CMD_I2C
#define CONFIG_CMD_JFFS2
#define CONFIG_CMD_NFS
#define CONFIG_CMD_PCI
#define CONFIG_CMD_PING
#define CONFIG_CMD_SDRAM
#define CONFIG_CMD_SNTP


#define CONFIG_NETCONSOLE

#define CONFIG_SYS_LONGHELP
#define CONFIG_SYS_PROMPT		"=> "
#define CONFIG_SYS_CBSIZE		256
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16)
#define CONFIG_SYS_MAXARGS		16
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE

#define CONFIG_SYS_MEMTEST_START	0x00400000
#define CONFIG_SYS_MEMTEST_END		0x07C00000

#define CONFIG_SYS_LOAD_ADDR		0x00100000
#define CONFIG_SYS_HZ			1000

#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200 }

#define CONFIG_SYS_INIT_RAM_ADDR	0x40000000
#define CONFIG_SYS_INIT_RAM_SIZE	0x1000
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)

#define CONFIG_SYS_SDRAM_BASE		0x00000000
#define CONFIG_SYS_FLASH_BASE		0x7C000000
#define CONFIG_SYS_EUMB_ADDR		0xFC000000
#define CONFIG_SYS_NVRAM_BASE_ADDR	0xFF000000
#define CONFIG_SYS_NS16550_COM1	0xFF080000
#define CONFIG_SYS_NS16550_COM2	0xFF080010
#define CONFIG_SYS_NS16550_COM3	0xFF080020
#define CONFIG_SYS_NS16550_COM4	0xFF080030
#define CONFIG_SYS_RESET_ADDRESS	0xFFF00100

#define CONFIG_SYS_MAX_RAM_SIZE	0x20000000
#define CONFIG_SYS_FLASH_SIZE		(16 * 1024 * 1024)
#define CONFIG_SYS_NVRAM_SIZE		0x7FFF8

#define CONFIG_VERY_BIG_RAM

#define CONFIG_SYS_MONITOR_LEN		0x00040000
#define CONFIG_SYS_MONITOR_BASE	CONFIG_SYS_TEXT_BASE
#define CONFIG_SYS_MALLOC_LEN		(512 << 10)

#define CONFIG_SYS_BOOTMAPSZ		(8 << 20)

#define CONFIG_SYS_FLASH_CFI
#define CONFIG_FLASH_CFI_DRIVER
#define CONFIG_SYS_FLASH_USE_BUFFER_WRITE
#define CONFIG_SYS_FLASH_PROTECTION
#define CONFIG_SYS_FLASH_EMPTY_INFO
#define CONFIG_SYS_FLASH_PROTECT_CLEAR

#define CONFIG_SYS_MAX_FLASH_BANKS	1
#define CONFIG_SYS_MAX_FLASH_SECT	256

#define CONFIG_SYS_FLASH_ERASE_TOUT	120000
#define CONFIG_SYS_FLASH_WRITE_TOUT	500

#define CONFIG_SYS_JFFS2_FIRST_BANK	0
#define CONFIG_SYS_JFFS2_NUM_BANKS	1

#define CONFIG_ENV_IS_IN_NVRAM	1
#define CONFIG_ENV_OVERWRITE	1
#define CONFIG_SYS_NVRAM_ACCESS_ROUTINE
#define CONFIG_ENV_ADDR		CONFIG_SYS_NVRAM_BASE_ADDR
#define CONFIG_ENV_SIZE		0x400
#define CONFIG_ENV_OFFSET		0

#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	1
#define CONFIG_SYS_NS16550_CLK		14745600

#define CONFIG_PCI
#define CONFIG_PCI_PNP

#define CONFIG_NET_MULTI
#define CONFIG_EEPRO100
#define CONFIG_EEPRO100_SROM_WRITE

#define CONFIG_SYS_RX_ETH_BUFFER	8

#define CONFIG_HARD_I2C		1
#define CONFIG_SYS_I2C_SPEED		400000
#define CONFIG_SYS_I2C_SLAVE		0x7F

#define CONFIG_SYS_I2C_EEPROM_ADDR		0x57
#define CONFIG_SYS_I2C_EEPROM_ADDR_LEN		1
#define CONFIG_SYS_EEPROM_PAGE_WRITE_BITS	3
#define CONFIG_SYS_EEPROM_PAGE_WRITE_DELAY_MS	10

#define CONFIG_SYS_CLK_FREQ	33333333

#define CONFIG_SYS_CACHELINE_SIZE	32
#if defined(CONFIG_CMD_KGDB)
#  define CONFIG_SYS_CACHELINE_SHIFT	5
#endif

#define CONFIG_SYS_DLL_EXTEND		0x00
#define CONFIG_SYS_PCI_HOLD_DEL	0x20

#define CONFIG_SYS_ROMNAL		15
#define CONFIG_SYS_ROMFAL		31

#define CONFIG_SYS_REFINT		430

#define CONFIG_SYS_DBUS_SIZE2		1

#define CONFIG_SYS_BSTOPRE		121
#define CONFIG_SYS_REFREC		8
#define CONFIG_SYS_RDLAT		4
#define CONFIG_SYS_PRETOACT		3
#define CONFIG_SYS_ACTTOPRE		5
#define CONFIG_SYS_ACTORW		3
#define CONFIG_SYS_SDMODE_CAS_LAT	3
#define CONFIG_SYS_SDMODE_WRAP		0

#define CONFIG_SYS_REGISTERD_TYPE_BUFFER	1
#define CONFIG_SYS_EXTROM			1
#define CONFIG_SYS_REGDIMM			0

#define CONFIG_SYS_BANK0_START		0x00000000
#define CONFIG_SYS_BANK0_END		(0x4000000 - 1)
#define CONFIG_SYS_BANK0_ENABLE	1
#define CONFIG_SYS_BANK1_START		0x04000000
#define CONFIG_SYS_BANK1_END		(0x8000000 - 1)
#define CONFIG_SYS_BANK1_ENABLE	1
#define CONFIG_SYS_BANK2_START		0x3ff00000
#define CONFIG_SYS_BANK2_END		0x3fffffff
#define CONFIG_SYS_BANK2_ENABLE	0
#define CONFIG_SYS_BANK3_START		0x3ff00000
#define CONFIG_SYS_BANK3_END		0x3fffffff
#define CONFIG_SYS_BANK3_ENABLE	0
#define CONFIG_SYS_BANK4_START		0x00000000
#define CONFIG_SYS_BANK4_END		0x00000000
#define CONFIG_SYS_BANK4_ENABLE	0
#define CONFIG_SYS_BANK5_START		0x00000000
#define CONFIG_SYS_BANK5_END		0x00000000
#define CONFIG_SYS_BANK5_ENABLE	0
#define CONFIG_SYS_BANK6_START		0x00000000
#define CONFIG_SYS_BANK6_END		0x00000000
#define CONFIG_SYS_BANK6_ENABLE	0
#define CONFIG_SYS_BANK7_START		0x00000000
#define CONFIG_SYS_BANK7_END		0x00000000
#define CONFIG_SYS_BANK7_ENABLE	0

#define CONFIG_SYS_BANK_ENABLE		0x03

#define CONFIG_SYS_ODCR		0x75
#define CONFIG_SYS_PGMAX		0x32

#define CONFIG_SYS_IBAT0L	(CONFIG_SYS_SDRAM_BASE | BATL_PP_10 | BATL_MEMCOHERENCE)
#define CONFIG_SYS_IBAT0U	(CONFIG_SYS_SDRAM_BASE | BATU_BL_256M | BATU_VS | BATU_VP)

#define CONFIG_SYS_IBAT1L	(CONFIG_SYS_INIT_RAM_ADDR | BATL_PP_10 | BATL_MEMCOHERENCE)
#define CONFIG_SYS_IBAT1U	(CONFIG_SYS_INIT_RAM_ADDR | BATU_BL_128K | BATU_VS | BATU_VP)

#define CONFIG_SYS_IBAT2L	(0x80000000 | BATL_PP_10 | BATL_CACHEINHIBIT)
#define CONFIG_SYS_IBAT2U	(0x80000000 | BATU_BL_256M | BATU_VS | BATU_VP)

#define CONFIG_SYS_IBAT3L	(0xF0000000 | BATL_PP_10 | BATL_CACHEINHIBIT)
#define CONFIG_SYS_IBAT3U	(0xF0000000 | BATU_BL_256M | BATU_VS | BATU_VP)

#define CONFIG_SYS_DBAT0L	CONFIG_SYS_IBAT0L
#define CONFIG_SYS_DBAT0U	CONFIG_SYS_IBAT0U
#define CONFIG_SYS_DBAT1L	CONFIG_SYS_IBAT1L
#define CONFIG_SYS_DBAT1U	CONFIG_SYS_IBAT1U
#define CONFIG_SYS_DBAT2L	CONFIG_SYS_IBAT2L
#define CONFIG_SYS_DBAT2U	CONFIG_SYS_IBAT2U
#define CONFIG_SYS_DBAT3L	CONFIG_SYS_IBAT3L
#define CONFIG_SYS_DBAT3U	CONFIG_SYS_IBAT3U

#endif	/* __CONFIG_H */
