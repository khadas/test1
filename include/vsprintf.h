/*
 * (C) Copyright 2000-2009
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __VSPRINTF_H
#define __VSPRINTF_H

ulong simple_strtoul(const char *cp, char **endp, unsigned int base);
int strict_strtoul(const char *cp, unsigned int base, unsigned long *res);
unsigned long long simple_strtoull(const char *cp, char **endp,
					unsigned int base);
long simple_strtol(const char *cp, char **endp, unsigned int base);
void panic(const char *fmt, ...)
		__attribute__ ((format (__printf__, 1, 2), noreturn));
int sprintf(char *buf, const char *fmt, ...)
		__attribute__ ((format (__printf__, 2, 3)));
int vsprintf(char *buf, const char *fmt, va_list args);
char *simple_itoa(ulong i);

#ifdef CONFIG_SYS_VSNPRINTF
int snprintf(char *buf, size_t size, const char *fmt, ...)
		__attribute__ ((format (__printf__, 3, 4)));
int scnprintf(char *buf, size_t size, const char *fmt, ...)
		__attribute__ ((format (__printf__, 3, 4)));
int vsnprintf(char *buf, size_t size, const char *fmt, va_list args);
int vscnprintf(char *buf, size_t size, const char *fmt, va_list args);
#else
/*
 * Use macros to silently drop the size parameter. Note that the 'cn'
 * versions are the same as the 'n' versions since the functions assume
 * there is always enough buffer space when !CONFIG_SYS_VSNPRINTF
 */
#define snprintf(buf, size, fmt, args...) sprintf(buf, fmt, ##args)
#define scnprintf(buf, size, fmt, args...) sprintf(buf, fmt, ##args)
#define vsnprintf(buf, size, fmt, args...) vsprintf(buf, fmt, ##args)
#define vscnprintf(buf, size, fmt, args...) vsprintf(buf, fmt, ##args)
#endif /* CONFIG_SYS_VSNPRINTF */

#endif
