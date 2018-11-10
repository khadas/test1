// SPDX-License-Identifier: (GPL-2.0+ OR MIT)
/*
 * Amlogic Meson SPI flash controller(SPIFC)
 *
 * Copyright (C) 2018 Amlogic Corporation
 *
 * Licensed under the GPL-2 or later.
 *
 */

#include <common.h>
#include <dm.h>
#include <errno.h>
#include <clk.h>
#include <asm/io.h>
#include <asm/gpio.h>
#include <asm/arch/secure_apb.h>
#include <spi.h>
#include <amlogic/spifc.h>
#include <dm/device-internal.h>
#include <dm/uclass-internal.h>
#include <dm/root.h>
#include <dm/lists.h>
#include <dm/util.h>
#include <dm/pinctrl.h>

DECLARE_GLOBAL_DATA_PTR;

struct spifc_regs {
	u32 cmd;
		#define SPI_FLASH_READ    31
		#define SPI_FLASH_WREN    30
		#define SPI_FLASH_WRDI    29
		#define SPI_FLASH_RDID    28
		#define SPI_FLASH_RDSR    27
		#define SPI_FLASH_WRSR    26
		#define SPI_FLASH_PP      25
		#define SPI_FLASH_SE      24
		#define SPI_FLASH_BE      23
		#define SPI_FLASH_CE      22
		#define SPI_FLASH_DP      21
		#define SPI_FLASH_RES     20
		#define SPI_HPM           19
		#define SPI_FLASH_USR     18
		#define SPI_FLASH_USR_ADDR 15
		#define SPI_FLASH_USR_DUMMY 14
		#define SPI_FLASH_USR_DIN   13
		#define SPI_FLASH_USR_DOUT   12
		#define SPI_FLASH_USR_DUMMY_BLEN   10
		#define SPI_FLASH_USR_CMD     0
	u32 addr;
		#define SPI_FLASH_BYTES_LEN 24
		#define SPI_FLASH_ADDR_START 0
	u32 ctrl;
		#define FAST_READ_QUAD_IO 24
		#define FAST_READ_DUAL_IO 23
		#define FAST_READ_QUAD_OUT 20
		#define SPI_ENABLE_AHB    17
		#define SPI_SST_AAI       16
		#define SPI_RES_RID       15
		#define FAST_READ_DUAL_OUT 14
		#define SPI_READ_READ_EN  13
		#define SPI_CLK_DIV0      12
		#define SPI_CLKCNT_N      8
		#define SPI_CLKCNT_H      4
		#define SPI_CLKCNT_L      0
	u32 ctrl1;
	u32 status;
	u32 ctrl2;
	u32 clock;
		#define SPI_CLK_DIV0_NEW  31
		#define SPI_PRE_SCALE_DIV 18
		#define SPI_CLKCNT_N_NEW  12
		#define SPI_CLKCNT_H_NEW  6
		#define SPI_CLKCNT_L_NEW  0
	u32 user;
		#define USER_CMD_INCLUDE_CMD        31
		#define USER_CMD_INCLUDE_ADDR       30
		#define USER_CMD_INCLUDE_DUMMY      29
		#define USER_CMD_INCLUDE_DIN        28
		#define USER_CMD_INCLUDE_DOUT       27
		#define USER_CMD_DUMMY_IDLE         26
		#define USER_CMD_HIGHPART_DURING_SPI_DOUT_STAGE      25
		#define USER_CMD_HIGHPART_DURING_SPI_DIN_STAGE       24
		#define USER_CMD_EXT_HOLD_IN_STA_PREP  23
		#define USER_CMD_EXT_HOLD_IN_STA_CMD   22
		#define USER_CMD_EXT_HOLD_IN_STA_ADDR  21
		#define USER_CMD_EXT_HOLD_IN_STA_DUMMY 20
		#define USER_CMD_EXT_HOLD_IN_STA_DIN   19
		#define USER_CMD_EXT_HOLD_IN_STA_DOUT  18
		#define USER_CMD_EXT_HOLD_POLARITY  17
		#define SINGLE_DIO_MODE             16
		#define FAST_WRITE_QUAD_IO          15
		#define FAST_WRITE_DUAL_IO          14
		#define FAST_WRITE_QUAD_OUT         13
		#define FAST_WRITE_DUAL_OUT         12
		#define WRITE_BYTE_ORDER            11
		#define READ_BYTE_ORDER             10
		#define AHB_ENDIAN_MODE             8
		#define MASTER_CLK_EDGE             7
		#define SLAVE_CLK_EDGE              6
		#define CS_VALID_IN_STA_PREP        5
		#define CS_VALID_IN_STA_DONE        4
		#define AHB_READ_APPLY_CONFIG       3
		#define COMPATIBLE_TO_APPOLO        2
		#define AHP_READ_SUPPORT_4BYTE_ADDR 1
		#define EN_DIN_DURING_SPI_DOUT_STAGE    0
	u32 user1;
		#define USER_CMD_ADDR_BITS         26
		#define USER_CMD_DOUT_BITS         17
		#define USER_CMD_DIN_BITS          8
		#define USER_CMD_DUMMY_BITS        0
	u32 user2;
		#define USER_CMD_CMD_BITS          28
		#define USER_CMD_CMD_VALUE         0
	u32 user3;
	u32 user4; //pin register
		#define CS_KEEP_ACTIVE_AFTER_TRANS 30
	u32 slave;
	u32 slave1;
	u32 slave2;
	u32 slave3;
	u32 cache[8];
	u32 buffer[8];
		#define SPIFC_CACHE_SIZE_IN_WORD 16
		#define SPIFC_CACHE_SIZE_IN_BYTE SPIFC_CACHE_SIZE_IN_WORD << 2
};

/*
 * @reg: controller registers address.
 * @mem_map: memory_mapped for read operations.
 * @core: clk source.
 * @speed: spi bus frequency, and you should know
 *         we use clk_81 as a clk source now, max
 *         speed is 166M.
 * @io_num: max io number, SIO0 SIO1 SIO2 SIO3.
 * @num_chipselect: the slave number we select.
 * @cs_gpios: gpio array, we use the cs pin as
 *            gpio, cause the spifc controller
 *            can not hold enough time sometimes.
 */

struct spifc_platdata {
	ulong reg;
	ulong mem_map;
#if defined(CONFIG_CLK) && (CONFIG_CLK)
	struct clk core;
#endif/* CONFIG_CLK */
	u32 speed;
	u32 io_num;
	u32 num_chipselect;
	struct gpio_desc cs_gpios[SPIFC_MAX_CS];
};

struct spifc_priv {
	struct spifc_regs *regs;
	void __iomem *mem_map;
	unsigned int speed;
	unsigned int mode;
	unsigned int wordlen;
	unsigned char cmd;
};

/* flash dual/quad read command */
#define FCMD_READ				0x03
#define FCMD_READ_FAST			0x0b
#define FCMD_READ_DUAL_OUT		0x3b
#define FCMD_READ_QUAD_OUT		0x6b
#define FCMD_READ_DUAL_IO		0xbb
#define FCMD_READ_QUAD_IO		0xeb
/* flash quad write command */
#define FCMD_WRITE				0x02
#define FCMD_WRITE_QUAD_OUT		0x32

#define CONFIG_SPIFC_DEFAULT_SPEED 40000000

static void spifc_set_rx_op_mode(struct spifc_priv *priv,
				 unsigned int slave_mode, unsigned char cmd)
{
	unsigned int val;

	val = readl(&priv->regs->ctrl);
	val &= ~((1 << FAST_READ_DUAL_OUT) |
			(1 << FAST_READ_QUAD_OUT) |
			(1 << FAST_READ_DUAL_IO) |
			(1 << FAST_READ_QUAD_IO));

	if (slave_mode & SPI_RX_DUAL) {
		if (cmd == FCMD_READ_DUAL_OUT)
			val |= 1 << FAST_READ_DUAL_OUT;
	}
	if (slave_mode & SPI_RX_QUAD) {
		if (cmd == FCMD_READ_QUAD_OUT)
			val |= 1 << FAST_READ_QUAD_OUT;
	}
	writel(val, &priv->regs->ctrl);
}

static void spifc_set_tx_op_mode(struct spifc_priv *priv,
				 unsigned int slave_mode, unsigned char cmd)
{
	unsigned int val = 0;

	if (slave_mode & SPI_TX_QUAD) {
		if (cmd == FCMD_WRITE_QUAD_OUT)
			val |= 1 << FAST_WRITE_QUAD_OUT;
	}
	writel(val, &priv->regs->user);
}

static int spifc_user_cmd(struct spifc_priv *priv,
			  u8 cmd, u8 *buf, u8 len)
{
	struct spifc_regs *regs = priv->regs;
	u16 bits = len ? ((len << 3) - 1) : 0;
	u32 addr = 0;

	if (buf)
		addr = (buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | buf[3];
	clrbits_le32(&regs->ctrl,
		     (1 << FAST_READ_DUAL_OUT) |
		     (1 << FAST_READ_QUAD_OUT) |
		     (1 << FAST_READ_DUAL_IO) |
		     (1 << FAST_READ_QUAD_IO));
	writel((1 << USER_CMD_INCLUDE_CMD) |
			((!!len) << USER_CMD_INCLUDE_ADDR),
			&regs->user);
	writel((7 << USER_CMD_CMD_BITS) |
			(cmd << USER_CMD_CMD_VALUE),
			&regs->user2);
	writel(bits << USER_CMD_ADDR_BITS, &regs->user1);
	writel(addr << SPI_FLASH_ADDR_START, &regs->addr);
	writel((1 << SPI_FLASH_USR) |
			(cmd << SPI_FLASH_USR_CMD),
			&regs->cmd);
	while ((readl(&regs->cmd) >> SPI_FLASH_USR) & 1)
		;
	return 0;
}

static int spifc_user_cmd_dout(struct spifc_priv *priv,
			       u8 *buf, int len, unsigned long flags)
{
	struct spifc_regs *regs = priv->regs;
	unsigned int *cache;
	u32 *p;
	int len32, i;

	p = (u32 *)buf;
	cache = (unsigned int *)&regs->cache;
	len32 = (len / 4) + !!(len % 4);
	for (i = 0; i < len32; i++)
		writel(*p++, cache++);

	setbits_le32(&regs->user, 1 << USER_CMD_INCLUDE_DOUT);
	writel(0, &regs->user2);
	writel(((len << 3) - 1) << USER_CMD_DOUT_BITS, &regs->user1);
	writel(0, &regs->addr);
	writel(1 << SPI_FLASH_USR, &regs->cmd);
	while ((readl(&regs->cmd) >> SPI_FLASH_USR) & 1)
		;
	return 0;
}

static int spifc_user_cmd_din(struct spifc_priv *priv,
			      u8 *buf, int len, unsigned long flags)
{
	struct spifc_regs *regs = priv->regs;
	unsigned int *cache;
	u32 *p;
	int len32, i;
	u8 temp_buf[SPIFC_CACHE_SIZE_IN_BYTE];

	writel(1 << USER_CMD_INCLUDE_DIN, &regs->user);
	writel(0, &regs->user2);
	writel(((len << 3) - 1) << USER_CMD_DIN_BITS, &regs->user1);
	writel(0, &regs->addr);
	writel(1 << SPI_FLASH_USR, &regs->cmd);
	while ((readl(&regs->cmd) >> SPI_FLASH_USR) & 1)
		;
	p = (u32 *)temp_buf;
	cache = (unsigned int *)&regs->cache;
	len32 = (len / 4) + !!(len % 4);
	for (i = 0; i < len32; i++)
		*p++ = readl(cache++);
	memcpy(buf, temp_buf, len);
	return 0;
}

static int spifc_claim_bus(struct udevice *dev)
{
#if 1
	struct udevice *bus = dev->parent;
	struct spifc_platdata *plat = dev_get_platdata(bus);
	int ret, i;

	ret = pinctrl_select_state(bus, "default");
	if (ret) {
		printf("%s %d ret %d\n", __func__, __LINE__, ret);
		return ret;
	}
	for (i = 0; i < ARRAY_SIZE(plat->cs_gpios); i++) {
		dm_gpio_free(bus, &plat->cs_gpios[i]);
		ret = gpio_request_by_name(bus, "cs-gpios",
					   i, &plat->cs_gpios[i], 0);
		if (ret) {
			printf("can't get cs pin%d\n", i);
			return ret;
		}
		ret = dm_gpio_is_valid(&plat->cs_gpios[i]);
		if (!ret) {
			printf("gpio:%d invalid!\n", i);
			return ret;
		}
		ret = dm_gpio_set_dir_flags(&plat->cs_gpios[i], GPIOD_IS_OUT);
	}
	return ret;
#else
	return 0;
#endif
}

static int spifc_release_bus(struct udevice *bus)
{
	return 0;
}

static void spifc_chipselect(struct udevice *dev, bool select)
{
	struct udevice *bus = dev->parent;
	struct spifc_platdata *plat = dev_get_platdata(bus);
	struct spi_slave *slave = dev_get_parent_priv(dev);
	bool level = slave->mode & SPI_CS_HIGH;
	int cs = spi_chip_select(dev);

	if (cs > plat->num_chipselect) {
		printf("cs %d exceed the bus num_chipselect\n", cs);
		return;
	}
	if (!select)
		level = !level;
	dm_gpio_set_value(&plat->cs_gpios[cs], level);
}

static int spifc_set_speed(struct udevice *bus, uint hz)
{
	struct spifc_priv *priv = dev_get_priv(bus);
	struct spifc_regs *regs = priv->regs;
	u32 div, value;

	priv->speed = hz;

	if (!hz)
		return 0;

	value = SPIFC_DEFAULT_CLK_RATE;
	div = value / hz;
	if (div < 2)
		div = 2;
#ifdef CONFIG_SPIFC_COMPATIBLE_TO_APPOLO
	if (div > 0x10)
		div = 0x10;
	value = readl(&regs->ctrl);
	value &= ~(0x1fff << SPI_CLKCNT_L);
	value |= ((div >> 1) - 1) << SPI_CLKCNT_H;
	value |= (div - 1) << SPI_CLKCNT_N;
	value |= (div - 1) << SPI_CLKCNT_L;
	writel(value, &regs->ctrl);
#else
	if (div > 0x40)
		div = 0x40;
	value = ((div >> 1) - 1) << SPI_CLKCNT_H_NEW;
	value |= (div - 1) << SPI_CLKCNT_N_NEW;
	value |= (div - 1) << SPI_CLKCNT_L_NEW;
	writel(value, &regs->clock);
#endif

	return 0;
}

static int spifc_set_mode(struct udevice *bus, uint mode)
{
	struct spifc_priv *priv = dev_get_priv(bus);

	if (mode == priv->mode)
		return 0;
	priv->mode = mode;
	return 0;
}

static int spifc_set_wordlen(struct udevice *bus, unsigned int wordlen)
{
	if (wordlen != 8)
		return -1;
	return 0;
}

static int spifc_xfer(struct udevice *dev,
		      unsigned int bitlen,
				const void *dout,
				void *din,
				unsigned long flags)
{
	struct udevice *bus = dev->parent;
	struct spi_slave *slave = dev_get_parent_priv(dev);
	struct spifc_priv *priv = dev_get_priv(bus);
	u8 *buf;
	int len = bitlen >> 3;
	int lening;
	int ret = 0;

	if (bitlen % 8) {
		printf("%s: error bitlen\n", __func__);
		return -EINVAL;
	}
	spifc_set_speed(bus, slave->max_hz);
	spifc_set_mode(bus, slave->mode);
	if (flags & SPI_XFER_BEGIN) {
		spifc_chipselect(dev, 1);
		buf = (u8 *)dout;
		if (!buf || len > 5) {
			printf("%s: error command\n", __func__);
			ret = -EINVAL;
		} else {
			spifc_user_cmd(priv, buf[0], &buf[1], len - 1);
			/* save the command for next xfer dual/quad setting */
			priv->cmd = buf[0];
		}
	} else if (dout && priv->cmd) {
		buf = (u8 *)dout;
		spifc_set_tx_op_mode(priv, slave->mode, priv->cmd);
		while (len > 0) {
			lening = min_t(size_t, SPIFC_CACHE_SIZE_IN_BYTE, len);
			ret = spifc_user_cmd_dout(priv, buf, lening, flags);
			if (ret)
				break;
			buf += lening;
			len -= lening;
		}
	} else if (din && priv->cmd) {
		buf = (u8 *)din;
		spifc_set_rx_op_mode(priv, slave->mode, priv->cmd);
		while (len > 0) {
			lening = min_t(size_t, SPIFC_CACHE_SIZE_IN_BYTE, len);
			ret = spifc_user_cmd_din(priv, buf, lening, flags);
			if (ret)
				break;
			buf += lening;
			len -= lening;
		}
	}
	if (ret || flags & SPI_XFER_END) {
		spifc_chipselect(dev, 0);
		priv->cmd = 0;
	}
	return ret;
}

static int spifc_probe(struct udevice *bus)
{
	struct spifc_platdata *plat = dev_get_platdata(bus);
	struct spifc_priv *priv = dev_get_priv(bus);

	priv->regs = (struct spifc_regs *)plat->reg;
	priv->speed = plat->speed;
	priv->mode = -1;

	return 0;
}

static int spifc_ofdata_to_platdata(struct udevice *bus)
{
	struct spifc_platdata *plat = dev_get_platdata(bus);
	const void *blob = gd->fdt_blob;
	int node = dev_of_offset(bus);
	int ret, i;

	plat->reg = (ulong)dev_read_addr_ptr(bus);
	/* plat->mem_map = fdtdec_get_addr(blob, node, "ahb"); */
#if defined(CONFIG_CLK) && (CONFIG_CLK)
	ret = clk_get_by_name(bus, "core", &plat->core);
	if (ret) {
		printf("can't get clk source!\n");
		return ret;
	}
	ret = clk_enable(&plat->core);
	if (ret) {
		printf("enable clk source fail\n");
		return ret;
	}
#endif/* CONFIG_CLK */
	plat->speed = fdtdec_get_uint(blob, node,
				      "max-frequency",
				      40000000);
	plat->io_num = fdtdec_get_uint(blob, node,
				       "max-io",
				       0);
	plat->num_chipselect = fdtdec_get_uint(blob, node,
					       "max-cs",
					       0);
	for (i = 0; i < ARRAY_SIZE(plat->cs_gpios); i++) {
		ret = gpio_request_by_name(bus, "cs-gpios",
					   i, &plat->cs_gpios[i], 0);
		if (ret) {
			printf("can't get cs pin%d\n", i);
			return ret;
		}
		ret = dm_gpio_is_valid(&plat->cs_gpios[i]);
		if (!ret) {
			printf("gpio:%d invalid!\n", i);
			return ret;
		}
		/* gpio act like cs pin, default dir-out and pull up */
		ret = dm_gpio_set_dir_flags(&plat->cs_gpios[i], GPIOD_IS_OUT);
	}
	printf("spifc freq %d, max io %d, reg %p\n",
	       plat->speed, plat->io_num, (void *)plat->reg);
	return ret;
}

static const struct udevice_id spifc_ids[] = {
	{ .compatible = "amlogic,spifc" },
	{ }
};

static const struct dm_spi_ops spifc_ops = {
	.claim_bus = spifc_claim_bus,
	.release_bus = spifc_release_bus,
	.xfer = spifc_xfer,
	.set_speed = spifc_set_speed,
	.set_mode = spifc_set_mode,
	.set_wordlen = spifc_set_wordlen,
};

U_BOOT_DRIVER(spifc) = {
	.name = "spifc",
	.id = UCLASS_SPI,
	.of_match = spifc_ids,
	.ofdata_to_platdata = spifc_ofdata_to_platdata,
	.platdata_auto_alloc_size = sizeof(struct spifc_platdata),
	.priv_auto_alloc_size = sizeof(struct spifc_priv),
	.per_child_auto_alloc_size = sizeof(struct spi_slave),
	.ops = &spifc_ops,
	.probe = spifc_probe,
};
