/*
 * Copyright (c) 2016, NVIDIA CORPORATION.
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#include <common.h>
#include <dm.h>
#include <fdtdec.h>
#include <mailbox_client.h>
#include <mailbox_uclass.h>

DECLARE_GLOBAL_DATA_PTR;

static inline struct mbox_ops *mbox_dev_ops(struct udevice *dev)
{
	return (struct mbox_ops *)dev->driver->ops;
}

static int mbox_of_xlate_default(struct mbox_chan *chan,
				 struct fdtdec_phandle_args *args)
{
	debug("%s(chan=%p)\n", __func__, chan);

	if (args->args_count != 1) {
		debug("Invaild args_count: %d\n", args->args_count);
		return -EINVAL;
	}

	chan->id = args->args[0];

	return 0;
}

int mbox_get_by_index(struct udevice *dev, int index, struct mbox_chan *chan)
{
	struct fdtdec_phandle_args args;
	int ret;
	struct udevice *dev_mbox;
	struct mbox_ops *ops;

	debug("%s(dev=%p, index=%d, chan=%p)\n", __func__, dev, index, chan);

	ret = fdtdec_parse_phandle_with_args(gd->fdt_blob, dev->of_offset,
					     "mboxes", "#mbox-cells", 0,
					     index, &args);
	if (ret) {
		debug("%s: fdtdec_parse_phandle_with_args failed: %d\n",
		      __func__, ret);
		return ret;
	}

	ret = uclass_get_device_by_of_offset(UCLASS_MAILBOX, args.node,
					     &dev_mbox);
	if (ret) {
		debug("%s: uclass_get_device_by_of_offset failed: %d\n",
		      __func__, ret);
		return ret;
	}
	ops = mbox_dev_ops(dev_mbox);

	chan->dev = dev_mbox;
	if (ops->of_xlate)
		ret = ops->of_xlate(chan, &args);
	else
		ret = mbox_of_xlate_default(chan, &args);
	if (ret) {
		debug("of_xlate() failed: %d\n", ret);
		return ret;
	}

	ret = ops->request(chan);
	if (ret) {
		debug("ops->request() failed: %d\n", ret);
		return ret;
	}

	return 0;
}

int mbox_get_by_name(struct udevice *dev, const char *name,
		     struct mbox_chan *chan)
{
	int index;

	debug("%s(dev=%p, name=%s, chan=%p)\n", __func__, dev, name, chan);

	index = fdt_find_string(gd->fdt_blob, dev->of_offset, "mbox-names",
				name);
	if (index < 0) {
		debug("fdt_find_string() failed: %d\n", index);
		return index;
	}

	return mbox_get_by_index(dev, index, chan);
}

int mbox_free(struct mbox_chan *chan)
{
	struct mbox_ops *ops = mbox_dev_ops(chan->dev);

	debug("%s(chan=%p)\n", __func__, chan);

	return ops->free(chan);
}

int mbox_send(struct mbox_chan *chan, const void *data)
{
	struct mbox_ops *ops = mbox_dev_ops(chan->dev);

	debug("%s(chan=%p, data=%p)\n", __func__, chan, data);

	return ops->send(chan, data);
}

int mbox_recv(struct mbox_chan *chan, void *data, ulong timeout_us)
{
	struct mbox_ops *ops = mbox_dev_ops(chan->dev);
	ulong start_time;
	int ret;

	debug("%s(chan=%p, data=%p, timeout_us=%ld)\n", __func__, chan, data,
	      timeout_us);

	start_time = timer_get_us();
	/*
	 * Account for partial us ticks, but if timeout_us is 0, ensure we
	 * still don't wait at all.
	 */
	if (timeout_us)
		timeout_us++;

	for (;;) {
		ret = ops->recv(chan, data);
		if (ret != -ENODATA)
			return ret;
		if ((timer_get_us() - start_time) >= timeout_us)
			return -ETIMEDOUT;
	}
}

UCLASS_DRIVER(mailbox) = {
	.id		= UCLASS_MAILBOX,
	.name		= "mailbox",
};
