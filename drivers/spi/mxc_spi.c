/*
 * Copyright (C) 2008, Guennadi Liakhovetski <lg@denx.de>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <malloc.h>
#include <spi.h>
#include <asm/errno.h>
#include <asm/io.h>
#include <asm/gpio.h>
#include <asm/arch/imx-regs.h>
#include <asm/arch/clock.h>
#include <asm/imx-common/spi.h>

#ifdef CONFIG_MX27
/* i.MX27 has a completely wrong register layout and register definitions in the
 * datasheet, the correct one is in the Freescale's Linux driver */

#error "i.MX27 CSPI not supported due to drastic differences in register definitions" \
"See linux mxc_spi driver from Freescale for details."
#endif

static unsigned long spi_bases[] = {
	MXC_SPI_BASE_ADDRESSES
};

__weak int board_spi_cs_gpio(unsigned bus, unsigned cs)
{
	return -1;
}

#define OUT	MXC_GPIO_DIRECTION_OUT

#define reg_read readl
#define reg_write(a, v) writel(v, a)

#if !defined(CONFIG_SYS_SPI_MXC_WAIT)
#define CONFIG_SYS_SPI_MXC_WAIT		(CONFIG_SYS_HZ/100)	/* 10 ms */
#endif

struct mxc_spi_slave {
	struct spi_slave slave;
	unsigned long	base;
	u32		ctrl_reg;
#if defined(MXC_ECSPI)
	u32		cfg_reg;
#endif
	int		gpio;
	int		ss_pol;
};

static inline struct mxc_spi_slave *to_mxc_spi_slave(struct spi_slave *slave)
{
	return container_of(slave, struct mxc_spi_slave, slave);
}

void spi_cs_activate(struct spi_slave *slave)
{
	struct mxc_spi_slave *mxcs = to_mxc_spi_slave(slave);
	if (mxcs->gpio > 0)
		gpio_set_value(mxcs->gpio, mxcs->ss_pol);
}

void spi_cs_deactivate(struct spi_slave *slave)
{
	struct mxc_spi_slave *mxcs = to_mxc_spi_slave(slave);
	if (mxcs->gpio > 0)
		gpio_set_value(mxcs->gpio,
			      !(mxcs->ss_pol));
}

u32 get_cspi_div(u32 div)
{
	int i;

	for (i = 0; i < 8; i++) {
		if (div <= (4 << i))
			return i;
	}
	return i;
}

#ifdef MXC_CSPI
static s32 spi_cfg_mxc(struct mxc_spi_slave *mxcs, unsigned int cs,
		unsigned int max_hz, unsigned int mode)
{
	unsigned int ctrl_reg;
	u32 clk_src;
	u32 div;

	clk_src = mxc_get_clock(MXC_CSPI_CLK);

	div = DIV_ROUND_UP(clk_src, max_hz);
	div = get_cspi_div(div);

	debug("clk %d Hz, div %d, real clk %d Hz\n",
		max_hz, div, clk_src / (4 << div));

	ctrl_reg = MXC_CSPICTRL_CHIPSELECT(cs) |
		MXC_CSPICTRL_BITCOUNT(MXC_CSPICTRL_MAXBITS) |
		MXC_CSPICTRL_DATARATE(div) |
		MXC_CSPICTRL_EN |
#ifdef CONFIG_MX35
		MXC_CSPICTRL_SSCTL |
#endif
		MXC_CSPICTRL_MODE;

	if (mode & SPI_CPHA)
		ctrl_reg |= MXC_CSPICTRL_PHA;
	if (mode & SPI_CPOL)
		ctrl_reg |= MXC_CSPICTRL_POL;
	if (mode & SPI_CS_HIGH)
		ctrl_reg |= MXC_CSPICTRL_SSPOL;
	mxcs->ctrl_reg = ctrl_reg;

	return 0;
}
#endif

#ifdef MXC_ECSPI
static s32 spi_cfg_mxc(struct mxc_spi_slave *mxcs, unsigned int cs,
		unsigned int max_hz, unsigned int mode)
{
	u32 clk_src = mxc_get_clock(MXC_CSPI_CLK);
	s32 reg_ctrl, reg_config;
	u32 ss_pol = 0, sclkpol = 0, sclkpha = 0, sclkctl = 0;
	u32 pre_div = 0, post_div = 0;
	struct cspi_regs *regs = (struct cspi_regs *)mxcs->base;

	if (max_hz == 0) {
		printf("Error: desired clock is 0\n");
		return -1;
	}

	/*
	 * Reset SPI and set all CSs to master mode, if toggling
	 * between slave and master mode we might see a glitch
	 * on the clock line
	 */
	reg_ctrl = MXC_CSPICTRL_MODE_MASK;
	reg_write(&regs->ctrl, reg_ctrl);
	reg_ctrl |=  MXC_CSPICTRL_EN;
	reg_write(&regs->ctrl, reg_ctrl);

	if (clk_src > max_hz) {
		pre_div = (clk_src - 1) / max_hz;
		/* fls(1) = 1, fls(0x80000000) = 32, fls(16) = 5 */
		post_div = fls(pre_div);
		if (post_div > 4) {
			post_div -= 4;
			if (post_div >= 16) {
				printf("Error: no divider for the freq: %d\n",
					max_hz);
				return -1;
			}
			pre_div >>= post_div;
		} else {
			post_div = 0;
		}
	}

	debug("pre_div = %d, post_div=%d\n", pre_div, post_div);
	reg_ctrl = (reg_ctrl & ~MXC_CSPICTRL_SELCHAN(3)) |
		MXC_CSPICTRL_SELCHAN(cs);
	reg_ctrl = (reg_ctrl & ~MXC_CSPICTRL_PREDIV(0x0F)) |
		MXC_CSPICTRL_PREDIV(pre_div);
	reg_ctrl = (reg_ctrl & ~MXC_CSPICTRL_POSTDIV(0x0F)) |
		MXC_CSPICTRL_POSTDIV(post_div);

	/* We need to disable SPI before changing registers */
	reg_ctrl &= ~MXC_CSPICTRL_EN;

	if (mode & SPI_CS_HIGH)
		ss_pol = 1;

	if (mode & SPI_CPOL) {
		sclkpol = 1;
		sclkctl = 1;
	}

	if (mode & SPI_CPHA)
		sclkpha = 1;

	reg_config = reg_read(&regs->cfg);

	/*
	 * Configuration register setup
	 * The MX51 supports different setup for each SS
	 */
	reg_config = (reg_config & ~(1 << (cs + MXC_CSPICON_SSPOL))) |
		(ss_pol << (cs + MXC_CSPICON_SSPOL));
	reg_config = (reg_config & ~(1 << (cs + MXC_CSPICON_POL))) |
		(sclkpol << (cs + MXC_CSPICON_POL));
	reg_config = (reg_config & ~(1 << (cs + MXC_CSPICON_CTL))) |
		(sclkctl << (cs + MXC_CSPICON_CTL));
	reg_config = (reg_config & ~(1 << (cs + MXC_CSPICON_PHA))) |
		(sclkpha << (cs + MXC_CSPICON_PHA));

	debug("reg_ctrl = 0x%x\n", reg_ctrl);
	reg_write(&regs->ctrl, reg_ctrl);
	debug("reg_config = 0x%x\n", reg_config);
	reg_write(&regs->cfg, reg_config);

	/* save config register and control register */
	mxcs->ctrl_reg = reg_ctrl;
	mxcs->cfg_reg = reg_config;

	/* clear interrupt reg */
	reg_write(&regs->intr, 0);
	reg_write(&regs->stat, MXC_CSPICTRL_TC | MXC_CSPICTRL_RXOVF);

	return 0;
}
#endif

int spi_xchg_single(struct spi_slave *slave, unsigned int bitlen,
	const u8 *dout, u8 *din, unsigned long flags)
{
	struct mxc_spi_slave *mxcs = to_mxc_spi_slave(slave);
	int nbytes = DIV_ROUND_UP(bitlen, 8);
	u32 data, cnt, i;
	struct cspi_regs *regs = (struct cspi_regs *)mxcs->base;
	u32 ts;
	int status;

	debug("%s: bitlen %d dout 0x%x din 0x%x\n",
		__func__, bitlen, (u32)dout, (u32)din);

	mxcs->ctrl_reg = (mxcs->ctrl_reg &
		~MXC_CSPICTRL_BITCOUNT(MXC_CSPICTRL_MAXBITS)) |
		MXC_CSPICTRL_BITCOUNT(bitlen - 1);

	reg_write(&regs->ctrl, mxcs->ctrl_reg | MXC_CSPICTRL_EN);
#ifdef MXC_ECSPI
	reg_write(&regs->cfg, mxcs->cfg_reg);
#endif

	/* Clear interrupt register */
	reg_write(&regs->stat, MXC_CSPICTRL_TC | MXC_CSPICTRL_RXOVF);

	/*
	 * The SPI controller works only with words,
	 * check if less than a word is sent.
	 * Access to the FIFO is only 32 bit
	 */
	if (bitlen % 32) {
		data = 0;
		cnt = (bitlen % 32) / 8;
		if (dout) {
			for (i = 0; i < cnt; i++) {
				data = (data << 8) | (*dout++ & 0xFF);
			}
		}
		debug("Sending SPI 0x%x\n", data);

		reg_write(&regs->txdata, data);
		nbytes -= cnt;
	}

	data = 0;

	while (nbytes > 0) {
		data = 0;
		if (dout) {
			/* Buffer is not 32-bit aligned */
			if ((unsigned long)dout & 0x03) {
				data = 0;
				for (i = 0; i < 4; i++)
					data = (data << 8) | (*dout++ & 0xFF);
			} else {
				data = *(u32 *)dout;
				data = cpu_to_be32(data);
				dout += 4;
			}
		}
		debug("Sending SPI 0x%x\n", data);
		reg_write(&regs->txdata, data);
		nbytes -= 4;
	}

	/* FIFO is written, now starts the transfer setting the XCH bit */
	reg_write(&regs->ctrl, mxcs->ctrl_reg |
		MXC_CSPICTRL_EN | MXC_CSPICTRL_XCH);

	ts = get_timer(0);
	status = reg_read(&regs->stat);
	/* Wait until the TC (Transfer completed) bit is set */
	while ((status & MXC_CSPICTRL_TC) == 0) {
		if (get_timer(ts) > CONFIG_SYS_SPI_MXC_WAIT) {
			printf("spi_xchg_single: Timeout!\n");
			return -1;
		}
		status = reg_read(&regs->stat);
	}

	/* Transfer completed, clear any pending request */
	reg_write(&regs->stat, MXC_CSPICTRL_TC | MXC_CSPICTRL_RXOVF);

	nbytes = DIV_ROUND_UP(bitlen, 8);

	cnt = nbytes % 32;

	if (bitlen % 32) {
		data = reg_read(&regs->rxdata);
		cnt = (bitlen % 32) / 8;
		data = cpu_to_be32(data) >> ((sizeof(data) - cnt) * 8);
		debug("SPI Rx unaligned: 0x%x\n", data);
		if (din) {
			memcpy(din, &data, cnt);
			din += cnt;
		}
		nbytes -= cnt;
	}

	while (nbytes > 0) {
		u32 tmp;
		tmp = reg_read(&regs->rxdata);
		data = cpu_to_be32(tmp);
		debug("SPI Rx: 0x%x 0x%x\n", tmp, data);
		cnt = min(nbytes, sizeof(data));
		if (din) {
			memcpy(din, &data, cnt);
			din += cnt;
		}
		nbytes -= cnt;
	}

	return 0;

}

int spi_xfer(struct spi_slave *slave, unsigned int bitlen, const void *dout,
		void *din, unsigned long flags)
{
	int n_bytes = DIV_ROUND_UP(bitlen, 8);
	int n_bits;
	int ret;
	u32 blk_size;
	u8 *p_outbuf = (u8 *)dout;
	u8 *p_inbuf = (u8 *)din;

	if (!slave)
		return -1;

	if (flags & SPI_XFER_BEGIN)
		spi_cs_activate(slave);

	while (n_bytes > 0) {
		if (n_bytes < MAX_SPI_BYTES)
			blk_size = n_bytes;
		else
			blk_size = MAX_SPI_BYTES;

		n_bits = blk_size * 8;

		ret = spi_xchg_single(slave, n_bits, p_outbuf, p_inbuf, 0);

		if (ret)
			return ret;
		if (dout)
			p_outbuf += blk_size;
		if (din)
			p_inbuf += blk_size;
		n_bytes -= blk_size;
	}

	if (flags & SPI_XFER_END) {
		spi_cs_deactivate(slave);
	}

	return 0;
}

void spi_init(void)
{
}

/*
 * Some SPI devices require active chip-select over multiple
 * transactions, we achieve this using a GPIO. Still, the SPI
 * controller has to be configured to use one of its own chipselects.
 * To use this feature you have to implement board_spi_cs_gpio() to assign
 * a gpio value for each cs (-1 if cs doesn't need to use gpio).
 * You must use some unused on this SPI controller cs between 0 and 3.
 */
static int setup_cs_gpio(struct mxc_spi_slave *mxcs,
			 unsigned int bus, unsigned int cs)
{
	int ret;

	mxcs->gpio = board_spi_cs_gpio(bus, cs);
	if (mxcs->gpio == -1)
		return 0;

	ret = gpio_direction_output(mxcs->gpio, !(mxcs->ss_pol));
	if (ret) {
		printf("mxc_spi: cannot setup gpio %d\n", mxcs->gpio);
		return -EINVAL;
	}

	return 0;
}

struct spi_slave *spi_setup_slave(unsigned int bus, unsigned int cs,
			unsigned int max_hz, unsigned int mode)
{
	struct mxc_spi_slave *mxcs;
	int ret;

	if (bus >= ARRAY_SIZE(spi_bases))
		return NULL;

	mxcs = spi_alloc_slave(struct mxc_spi_slave, bus, cs);
	if (!mxcs) {
		puts("mxc_spi: SPI Slave not allocated !\n");
		return NULL;
	}

	mxcs->ss_pol = (mode & SPI_CS_HIGH) ? 1 : 0;

	ret = setup_cs_gpio(mxcs, bus, cs);
	if (ret < 0) {
		free(mxcs);
		return NULL;
	}

	mxcs->base = spi_bases[bus];

	ret = spi_cfg_mxc(mxcs, cs, max_hz, mode);
	if (ret) {
		printf("mxc_spi: cannot setup SPI controller\n");
		free(mxcs);
		return NULL;
	}
	return &mxcs->slave;
}

void spi_free_slave(struct spi_slave *slave)
{
	struct mxc_spi_slave *mxcs = to_mxc_spi_slave(slave);

	free(mxcs);
}

int spi_claim_bus(struct spi_slave *slave)
{
	struct mxc_spi_slave *mxcs = to_mxc_spi_slave(slave);
	struct cspi_regs *regs = (struct cspi_regs *)mxcs->base;

	reg_write(&regs->rxdata, 1);
	udelay(1);
	reg_write(&regs->ctrl, mxcs->ctrl_reg);
	reg_write(&regs->period, MXC_CSPIPERIOD_32KHZ);
	reg_write(&regs->intr, 0);

	return 0;
}

void spi_release_bus(struct spi_slave *slave)
{
	/* TODO: Shut the controller down */
}
