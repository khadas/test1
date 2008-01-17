/*
 * Copyright (c) 2006 Ben Warren, Qstreams Networks Inc.
 * With help from the common/soft_spi and cpu/mpc8260 drivers
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <spi.h>
#include <asm/mpc8xxx_spi.h>

#ifdef CONFIG_HARD_SPI

#define SPI_EV_NE	0x80000000 >> 22	/* Receiver Not Empty */
#define SPI_EV_NF	0x80000000 >> 23	/* Transmitter Not Full */

#define SPI_MODE_LOOP	0x80000000 >> 1	/* Loopback mode */
#define SPI_MODE_REV	0x80000000 >> 5	/* Reverse mode - MSB first */
#define SPI_MODE_MS	0x80000000 >> 6	/* Always master */
#define SPI_MODE_EN	0x80000000 >> 7	/* Enable interface */

#define SPI_PRESCALER(reg, div) (reg)=((reg) & 0xfff0ffff) | ((div)<<16)
#define SPI_CHARLENGTH(reg, div) (reg)=((reg) & 0xff0fffff) | ((div)<<20)

#define SPI_TIMEOUT	1000

void spi_init(void)
{
	volatile spi8xxx_t *spi = &((immap_t *) (CFG_IMMR))->spi;

	/* ------------------------------------------------
	 * SPI pins on the MPC83xx are not muxed, so all we do is initialize
	 * some registers
	 * ------------------------------------------------ */
	spi->mode = SPI_MODE_REV | SPI_MODE_MS | SPI_MODE_EN;
	SPI_PRESCALER(spi->mode, 1);	/* Use SYSCLK / 8  (16.67MHz typ.) */
	spi->event = 0xffffffff;	/* Clear all SPI events */
	spi->mask = 0x00000000;	/* Mask  all SPI interrupts */
	spi->com = 0;		/* LST bit doesn't do anything, so disregard */
}

int spi_xfer(spi_chipsel_type chipsel, int bitlen, uchar * dout, uchar * din)
{
	volatile spi8xxx_t *spi = &((immap_t *) (CFG_IMMR))->spi;
	unsigned int tmpdout, tmpdin, event;
	int numBlks = bitlen / 32 + (bitlen % 32 ? 1 : 0);
	int tm, isRead = 0;
	unsigned char charSize = 32;

	debug("spi_xfer: chipsel %08X dout %08X din %08X bitlen %d\n",
	      (int)chipsel, *(uint *) dout, *(uint *) din, bitlen);

	if (chipsel != NULL)
		(*chipsel) (1);	/* select the target chip */

	spi->event = 0xffffffff;	/* Clear all SPI events */

	/* handle data in 32-bit chunks */
	while (numBlks--) {
		tmpdout = 0;
		charSize = (bitlen >= 32 ? 32 : bitlen);

		/* Shift data so it's msb-justified */
		tmpdout = *(u32 *) dout >> (32 - charSize);

		/* The LEN field of the SPMODE register is set as follows:
		 *
		 * Bit length           setting
		 * l <= 4               3
		 * 4 < l <= 16          l - 1
		 * l > 16               0
		 */

		if (bitlen <= 16)
			SPI_CHARLENGTH(spi->mode, bitlen <= 4 ? 3 : bitlen - 1);
		else {
			SPI_CHARLENGTH(spi->mode, 0);
			/* Set up the next iteration if sending > 32 bits */
			bitlen -= 32;
			dout += 4;
		}

		spi->tx = tmpdout;	/* Write the data out */
		debug("*** spi_xfer: ... %08x written\n", tmpdout);

		/* --------------------------------
		 * Wait for SPI transmit to get out
		 * or time out (1 second = 1000 ms)
		 * The NE event must be read and cleared first
		 * -------------------------------- */
		for (tm = 0, isRead = 0; tm < SPI_TIMEOUT; ++tm) {
			event = spi->event;
			if (event & SPI_EV_NE) {
				tmpdin = spi->rx;
				spi->event |= SPI_EV_NE;
				isRead = 1;

				*(u32 *) din = (tmpdin << (32 - charSize));
				if (charSize == 32) {
					/* Advance output buffer by 32 bits */
					din += 4;
				}
			}
			/* Only bail when we've had both NE and NF events.
			 * This will cause timeouts on RO devices, so maybe
			 * in the future put an arbitrary delay after writing
			 * the device.  Arbitrary delays suck, though... */
			if (isRead && (event & SPI_EV_NF))
				break;
		}
		if (tm >= SPI_TIMEOUT)
			puts("*** spi_xfer: Time out during SPI transfer");

		debug("*** spi_xfer: transfer ended. Value=%08x\n", tmpdin);
	}

	if (chipsel != NULL)
		(*chipsel) (0);	/* deselect the target chip */
	return 0;
}

#endif				/* CONFIG_HARD_SPI */
