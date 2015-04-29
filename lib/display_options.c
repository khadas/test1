/*
 * (C) Copyright 2000-2002
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <config.h>
#include <common.h>
#include <div64.h>
#include <inttypes.h>
#include <version.h>
#include <linux/ctype.h>
#include <asm/io.h>

int display_options (void)
{
#if defined(BUILD_TAG)
	printf ("\n\n%s, Build: %s\n\n", version_string, BUILD_TAG);
#else
	printf ("\n\n%s\n\n", version_string);
#endif
	return 0;
}

void print_freq(uint64_t freq, const char *s)
{
	unsigned long m = 0, n;
	uint32_t f;
	static const char names[] = {'G', 'M', 'K'};
	unsigned long d = 1e9;
	char c = 0;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(names); i++, d /= 1000) {
		if (freq >= d) {
			c = names[i];
			break;
		}
	}

	if (!c) {
		printf("%" PRIu64 " Hz%s", freq, s);
		return;
	}

	f = do_div(freq, d);
	n = freq;

	/* If there's a remainder, show the first few digits */
	if (f) {
		m = f;
		while (m > 1000)
			m /= 10;
		while (m && !(m % 10))
			m /= 10;
		if (m >= 100)
			m = (m / 10) + (m % 100 >= 50);
	}

	printf("%lu", n);
	if (m)
		printf(".%ld", m);
	printf(" %cHz%s", c, s);
}

void print_size(uint64_t size, const char *s)
{
	unsigned long m = 0, n;
	uint64_t f;
	static const char names[] = {'E', 'P', 'T', 'G', 'M', 'K'};
	unsigned long d = 10 * ARRAY_SIZE(names);
	char c = 0;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(names); i++, d -= 10) {
		if (size >> d) {
			c = names[i];
			break;
		}
	}

	if (!c) {
		printf("%" PRIu64 " Bytes%s", size, s);
		return;
	}

	n = size >> d;
	f = size & ((1ULL << d) - 1);

	/* If there's a remainder, deal with it */
	if (f) {
		m = (10ULL * f + (1ULL << (d - 1))) >> d;

		if (m >= 10) {
			m -= 10;
			n += 1;
		}
	}

	printf ("%lu", n);
	if (m) {
		printf (".%ld", m);
	}
	printf (" %ciB%s", c, s);
}

#define MAX_LINE_LENGTH_BYTES (64)
#define DEFAULT_LINE_LENGTH_BYTES (16)
int print_buffer(ulong addr, const void *data, uint width, uint count,
		 uint linelen)
{
	/* linebuf as a union causes proper alignment */
	union linebuf {
#ifdef CONFIG_SYS_SUPPORT_64BIT_DATA
		uint64_t uq[MAX_LINE_LENGTH_BYTES/sizeof(uint64_t) + 1];
#endif
		uint32_t ui[MAX_LINE_LENGTH_BYTES/sizeof(uint32_t) + 1];
		uint16_t us[MAX_LINE_LENGTH_BYTES/sizeof(uint16_t) + 1];
		uint8_t  uc[MAX_LINE_LENGTH_BYTES/sizeof(uint8_t) + 1];
	} lb;
	int i;
#ifdef CONFIG_SYS_SUPPORT_64BIT_DATA
	uint64_t x;
#else
	uint32_t x;
#endif

	if (linelen*width > MAX_LINE_LENGTH_BYTES)
		linelen = MAX_LINE_LENGTH_BYTES / width;
	if (linelen < 1)
		linelen = DEFAULT_LINE_LENGTH_BYTES / width;

	while (count) {
		uint thislinelen = linelen;
		printf("%08lx:", addr);

		/* check for overflow condition */
		if (count < thislinelen)
			thislinelen = count;

		/* Copy from memory into linebuf and print hex values */
		for (i = 0; i < thislinelen; i++) {
			if (width == 4)
				x = lb.ui[i] = *(volatile uint32_t *)data;
#ifdef CONFIG_SYS_SUPPORT_64BIT_DATA
			else if (width == 8)
				x = lb.uq[i] = *(volatile uint64_t *)data;
#endif
			else if (width == 2)
				x = lb.us[i] = *(volatile uint16_t *)data;
			else
				x = lb.uc[i] = *(volatile uint8_t *)data;
#ifdef CONFIG_SYS_SUPPORT_64BIT_DATA
			printf(" %0*" PRIx64, width * 2, x);
#else
			printf(" %0*x", width * 2, x);
#endif
			data += width;
		}

		while (thislinelen < linelen) {
			/* fill line with whitespace for nice ASCII print */
			for (i=0; i<width*2+1; i++)
				puts(" ");
			linelen--;
		}

		/* Print data in ASCII characters */
		for (i = 0; i < thislinelen * width; i++) {
			if (!isprint(lb.uc[i]) || lb.uc[i] >= 0x80)
				lb.uc[i] = '.';
		}
		lb.uc[i] = '\0';
		printf("    %s\n", lb.uc);

		/* update references */
		addr += thislinelen * width;
		count -= thislinelen;

		if (ctrlc())
			return -1;
	}

	return 0;
}
