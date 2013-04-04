/*
 * (C) Copyright 2012 Samsung Electronics
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 */

#ifndef __TZPC_H_
#define __TZPC_H_

#ifndef __ASSEMBLY__
struct exynos_tzpc {
	unsigned int r0size;
	char res1[0x7FC];
	unsigned int decprot0stat;
	unsigned int decprot0set;
	unsigned int decprot0clr;
	unsigned int decprot1stat;
	unsigned int decprot1set;
	unsigned int decprot1clr;
	unsigned int decprot2stat;
	unsigned int decprot2set;
	unsigned int decprot2clr;
	unsigned int decprot3stat;
	unsigned int decprot3set;
	unsigned int decprot3clr;
	char res2[0x7B0];
	unsigned int periphid0;
	unsigned int periphid1;
	unsigned int periphid2;
	unsigned int periphid3;
	unsigned int pcellid0;
	unsigned int pcellid1;
	unsigned int pcellid2;
	unsigned int pcellid3;
};

/* TZPC : Register Offsets */
#define TZPC0_BASE		0x10100000
#define TZPC1_BASE		0x10110000
#define TZPC2_BASE		0x10120000
#define TZPC3_BASE		0x10130000
#define TZPC4_BASE		0x10140000
#define TZPC5_BASE		0x10150000
#define TZPC6_BASE		0x10160000
#define TZPC7_BASE		0x10170000
#define TZPC8_BASE		0x10180000
#define TZPC9_BASE		0x10190000

#define TZPC_BASE_OFFSET		0x10000

/*
 * TZPC Register Value :
 * R0SIZE: 0x0 : Size of secured ram
 */
#define R0SIZE			0x0

/*
 * TZPC Decode Protection Register Value :
 * DECPROTXSET: 0xFF : Set Decode region to non-secure
 */
#define DECPROTXSET		0xFF
void tzpc_init(void);

#endif

#endif
