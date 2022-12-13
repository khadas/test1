// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Copyright (c) 2019 Amlogic, Inc. All rights reserved.
 */

#include <common.h>
#include <dm.h>
#include <errno.h>
#include <clk.h>
#include <linux/bitfield.h>
#include <asm/io.h>
#include <asm/arch/secure_apb.h>
#include <spi.h>
#include <dm/device-internal.h>
#include <dm/uclass-internal.h>
#include <dm/root.h>
#include <dm/lists.h>
#include <dm/util.h>
#ifdef CONFIG_SECURE_POWER_CONTROL
#include <asm/arch/pwr_ctrl.h>
#endif
#include <mapmem.h>

/* Register Map */
#define SPICC_REG_CFG_READY		0x00
#define SPICC_REG_CFG_SPI		0x04
#define SPICC_REG_CFG_START		0x08
#define SPICC_REG_CFG_BUS		0x0C
#define SPICC_REG_PIO_TX_DATA_L		0x10
#define SPICC_REG_PIO_TX_DATA_H		0x14
#define SPICC_REG_PIO_RX_DATA_L		0x18
#define SPICC_REG_PIO_RX_DATA_H		0x1C
#define SPICC_REG_MEM_TX_ADDR_L		0x10
#define SPICC_REG_MEM_TX_ADDR_H		0x14
#define SPICC_REG_MEM_RX_ADDR_L		0x18
#define SPICC_REG_MEM_RX_ADDR_H		0x1C
#define SPICC_REG_DESC_LIST_L		0x20
#define SPICC_REG_DESC_LIST_H		0x24
#define SPICC_DESC_PENDING		BIT(31)
#define SPICC_REG_DESC_CURRENT_L	0x28
#define SPICC_REG_DESC_CURRENT_H	0x2c
#define SPICC_REG_IRQ_STS		0x30
#define SPICC_REG_IRQ_ENABLE		0x34
#define SPICC_RCH_DESC_EOC		BIT(0)
#define SPICC_RCH_DESC_INVALID		BIT(1)
#define SPICC_RCH_DESC_RESP		BIT(2)
#define SPICC_RCH_DATA_RESP		BIT(3)
#define SPICC_WCH_DESC_EOC		BIT(4)
#define SPICC_WCH_DESC_INVALID		BIT(5)
#define SPICC_WCH_DESC_RESP		BIT(6)
#define SPICC_WCH_DATA_RESP		BIT(7)
#define SPICC_DESC_ERR			BIT(8)
#define SPICC_SPI_READY			BIT(9)
#define SPICC_DESC_DONE			BIT(10)
#define SPICC_DESC_CHAIN_DONE		BIT(11)

union spicc_cfg_spi {
	uint32_t			d32;
	struct  {
		uint32_t		bus64_en:1;
		uint32_t		slave_en:1;
		uint32_t		ss:2;
		uint32_t		flash_wp_pin_en:1;
		uint32_t		flash_hold_pin_en:1;
		uint32_t		hw_pos:1; /* start on vsync rising */
		uint32_t		hw_neg:1; /* start on vsync falling */
		uint32_t		rsv:24;
	} b;
};

union spicc_cfg_start {
	uint32_t			d32;
	struct  {
		uint32_t		block_num:20;
#define SPICC_BLOCK_MAX			0x100000

		uint32_t		block_size:3;
		uint32_t		dc_level:1;
#define SPICC_DC_DATA0_CMD1		0
#define SPICC_DC_DATA1_CMD0		1

		uint32_t		op_mode:2;
#define SPICC_OP_MODE_WRITE_CMD		0
#define SPICC_OP_MODE_READ_STS		1
#define SPICC_OP_MODE_WRITE		2
#define SPICC_OP_MODE_READ		3

		uint32_t		rx_data_mode:2;
		uint32_t		tx_data_mode:2;
#define SPICC_DATA_MODE_NONE		0
#define SPICC_DATA_MODE_PIO		1
#define SPICC_DATA_MODE_MEM		2
#define SPICC_DATA_MODE_SG		3

		uint32_t		eoc:1;
		uint32_t		pending:1;
	} b;
};

union spicc_cfg_bus {
	uint32_t			d32;
	struct  {
		uint32_t		clk_div:8;
#define SPICC_CLK_DIV_MAX		255

		/* signed, -8~-1 early, 1~7 later */
		uint32_t		rx_tuning:4;
		uint32_t		tx_tuning:4;

		uint32_t		ss_leading_gap:4;
		uint32_t		lane:2;
#define SPICC_SINGLE_SPI		0
#define SPICC_DUAL_SPI			1
#define SPICC_QUAD_SPI			2

		uint32_t		half_duplex_en:1;
		uint32_t		little_endian_en:1;
		uint32_t		dc_mode:1;
#define SPICC_DC_MODE_PIN		0
#define SPICC_DC_MODE_9BIT		1

		uint32_t		null_ctl:1;
		uint32_t		dummy_ctl:1;
		uint32_t		read_turn_around:2;
#define SPICC_READ_TURN_AROUND_DEFAULT	1

		uint32_t		keep_ss:1;
		uint32_t		cpha:1;
		uint32_t		cpol:1;
	} b;
};

struct spicc_sg_link {
	uint32_t			valid:1;
	uint32_t			eoc:1;
	uint32_t			irq:1;
	uint32_t			act:3;
	uint32_t			ring:1;
	uint32_t			rsv:1;
	uint32_t			len:24;
#define SPICC_SG_LEN_MAX		0x1000000
#define SPICC_SG_TX_LEN_MAX		SPICC_SG_LEN_MAX
#define SPICC_SG_RX_LEN_MAX		SPICC_SG_LEN_MAX

#ifdef CONFIG_ARM64_SPICC
	uint64_t			addr;
	uint32_t			addr_rsv;
#else
	uint32_t			addr;
#endif
};

struct spicc_descriptor {
	union spicc_cfg_start		cfg_start;
	union spicc_cfg_bus		cfg_bus;
	struct spicc_sg_link		*tx_sg;
	struct spicc_sg_link		*rx_sg;
};

struct spicc_xfer {
	const void			*tx_buf;
	void				*rx_buf;
	int				len;
	unsigned long			flags;
};

struct spicc_device {
	void __iomem			*base;
	struct clk			sys_clk;
	struct clk			spi_clk;
	uint32_t			real_speed_hz;
	uint32_t			bytes_per_word;
	uint32_t			pm_id;
	union spicc_cfg_spi		cfg_spi;
	union spicc_cfg_start		cfg_start;
	union spicc_cfg_bus		cfg_bus;
	uint8_t				config_data_mode;
	struct spicc_xfer		xfer[8];
	int				xfer_num;
};

#define spicc_info(fmt, args...) \
	printf("[info]%s: " fmt, __func__, ## args)

#define spicc_err(fmt, args...) \
	printf("[error]%s: " fmt, __func__, ## args)

//#define SPICC_DEBUG_EN
#ifdef SPICC_DEBUG_EN
#define spicc_dbg(fmt, args...) \
	printf("[debug]%s: " fmt, __func__, ## args)
#else
#define spicc_dbg(fmt, args...)
#endif

#define spicc_writel(_spicc, _val, _offset) \
	 writel(_val, (_spicc)->base + (_offset))
#define spicc_readl(_spicc, _offset) \
	readl((_spicc)->base + (_offset))

/* test flags for spicc, must keep with xfer flags in spi.h */
#define SPI_XFER_LANE		GENMASK(9, 8)	/* 0-single, 1-dual, 2-quad */
#define SPI_XFER_HALF_DUPLEX_EN	BIT(10)		/* 0-full, 1-half */
#define SPI_XFER_DC_MODE	BIT(11)		/* 0-pin, 1-9bit */
#define SPI_XFER_DC_LEVEL	BIT(12)		/* dc bit level */
#define SPI_XFER_NULL_CTL	BIT(13)
#define SPI_XFER_DUMMY_CTL	BIT(14)

#define CONFIG_SPICC_HW_PINCTRL
#define CONFIG_SPICC_HW_CLK

static inline void spicc_flush_dcache(uint64_t addr, int sz)
{
	flush_dcache_range(addr, addr + sz);
}

static inline void spicc_invalidate_dcache(uint64_t addr, int sz)
{
	invalidate_dcache_range(addr, addr + sz);
}

#ifdef CONFIG_SPICC_HW_PINCTRL
/*
 * GPIOT_11[DQ2]	regC[15:12]
 * GPIOT_12[DQ3]	regC[19:16]
 * GPIOT_13[CLK]	regC[23:20]
 * GPIOT_14[MOSI]	regC[27:24]
 * GPIOT_15[MISO]	regC[31:28]
 * GPIOT_16[SS0]	regD[3:0]
 * GPIOT_17[SS1]	regD[7:4]
 * GPIOT_18[SS2]	regD[11:8]
 */
static int spicc0_hw_pinctrl_init(void)
{
	uint32_t val;

	val = readl(PADCTRL_PIN_MUX_REGC);
	val &= 0x00000fff;
	val |= 0x22222000;
	writel(val, PADCTRL_PIN_MUX_REGC);

	val = readl(PADCTRL_PIN_MUX_REGD);
	val &= 0xfffffff0;
	val |= 0x00000002;
	writel(val, PADCTRL_PIN_MUX_REGD);

	/* DQ2/DQ3/MISO/SS0 pullup */
	val = readl(PADCTRL_GPIOT_PULL_UP);
	val |= (1 << 16) | (1 << 15) | (1 << 12) | (1 << 11);
	writel(val, PADCTRL_GPIOT_PULL_UP);

	val = readl(PADCTRL_GPIOT_PULL_EN);
	val |= (1 << 16) | (1 << 15) | (1 << 12) | (1 << 11);
	writel(val, PADCTRL_GPIOT_PULL_EN);

	return 0;
}
#endif /* end of CONFIG_SPICC_HW_PINCTRL */

#ifdef CONFIG_SPICC_HW_CLK
uint32_t spicc_parent_clk_rate[] = {
	24000000,	/* cts_oscin_clk */
	166666667,	/* cts_sys_clk */
	500000000,	/* fclk_div4 */
	666666667,	/* fclk_div3 */
	1000000000,	/* fclk_div2 */
	400000000,	/* fclk_div5 */
	285714287,	/* fclk_div7 */
	000000000,	/* gp1_pll_clk */
};

static int spicc0_hw_clk_init(void)
{
	uint32_t val;

	/* [9]: spicc1 gate, [10]: spicc0 gate */
	val = readl(CLKCTRL_SYS_CLK_EN0_REG1);
	writel(val | (1 << 10) | (1 << 9), CLKCTRL_SYS_CLK_EN0_REG1);

	val = readl(CLKCTRL_SPICC_CLK_CTRL);
	val &= 0xffff0000;
	val |= (5 << 7) | (1 << 6) | (0 << 0);
	writel(val, CLKCTRL_SPICC_CLK_CTRL);

	return 0;
}
#endif /* end of CONFIG_SPICC_HW_CLK */

#ifdef SPICC_DEBUG_EN
static void spicc_dump_sg(struct spicc_sg_link *sg_table, bool is_tx)
{
	struct spicc_sg_link *sg = sg_table;
	uint32_t buf[16];

	do {
		printf("%s_sg@%p\n", is_tx ? "tx" : "rx", sg);
		memcpy(buf, (void *)sg, sizeof(*sg));
		print_buffer((ulong)sg, buf, 4, sizeof(*sg) / sizeof(uint32_t), 0);
		if (sg->eoc)
			break;
		sg++;
	} while (1);
}

static void spicc_dump(struct spicc_device *spicc, struct spicc_descriptor *desc)
{
	uint32_t buf[16];
	int i;

	for (i = 0; i < 16; i++)
		buf[i] = readl(spicc->base + (i * 4));
	printf("register@%p\n", spicc->base);
	print_buffer((ulong)spicc->base, buf, 4, 16, 0);

	if (!desc) {
		printf("no desc\n");
		return;
	}
	do {
		printf("desc@%p\n", desc);
		memcpy(buf, (void *)desc, sizeof(*desc));
		print_buffer((ulong)desc, buf, 4, sizeof(*desc) / sizeof(uint32_t), 0);

		if (!desc->tx_sg)
			printf("no tx\n");
		else if (desc->cfg_start.b.tx_data_mode == SPICC_DATA_MODE_SG)
			spicc_dump_sg(desc->tx_sg, 1);
		else
			printf("tx_mem@%p\n", desc->tx_sg);

		if (!desc->rx_sg)
			printf("no rx\n");
		else if (desc->cfg_start.b.rx_data_mode == SPICC_DATA_MODE_SG)
			spicc_dump_sg(desc->rx_sg, 0);
		else
			printf("rx_mem@%p\n", desc->rx_sg);

		if (desc->cfg_start.b.eoc)
			break;
		desc++;
	} while (1);
}
#endif

static inline int spicc_sem_down_read(struct spicc_device *spicc)
{
	int ret;

	ret = spicc_readl(spicc, SPICC_REG_CFG_READY);
	if (ret)
		spicc_writel(spicc, 0, SPICC_REG_CFG_READY);

	return ret;
}

static inline void spicc_sem_up_write(struct spicc_device *spicc)
{
	spicc_writel(spicc, 1, SPICC_REG_CFG_READY);
}

static int spicc_wait_complete(struct spicc_device *spicc, uint32_t flags, int len)
{
	unsigned long long time;
	uint32_t sts;

	time = 8LL * 1000LL * len / spicc->real_speed_hz; /* unit ms */
	time += time + 20; /* some tolerance */
	time *= 1000; /* unit us */

	do {
		sts = spicc_readl(spicc, SPICC_REG_IRQ_STS);
		if (sts & (SPICC_RCH_DESC_INVALID |
			   SPICC_RCH_DESC_RESP |
			   SPICC_RCH_DATA_RESP |
			   SPICC_WCH_DESC_INVALID |
			   SPICC_WCH_DESC_RESP |
			   SPICC_WCH_DATA_RESP |
			   SPICC_DESC_ERR)) {
			spicc_err("controller error sts=0x%x\n", sts);
			return -EIO;
		}

		if (sts & flags) {
			spicc_writel(spicc, sts, SPICC_REG_IRQ_STS);
			return 0;
		}
		udelay(1);
	} while (time--);

	spicc_err("timedout, sts=0x%x\n", sts);
	return -ETIMEDOUT;
}

static int spicc_claim_bus(struct udevice *dev)
{
	struct spicc_device *spicc = dev_get_priv(dev->parent);
	struct spi_slave *slave = dev_get_parent_priv(dev);
	int ss = spi_chip_select(dev);

	if (!slave->wordlen || slave->wordlen > 64 || slave->wordlen % 8) {
		spicc_err("invalid wordlen %d\n", slave->wordlen);
		return -EINVAL;
	}

	spicc->bytes_per_word = slave->wordlen >> 3;
	spicc->cfg_start.b.block_size = spicc->bytes_per_word & 0x7;
	spicc->cfg_spi.b.ss = ss;

	return 0;
}

static int spicc_release_bus(struct udevice *dev)
{
	return 0;
}

static int spicc_set_speed(struct udevice *bus, uint speed_hz)
{
	struct spicc_device *spicc = dev_get_priv(bus);
	uint32_t pclk_rate;
	uint32_t div;
#ifdef CONFIG_SPICC_HW_CLK
	uint32_t val;
#endif

	if (!speed_hz)
		return 0;

	/* speed = spi_clk rate / (div + 1) */
#ifdef CONFIG_SPICC_HW_CLK
	val = readl(CLKCTRL_SPICC_CLK_CTRL);
	pclk_rate = spicc_parent_clk_rate[(val >> 7) & 0x7];
	pclk_rate /= (val & 0x3f) + 1;
#else
	pclk_rate = clk_get_rate(&spicc->spi_clk);
#endif
	div = DIV_ROUND_UP(pclk_rate, speed_hz);
	if (div)
		div--;
	if (div > SPICC_CLK_DIV_MAX)
		div = SPICC_CLK_DIV_MAX;

	spicc->cfg_bus.b.clk_div = div;
	spicc->real_speed_hz = pclk_rate / (div + 1);
	spicc_dbg("set speed %dHz (real %dHz)\n", speed_hz, spicc->real_speed_hz);

	return 0;
}

static int spicc_set_mode(struct udevice *bus, uint mode)
{
	struct spicc_device *spicc = dev_get_priv(bus);
	union spicc_cfg_bus *cfg_bus = &spicc->cfg_bus;

	cfg_bus->b.cpol = !!(mode & SPI_CPOL);
	cfg_bus->b.cpha = !!(mode & SPI_CPHA);
	cfg_bus->b.little_endian_en = !!(mode & SPI_LSB_FIRST);
	cfg_bus->b.half_duplex_en = !!(mode & SPI_3WIRE);

	if (mode & SPI_TX_QUAD && mode & SPI_RX_QUAD)
		cfg_bus->b.lane = SPICC_QUAD_SPI;
	else if (mode & SPI_TX_DUAL && mode & SPI_RX_DUAL)
		cfg_bus->b.lane = SPICC_DUAL_SPI;
	else
		cfg_bus->b.lane = SPICC_SINGLE_SPI;

	spicc_dbg("set mode 0x%x\n", mode);
	return 0;
}

static void spicc_import_config(struct spicc_device *spicc, unsigned long flags)
{
	spicc->cfg_start.b.dc_level = !!(flags & SPI_XFER_DC_LEVEL);
	spicc->cfg_bus.b.dc_mode = !!(flags & SPI_XFER_DC_MODE);
	spicc->cfg_bus.b.lane = FIELD_GET(SPI_XFER_LANE, flags);
	spicc->cfg_bus.b.half_duplex_en = !!(flags & SPI_XFER_HALF_DUPLEX_EN);
	spicc->cfg_bus.b.null_ctl = !!(flags & SPI_XFER_NULL_CTL);
	spicc->cfg_bus.b.dummy_ctl = !!(flags & SPI_XFER_DUMMY_CTL);
}

static int spicc_xfer_pio(struct spicc_device *spicc, const void *tx_buf,
			  void *rx_buf, int len, bool end)
{
	const uint8_t *t8 = (const uint8_t *)tx_buf;
	uint8_t *r8 = (uint8_t *)rx_buf;
	const uint16_t *t16 = (const uint16_t *)tx_buf;
	uint16_t *r16 = (uint16_t *)rx_buf;
	const uint32_t *t32 = (const uint32_t *)tx_buf;
	uint32_t *r32 = (uint32_t *)rx_buf;
	int ret;

	spicc->cfg_start.b.block_num = 1;
	spicc->cfg_start.b.pending = 1;

	spicc_writel(spicc, 0, SPICC_REG_DESC_LIST_L);
	spicc_writel(spicc, 0, SPICC_REG_DESC_LIST_H);
	len /= spicc->bytes_per_word;
	while (len) {
		len--;
		spicc->cfg_bus.b.keep_ss =  (end && !len) ? 0 : 1;

		if (tx_buf) {
			if (spicc->bytes_per_word == 1) {
				spicc_writel(spicc, *t8++, SPICC_REG_PIO_TX_DATA_L);
			} else if (spicc->bytes_per_word == 2) {
				spicc_writel(spicc, *t16++, SPICC_REG_PIO_TX_DATA_L);
			} else if (spicc->bytes_per_word == 4) {
				spicc_writel(spicc, *t32++, SPICC_REG_PIO_TX_DATA_L);
			} else if (spicc->bytes_per_word == 8) {
				spicc_writel(spicc, *t32++, SPICC_REG_PIO_TX_DATA_L);
				spicc_writel(spicc, *t32++, SPICC_REG_PIO_TX_DATA_H);
			}
		}

		spicc_writel(spicc, spicc->cfg_spi.d32, SPICC_REG_CFG_SPI);
		spicc_writel(spicc, spicc->cfg_bus.d32, SPICC_REG_CFG_BUS);
		spicc_writel(spicc, spicc->cfg_start.d32, SPICC_REG_CFG_START);
		ret = spicc_wait_complete(spicc, SPICC_DESC_DONE, 8);
		if (ret)
			break;

		if (rx_buf) {
			if (spicc->bytes_per_word == 1) {
				*r8++ = spicc_readl(spicc, SPICC_REG_PIO_RX_DATA_L);
			} else if (spicc->bytes_per_word == 2) {
				*r16++ = spicc_readl(spicc, SPICC_REG_PIO_RX_DATA_L);
			} else if (spicc->bytes_per_word == 4) {
				*r32++ = spicc_readl(spicc, SPICC_REG_PIO_RX_DATA_L);
			} else if (spicc->bytes_per_word == 8) {
				*r32++ = spicc_readl(spicc, SPICC_REG_PIO_RX_DATA_L);
				*r32++ = spicc_readl(spicc, SPICC_REG_PIO_RX_DATA_H);
			}
		}
	}

#ifdef SPICC_DEBUG_EN
	spicc_dump(spicc, 0);
#endif

	return ret;
}

static struct spicc_sg_link *spicc_map_buf(uint64_t *addr_table, int *len_table, int nents)
{
	struct spicc_sg_link *sg_table, *sg;
	int i;

	sg_table = kcalloc(nents, sizeof(*sg), GFP_KERNEL);
	if (!sg_table)
		return NULL;

	for (i = 0; i < nents; i++) {
		sg = &sg_table[i];
		sg->valid = 1;
		/* EOC specially for the last sg */
		sg->eoc = (i == nents - 1) ? 1 : 0;
		sg->ring = 0;
		sg->len = len_table[i];
#ifdef CONFIG_ARM64_SPICC
		sg->addr = addr_table[i];
#else
		sg->addr = (uint32_t)addr_table[i];
#endif
	}

	return sg_table;
}

static int spicc_get_sg_num(struct spicc_sg_link *sg_table)
{
	struct spicc_sg_link *sg = sg_table;
	int sg_num = 0;

	if (sg) {
		while (1) {
			sg_num++;
			if (sg->eoc)
				break;
			sg++;
		}
	}

	return sg_num;
}

static int spicc_get_desc_num(struct spicc_descriptor *desc_table)
{
	struct spicc_descriptor *desc = desc_table;
	int desc_num = 0;

	if (desc) {
		while (1) {
			desc_num++;
			if (desc->cfg_start.b.eoc)
				break;
			desc++;
		}
	}

	return desc_num;
}

static int spicc_get_desc_blocks(struct spicc_descriptor *desc_table)
{
	struct spicc_descriptor *desc = desc_table;
	int blocks = 0;

	if (desc) {
		while (1) {
			blocks += desc->cfg_start.b.block_num;
			if (desc->cfg_start.b.eoc)
				break;
			desc++;
		}
	}

	return blocks;
}

static void spicc_sg_flush_dache(struct spicc_sg_link *sg_table)
{
	struct spicc_sg_link *sg;

	if (!sg_table)
		return;

	spicc_flush_dcache((uint64_t)sg_table,
			sizeof(*sg) * spicc_get_sg_num(sg_table));

	sg = sg_table;
	while (1) {
		if (sg->addr && sg->len)
			spicc_flush_dcache(sg->addr, sg->len);
		if (sg->eoc)
			break;
		sg++;
	}
}

static void spicc_sg_invalidate_dcache(struct spicc_sg_link *sg_table)
{
	struct spicc_sg_link *sg;

	if (!sg_table)
		return;

	sg = sg_table;
	while (1) {
		if (sg->addr && sg->len)
			spicc_invalidate_dcache(sg->addr, sg->len);
		if (sg->eoc)
			break;
		sg++;
	}
	spicc_invalidate_dcache((uint64_t)sg_table,
			sizeof(*sg) * spicc_get_sg_num(sg_table));
}

static void spicc_desc_flush_dcache(struct spicc_descriptor *desc_table)
{
	struct spicc_descriptor *desc;
	int len;

	if (!desc_table)
		return;

	spicc_flush_dcache((uint64_t)desc_table,
			sizeof(*desc) * spicc_get_desc_num(desc_table));

	desc = desc_table;
	while (1) {
		len = (desc->cfg_start.b.block_size | 0x8) & 0x7;
		len *= desc->cfg_start.b.block_num;
		if (desc->cfg_start.b.tx_data_mode == SPICC_DATA_MODE_SG)
			spicc_sg_flush_dache(desc->tx_sg);
		else if (desc->cfg_start.b.tx_data_mode == SPICC_DATA_MODE_MEM)
			spicc_flush_dcache((uint64_t)desc->tx_sg, len);
		if (desc->cfg_start.b.rx_data_mode == SPICC_DATA_MODE_SG)
			spicc_sg_flush_dache(desc->rx_sg);
		else if (desc->cfg_start.b.rx_data_mode == SPICC_DATA_MODE_MEM)
			spicc_flush_dcache((uint64_t)desc->rx_sg, len);

		if (desc->cfg_start.b.eoc)
			break;
		desc++;
	}
}

static void spicc_desc_invalidate_dcache(struct spicc_descriptor *desc_table)
{
	struct spicc_descriptor *desc;
	int len;

	if (!desc_table)
		return;

	desc = desc_table;
	while (1) {
		len = (desc->cfg_start.b.block_size | 0x8) & 0x7;
		len *= desc->cfg_start.b.block_num;
		if (desc->cfg_start.b.tx_data_mode == SPICC_DATA_MODE_SG)
			spicc_sg_invalidate_dcache(desc->tx_sg);
		else if (desc->cfg_start.b.tx_data_mode == SPICC_DATA_MODE_MEM)
			spicc_invalidate_dcache((uint64_t)desc->tx_sg, len);
		if (desc->cfg_start.b.rx_data_mode == SPICC_DATA_MODE_SG)
			spicc_sg_invalidate_dcache(desc->rx_sg);
		else if (desc->cfg_start.b.rx_data_mode == SPICC_DATA_MODE_MEM)
			spicc_invalidate_dcache((uint64_t)desc->rx_sg, len);
		if (desc->cfg_start.b.eoc)
			break;
		desc++;
	}
	spicc_invalidate_dcache((uint64_t)desc_table,
			sizeof(*desc) * spicc_get_desc_num(desc_table));
}

static int spicc_config_desc_one_transfer(struct spicc_device *spicc,
			struct spicc_descriptor *desc,
			struct spicc_xfer *xfer)
{
	uint64_t tx_addr = (uint64_t)xfer->tx_buf;
	uint64_t rx_addr = (uint64_t)xfer->rx_buf;
	int xfer_blocks = xfer->len / spicc->bytes_per_word;
	int blocks, len, desc_used_num = 0;
	bool first_desc = 1;

	spicc_import_config(spicc, xfer->flags);
	while (xfer_blocks) {
		blocks = min_t(int, xfer_blocks, SPICC_BLOCK_MAX);
		len = blocks * spicc->bytes_per_word;
		desc->cfg_start.d32 = spicc->cfg_start.d32;
		desc->cfg_bus.d32 = spicc->cfg_bus.d32;
		desc->cfg_start.b.block_size = spicc->bytes_per_word & 0x7;
		desc->cfg_start.b.block_num = blocks;

		if (tx_addr) {
			desc->cfg_start.b.op_mode = SPICC_OP_MODE_WRITE;
			desc->cfg_start.b.tx_data_mode = spicc->config_data_mode;
			if (spicc->config_data_mode == SPICC_DATA_MODE_SG)
				desc->tx_sg = spicc_map_buf(&tx_addr, &len, 1);
			else if (first_desc)
				desc->tx_sg = (struct spicc_sg_link *)tx_addr;
			else
				desc->tx_sg = 0;
			tx_addr += len;
		}

		if (rx_addr) {
			desc->cfg_start.b.op_mode = SPICC_OP_MODE_READ;
			desc->cfg_start.b.rx_data_mode = spicc->config_data_mode;
			desc->cfg_bus.b.read_turn_around = SPICC_READ_TURN_AROUND_DEFAULT;
			if (spicc->config_data_mode == SPICC_DATA_MODE_SG)
				desc->rx_sg = spicc_map_buf(&rx_addr, &len, 1);
			else if (first_desc)
				desc->rx_sg = (struct spicc_sg_link *)rx_addr;
			else
				desc->rx_sg = 0;
			rx_addr += len;
		}

		desc++;
		desc_used_num++;
		xfer_blocks -= blocks;
		first_desc = 0;
	}

	if (desc_used_num && (xfer->flags & SPI_XFER_END)) {
		desc--;
		desc->cfg_start.b.eoc = 1;
		desc->cfg_bus.b.keep_ss = 0;
	}

	return desc_used_num;
}

static struct spicc_descriptor *spicc_create_desc_table
			(struct spicc_device *spicc,
			struct spicc_xfer *xfer,
			int  xfer_num)
{
	struct spicc_descriptor *desc, *desc_bk;
	int blocks, desc_num = 0;
	int i;

	/*calculate the desc num for all xfer */
	for (i = 0; i < xfer_num; i++) {
		blocks = xfer[i].len / spicc->bytes_per_word;
		desc_num += DIV_ROUND_UP(blocks, SPICC_BLOCK_MAX);
	}

	desc = kcalloc(desc_num, sizeof(*desc), GFP_KERNEL);
	desc_bk = desc;
	if (!desc_num || !desc)
		return NULL;

	/* default */
	spicc->cfg_start.b.tx_data_mode = SPICC_DATA_MODE_NONE;
	spicc->cfg_start.b.rx_data_mode = SPICC_DATA_MODE_NONE;
	spicc->cfg_start.b.pending = 1;
	spicc->cfg_start.b.eoc = 0;
	spicc->cfg_bus.b.keep_ss = 1;

	while (xfer_num--) {
		desc_num = spicc_config_desc_one_transfer(spicc, desc, xfer);
		desc += desc_num;
		xfer++;
	}

	return desc_bk;
}

static void spicc_destroy_desc_table(struct spicc_descriptor *desc_table)
{
	struct spicc_descriptor *desc = desc_table;

	if (!desc)
		return;

	while (1) {
		if (desc->tx_sg && desc->cfg_start.b.tx_data_mode == SPICC_DATA_MODE_SG)
			free(desc->tx_sg);
		if (desc->rx_sg && desc->cfg_start.b.rx_data_mode == SPICC_DATA_MODE_SG)
			free(desc->rx_sg);

		if (desc->cfg_start.b.eoc)
			break;
		desc++;
	}

	free(desc_table);
}

static int spicc_xfer_desc(struct spicc_device *spicc,
			 struct spicc_descriptor *desc_table)
{
	int ret;

	spicc_desc_flush_dcache(desc_table);
	spicc_writel(spicc, spicc->cfg_spi.d32, SPICC_REG_CFG_SPI);
	spicc_writel(spicc, 0, SPICC_REG_CFG_BUS);
	spicc_writel(spicc, 0, SPICC_REG_CFG_START);
	spicc_writel(spicc, (uint64_t)desc_table & 0xffffffff,
		     SPICC_REG_DESC_LIST_L);
	spicc_writel(spicc, ((uint64_t)desc_table >> 32) | SPICC_DESC_PENDING,
		     SPICC_REG_DESC_LIST_H);
	ret = spicc_wait_complete(spicc, SPICC_DESC_CHAIN_DONE,
		spicc_get_desc_blocks(desc_table) * spicc->bytes_per_word);
#ifdef SPICC_DEBUG_EN
	spicc_dump(spicc, desc_table);
#endif
	spicc_desc_invalidate_dcache(desc_table);

	return ret;
}

static int spicc_xfer(struct udevice *dev, unsigned int bitlen,
		      const void *dout, void *din, unsigned long flags)
{
	struct spicc_device *spicc = dev_get_priv(dev->parent);
	struct spi_slave *slave = dev_get_parent_priv(dev);
	int len = bitlen >> 3;
	struct spicc_descriptor *desc_table;
	int ret = -EIO;

	spicc_dbg("bitlen %d, dout %p, din %p, flags 0x%x\n",
		   bitlen, dout, din, (unsigned int)flags);

	if (bitlen % slave->wordlen) {
		spicc_err("invalid transfer length %d\n", bitlen);
		return -EINVAL;
	}

	if (spicc->config_data_mode != SPICC_DATA_MODE_PIO) {
		struct spicc_xfer *xfer;

		if (flags & SPI_XFER_BEGIN)
			spicc->xfer_num = 0;
		xfer = &spicc->xfer[spicc->xfer_num];
		xfer->tx_buf = dout;
		xfer->rx_buf = din;
		xfer->len = len;
		xfer->flags = flags;
		spicc->xfer_num++;

		if (!(flags & SPI_XFER_END))
			return spicc->xfer_num;
	}

	if (!spicc_sem_down_read(spicc)) {
		spicc_err("controller busy\n");
		return -EBUSY;
	}

	if (spicc->config_data_mode == SPICC_DATA_MODE_PIO) {
		ret = spicc_xfer_pio(spicc, dout, din, len, flags & SPI_XFER_END);
	} else {
		desc_table = spicc_create_desc_table(spicc, spicc->xfer,
						     spicc->xfer_num);
		ret = spicc_xfer_desc(spicc, desc_table);
		spicc_destroy_desc_table(desc_table);
	}

	spicc_sem_up_write(spicc);
	spicc_dbg("end: %d\n", ret);

	return ret;
}

static int spicc_probe(struct udevice *bus)
{
	struct spicc_device *spicc = dev_get_priv(bus);
	int ret;

	spicc->base = (void __iomem *)dev_read_addr(bus);
	spicc_info("addr base 0x%p\n", spicc->base);

#ifdef CONFIG_SECURE_POWER_CONTROL
	if (!dev_read_u32(bus, "pm-id", &spicc->pm_id)) {
		pwr_ctrl_psci_smc(spicc->pm_id, true);
		spicc_info("power on %d\n", spicc->pm_id);
	}
#endif

	/* there are 2 clk using in spi controller,
	 * spi_clk: from clock tree control, using for spi phy;
	 * sys_clk: from clk81(166MHz), using for others such as apb bus;
	 */
#ifdef CONFIG_SPICC_HW_CLK
	ret = spicc0_hw_clk_init();
#else
	if (!clk_get_by_name(bus, "sys_clk", &spicc->sys_clk))
		clk_enable(&spicc->sys_clk);
	ret = clk_get_by_name(bus, "spi_clk", &spicc->spi_clk);
	if (ret) {
		spicc_err("failed to get spi_clk(%d)\n", ret);
		return ret;
	}
	clk_enable(&spicc->spi_clk);
	spicc_info("spi_clk rate %lu\n", clk_get_rate(&spicc->spi_clk));
#endif

#ifdef CONFIG_SPICC_HW_PINCTRL
	ret = spicc0_hw_pinctrl_init();
#endif

	spicc->config_data_mode = SPICC_DATA_MODE_MEM;
	spicc->cfg_spi.d32 = 0;
	spicc->cfg_start.d32 = 0;
	spicc->cfg_bus.d32 = 0;

	spicc->cfg_spi.b.flash_wp_pin_en = 1;
	spicc->cfg_spi.b.flash_hold_pin_en = 1;
	/* default no eoc */
	spicc->cfg_start.b.eoc = 0;
	/* default pending */
	spicc->cfg_start.b.pending = 1;
	/* default keep ss */
	spicc->cfg_bus.b.keep_ss = 1;

	return ret;
}

static const struct udevice_id spicc_of_match[] = {
	{
		.compatible	= "amlogic,meson-a4-spicc",
		.data		= 0,
	},
	{ /* sentinel */ }
};

static const struct dm_spi_ops spicc_ops = {
	.claim_bus = spicc_claim_bus,
	.release_bus = spicc_release_bus,
	.xfer = spicc_xfer,
	.set_speed = spicc_set_speed,
	.set_mode = spicc_set_mode,
	.set_wordlen = 0,
};

U_BOOT_DRIVER(spicc_v2) = {
	.name = "spicc_v2",
	.id = UCLASS_SPI,
	.of_match = spicc_of_match,
	.priv_auto_alloc_size = sizeof(struct spicc_device),
	.per_child_auto_alloc_size = sizeof(struct spi_slave),
	.ops = &spicc_ops,
	.probe = spicc_probe,
};
