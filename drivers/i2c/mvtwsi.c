/*
 * Driver for the TWSI (i2c) controller found on the Marvell
 * orion5x and kirkwood SoC families.
 *
 * Author: Albert Aribaud <albert.u.boot@aribaud.net>
 * Copyright (c) 2010 Albert Aribaud.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <i2c.h>
#include <asm/errno.h>
#include <asm/io.h>
#ifdef CONFIG_DM_I2C
#include <dm.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

/*
 * Include a file that will provide CONFIG_I2C_MVTWSI_BASE*, and possibly other
 * settings
 */

#ifndef CONFIG_DM_I2C
#if defined(CONFIG_ORION5X)
#include <asm/arch/orion5x.h>
#elif (defined(CONFIG_KIRKWOOD) || defined(CONFIG_ARCH_MVEBU))
#include <asm/arch/soc.h>
#elif defined(CONFIG_SUNXI)
#include <asm/arch/i2c.h>
#else
#error Driver mvtwsi not supported by SoC or board
#endif
#endif /* CONFIG_DM_I2C */

/*
 * TWSI register structure
 */

#ifdef CONFIG_SUNXI

struct  mvtwsi_registers {
	u32 slave_address;
	u32 xtnd_slave_addr;
	u32 data;
	u32 control;
	u32 status;
	u32 baudrate;
	u32 soft_reset;
};

#else

struct  mvtwsi_registers {
	u32 slave_address;
	u32 data;
	u32 control;
	union {
		u32 status;	/* When reading */
		u32 baudrate;	/* When writing */
	};
	u32 xtnd_slave_addr;
	u32 reserved[2];
	u32 soft_reset;
};

#endif

#ifdef CONFIG_DM_I2C
struct mvtwsi_i2c_dev {
	/* TWSI Register base for the device */
	struct mvtwsi_registers *base;
	/* Number of the device (determined from cell-index property) */
	int index;
	/* The I2C slave address for the device */
	u8 slaveadd;
	/* The configured I2C speed in Hz */
	uint speed;
};
#endif /* CONFIG_DM_I2C */

/*
 * enum mvtwsi_ctrl_register_fields - Bit masks for flags in the control
 * register
 */
enum mvtwsi_ctrl_register_fields {
	/* Acknowledge bit */
	MVTWSI_CONTROL_ACK	= 0x00000004,
	/* Interrupt flag */
	MVTWSI_CONTROL_IFLG	= 0x00000008,
	/* Stop bit */
	MVTWSI_CONTROL_STOP	= 0x00000010,
	/* Start bit */
	MVTWSI_CONTROL_START	= 0x00000020,
	/* I2C enable */
	MVTWSI_CONTROL_TWSIEN	= 0x00000040,
	/* Interrupt enable */
	MVTWSI_CONTROL_INTEN	= 0x00000080,
};

/*
 * On sun6i and newer, IFLG is a write-clear bit, which is cleared by writing 1;
 * on other platforms, it is a normal r/w bit, which is cleared by writing 0.
 */

#ifdef CONFIG_SUNXI_GEN_SUN6I
#define	MVTWSI_CONTROL_CLEAR_IFLG	0x00000008
#else
#define	MVTWSI_CONTROL_CLEAR_IFLG	0x00000000
#endif

/*
 * enum mvstwsi_status_values - Possible values of I2C controller's status
 * register
 *
 * Only those statuses expected in normal master operation on
 * non-10-bit-address devices are specified.
 *
 * Every status that's unexpected during normal operation (bus errors,
 * arbitration losses, missing ACKs...) is passed back to the caller as an error
 * code.
 */
enum mvstwsi_status_values {
	/* START condition transmitted */
	MVTWSI_STATUS_START		= 0x08,
	/* Repeated START condition transmitted */
	MVTWSI_STATUS_REPEATED_START	= 0x10,
	/* Address + write bit transmitted, ACK received */
	MVTWSI_STATUS_ADDR_W_ACK	= 0x18,
	/* Data transmitted, ACK received */
	MVTWSI_STATUS_DATA_W_ACK	= 0x28,
	/* Address + read bit transmitted, ACK received */
	MVTWSI_STATUS_ADDR_R_ACK	= 0x40,
	/* Address + read bit transmitted, ACK not received */
	MVTWSI_STATUS_ADDR_R_NAK	= 0x48,
	/* Data received, ACK transmitted */
	MVTWSI_STATUS_DATA_R_ACK	= 0x50,
	/* Data received, ACK not transmitted */
	MVTWSI_STATUS_DATA_R_NAK	= 0x58,
	/* No relevant status */
	MVTWSI_STATUS_IDLE		= 0xF8,
};

/*
 * enum mvstwsi_ack_flags - Determine whether a read byte should be
 * acknowledged or not.
 */
enum mvtwsi_ack_flags {
	/* Send NAK after received byte */
	MVTWSI_READ_NAK = 0,
	/* Send ACK after received byte */
	MVTWSI_READ_ACK = 1,
};

#ifndef CONFIG_DM_I2C
/*
 * MVTWSI controller base
 */

static struct mvtwsi_registers *twsi_get_base(struct i2c_adapter *adap)
{
	switch (adap->hwadapnr) {
#ifdef CONFIG_I2C_MVTWSI_BASE0
	case 0:
		return (struct mvtwsi_registers *)CONFIG_I2C_MVTWSI_BASE0;
#endif
#ifdef CONFIG_I2C_MVTWSI_BASE1
	case 1:
		return (struct mvtwsi_registers *)CONFIG_I2C_MVTWSI_BASE1;
#endif
#ifdef CONFIG_I2C_MVTWSI_BASE2
	case 2:
		return (struct mvtwsi_registers *)CONFIG_I2C_MVTWSI_BASE2;
#endif
#ifdef CONFIG_I2C_MVTWSI_BASE3
	case 3:
		return (struct mvtwsi_registers *)CONFIG_I2C_MVTWSI_BASE3;
#endif
#ifdef CONFIG_I2C_MVTWSI_BASE4
	case 4:
		return (struct mvtwsi_registers *)CONFIG_I2C_MVTWSI_BASE4;
#endif
#ifdef CONFIG_I2C_MVTWSI_BASE5
	case 5:
		return (struct mvtwsi_registers *)CONFIG_I2C_MVTWSI_BASE5;
#endif
	default:
		printf("Missing mvtwsi controller %d base\n", adap->hwadapnr);
		break;
	}

	return NULL;
}
#endif

/*
 * enum mvtwsi_error_class - types of I2C errors
 */
enum mvtwsi_error_class {
	/* The controller returned a different status than expected */
	MVTWSI_ERROR_WRONG_STATUS       = 0x01,
	/* The controller timed out */
	MVTWSI_ERROR_TIMEOUT            = 0x02,
};

/*
 * mvtwsi_error() - Build I2C return code from error information
 *
 * For debugging purposes, this function packs some information of an occurred
 * error into a return code. These error codes are returned from I2C API
 * functions (i2c_{read,write}, dm_i2c_{read,write}, etc.).
 *
 * @ec:		The error class of the error (enum mvtwsi_error_class).
 * @lc:		The last value of the control register.
 * @ls:		The last value of the status register.
 * @es:		The expected value of the status register.
 * @return The generated error code.
 */
inline uint mvtwsi_error(uint ec, uint lc, uint ls, uint es)
{
	return ((ec << 24) & 0xFF000000)
	       | ((lc << 16) & 0x00FF0000)
	       | ((ls << 8) & 0x0000FF00)
	       | (es & 0xFF);
}

/*
 * Wait for IFLG to raise, or return 'timeout.' Then, if the status is as
 * expected, return 0 (ok) or 'wrong status' otherwise.
 */
static int twsi_wait(struct mvtwsi_registers *twsi, int expected_status)
{
	int control, status;
	int timeout = 1000;

	do {
		control = readl(&twsi->control);
		if (control & MVTWSI_CONTROL_IFLG) {
			status = readl(&twsi->status);
			if (status == expected_status)
				return 0;
			else
				return mvtwsi_error(
					MVTWSI_ERROR_WRONG_STATUS,
					control, status, expected_status);
		}
		udelay(10); /* One clock cycle at 100 kHz */
	} while (timeout--);
	status = readl(&twsi->status);
	return mvtwsi_error(MVTWSI_ERROR_TIMEOUT, control, status,
			    expected_status);
}

/*
 * Assert the START condition, either in a single I2C transaction
 * or inside back-to-back ones (repeated starts).
 */
static int twsi_start(struct mvtwsi_registers *twsi, int expected_status)
{
	/* Assert START */
	writel(MVTWSI_CONTROL_TWSIEN | MVTWSI_CONTROL_START |
	       MVTWSI_CONTROL_CLEAR_IFLG, &twsi->control);
	/* Wait for controller to process START */
	return twsi_wait(twsi, expected_status);
}

/*
 * Send a byte (i2c address or data).
 */
static int twsi_send(struct mvtwsi_registers *twsi, u8 byte,
		     int expected_status)
{
	/* Write byte to data register for sending */
	writel(byte, &twsi->data);
	/* Clear any pending interrupt -- that will cause sending */
	writel(MVTWSI_CONTROL_TWSIEN | MVTWSI_CONTROL_CLEAR_IFLG,
	       &twsi->control);
	/* Wait for controller to receive byte, and check ACK */
	return twsi_wait(twsi, expected_status);
}

/*
 * Receive a byte.
 */
static int twsi_recv(struct mvtwsi_registers *twsi, u8 *byte, int ack_flag)
{
	int expected_status, status, control;

	/* Compute expected status based on passed ACK flag */
	expected_status = ack_flag ? MVTWSI_STATUS_DATA_R_ACK :
			  MVTWSI_STATUS_DATA_R_NAK;
	/* Acknowledge *previous state*, and launch receive */
	control = MVTWSI_CONTROL_TWSIEN;
	control |= ack_flag == MVTWSI_READ_ACK ? MVTWSI_CONTROL_ACK : 0;
	writel(control | MVTWSI_CONTROL_CLEAR_IFLG, &twsi->control);
	/* Wait for controller to receive byte, and assert ACK or NAK */
	status = twsi_wait(twsi, expected_status);
	/* If we did receive the expected byte, store it */
	if (status == 0)
		*byte = readl(&twsi->data);
	return status;
}

/*
 * Assert the STOP condition.
 * This is also used to force the bus back to idle (SDA = SCL = 1).
 */
static int twsi_stop(struct mvtwsi_registers *twsi)
{
	int control, stop_status;
	int status = 0;
	int timeout = 1000;

	/* Assert STOP */
	control = MVTWSI_CONTROL_TWSIEN | MVTWSI_CONTROL_STOP;
	writel(control | MVTWSI_CONTROL_CLEAR_IFLG, &twsi->control);
	/* Wait for IDLE; IFLG won't rise, so we can't use twsi_wait() */
	do {
		stop_status = readl(&twsi->status);
		if (stop_status == MVTWSI_STATUS_IDLE)
			break;
		udelay(10); /* One clock cycle at 100 kHz */
	} while (timeout--);
	control = readl(&twsi->control);
	if (stop_status != MVTWSI_STATUS_IDLE)
		status = mvtwsi_error(MVTWSI_ERROR_TIMEOUT,
				      control, status, MVTWSI_STATUS_IDLE);
	return status;
}

static uint twsi_calc_freq(const int n, const int m)
{
#ifdef CONFIG_SUNXI
	return CONFIG_SYS_TCLK / (10 * (m + 1) * (1 << n));
#else
	return CONFIG_SYS_TCLK / (10 * (m + 1) * (2 << n));
#endif
}

/*
 * Reset controller.
 * Controller reset also resets the baud rate and slave address, so
 * they must be re-established afterwards.
 */
static void twsi_reset(struct mvtwsi_registers *twsi)
{
	/* Reset controller */
	writel(0, &twsi->soft_reset);
	/* Wait 2 ms -- this is what the Marvell LSP does */
	udelay(20000);
}

/*
 * Sets baud to the highest possible value not exceeding the requested one.
 */
static uint __twsi_i2c_set_bus_speed(struct mvtwsi_registers *twsi,
				     uint requested_speed)
{
	uint tmp_speed, highest_speed, n, m;
	uint baud = 0x44; /* Baud rate after controller reset */

	highest_speed = 0;
	/* Successively try m, n combinations, and use the combination
	 * resulting in the largest speed that's not above the requested
	 * speed */
	for (n = 0; n < 8; n++) {
		for (m = 0; m < 16; m++) {
			tmp_speed = twsi_calc_freq(n, m);
			if ((tmp_speed <= requested_speed) &&
			    (tmp_speed > highest_speed)) {
				highest_speed = tmp_speed;
				baud = (m << 3) | n;
			}
		}
	}
	writel(baud, &twsi->baudrate);
	return 0;
}

static void __twsi_i2c_init(struct mvtwsi_registers *twsi, int speed,
			    int slaveadd)
{
	/* Reset controller */
	twsi_reset(twsi);
	/* Set speed */
	__twsi_i2c_set_bus_speed(twsi, speed);
	/* Set slave address; even though we don't use it */
	writel(slaveadd, &twsi->slave_address);
	writel(0, &twsi->xtnd_slave_addr);
	/* Assert STOP, but don't care for the result */
	(void) twsi_stop(twsi);
}

/*
 * Begin I2C transaction with expected start status, at given address.
 * Expected address status will derive from direction bit (bit 0) in addr.
 */
static int i2c_begin(struct mvtwsi_registers *twsi, int expected_start_status,
		     u8 addr)
{
	int status, expected_addr_status;

	/* Compute the expected address status from the direction bit in
	 * the address byte */
	if (addr & 1) /* Reading */
		expected_addr_status = MVTWSI_STATUS_ADDR_R_ACK;
	else /* Writing */
		expected_addr_status = MVTWSI_STATUS_ADDR_W_ACK;
	/* Assert START */
	status = twsi_start(twsi, expected_start_status);
	/* Send out the address if the start went well */
	if (status == 0)
		status = twsi_send(twsi, addr, expected_addr_status);
	/* Return 0, or the status of the first failure */
	return status;
}

/*
 * Begin read, nak data byte, end.
 */
static int __twsi_i2c_probe_chip(struct mvtwsi_registers *twsi, uchar chip)
{
	u8 dummy_byte;
	int status;

	/* Begin i2c read */
	status = i2c_begin(twsi, MVTWSI_STATUS_START, (chip << 1) | 1);
	/* Dummy read was accepted: receive byte, but NAK it. */
	if (status == 0)
		status = twsi_recv(twsi, &dummy_byte, MVTWSI_READ_NAK);
	/* Stop transaction */
	twsi_stop(twsi);
	/* Return 0, or the status of the first failure */
	return status;
}

/*
 * Begin write, send address byte(s), begin read, receive data bytes, end.
 *
 * NOTE: Some devices want a stop right before the second start, while some
 * will choke if it is there. Since deciding this is not yet supported in
 * higher level APIs, we need to make a decision here, and for the moment that
 * will be a repeated start without a preceding stop.
 */
static int __twsi_i2c_read(struct mvtwsi_registers *twsi, uchar chip,
			   u8 *addr, int alen, uchar *data, int length)
{
	int status = 0;
	int stop_status;

	/* Begin i2c write to send the address bytes */
	status = i2c_begin(twsi, MVTWSI_STATUS_START, (chip << 1));
	/* Send address bytes */
	while ((status == 0) && alen--)
		status = twsi_send(twsi, *(addr++), MVTWSI_STATUS_DATA_W_ACK);
	/* Begin i2c read to receive data bytes */
	if (status == 0)
		status = i2c_begin(twsi, MVTWSI_STATUS_REPEATED_START,
				   (chip << 1) | 1);
	/* Receive actual data bytes; set NAK if we if we have nothing more to
	 * read */
	while ((status == 0) && length--)
		status = twsi_recv(twsi, data++,
				   length > 0 ?
				   MVTWSI_READ_ACK : MVTWSI_READ_NAK);
	/* Stop transaction */
	stop_status = twsi_stop(twsi);
	/* Return 0, or the status of the first failure */
	return status != 0 ? status : stop_status;
}

/*
 * Begin write, send address byte(s), send data bytes, end.
 */
static int __twsi_i2c_write(struct mvtwsi_registers *twsi, uchar chip,
			    u8 *addr, int alen, uchar *data, int length)
{
	int status, stop_status;

	/* Begin i2c write to send first the address bytes, then the
	 * data bytes */
	status = i2c_begin(twsi, MVTWSI_STATUS_START, (chip << 1));
	/* Send address bytes */
	while ((status == 0) && (alen-- > 0))
		status = twsi_send(twsi, *(addr++), MVTWSI_STATUS_DATA_W_ACK);
	/* Send data bytes */
	while ((status == 0) && (length-- > 0))
		status = twsi_send(twsi, *(data++), MVTWSI_STATUS_DATA_W_ACK);
	/* Stop transaction */
	stop_status = twsi_stop(twsi);
	/* Return 0, or the status of the first failure */
	return status != 0 ? status : stop_status;
}

#ifndef CONFIG_DM_I2C
static void twsi_i2c_init(struct i2c_adapter *adap, int speed,
			  int slaveadd)
{
	struct mvtwsi_registers *twsi = twsi_get_base(adap);
	__twsi_i2c_init(twsi, speed, slaveadd);
}

static uint twsi_i2c_set_bus_speed(struct i2c_adapter *adap,
				   uint requested_speed)
{
	struct mvtwsi_registers *twsi = twsi_get_base(adap);
	return __twsi_i2c_set_bus_speed(twsi, requested_speed);
}

static int twsi_i2c_probe(struct i2c_adapter *adap, uchar chip)
{
	struct mvtwsi_registers *twsi = twsi_get_base(adap);
	return __twsi_i2c_probe_chip(twsi, chip);
}

static int twsi_i2c_read(struct i2c_adapter *adap, uchar chip, uint addr,
			 int alen, uchar *data, int length)
{
	struct mvtwsi_registers *twsi = twsi_get_base(adap);
	u8 addr_bytes[4];

	addr_bytes[0] = (addr >> 0) & 0xFF;
	addr_bytes[1] = (addr >> 8) & 0xFF;
	addr_bytes[2] = (addr >> 16) & 0xFF;
	addr_bytes[3] = (addr >> 24) & 0xFF;

	return __twsi_i2c_read(twsi, chip, addr_bytes, alen, data, length);
}

static int twsi_i2c_write(struct i2c_adapter *adap, uchar chip, uint addr,
			  int alen, uchar *data, int length)
{
	struct mvtwsi_registers *twsi = twsi_get_base(adap);
	u8 addr_bytes[4];

	addr_bytes[0] = (addr >> 0) & 0xFF;
	addr_bytes[1] = (addr >> 8) & 0xFF;
	addr_bytes[2] = (addr >> 16) & 0xFF;
	addr_bytes[3] = (addr >> 24) & 0xFF;

	return __twsi_i2c_write(twsi, chip, addr_bytes, alen, data, length);
}

#ifdef CONFIG_I2C_MVTWSI_BASE0
U_BOOT_I2C_ADAP_COMPLETE(twsi0, twsi_i2c_init, twsi_i2c_probe,
			 twsi_i2c_read, twsi_i2c_write,
			 twsi_i2c_set_bus_speed,
			 CONFIG_SYS_I2C_SPEED, CONFIG_SYS_I2C_SLAVE, 0)
#endif
#ifdef CONFIG_I2C_MVTWSI_BASE1
U_BOOT_I2C_ADAP_COMPLETE(twsi1, twsi_i2c_init, twsi_i2c_probe,
			 twsi_i2c_read, twsi_i2c_write,
			 twsi_i2c_set_bus_speed,
			 CONFIG_SYS_I2C_SPEED, CONFIG_SYS_I2C_SLAVE, 1)

#endif
#ifdef CONFIG_I2C_MVTWSI_BASE2
U_BOOT_I2C_ADAP_COMPLETE(twsi2, twsi_i2c_init, twsi_i2c_probe,
			 twsi_i2c_read, twsi_i2c_write,
			 twsi_i2c_set_bus_speed,
			 CONFIG_SYS_I2C_SPEED, CONFIG_SYS_I2C_SLAVE, 2)

#endif
#ifdef CONFIG_I2C_MVTWSI_BASE3
U_BOOT_I2C_ADAP_COMPLETE(twsi3, twsi_i2c_init, twsi_i2c_probe,
			 twsi_i2c_read, twsi_i2c_write,
			 twsi_i2c_set_bus_speed,
			 CONFIG_SYS_I2C_SPEED, CONFIG_SYS_I2C_SLAVE, 3)

#endif
#ifdef CONFIG_I2C_MVTWSI_BASE4
U_BOOT_I2C_ADAP_COMPLETE(twsi4, twsi_i2c_init, twsi_i2c_probe,
			 twsi_i2c_read, twsi_i2c_write,
			 twsi_i2c_set_bus_speed,
			 CONFIG_SYS_I2C_SPEED, CONFIG_SYS_I2C_SLAVE, 4)

#endif
#ifdef CONFIG_I2C_MVTWSI_BASE5
U_BOOT_I2C_ADAP_COMPLETE(twsi5, twsi_i2c_init, twsi_i2c_probe,
			 twsi_i2c_read, twsi_i2c_write,
			 twsi_i2c_set_bus_speed,
			 CONFIG_SYS_I2C_SPEED, CONFIG_SYS_I2C_SLAVE, 5)

#endif
#else /* CONFIG_DM_I2C */

static int mvtwsi_i2c_probe_chip(struct udevice *bus, u32 chip_addr,
				 u32 chip_flags)
{
	struct mvtwsi_i2c_dev *dev = dev_get_priv(bus);
	return __twsi_i2c_probe_chip(dev->base, chip_addr);
}

static int mvtwsi_i2c_set_bus_speed(struct udevice *bus, uint speed)
{
	struct mvtwsi_i2c_dev *dev = dev_get_priv(bus);
	return __twsi_i2c_set_bus_speed(dev->base, speed);
}

static int mvtwsi_i2c_ofdata_to_platdata(struct udevice *bus)
{
	struct mvtwsi_i2c_dev *dev = dev_get_priv(bus);

	dev->base = dev_get_addr_ptr(bus);

	if (!dev->base)
		return -ENOMEM;

	dev->index = fdtdec_get_int(gd->fdt_blob, bus->of_offset,
				    "cell-index", -1);
	dev->slaveadd = fdtdec_get_int(gd->fdt_blob, bus->of_offset,
				       "u-boot,i2c-slave-addr", 0x0);
	dev->speed = fdtdec_get_int(gd->fdt_blob, bus->of_offset,
				    "clock-frequency", 100000);
	return 0;
}

static int mvtwsi_i2c_probe(struct udevice *bus)
{
	struct mvtwsi_i2c_dev *dev = dev_get_priv(bus);
	__twsi_i2c_init(dev->base, dev->speed, dev->slaveadd);
	return 0;
}

static int mvtwsi_i2c_xfer(struct udevice *bus, struct i2c_msg *msg, int nmsgs)
{
	struct mvtwsi_i2c_dev *dev = dev_get_priv(bus);
	struct i2c_msg *dmsg, *omsg, dummy;

	memset(&dummy, 0, sizeof(struct i2c_msg));

	/* We expect either two messages (one with an offset and one with the
	 * actual data) or one message (just data or offset/data combined) */
	if (nmsgs > 2 || nmsgs == 0) {
		debug("%s: Only one or two messages are supported.", __func__);
		return -1;
	}

	omsg = nmsgs == 1 ? &dummy : msg;
	dmsg = nmsgs == 1 ? msg : msg + 1;

	if (dmsg->flags & I2C_M_RD)
		return __twsi_i2c_read(dev->base, dmsg->addr, omsg->buf,
				       omsg->len, dmsg->buf, dmsg->len);
	else
		return __twsi_i2c_write(dev->base, dmsg->addr, omsg->buf,
					omsg->len, dmsg->buf, dmsg->len);
}

static const struct dm_i2c_ops mvtwsi_i2c_ops = {
	.xfer		= mvtwsi_i2c_xfer,
	.probe_chip	= mvtwsi_i2c_probe_chip,
	.set_bus_speed	= mvtwsi_i2c_set_bus_speed,
};

static const struct udevice_id mvtwsi_i2c_ids[] = {
	{ .compatible = "marvell,mv64xxx-i2c", },
	{ /* sentinel */ }
};

U_BOOT_DRIVER(i2c_mvtwsi) = {
	.name = "i2c_mvtwsi",
	.id = UCLASS_I2C,
	.of_match = mvtwsi_i2c_ids,
	.probe = mvtwsi_i2c_probe,
	.ofdata_to_platdata = mvtwsi_i2c_ofdata_to_platdata,
	.priv_auto_alloc_size = sizeof(struct mvtwsi_i2c_dev),
	.ops = &mvtwsi_i2c_ops,
};
#endif /* CONFIG_DM_I2C */
