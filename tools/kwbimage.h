/*
 * (C) Copyright 2008
 * Marvell Semiconductor <www.marvell.com>
 * Written-by: Prafulla Wadaskar <prafulla@marvell.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _KWBIMAGE_H_
#define _KWBIMAGE_H_

#include <compiler.h>
#include <stdint.h>

#define KWBIMAGE_MAX_CONFIG	((0x1dc - 0x20)/sizeof(struct reg_config))
#define MAX_TEMPBUF_LEN		32

/* NAND ECC Mode */
#define IBR_HDR_ECC_DEFAULT		0x00
#define IBR_HDR_ECC_FORCED_HAMMING	0x01
#define IBR_HDR_ECC_FORCED_RS  		0x02
#define IBR_HDR_ECC_DISABLED  		0x03

/* Boot Type - block ID */
#define IBR_HDR_I2C_ID			0x4D
#define IBR_HDR_SPI_ID			0x5A
#define IBR_HDR_NAND_ID			0x8B
#define IBR_HDR_SATA_ID			0x78
#define IBR_HDR_PEX_ID			0x9C
#define IBR_HDR_UART_ID			0x69
#define IBR_DEF_ATTRIB	 		0x00

#define ALIGN_SUP(x, a) (((x) + (a - 1)) & ~(a - 1))

/* Structure of the main header, version 0 (Kirkwood, Dove) */
struct main_hdr_v0 {
	uint8_t  blockid;		/*0     */
	uint8_t  nandeccmode;		/*1     */
	uint16_t nandpagesize;		/*2-3   */
	uint32_t blocksize;		/*4-7   */
	uint32_t rsvd1;			/*8-11  */
	uint32_t srcaddr;		/*12-15 */
	uint32_t destaddr;		/*16-19 */
	uint32_t execaddr;		/*20-23 */
	uint8_t  satapiomode;		/*24    */
	uint8_t  rsvd3;			/*25    */
	uint16_t ddrinitdelay;		/*26-27 */
	uint16_t rsvd2;			/*28-29 */
	uint8_t  ext;			/*30    */
	uint8_t  checksum;		/*31    */
};

struct ext_hdr_v0_reg {
	uint32_t raddr;
	uint32_t rdata;
};

#define EXT_HDR_V0_REG_COUNT ((0x1dc - 0x20) / sizeof(struct ext_hdr_v0_reg))

struct ext_hdr_v0 {
	uint32_t              offset;
	uint8_t               reserved[0x20 - sizeof(uint32_t)];
	struct ext_hdr_v0_reg rcfg[EXT_HDR_V0_REG_COUNT];
	uint8_t               reserved2[7];
	uint8_t               checksum;
};

struct kwb_header {
	struct main_hdr_v0	kwb_hdr;
	struct ext_hdr_v0	kwb_exthdr;
};

/* Structure of the main header, version 1 (Armada 370, Armada XP) */
struct main_hdr_v1 {
	uint8_t  blockid;               /* 0 */
	uint8_t  reserved1;             /* 1 */
	uint16_t reserved2;             /* 2-3 */
	uint32_t blocksize;             /* 4-7 */
	uint8_t  version;               /* 8 */
	uint8_t  headersz_msb;          /* 9 */
	uint16_t headersz_lsb;          /* A-B */
	uint32_t srcaddr;               /* C-F */
	uint32_t destaddr;              /* 10-13 */
	uint32_t execaddr;              /* 14-17 */
	uint8_t  reserved3;             /* 18 */
	uint8_t  nandblocksize;         /* 19 */
	uint8_t  nandbadblklocation;    /* 1A */
	uint8_t  reserved4;             /* 1B */
	uint16_t reserved5;             /* 1C-1D */
	uint8_t  ext;                   /* 1E */
	uint8_t  checksum;              /* 1F */
};

/*
 * Header for the optional headers, version 1 (Armada 370, Armada XP)
 */
struct opt_hdr_v1 {
	uint8_t  headertype;
	uint8_t  headersz_msb;
	uint16_t headersz_lsb;
	char     data[0];
};

/*
 * Various values for the opt_hdr_v1->headertype field, describing the
 * different types of optional headers. The "secure" header contains
 * informations related to secure boot (encryption keys, etc.). The
 * "binary" header contains ARM binary code to be executed prior to
 * executing the main payload (usually the bootloader). This is
 * typically used to execute DDR3 training code. The "register" header
 * allows to describe a set of (address, value) tuples that are
 * generally used to configure the DRAM controller.
 */
#define OPT_HDR_V1_SECURE_TYPE   0x1
#define OPT_HDR_V1_BINARY_TYPE   0x2
#define OPT_HDR_V1_REGISTER_TYPE 0x3

#define KWBHEADER_V1_SIZE(hdr) \
	(((hdr)->headersz_msb << 16) | le16_to_cpu((hdr)->headersz_lsb))

enum kwbimage_cmd {
	CMD_INVALID,
	CMD_BOOT_FROM,
	CMD_NAND_ECC_MODE,
	CMD_NAND_PAGE_SIZE,
	CMD_SATA_PIO_MODE,
	CMD_DDR_INIT_DELAY,
	CMD_DATA
};

enum kwbimage_cmd_types {
	CFG_INVALID = -1,
	CFG_COMMAND,
	CFG_DATA0,
	CFG_DATA1
};

/*
 * functions
 */
void init_kwb_image_type (void);

/*
 * Byte 8 of the image header contains the version number. In the v0
 * header, byte 8 was reserved, and always set to 0. In the v1 header,
 * byte 8 has been changed to a proper field, set to 1.
 */
static inline unsigned int image_version(void *header)
{
	unsigned char *ptr = header;
	return ptr[8];
}

#endif /* _KWBIMAGE_H_ */
