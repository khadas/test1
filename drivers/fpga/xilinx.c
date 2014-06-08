/*
 * (C) Copyright 2012-2013, Xilinx, Michal Simek
 *
 * (C) Copyright 2002
 * Rich Ireland, Enterasys Networks, rireland@enterasys.com.
 * Keith Outwater, keith_outwater@mvis.com
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

/*
 *  Xilinx FPGA support
 */

#include <common.h>
#include <fpga.h>
#include <virtex2.h>
#include <spartan2.h>
#include <spartan3.h>
#include <zynqpl.h>

/* Local Static Functions */
static int xilinx_validate(xilinx_desc *desc, char *fn);

/* ------------------------------------------------------------------------- */

int fpga_loadbitstream(int devnum, char *fpgadata, size_t size,
		       bitstream_type bstype)
{
	unsigned int length;
	unsigned int swapsize;
	char buffer[80];
	unsigned char *dataptr;
	unsigned int i;
	const fpga_desc *desc;
	xilinx_desc *xdesc;

	dataptr = (unsigned char *)fpgadata;
	/* Find out fpga_description */
	desc = fpga_validate(devnum, dataptr, 0, (char *)__func__);
	/* Assign xilinx device description */
	xdesc = desc->devdesc;

	/* skip the first bytes of the bitsteam, their meaning is unknown */
	length = (*dataptr << 8) + *(dataptr + 1);
	dataptr += 2;
	dataptr += length;

	/* get design name (identifier, length, string) */
	length = (*dataptr << 8) + *(dataptr + 1);
	dataptr += 2;
	if (*dataptr++ != 0x61) {
		debug("%s: Design name id not recognized in bitstream\n",
		      __func__);
		return FPGA_FAIL;
	}

	length = (*dataptr << 8) + *(dataptr + 1);
	dataptr += 2;
	for (i = 0; i < length; i++)
		buffer[i] = *dataptr++;

	printf("  design filename = \"%s\"\n", buffer);

	/* get part number (identifier, length, string) */
	if (*dataptr++ != 0x62) {
		printf("%s: Part number id not recognized in bitstream\n",
		       __func__);
		return FPGA_FAIL;
	}

	length = (*dataptr << 8) + *(dataptr + 1);
	dataptr += 2;
	for (i = 0; i < length; i++)
		buffer[i] = *dataptr++;

	if (xdesc->name) {
		i = strncmp(buffer, xdesc->name, strlen(xdesc->name));
		if (i) {
			printf("%s: Wrong bitstream ID for this device\n",
			       __func__);
			printf("%s: Bitstream ID %s, current device ID %d/%s\n",
			       __func__, buffer, devnum, xdesc->name);
			return FPGA_FAIL;
		}
	} else {
		printf("%s: Please fill correct device ID to xilinx_desc\n",
		       __func__);
	}
	printf("  part number = \"%s\"\n", buffer);

	/* get date (identifier, length, string) */
	if (*dataptr++ != 0x63) {
		printf("%s: Date identifier not recognized in bitstream\n",
		       __func__);
		return FPGA_FAIL;
	}

	length = (*dataptr << 8) + *(dataptr+1);
	dataptr += 2;
	for (i = 0; i < length; i++)
		buffer[i] = *dataptr++;
	printf("  date = \"%s\"\n", buffer);

	/* get time (identifier, length, string) */
	if (*dataptr++ != 0x64) {
		printf("%s: Time identifier not recognized in bitstream\n",
		       __func__);
		return FPGA_FAIL;
	}

	length = (*dataptr << 8) + *(dataptr+1);
	dataptr += 2;
	for (i = 0; i < length; i++)
		buffer[i] = *dataptr++;
	printf("  time = \"%s\"\n", buffer);

	/* get fpga data length (identifier, length) */
	if (*dataptr++ != 0x65) {
		printf("%s: Data length id not recognized in bitstream\n",
		       __func__);
		return FPGA_FAIL;
	}
	swapsize = ((unsigned int) *dataptr << 24) +
		   ((unsigned int) *(dataptr + 1) << 16) +
		   ((unsigned int) *(dataptr + 2) << 8) +
		   ((unsigned int) *(dataptr + 3));
	dataptr += 4;
	printf("  bytes in bitstream = %d\n", swapsize);

	return fpga_load(devnum, dataptr, swapsize, bstype);
}

int xilinx_load(xilinx_desc *desc, const void *buf, size_t bsize,
		bitstream_type bstype)
{
	if (!xilinx_validate (desc, (char *)__FUNCTION__)) {
		printf ("%s: Invalid device descriptor\n", __FUNCTION__);
		return FPGA_FAIL;
	}

	return desc->operations->load(desc, buf, bsize, bstype);
}

#if defined(CONFIG_CMD_FPGA_LOADFS)
int xilinx_loadfs(xilinx_desc *desc, const void *buf, size_t bsize,
		   fpga_fs_info *fpga_fsinfo)
{
	if (!xilinx_validate(desc, (char *)__func__)) {
		printf("%s: Invalid device descriptor\n", __func__);
		return FPGA_FAIL;
	}

	if (!desc->operations->loadfs)
		return FPGA_FAIL;

	return desc->operations->loadfs(desc, buf, bsize, fpga_fsinfo);
}
#endif

int xilinx_dump(xilinx_desc *desc, const void *buf, size_t bsize)
{
	if (!xilinx_validate (desc, (char *)__FUNCTION__)) {
		printf ("%s: Invalid device descriptor\n", __FUNCTION__);
		return FPGA_FAIL;
	}

	return desc->operations->dump(desc, buf, bsize);
}

int xilinx_info(xilinx_desc *desc)
{
	int ret_val = FPGA_FAIL;

	if (xilinx_validate (desc, (char *)__FUNCTION__)) {
		printf ("Family:        \t");
		switch (desc->family) {
		case xilinx_spartan2:
			printf ("Spartan-II\n");
			break;
		case xilinx_spartan3:
			printf ("Spartan-III\n");
			break;
		case xilinx_virtex2:
			printf ("Virtex-II\n");
			break;
		case xilinx_zynq:
			printf("Zynq PL\n");
			break;
			/* Add new family types here */
		default:
			printf ("Unknown family type, %d\n", desc->family);
		}

		printf ("Interface type:\t");
		switch (desc->iface) {
		case slave_serial:
			printf ("Slave Serial\n");
			break;
		case master_serial:	/* Not used */
			printf ("Master Serial\n");
			break;
		case slave_parallel:
			printf ("Slave Parallel\n");
			break;
		case jtag_mode:		/* Not used */
			printf ("JTAG Mode\n");
			break;
		case slave_selectmap:
			printf ("Slave SelectMap Mode\n");
			break;
		case master_selectmap:
			printf ("Master SelectMap Mode\n");
			break;
		case devcfg:
			printf("Device configuration interface (Zynq)\n");
			break;
			/* Add new interface types here */
		default:
			printf ("Unsupported interface type, %d\n", desc->iface);
		}

		printf("Device Size:   \t%zd bytes\n"
		       "Cookie:        \t0x%x (%d)\n",
		       desc->size, desc->cookie, desc->cookie);
		if (desc->name)
			printf("Device name:   \t%s\n", desc->name);

		if (desc->iface_fns) {
			printf ("Device Function Table @ 0x%p\n", desc->iface_fns);
			desc->operations->info(desc);
		} else
			printf ("No Device Function Table.\n");

		ret_val = FPGA_SUCCESS;
	} else {
		printf ("%s: Invalid device descriptor\n", __FUNCTION__);
	}

	return ret_val;
}

/* ------------------------------------------------------------------------- */

static int xilinx_validate(xilinx_desc *desc, char *fn)
{
	int ret_val = false;

	if (desc) {
		if ((desc->family > min_xilinx_type) &&
			(desc->family < max_xilinx_type)) {
			if ((desc->iface > min_xilinx_iface_type) &&
				(desc->iface < max_xilinx_iface_type)) {
				if (desc->size) {
					ret_val = true;
				} else
					printf ("%s: NULL part size\n", fn);
			} else
				printf ("%s: Invalid Interface type, %d\n",
						fn, desc->iface);
		} else
			printf ("%s: Invalid family type, %d\n", fn, desc->family);
	} else
		printf ("%s: NULL descriptor!\n", fn);

	return ret_val;
}
