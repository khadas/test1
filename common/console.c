/*
 * (C) Copyright 2000
 * Paolo Scaffardi, AIRVENT SAM s.p.a - RIMINI(ITALY), arsenio@tin.it
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
#include <stdarg.h>
#include <malloc.h>
#include <console.h>
#include <exports.h>

DECLARE_GLOBAL_DATA_PTR;

#ifdef CONFIG_AMIGAONEG3SE
int console_changed = 0;
#endif

#ifdef CONFIG_SYS_CONSOLE_IS_IN_ENV
/*
 * if overwrite_console returns 1, the stdin, stderr and stdout
 * are switched to the serial port, else the settings in the
 * environment are used
 */
#ifdef CONFIG_SYS_CONSOLE_OVERWRITE_ROUTINE
extern int overwrite_console (void);
#define OVERWRITE_CONSOLE overwrite_console ()
#else
#define OVERWRITE_CONSOLE 0
#endif /* CONFIG_SYS_CONSOLE_OVERWRITE_ROUTINE */

#endif /* CONFIG_SYS_CONSOLE_IS_IN_ENV */

static int console_setfile (int file, device_t * dev)
{
	int error = 0;

	if (dev == NULL)
		return -1;

	switch (file) {
	case stdin:
	case stdout:
	case stderr:
		/* Start new device */
		if (dev->start) {
			error = dev->start ();
			/* If it's not started dont use it */
			if (error < 0)
				break;
		}

		/* Assign the new device (leaving the existing one started) */
		stdio_devices[file] = dev;

		/*
		 * Update monitor functions
		 * (to use the console stuff by other applications)
		 */
		switch (file) {
		case stdin:
			gd->jt[XF_getc] = dev->getc;
			gd->jt[XF_tstc] = dev->tstc;
			break;
		case stdout:
			gd->jt[XF_putc] = dev->putc;
			gd->jt[XF_puts] = dev->puts;
			gd->jt[XF_printf] = printf;
			break;
		}
		break;

	default:		/* Invalid file ID */
		error = -1;
	}
	return error;
}

#if defined(CONFIG_CONSOLE_MUX)
/** Console I/O multiplexing *******************************************/

static device_t *tstcdev;
device_t **console_devices[MAX_FILES];
int cd_count[MAX_FILES];

/*
 * This depends on tstc() always being called before getc().
 * This is guaranteed to be true because this routine is called
 * only from fgetc() which assures it.
 * No attempt is made to demultiplex multiple input sources.
 */
static int iomux_getc(void)
{
	unsigned char ret;

	/* This is never called with testcdev == NULL */
	ret = tstcdev->getc();
	tstcdev = NULL;
	return ret;
}

static int iomux_tstc(int file)
{
	int i, ret;
	device_t *dev;

	disable_ctrlc(1);
	for (i = 0; i < cd_count[file]; i++) {
		dev = console_devices[file][i];
		if (dev->tstc != NULL) {
			ret = dev->tstc();
			if (ret > 0) {
				tstcdev = dev;
				disable_ctrlc(0);
				return ret;
			}
		}
	}
	disable_ctrlc(0);

	return 0;
}

static void iomux_putc(int file, const char c)
{
	int i;
	device_t *dev;

	for (i = 0; i < cd_count[file]; i++) {
		dev = console_devices[file][i];
		if (dev->putc != NULL)
			dev->putc(c);
	}
}

static void iomux_puts(int file, const char *s)
{
	int i;
	device_t *dev;

	for (i = 0; i < cd_count[file]; i++) {
		dev = console_devices[file][i];
		if (dev->puts != NULL)
			dev->puts(s);
	}
}
#endif /* defined(CONFIG_CONSOLE_MUX) */

/** U-Boot INITIAL CONSOLE-NOT COMPATIBLE FUNCTIONS *************************/

void serial_printf (const char *fmt, ...)
{
	va_list args;
	uint i;
	char printbuffer[CONFIG_SYS_PBSIZE];

	va_start (args, fmt);

	/* For this to work, printbuffer must be larger than
	 * anything we ever want to print.
	 */
	i = vsprintf (printbuffer, fmt, args);
	va_end (args);

	serial_puts (printbuffer);
}

int fgetc (int file)
{
	if (file < MAX_FILES) {
#if defined(CONFIG_CONSOLE_MUX)
		/*
		 * Effectively poll for input wherever it may be available.
		 */
		for (;;) {
			/*
			 * Upper layer may have already called tstc() so
			 * check for that first.
			 */
			if (tstcdev != NULL)
				return iomux_getc();
			iomux_tstc(file);
#ifdef CONFIG_WATCHDOG
			/*
			 * If the watchdog must be rate-limited then it should
			 * already be handled in board-specific code.
			 */
			 udelay(1);
#endif
		}
#else
		return stdio_devices[file]->getc ();
#endif
	}

	return -1;
}

int ftstc (int file)
{
	if (file < MAX_FILES)
#if defined(CONFIG_CONSOLE_MUX)
		return iomux_tstc(file);
#else
		return stdio_devices[file]->tstc ();
#endif

	return -1;
}

void fputc (int file, const char c)
{
	if (file < MAX_FILES)
#if defined(CONFIG_CONSOLE_MUX)
		iomux_putc(file, c);
#else
		stdio_devices[file]->putc (c);
#endif
}

void fputs (int file, const char *s)
{
	if (file < MAX_FILES)
#if defined(CONFIG_CONSOLE_MUX)
		iomux_puts(file, s);
#else
		stdio_devices[file]->puts (s);
#endif
}

void fprintf (int file, const char *fmt, ...)
{
	va_list args;
	uint i;
	char printbuffer[CONFIG_SYS_PBSIZE];

	va_start (args, fmt);

	/* For this to work, printbuffer must be larger than
	 * anything we ever want to print.
	 */
	i = vsprintf (printbuffer, fmt, args);
	va_end (args);

	/* Send to desired file */
	fputs (file, printbuffer);
}

/** U-Boot INITIAL CONSOLE-COMPATIBLE FUNCTION *****************************/

int getc (void)
{
#ifdef CONFIG_DISABLE_CONSOLE
	if (gd->flags & GD_FLG_DISABLE_CONSOLE)
		return 0;
#endif

	if (gd->flags & GD_FLG_DEVINIT) {
		/* Get from the standard input */
		return fgetc (stdin);
	}

	/* Send directly to the handler */
	return serial_getc ();
}

int tstc (void)
{
#ifdef CONFIG_DISABLE_CONSOLE
	if (gd->flags & GD_FLG_DISABLE_CONSOLE)
		return 0;
#endif

	if (gd->flags & GD_FLG_DEVINIT) {
		/* Test the standard input */
		return ftstc (stdin);
	}

	/* Send directly to the handler */
	return serial_tstc ();
}

void putc (const char c)
{
#ifdef CONFIG_SILENT_CONSOLE
	if (gd->flags & GD_FLG_SILENT)
		return;
#endif

#ifdef CONFIG_DISABLE_CONSOLE
	if (gd->flags & GD_FLG_DISABLE_CONSOLE)
		return;
#endif

	if (gd->flags & GD_FLG_DEVINIT) {
		/* Send to the standard output */
		fputc (stdout, c);
	} else {
		/* Send directly to the handler */
		serial_putc (c);
	}
}

void puts (const char *s)
{
#ifdef CONFIG_SILENT_CONSOLE
	if (gd->flags & GD_FLG_SILENT)
		return;
#endif

#ifdef CONFIG_DISABLE_CONSOLE
	if (gd->flags & GD_FLG_DISABLE_CONSOLE)
		return;
#endif

	if (gd->flags & GD_FLG_DEVINIT) {
		/* Send to the standard output */
		fputs (stdout, s);
	} else {
		/* Send directly to the handler */
		serial_puts (s);
	}
}

void printf (const char *fmt, ...)
{
	va_list args;
	uint i;
	char printbuffer[CONFIG_SYS_PBSIZE];

	va_start (args, fmt);

	/* For this to work, printbuffer must be larger than
	 * anything we ever want to print.
	 */
	i = vsprintf (printbuffer, fmt, args);
	va_end (args);

	/* Print the string */
	puts (printbuffer);
}

void vprintf (const char *fmt, va_list args)
{
	uint i;
	char printbuffer[CONFIG_SYS_PBSIZE];

	/* For this to work, printbuffer must be larger than
	 * anything we ever want to print.
	 */
	i = vsprintf (printbuffer, fmt, args);

	/* Print the string */
	puts (printbuffer);
}

/* test if ctrl-c was pressed */
static int ctrlc_disabled = 0;	/* see disable_ctrl() */
static int ctrlc_was_pressed = 0;
int ctrlc (void)
{
	if (!ctrlc_disabled && gd->have_console) {
		if (tstc ()) {
			switch (getc ()) {
			case 0x03:		/* ^C - Control C */
				ctrlc_was_pressed = 1;
				return 1;
			default:
				break;
			}
		}
	}
	return 0;
}

/* pass 1 to disable ctrlc() checking, 0 to enable.
 * returns previous state
 */
int disable_ctrlc (int disable)
{
	int prev = ctrlc_disabled;	/* save previous state */

	ctrlc_disabled = disable;
	return prev;
}

int had_ctrlc (void)
{
	return ctrlc_was_pressed;
}

void clear_ctrlc (void)
{
	ctrlc_was_pressed = 0;
}

#ifdef CONFIG_MODEM_SUPPORT_DEBUG
char	screen[1024];
char *cursor = screen;
int once = 0;
inline void dbg(const char *fmt, ...)
{
	va_list	args;
	uint	i;
	char	printbuffer[CONFIG_SYS_PBSIZE];

	if (!once) {
		memset(screen, 0, sizeof(screen));
		once++;
	}

	va_start(args, fmt);

	/* For this to work, printbuffer must be larger than
	 * anything we ever want to print.
	 */
	i = vsprintf(printbuffer, fmt, args);
	va_end(args);

	if ((screen + sizeof(screen) - 1 - cursor) < strlen(printbuffer)+1) {
		memset(screen, 0, sizeof(screen));
		cursor = screen;
	}
	sprintf(cursor, printbuffer);
	cursor += strlen(printbuffer);

}
#else
inline void dbg(const char *fmt, ...)
{
}
#endif

/** U-Boot INIT FUNCTIONS *************************************************/

device_t *search_device (int flags, char *name)
{
	device_t *dev;

	dev = device_get_by_name(name);

	if(dev && (dev->flags & flags))
		return dev;

	return NULL;
}

int console_assign (int file, char *devname)
{
	int flag;
	device_t *dev;

	/* Check for valid file */
	switch (file) {
	case stdin:
		flag = DEV_FLAGS_INPUT;
		break;
	case stdout:
	case stderr:
		flag = DEV_FLAGS_OUTPUT;
		break;
	default:
		return -1;
	}

	/* Check for valid device name */

	dev = search_device(flag, devname);

	if(dev)
		return console_setfile (file, dev);

	return -1;
}

/* Called before relocation - use serial functions */
int console_init_f (void)
{
	gd->have_console = 1;

#ifdef CONFIG_SILENT_CONSOLE
	if (getenv("silent") != NULL)
		gd->flags |= GD_FLG_SILENT;
#endif

	return (0);
}

#ifdef CONFIG_SYS_CONSOLE_IS_IN_ENV
/* Called after the relocation - use desired console functions */
int console_init_r (void)
{
	char *stdinname, *stdoutname, *stderrname;
	device_t *inputdev = NULL, *outputdev = NULL, *errdev = NULL;
#ifdef CONFIG_SYS_CONSOLE_ENV_OVERWRITE
	int i;
#endif /* CONFIG_SYS_CONSOLE_ENV_OVERWRITE */
#ifdef CONFIG_CONSOLE_MUX
	int iomux_err = 0;
#endif

	/* set default handlers at first */
	gd->jt[XF_getc] = serial_getc;
	gd->jt[XF_tstc] = serial_tstc;
	gd->jt[XF_putc] = serial_putc;
	gd->jt[XF_puts] = serial_puts;
	gd->jt[XF_printf] = serial_printf;

	/* stdin stdout and stderr are in environment */
	/* scan for it */
	stdinname  = getenv ("stdin");
	stdoutname = getenv ("stdout");
	stderrname = getenv ("stderr");

	if (OVERWRITE_CONSOLE == 0) {	/* if not overwritten by config switch */
		inputdev  = search_device (DEV_FLAGS_INPUT,  stdinname);
		outputdev = search_device (DEV_FLAGS_OUTPUT, stdoutname);
		errdev    = search_device (DEV_FLAGS_OUTPUT, stderrname);
#ifdef CONFIG_CONSOLE_MUX
		iomux_err = iomux_doenv(stdin, stdinname);
		iomux_err += iomux_doenv(stdout, stdoutname);
		iomux_err += iomux_doenv(stderr, stderrname);
		if (!iomux_err)
			/* Successful, so skip all the code below. */
			goto done;
#endif
	}
	/* if the devices are overwritten or not found, use default device */
	if (inputdev == NULL) {
		inputdev  = search_device (DEV_FLAGS_INPUT,  "serial");
	}
	if (outputdev == NULL) {
		outputdev = search_device (DEV_FLAGS_OUTPUT, "serial");
	}
	if (errdev == NULL) {
		errdev    = search_device (DEV_FLAGS_OUTPUT, "serial");
	}
	/* Initializes output console first */
	if (outputdev != NULL) {
#ifdef CONFIG_CONSOLE_MUX
		/* need to set a console if not done above. */
		iomux_doenv(stdout, outputdev->name);
#else
		console_setfile (stdout, outputdev);
#endif
	}
	if (errdev != NULL) {
#ifdef CONFIG_CONSOLE_MUX
		/* need to set a console if not done above. */
		iomux_doenv(stderr, errdev->name);
#else
		console_setfile (stderr, errdev);
#endif
	}
	if (inputdev != NULL) {
#ifdef CONFIG_CONSOLE_MUX
		/* need to set a console if not done above. */
		iomux_doenv(stdin, inputdev->name);
#else
		console_setfile (stdin, inputdev);
#endif
	}

#ifdef CONFIG_CONSOLE_MUX
done:
#endif

	gd->flags |= GD_FLG_DEVINIT;	/* device initialization completed */

#ifndef CONFIG_SYS_CONSOLE_INFO_QUIET
	/* Print information */
	puts ("In:    ");
	if (stdio_devices[stdin] == NULL) {
		puts ("No input devices available!\n");
	} else {
#ifdef CONFIG_CONSOLE_MUX
		iomux_printdevs(stdin);
#else
		printf ("%s\n", stdio_devices[stdin]->name);
#endif
	}

	puts ("Out:   ");
	if (stdio_devices[stdout] == NULL) {
		puts ("No output devices available!\n");
	} else {
#ifdef CONFIG_CONSOLE_MUX
		iomux_printdevs(stdout);
#else
		printf ("%s\n", stdio_devices[stdout]->name);
#endif
	}

	puts ("Err:   ");
	if (stdio_devices[stderr] == NULL) {
		puts ("No error devices available!\n");
	} else {
#ifdef CONFIG_CONSOLE_MUX
		iomux_printdevs(stderr);
#else
		printf ("%s\n", stdio_devices[stderr]->name);
#endif
	}
#endif /* CONFIG_SYS_CONSOLE_INFO_QUIET */

#ifdef CONFIG_SYS_CONSOLE_ENV_OVERWRITE
	/* set the environment variables (will overwrite previous env settings) */
	for (i = 0; i < 3; i++) {
		setenv (stdio_names[i], stdio_devices[i]->name);
	}
#endif /* CONFIG_SYS_CONSOLE_ENV_OVERWRITE */

#if 0
	/* If nothing usable installed, use only the initial console */
	if ((stdio_devices[stdin] == NULL) && (stdio_devices[stdout] == NULL))
		return (0);
#endif
	return (0);
}

#else /* CONFIG_SYS_CONSOLE_IS_IN_ENV */

/* Called after the relocation - use desired console functions */
int console_init_r (void)
{
	device_t *inputdev = NULL, *outputdev = NULL;
	int i;
	struct list_head *list = device_get_list();
	struct list_head *pos;
	device_t *dev;

#ifdef CONFIG_SPLASH_SCREEN
	/* suppress all output if splash screen is enabled and we have
	   a bmp to display                                            */
	if (getenv("splashimage") != NULL)
		gd->flags |= GD_FLG_SILENT;
#endif

	/* Scan devices looking for input and output devices */
	list_for_each(pos, list) {
		dev = list_entry(pos, device_t, list);

		if ((dev->flags & DEV_FLAGS_INPUT) && (inputdev == NULL)) {
			inputdev = dev;
		}
		if ((dev->flags & DEV_FLAGS_OUTPUT) && (outputdev == NULL)) {
			outputdev = dev;
		}
		if(inputdev && outputdev)
			break;
	}

	/* Initializes output console first */
	if (outputdev != NULL) {
		console_setfile (stdout, outputdev);
		console_setfile (stderr, outputdev);
#ifdef CONFIG_CONSOLE_MUX
		console_devices[stdout][0] = outputdev;
		console_devices[stderr][0] = outputdev;
#endif
	}

	/* Initializes input console */
	if (inputdev != NULL) {
		console_setfile (stdin, inputdev);
#ifdef CONFIG_CONSOLE_MUX
		console_devices[stdin][0] = inputdev;
#endif
	}

	gd->flags |= GD_FLG_DEVINIT;	/* device initialization completed */

#ifndef CONFIG_SYS_CONSOLE_INFO_QUIET
	/* Print information */
	puts ("In:    ");
	if (stdio_devices[stdin] == NULL) {
		puts ("No input devices available!\n");
	} else {
		printf ("%s\n", stdio_devices[stdin]->name);
	}

	puts ("Out:   ");
	if (stdio_devices[stdout] == NULL) {
		puts ("No output devices available!\n");
	} else {
		printf ("%s\n", stdio_devices[stdout]->name);
	}

	puts ("Err:   ");
	if (stdio_devices[stderr] == NULL) {
		puts ("No error devices available!\n");
	} else {
		printf ("%s\n", stdio_devices[stderr]->name);
	}
#endif /* CONFIG_SYS_CONSOLE_INFO_QUIET */

	/* Setting environment variables */
	for (i = 0; i < 3; i++) {
		setenv (stdio_names[i], stdio_devices[i]->name);
	}

#if 0
	/* If nothing usable installed, use only the initial console */
	if ((stdio_devices[stdin] == NULL) && (stdio_devices[stdout] == NULL))
		return (0);
#endif

	return (0);
}

#endif /* CONFIG_SYS_CONSOLE_IS_IN_ENV */
