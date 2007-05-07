/*
 * libfdt - Flat Device Tree manipulation
 * Copyright (C) 2006 David Gibson, IBM Corporation.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */
#include "libfdt_env.h"

#include <fdt.h>
#include <libfdt.h>

#include "libfdt_internal.h"

static int check_header_sw(void *fdt)
{
	if (fdt_magic(fdt) != SW_MAGIC)
		return -FDT_ERR_BADMAGIC;
	return 0;
}

static void *grab_space(void *fdt, int len)
{
	int offset = fdt_size_dt_struct(fdt);
	int spaceleft;

	spaceleft = fdt_totalsize(fdt) - fdt_off_dt_struct(fdt)
		- fdt_size_dt_strings(fdt);

	if ((offset + len < offset) || (offset + len > spaceleft))
		return NULL;

	fdt_set_header(fdt, size_dt_struct, offset + len);
	return fdt_offset_ptr(fdt, offset, len);
}

int fdt_create(void *buf, int bufsize)
{
	void *fdt = buf;

	if (bufsize < sizeof(struct fdt_header))
		return -FDT_ERR_NOSPACE;

	memset(buf, 0, bufsize);

	fdt_set_header(fdt, magic, SW_MAGIC);
	fdt_set_header(fdt, version, FDT_LAST_SUPPORTED_VERSION);
	fdt_set_header(fdt, last_comp_version, FDT_FIRST_SUPPORTED_VERSION);
	fdt_set_header(fdt, totalsize, bufsize);

	fdt_set_header(fdt, off_mem_rsvmap, ALIGN(sizeof(struct fdt_header),
					      sizeof(struct fdt_reserve_entry)));
	fdt_set_header(fdt, off_dt_struct, fdt_off_mem_rsvmap(fdt));
	fdt_set_header(fdt, off_dt_strings, bufsize);

	return 0;
}

int fdt_add_reservemap_entry(void *fdt, uint64_t addr, uint64_t size)
{
	struct fdt_reserve_entry *re;
	int err = check_header_sw(fdt);
	int offset;

	if (err)
		return err;
	if (fdt_size_dt_struct(fdt))
		return -FDT_ERR_BADSTATE;

	offset = fdt_off_dt_struct(fdt);
	if ((offset + sizeof(*re)) > fdt_totalsize(fdt))
		return -FDT_ERR_NOSPACE;

	re = (struct fdt_reserve_entry *)((void *)fdt + offset);
	re->address = cpu_to_fdt64(addr);
	re->size = cpu_to_fdt64(size);

	fdt_set_header(fdt, off_dt_struct, offset + sizeof(*re));

	return 0;
}

int fdt_finish_reservemap(void *fdt)
{
	return fdt_add_reservemap_entry(fdt, 0, 0);
}

int fdt_begin_node(void *fdt, const char *name)
{
	struct fdt_node_header *nh;
	int err = check_header_sw(fdt);
	int namelen = strlen(name) + 1;

	if (err)
		return err;

	nh = grab_space(fdt, sizeof(*nh) + ALIGN(namelen, FDT_TAGSIZE));
	if (! nh)
		return -FDT_ERR_NOSPACE;

	nh->tag = cpu_to_fdt32(FDT_BEGIN_NODE);
	memcpy(nh->name, name, namelen);
	return 0;
}

int fdt_end_node(void *fdt)
{
	uint32_t *en;
	int err = check_header_sw(fdt);

	if (err)
		return err;

	en = grab_space(fdt, FDT_TAGSIZE);
	if (! en)
		return -FDT_ERR_NOSPACE;

	*en = cpu_to_fdt32(FDT_END_NODE);
	return 0;
}

static int find_add_string(void *fdt, const char *s)
{
	char *strtab = (char *)fdt + fdt_totalsize(fdt);
	const char *p;
	int strtabsize = fdt_size_dt_strings(fdt);
	int len = strlen(s) + 1;
	int struct_top, offset;

	p = _fdt_find_string(strtab - strtabsize, strtabsize, s);
	if (p)
		return p - strtab;

	/* Add it */
	offset = -strtabsize - len;
	struct_top = fdt_off_dt_struct(fdt) + fdt_size_dt_struct(fdt);
	if (fdt_totalsize(fdt) + offset < struct_top)
		return 0; /* no more room :( */

	memcpy(strtab + offset, s, len);
	fdt_set_header(fdt, size_dt_strings, strtabsize + len);
	return offset;
}

int fdt_property(void *fdt, const char *name, const void *val, int len)
{
	struct fdt_property *prop;
	int err = check_header_sw(fdt);
	int nameoff;

	if (err)
		return err;

	nameoff = find_add_string(fdt, name);
	if (nameoff == 0)
		return -FDT_ERR_NOSPACE;

	prop = grab_space(fdt, sizeof(*prop) + ALIGN(len, FDT_TAGSIZE));
	if (! prop)
		return -FDT_ERR_NOSPACE;

	prop->tag = cpu_to_fdt32(FDT_PROP);
	prop->nameoff = cpu_to_fdt32(nameoff);
	prop->len = cpu_to_fdt32(len);
	memcpy(prop->data, val, len);
	return 0;
}

int fdt_finish(void *fdt)
{
	int err = check_header_sw(fdt);
	char *p = (char *)fdt;
	uint32_t *end;
	int oldstroffset, newstroffset;
	uint32_t tag;
	int offset, nextoffset;

	if (err)
		return err;

	/* Add terminator */
	end = grab_space(fdt, sizeof(*end));
	if (! end)
		return -FDT_ERR_NOSPACE;
	*end = cpu_to_fdt32(FDT_END);

	/* Relocate the string table */
	oldstroffset = fdt_totalsize(fdt) - fdt_size_dt_strings(fdt);
	newstroffset = fdt_off_dt_struct(fdt) + fdt_size_dt_struct(fdt);
	memmove(p + newstroffset, p + oldstroffset, fdt_size_dt_strings(fdt));
	fdt_set_header(fdt, off_dt_strings, newstroffset);

	/* Walk the structure, correcting string offsets */
	offset = 0;
	while ((tag = fdt_next_tag(fdt, offset, &nextoffset, NULL)) != FDT_END) {
		if (tag == FDT_PROP) {
			struct fdt_property *prop = fdt_offset_ptr(fdt, offset,
								   sizeof(*prop));
			int nameoff;

			if (! prop)
				return -FDT_ERR_BADSTRUCTURE;

			nameoff = fdt32_to_cpu(prop->nameoff);
			nameoff += fdt_size_dt_strings(fdt);
			prop->nameoff = cpu_to_fdt32(nameoff);
		}
		offset = nextoffset;
	}

	/* Finally, adjust the header */
	fdt_set_header(fdt, totalsize, newstroffset + fdt_size_dt_strings(fdt));
	fdt_set_header(fdt, magic, FDT_MAGIC);
	return 0;
}
