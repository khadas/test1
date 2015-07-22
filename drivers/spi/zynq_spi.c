/*
 * (C) Copyright 2013 Inc.
 * (C) Copyright 2015 Jagan Teki <jteki@openedev.com>
 *
 * Xilinx Zynq PS SPI controller driver (master mode only)
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <config.h>
#include <common.h>
#include <dm.h>
#include <errno.h>
#include <malloc.h>
#include <spi.h>
#include <fdtdec.h>
#include <asm/io.h>
#include <asm/arch/hardware.h>

DECLARE_GLOBAL_DATA_PTR;

/* zynq spi register bit masks ZYNQ_SPI_<REG>_<BIT>_MASK */
#define ZYNQ_SPI_CR_MSA_MASK		(1 << 15)	/* Manual start enb */
#define ZYNQ_SPI_CR_MCS_MASK		(1 << 14)	/* Manual chip select */
#define ZYNQ_SPI_CR_CS_MASK		(0xF << 10)	/* Chip select */
#define ZYNQ_SPI_CR_BRD_MASK		(0x7 << 3)	/* Baud rate div */
#define ZYNQ_SPI_CR_CPHA_MASK		(1 << 2)	/* Clock phase */
#define ZYNQ_SPI_CR_CPOL_MASK		(1 << 1)	/* Clock polarity */
#define ZYNQ_SPI_CR_MSTREN_MASK		(1 << 0)	/* Mode select */
#define ZYNQ_SPI_IXR_RXNEMPTY_MASK	(1 << 4)	/* RX_FIFO_not_empty */
#define ZYNQ_SPI_IXR_TXOW_MASK		(1 << 2)	/* TX_FIFO_not_full */
#define ZYNQ_SPI_IXR_ALL_MASK		0x7F		/* All IXR bits */
#define ZYNQ_SPI_ENR_SPI_EN_MASK	(1 << 0)	/* SPI Enable */

#define ZYNQ_SPI_FIFO_DEPTH		128
#ifndef CONFIG_SYS_ZYNQ_SPI_WAIT
#define CONFIG_SYS_ZYNQ_SPI_WAIT	(CONFIG_SYS_HZ/100)	/* 10 ms */
#endif

/* zynq spi register set */
struct zynq_spi_regs {
	u32 cr;		/* 0x00 */
	u32 isr;	/* 0x04 */
	u32 ier;	/* 0x08 */
	u32 idr;	/* 0x0C */
	u32 imr;	/* 0x10 */
	u32 enr;	/* 0x14 */
	u32 dr;		/* 0x18 */
	u32 txdr;	/* 0x1C */
	u32 rxdr;	/* 0x20 */
};


/* zynq spi platform data */
struct zynq_spi_platdata {
	struct zynq_spi_regs *regs;
	u32 frequency;		/* input frequency */
	u32 speed_hz;
};

/* zynq spi priv */
struct zynq_spi_priv {
	struct zynq_spi_regs *regs;
	u8 mode;
	u8 fifo_depth;
	u32 freq;		/* required frequency */
};

static int zynq_spi_ofdata_to_platdata(struct udevice *bus)
{
	struct zynq_spi_platdata *plat = bus->platdata;
	const void *blob = gd->fdt_blob;
	int node = bus->of_offset;

	plat->regs = (struct zynq_spi_regs *)fdtdec_get_addr(blob, node, "reg");

	/* FIXME: Use 250MHz as a suitable default */
	plat->frequency = fdtdec_get_int(blob, node, "spi-max-frequency",
					250000000);
	plat->speed_hz = plat->frequency / 2;

	debug("zynq_spi_ofdata_to_platdata: regs=%p max-frequency=%d\n",
	      plat->regs, plat->frequency);

	return 0;
}

static void zynq_spi_init_hw(struct zynq_spi_priv *priv)
{
	struct zynq_spi_regs *regs = priv->regs;
	u32 confr;

	/* Disable SPI */
	writel(~ZYNQ_SPI_ENR_SPI_EN_MASK, &regs->enr);

	/* Disable Interrupts */
	writel(ZYNQ_SPI_IXR_ALL_MASK, &regs->idr);

	/* Clear RX FIFO */
	while (readl(&regs->isr) &
			ZYNQ_SPI_IXR_RXNEMPTY_MASK)
		readl(&regs->rxdr);

	/* Clear Interrupts */
	writel(ZYNQ_SPI_IXR_ALL_MASK, &regs->isr);

	/* Manual slave select and Auto start */
	confr = ZYNQ_SPI_CR_MCS_MASK | ZYNQ_SPI_CR_CS_MASK |
		ZYNQ_SPI_CR_MSTREN_MASK;
	confr &= ~ZYNQ_SPI_CR_MSA_MASK;
	writel(confr, &regs->cr);

	/* Enable SPI */
	writel(ZYNQ_SPI_ENR_SPI_EN_MASK, &regs->enr);
}

static int zynq_spi_probe(struct udevice *bus)
{
	struct zynq_spi_platdata *plat = dev_get_platdata(bus);
	struct zynq_spi_priv *priv = dev_get_priv(bus);

	priv->regs = plat->regs;
	priv->fifo_depth = ZYNQ_SPI_FIFO_DEPTH;

	/* init the zynq spi hw */
	zynq_spi_init_hw(priv);

	return 0;
}

static void spi_cs_activate(struct udevice *dev, uint cs)
{
	struct udevice *bus = dev->parent;
	struct zynq_spi_priv *priv = dev_get_priv(bus);
	struct zynq_spi_regs *regs = priv->regs;
	u32 cr;

	clrbits_le32(&regs->cr, ZYNQ_SPI_CR_CS_MASK);
	cr = readl(&regs->cr);
	/*
	 * CS cal logic: CS[13:10]
	 * xxx0	- cs0
	 * xx01	- cs1
	 * x011 - cs2
	 */
	cr |= (~(0x1 << cs) << 10) & ZYNQ_SPI_CR_CS_MASK;
	writel(cr, &regs->cr);
}

static void spi_cs_deactivate(struct udevice *dev)
{
	struct udevice *bus = dev->parent;
	struct zynq_spi_priv *priv = dev_get_priv(bus);
	struct zynq_spi_regs *regs = priv->regs;

	setbits_le32(&regs->cr, ZYNQ_SPI_CR_CS_MASK);
}

static int zynq_spi_claim_bus(struct udevice *dev)
{
	struct udevice *bus = dev->parent;
	struct zynq_spi_priv *priv = dev_get_priv(bus);
	struct zynq_spi_regs *regs = priv->regs;

	writel(ZYNQ_SPI_ENR_SPI_EN_MASK, &regs->enr);

	return 0;
}

static int zynq_spi_release_bus(struct udevice *dev)
{
	struct udevice *bus = dev->parent;
	struct zynq_spi_priv *priv = dev_get_priv(bus);
	struct zynq_spi_regs *regs = priv->regs;

	writel(~ZYNQ_SPI_ENR_SPI_EN_MASK, &regs->enr);

	return 0;
}

static int zynq_spi_xfer(struct udevice *dev, unsigned int bitlen,
			    const void *dout, void *din, unsigned long flags)
{
	struct udevice *bus = dev->parent;
	struct zynq_spi_priv *priv = dev_get_priv(bus);
	struct zynq_spi_regs *regs = priv->regs;
	struct dm_spi_slave_platdata *slave_plat = dev_get_parent_platdata(dev);
	u32 len = bitlen / 8;
	u32 tx_len = len, rx_len = len, tx_tvl;
	const u8 *tx_buf = dout;
	u8 *rx_buf = din, buf;
	u32 ts, status;

	debug("spi_xfer: bus:%i cs:%i bitlen:%i len:%i flags:%lx\n",
	      bus->seq, slave_plat->cs, bitlen, len, flags);

	if (bitlen % 8) {
		debug("spi_xfer: Non byte aligned SPI transfer\n");
		return -1;
	}

	if (flags & SPI_XFER_BEGIN)
		spi_cs_activate(dev, slave_plat->cs);

	while (rx_len > 0) {
		/* Write the data into TX FIFO - tx threshold is fifo_depth */
		tx_tvl = 0;
		while ((tx_tvl < priv->fifo_depth) && tx_len) {
			if (tx_buf)
				buf = *tx_buf++;
			else
				buf = 0;
			writel(buf, &regs->txdr);
			tx_len--;
			tx_tvl++;
		}

		/* Check TX FIFO completion */
		ts = get_timer(0);
		status = readl(&regs->isr);
		while (!(status & ZYNQ_SPI_IXR_TXOW_MASK)) {
			if (get_timer(ts) > CONFIG_SYS_ZYNQ_SPI_WAIT) {
				printf("spi_xfer: Timeout! TX FIFO not full\n");
				return -1;
			}
			status = readl(&regs->isr);
		}

		/* Read the data from RX FIFO */
		status = readl(&regs->isr);
		while (status & ZYNQ_SPI_IXR_RXNEMPTY_MASK) {
			buf = readl(&regs->rxdr);
			if (rx_buf)
				*rx_buf++ = buf;
			status = readl(&regs->isr);
			rx_len--;
		}
	}

	if (flags & SPI_XFER_END)
		spi_cs_deactivate(dev);

	return 0;
}

static int zynq_spi_set_speed(struct udevice *bus, uint speed)
{
	struct zynq_spi_platdata *plat = bus->platdata;
	struct zynq_spi_priv *priv = dev_get_priv(bus);
	struct zynq_spi_regs *regs = priv->regs;
	uint32_t confr;
	u8 baud_rate_val = 0;

	if (speed > plat->frequency)
		speed = plat->frequency;

	/* Set the clock frequency */
	confr = readl(&regs->cr);
	if (speed == 0) {
		/* Set baudrate x8, if the freq is 0 */
		baud_rate_val = 0x2;
	} else if (plat->speed_hz != speed) {
		while ((baud_rate_val < 8) &&
				((plat->frequency /
				(2 << baud_rate_val)) > speed))
			baud_rate_val++;
		plat->speed_hz = speed / (2 << baud_rate_val);
	}
	confr &= ~ZYNQ_SPI_CR_BRD_MASK;
	confr |= (baud_rate_val << 3);

	writel(confr, &regs->cr);
	priv->freq = speed;

	debug("zynq_spi_set_speed: regs=%p, mode=%d\n", priv->regs, priv->freq);

	return 0;
}

static int zynq_spi_set_mode(struct udevice *bus, uint mode)
{
	struct zynq_spi_priv *priv = dev_get_priv(bus);
	struct zynq_spi_regs *regs = priv->regs;
	uint32_t confr;

	/* Set the SPI Clock phase and polarities */
	confr = readl(&regs->cr);
	confr &= ~(ZYNQ_SPI_CR_CPHA_MASK | ZYNQ_SPI_CR_CPOL_MASK);

	if (priv->mode & SPI_CPHA)
		confr |= ZYNQ_SPI_CR_CPHA_MASK;
	if (priv->mode & SPI_CPOL)
		confr |= ZYNQ_SPI_CR_CPOL_MASK;

	writel(confr, &regs->cr);
	priv->mode = mode;

	debug("zynq_spi_set_mode: regs=%p, mode=%d\n", priv->regs, priv->mode);

	return 0;
}

static const struct dm_spi_ops zynq_spi_ops = {
	.claim_bus	= zynq_spi_claim_bus,
	.release_bus	= zynq_spi_release_bus,
	.xfer		= zynq_spi_xfer,
	.set_speed	= zynq_spi_set_speed,
	.set_mode	= zynq_spi_set_mode,
};

static const struct udevice_id zynq_spi_ids[] = {
	{ .compatible = "xlnx,zynq-spi-r1p6" },
	{ }
};

U_BOOT_DRIVER(zynq_spi) = {
	.name	= "zynq_spi",
	.id	= UCLASS_SPI,
	.of_match = zynq_spi_ids,
	.ops	= &zynq_spi_ops,
	.ofdata_to_platdata = zynq_spi_ofdata_to_platdata,
	.platdata_auto_alloc_size = sizeof(struct zynq_spi_platdata),
	.priv_auto_alloc_size = sizeof(struct zynq_spi_priv),
	.probe	= zynq_spi_probe,
};
