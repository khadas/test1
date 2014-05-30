/*
 * (C) Copyright 2007-2011
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 * Tom Cubie <tangliang@allwinnertech.com>
 *
 * a simple tool to generate bootable image for sunxi platform.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

/* boot head definition from sun4i boot code */
struct boot_file_head {
	uint32_t b_instruction;	/* one intruction jumping to real code */
	uint8_t magic[8];	/* ="eGON.BT0" or "eGON.BT1", not C-style str */
	uint32_t check_sum;	/* generated by PC */
	uint32_t length;	/* generated by PC */
	/*
	 * We use a simplified header, only filling in what is needed
	 * by the boot ROM. To be compatible with Allwinner tools we
	 * would need to implement the proper fields here instead of
	 * padding.
	 */
	uint8_t pad[12];		/* align to 32 bytes */
};

#define BOOT0_MAGIC                     "eGON.BT0"
#define STAMP_VALUE                     0x5F0A6C39

/* check sum functon from sun4i boot code */
int gen_check_sum(struct boot_file_head *head_p)
{
	uint32_t length;
	uint32_t *buf;
	uint32_t loop;
	uint32_t i;
	uint32_t sum;

	length = head_p->length;
	if ((length & 0x3) != 0)	/* must 4-byte-aligned */
		return -1;
	buf = (uint32_t *)head_p;
	head_p->check_sum = STAMP_VALUE;	/* fill stamp */
	loop = length >> 2;

	/* calculate the sum */
	for (i = 0, sum = 0; i < loop; i++)
		sum += buf[i];

	/* write back check sum */
	head_p->check_sum = sum;

	return 0;
}

#define ALIGN(x, a) __ALIGN_MASK((x), (typeof(x))(a)-1)
#define __ALIGN_MASK(x, mask) (((x)+(mask))&~(mask))

#define SUN4I_SRAM_SIZE 0x7600	/* 0x7748+ is used by BROM */
#define SRAM_LOAD_MAX_SIZE (SUN4I_SRAM_SIZE - sizeof(struct boot_file_head))
#define BLOCK_SIZE 512

struct boot_img {
	struct boot_file_head header;
	char code[SRAM_LOAD_MAX_SIZE];
	char pad[BLOCK_SIZE];
};

int main(int argc, char *argv[])
{
	int fd_in, fd_out;
	struct boot_img img;
	unsigned file_size, load_size;
	int count;

	if (argc < 2) {
		printf("\tThis program makes an input bin file to sun4i " \
		       "bootable image.\n" \
		       "\tUsage: %s input_file out_putfile\n", argv[0]);
		return EXIT_FAILURE;
	}

	fd_in = open(argv[1], O_RDONLY);
	if (fd_in < 0) {
		perror("Open input file");
		return EXIT_FAILURE;
	}

	memset(img.pad, 0, BLOCK_SIZE);

	/* get input file size */
	file_size = lseek(fd_in, 0, SEEK_END);

	if (file_size > SRAM_LOAD_MAX_SIZE) {
		fprintf(stderr, "ERROR: File too large!\n");
		return EXIT_FAILURE;
	} else {
		load_size = ALIGN(file_size, sizeof(int));
	}

	fd_out = open(argv[2], O_WRONLY | O_CREAT, 0666);
	if (fd_out < 0) {
		perror("Open output file");
		return EXIT_FAILURE;
	}

	/* read file to buffer to calculate checksum */
	lseek(fd_in, 0, SEEK_SET);
	count = read(fd_in, img.code, load_size);
	if (count != load_size) {
		perror("Reading input image");
		return EXIT_FAILURE;
	}

	/* fill the header */
	img.header.b_instruction =	/* b instruction */
		0xEA000000 |	/* jump to the first instr after the header */
		((sizeof(struct boot_file_head) / sizeof(int) - 2)
		 & 0x00FFFFFF);
	memcpy(img.header.magic, BOOT0_MAGIC, 8);	/* no '0' termination */
	img.header.length =
		ALIGN(load_size + sizeof(struct boot_file_head), BLOCK_SIZE);
	gen_check_sum(&img.header);

	count = write(fd_out, &img, img.header.length);
	if (count != img.header.length) {
		perror("Writing output");
		return EXIT_FAILURE;
	}

	close(fd_in);
	close(fd_out);

	return EXIT_SUCCESS;
}
