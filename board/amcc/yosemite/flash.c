/*
 * (C) Copyright 2002-2004
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * (C) Copyright 2002 Jun Gu <jung@artesyncp.com>
 * Add support for Am29F016D and dynamic switch setting.
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

/*
 * Modified 4/5/2001
 * Wait for completion of each sector erase command issued
 * 4/5/2001
 * Chris Hallinan - DS4.COM, Inc. - clh@net1plus.com
 */

/*
 * Ported to XPedite1000, 1/2 mb boot flash only
 * Travis B. Sawyer, <travis.sawyer@sandburst.com>
 */

#include <common.h>
#include <ppc4xx.h>
#include <asm/processor.h>

#undef DEBUG
#ifdef DEBUG
#define DEBUGF(x...) printf(x)
#else
#define DEBUGF(x...)
#endif				/* DEBUG */

#define BOOT_SMALL_FLASH	32	/* 00100000 */
#define FLASH_ONBD_N		2	/* 00000010 */
#define FLASH_SRAM_SEL		1	/* 00000001 */

#define BOOT_SMALL_FLASH_VAL	4
#define FLASH_ONBD_N_VAL	2
#define FLASH_SRAM_SEL_VAL	1

flash_info_t flash_info[CFG_MAX_FLASH_BANKS];	/* info for FLASH chips   */

unsigned long flash_addr_table[512][CFG_MAX_FLASH_BANKS] = {
	{0xfe000000}

};

/*-----------------------------------------------------------------------
 * Functions
 */
static ulong flash_get_size(vu_long * addr, flash_info_t * info);
static int write_word(flash_info_t * info, ulong dest, ulong data);

#define ADDR0		0xaaaa
#define ADDR1		0x5554
#define FLASH_WORD_SIZE unsigned short

/*-----------------------------------------------------------------------
 */

unsigned long flash_init(void)
{
	unsigned long total_b = 0;
	unsigned long size_b[CFG_MAX_FLASH_BANKS];
	unsigned short index = 0;
	int i;

	DEBUGF("\n");
	DEBUGF("FLASH: Index: %d\n", index);

	/* Init: no FLASHes known */
	for (i = 0; i < CFG_MAX_FLASH_BANKS; ++i) {
		flash_info[i].flash_id = FLASH_UNKNOWN;
		flash_info[i].sector_count = -1;
		flash_info[i].size = 0;

		/* check whether the address is 0 */
		if (flash_addr_table[index][i] == 0) {
			continue;
		}

		/* call flash_get_size() to initialize sector address */
		size_b[i] = flash_get_size((vu_long *)
					   flash_addr_table[index][i],
					   &flash_info[i]);
		flash_info[i].size = size_b[i];
		if (flash_info[i].flash_id == FLASH_UNKNOWN) {
			printf
			    ("## Unknown FLASH on Bank %d - Size = 0x%08lx = %ld MB\n",
			     i, size_b[i], size_b[i] << 20);
			flash_info[i].sector_count = -1;
			flash_info[i].size = 0;
		}

		total_b += flash_info[i].size;
	}

	/* FLASH protect Monitor */
	flash_protect(FLAG_PROTECT_SET,
		      CFG_MONITOR_BASE, 0xFFFFFFFF, &flash_info[0]);

	return total_b;
}

/*-----------------------------------------------------------------------
 */
void flash_print_info(flash_info_t * info)
{
	int i;
	int k;
	int size;
	int erased;
	volatile unsigned long *flash;

	if (info->flash_id == FLASH_UNKNOWN) {
		printf("missing or unknown FLASH type\n");
		return;
	}

	switch (info->flash_id & FLASH_VENDMASK) {
	case FLASH_MAN_AMD:
		printf("AMD ");
		break;
	case FLASH_MAN_FUJ:
		printf("FUJITSU ");
		break;
	case FLASH_MAN_SST:
		printf("SST ");
		break;
	default:
		printf("Unknown Vendor ");
		break;
	}

	switch (info->flash_id & FLASH_TYPEMASK) {
	case FLASH_AMD016:
		printf("AM29F016D (16 Mbit, uniform sector size)\n");
		break;
	case FLASH_AM040:
		printf("AM29F040 (512 Kbit, uniform sector size)\n");
		break;
	case FLASH_AM400B:
		printf("AM29LV400B (4 Mbit, bottom boot sect)\n");
		break;
	case FLASH_AM400T:
		printf("AM29LV400T (4 Mbit, top boot sector)\n");
		break;
	case FLASH_AM800B:
		printf("AM29LV800B (8 Mbit, bottom boot sect)\n");
		break;
	case FLASH_AM800T:
		printf("AM29LV800T (8 Mbit, top boot sector)\n");
		break;
	case FLASH_AM160B:
		printf("AM29LV160B (16 Mbit, bottom boot sect)\n");
		break;
	case FLASH_AM160T:
		printf("AM29LV160T (16 Mbit, top boot sector)\n");
		break;
	case FLASH_AM320B:
		printf("AM29LV320B (32 Mbit, bottom boot sect)\n");
		break;
	case FLASH_AM320T:
		printf("AM29LV320T (32 Mbit, top boot sector)\n");
		break;
	case FLASH_SST800A:
		printf("SST39LF/VF800 (8 Mbit, uniform sector size)\n");
		break;
	case FLASH_SST160A:
		printf("SST39LF/VF160 (16 Mbit, uniform sector size)\n");
		break;
	default:
		printf("Unknown Chip Type\n");
		break;
	}

	printf("  Size: %ld KB in %d Sectors\n",
	       info->size >> 10, info->sector_count);

	printf("  Sector Start Addresses:");
	for (i = 0; i < info->sector_count; ++i) {
		/*
		 * Check if whole sector is erased
		 */
		if (i != (info->sector_count - 1))
			size = info->start[i + 1] - info->start[i];
		else
			size = info->start[0] + info->size - info->start[i];
		erased = 1;
		flash = (volatile unsigned long *)info->start[i];
		size = size >> 2;	/* divide by 4 for longword access */
		for (k = 0; k < size; k++) {
			if (*flash++ != 0xffffffff) {
				erased = 0;
				break;
			}
		}

		if ((i % 5) == 0)
			printf("\n   ");
		printf(" %08lX%s%s",
		       info->start[i],
		       erased ? " E" : "  ", info->protect[i] ? "RO " : "   ");
	}
	printf("\n");
	return;
}

/*-----------------------------------------------------------------------
 */

/*-----------------------------------------------------------------------
 */

/*
 * The following code cannot be run from FLASH!
 */
static ulong flash_get_size(vu_long * addr, flash_info_t * info)
{
	short i;
	FLASH_WORD_SIZE value;
	ulong base = (ulong) addr;
	volatile FLASH_WORD_SIZE *addr2 = (FLASH_WORD_SIZE *) addr;

	DEBUGF("FLASH ADDR: %08x\n", (unsigned)addr);

	/* Write auto select command: read Manufacturer ID */
	udelay(10000);
	*(FLASH_WORD_SIZE *) ((int)addr + ADDR0) = (FLASH_WORD_SIZE) 0x00AA;
	udelay(1000);
	*(FLASH_WORD_SIZE *) ((int)addr + ADDR1) = (FLASH_WORD_SIZE) 0x0055;
	udelay(1000);
	*(FLASH_WORD_SIZE *) ((int)addr + ADDR0) = (FLASH_WORD_SIZE) 0x0090;
	udelay(1000);

	value = addr2[0];

	DEBUGF("FLASH MANUFACT: %x\n", value);

	switch (value) {
	case (FLASH_WORD_SIZE) AMD_MANUFACT:
		info->flash_id = FLASH_MAN_AMD;
		break;
	case (FLASH_WORD_SIZE) FUJ_MANUFACT:
		info->flash_id = FLASH_MAN_FUJ;
		break;
	case (FLASH_WORD_SIZE) SST_MANUFACT:
		info->flash_id = FLASH_MAN_SST;
		break;
	case (FLASH_WORD_SIZE) STM_MANUFACT:
		info->flash_id = FLASH_MAN_STM;
		break;
	default:
		info->flash_id = FLASH_UNKNOWN;
		info->sector_count = 0;
		info->size = 0;
		return (0);	/* no or unknown flash  */
	}

#ifdef CONFIG_ADCIOP
	value = addr2[0];	/* device ID            */
	debug("\ndev_code=%x\n", value);
#else
	value = addr2[1];	/* device ID            */
#endif

	DEBUGF("\nFLASH DEVICEID: %x\n", value);

	info->flash_id = 0;
	info->sector_count = CFG_MAX_FLASH_SECT;
	info->size = 0x02000000;

	/* set up sector start address table */
	for (i = 0; i < info->sector_count; i++) {
		info->start[i] = (int)base + (i * 0x00020000);
		info->protect[i] = 0;
	}

	*(FLASH_WORD_SIZE *) ((int)addr) = (FLASH_WORD_SIZE) 0x00F0;	/* reset bank */

	return (info->size);
}

int wait_for_DQ7(flash_info_t * info, int sect)
{
	ulong start, now, last;
	volatile FLASH_WORD_SIZE *addr =
	    (FLASH_WORD_SIZE *) (info->start[sect]);

	start = get_timer(0);
	last = start;
	while ((addr[0] & (FLASH_WORD_SIZE) 0x00800080) !=
	       (FLASH_WORD_SIZE) 0x00800080) {
		if ((now = get_timer(start)) > CFG_FLASH_ERASE_TOUT) {
			printf("Timeout\n");
			return -1;
		}
		/* show that we're waiting */
		if ((now - last) > 1000) {	/* every second */
			putc('.');
			last = now;
		}
	}
	return 0;
}

/*-----------------------------------------------------------------------
 */

int flash_erase(flash_info_t * info, int s_first, int s_last)
{
	volatile FLASH_WORD_SIZE *addr = (FLASH_WORD_SIZE *) (info->start[0]);
	volatile FLASH_WORD_SIZE *addr2;
	int flag, prot, sect, l_sect;

	if ((s_first < 0) || (s_first > s_last)) {
		if (info->flash_id == FLASH_UNKNOWN) {
			printf("- missing\n");
		} else {
			printf("- no sectors to erase\n");
		}
		return 1;
	}

	if (info->flash_id == FLASH_UNKNOWN) {
		printf("Can't erase unknown flash type - aborted\n");
		return 1;
	}

	prot = 0;
	for (sect = s_first; sect <= s_last; ++sect) {
		if (info->protect[sect]) {
			prot++;
		}
	}

	if (prot) {
		printf("- Warning: %d protected sectors will not be erased!\n",
		       prot);
	} else {
		printf("\n");
	}

	l_sect = -1;

	/* Disable interrupts which might cause a timeout here */
	flag = disable_interrupts();

	/* Start erase on unprotected sectors */
	for (sect = s_first; sect <= s_last; sect++) {
		if (info->protect[sect] == 0) {	/* not protected */
			addr2 = (FLASH_WORD_SIZE *) (info->start[sect]);
			printf("Erasing sector %p\n", addr2);
			*(FLASH_WORD_SIZE *) ((int)addr + ADDR0) =
			    (FLASH_WORD_SIZE) 0x00AA;
			asm("sync");
			asm("isync");
			*(FLASH_WORD_SIZE *) ((int)addr + ADDR1) =
			    (FLASH_WORD_SIZE) 0x0055;
			asm("sync");
			asm("isync");
			*(FLASH_WORD_SIZE *) ((int)addr + ADDR0) =
			    (FLASH_WORD_SIZE) 0x0080;
			asm("sync");
			asm("isync");
			*(FLASH_WORD_SIZE *) ((int)addr + ADDR0) =
			    (FLASH_WORD_SIZE) 0x00AA;
			asm("sync");
			asm("isync");
			*(FLASH_WORD_SIZE *) ((int)addr + ADDR1) =
			    (FLASH_WORD_SIZE) 0x0055;
			asm("sync");
			asm("isync");
			addr2[0] = (FLASH_WORD_SIZE) 0x00300030;	/* sector erase */
			asm("sync");
			asm("isync");

			l_sect = sect;
			/*
			 * Wait for each sector to complete, it's more
			 * reliable.  According to AMD Spec, you must
			 * issue all erase commands within a specified
			 * timeout.  This has been seen to fail, especially
			 * if printf()s are included (for debug)!!
			 */
			wait_for_DQ7(info, sect);
		}
	}

	/* re-enable interrupts if necessary */
	if (flag)
		enable_interrupts();

	/* wait at least 80us - let's wait 1 ms */
	udelay(1000);

#if 0
	/*
	 * We wait for the last triggered sector
	 */
	if (l_sect < 0)
		goto DONE;
	wait_for_DQ7(info, l_sect);

      DONE:
#endif
	/* reset to read mode */
	addr = (FLASH_WORD_SIZE *) info->start[0];
	addr[0] = (FLASH_WORD_SIZE) 0x00F000F0;	/* reset bank */

	printf(" done\n");
	return 0;
}

/*-----------------------------------------------------------------------
 * Copy memory to flash, returns:
 * 0 - OK
 * 1 - write timeout
 * 2 - Flash not erased
 */
int write_buff(flash_info_t * info, uchar * src, ulong addr, ulong cnt)
{
	ulong cp, wp, data;
	int i, l, rc;
	ulong status_value = 0;

	wp = (addr & ~3);	/* get lower word aligned address */

	/*
	 * handle unaligned start bytes
	 */
	if ((l = addr - wp) != 0) {
		data = 0;
		for (i = 0, cp = wp; i < l; ++i, ++cp) {
			data = (data << 8) | (*(uchar *) cp);
		}
		for (; i < 4 && cnt > 0; ++i) {
			data = (data << 8) | *src++;
			--cnt;
			++cp;
		}
		for (; cnt == 0 && i < 4; ++i, ++cp) {
			data = (data << 8) | (*(uchar *) cp);
		}

		if ((rc = write_word(info, wp, data)) != 0) {
			return (rc);
		}
		wp += 4;
	}

	/*
	 * handle word aligned part
	 */
	while (cnt >= 4) {

		/*print status if needed */
		if ((wp >= (status_value + 0x20000))
		    && (status_value < 0xFFFE0000)) {
			status_value = wp;
			printf("writing to sector 0x%X\n", status_value);
		}

		data = 0;
		for (i = 0; i < 4; ++i) {
			data = (data << 8) | *src++;
		}
		if ((rc = write_word(info, wp, data)) != 0) {
			return (rc);
		}
		wp += 4;
		cnt -= 4;
	}

	if (cnt == 0) {
		return (0);
	}

	/*
	 * handle unaligned tail bytes
	 */
	data = 0;
	for (i = 0, cp = wp; i < 4 && cnt > 0; ++i, ++cp) {
		data = (data << 8) | *src++;
		--cnt;
	}
	for (; i < 4; ++i, ++cp) {
		data = (data << 8) | (*(uchar *) cp);
	}

	return (write_word(info, wp, data));
}

/*-----------------------------------------------------------------------
 * Write a word to Flash, returns:
 * 0 - OK
 * 1 - write timeout
 * 2 - Flash not erased
 */
static int write_word(flash_info_t * info, ulong dest, ulong data)
{
	vu_long *addr2 = (vu_long *) (info->start[0]);
	volatile FLASH_WORD_SIZE *dest2 = (FLASH_WORD_SIZE *) dest;
	volatile FLASH_WORD_SIZE *data2 = (FLASH_WORD_SIZE *) & data;
	ulong start;
	int i;

	/* Check if Flash is (sufficiently) erased */
	if ((*((volatile FLASH_WORD_SIZE *)dest) &
	     (FLASH_WORD_SIZE) data) != (FLASH_WORD_SIZE) data) {
		return (2);
	}

	for (i = 0; i < 4 / sizeof(FLASH_WORD_SIZE); i++) {
		int flag;

		/* Disable interrupts which might cause a timeout here */
		flag = disable_interrupts();

		*(FLASH_WORD_SIZE *) ((int)addr2 + ADDR0) =
		    (FLASH_WORD_SIZE) 0x00AA;
		asm("sync");
		asm("isync");
		*(FLASH_WORD_SIZE *) ((int)addr2 + ADDR1) =
		    (FLASH_WORD_SIZE) 0x0055;
		asm("sync");
		asm("isync");
		*(FLASH_WORD_SIZE *) ((int)addr2 + ADDR0) =
		    (FLASH_WORD_SIZE) 0x00A0;
		asm("sync");
		asm("isync");

		dest2[i] = data2[i];

		/* re-enable interrupts if necessary */
		if (flag)
			enable_interrupts();

		/* data polling for D7 */
		start = get_timer(0);
		while ((dest2[i] & (FLASH_WORD_SIZE) 0x00800080) !=
		       (data2[i] & (FLASH_WORD_SIZE) 0x00800080)) {

			if (get_timer(start) > CFG_FLASH_WRITE_TOUT) {
				return (1);
			}
		}
	}

	return (0);
}

/*-----------------------------------------------------------------------
 */
