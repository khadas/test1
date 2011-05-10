/*
 * BF537-STAMP POST code
 *
 * Enter bugs at http://blackfin.uclinux.org/
 *
 * Copyright (c) 2005-2009 Analog Devices Inc.
 *
 * Licensed under the GPL-2 or later.
 */

#include <common.h>
#include <config.h>
#include <command.h>
#include <asm/blackfin.h>
#include <asm/gpio.h>

/****************************************************
 * LED1 ---- PF6	LED2 ---- PF7		    *
 * LED3 ---- PF8	LED4 ---- PF9		    *
 * LED5 ---- PF10	LED6 ---- PF11		    *
 ****************************************************/
int led_post_test(int flags)
{
	unsigned int leds[] = {
		GPIO_PF6, GPIO_PF7, GPIO_PF8,
		GPIO_PF9, GPIO_PF10, GPIO_PF11,
	};
	int i;

	for (i = 0; i < ARRAY_SIZE(leds); ++i) {
		gpio_request(leds[i], "post");
		gpio_direction_output(leds[i], 0);

		printf("LED%i on", i + 1);
		gpio_set_value(leds[i], 1);
		udelay(1000000);
		printf("\b\b\b\b\b\b\b");

		gpio_free(leds[i]);
	}

	return 0;
}

/************************************************
 *  SW10 ---- PF5	SW11 ---- PF4		*
 *  SW12 ---- PF3	SW13 ---- PF2		*
 ************************************************/
int button_post_test(int flags)
{
	unsigned int buttons[] = {
		GPIO_PF2, GPIO_PF3, GPIO_PF4, GPIO_PF5,
	};
	unsigned int sws[] = { 13, 12, 11, 10, };
	int i, delay = 5;
	unsigned short value = 0;
	int result = 0;

	for (i = 0; i < ARRAY_SIZE(buttons); ++i) {
		gpio_request(buttons[i], "post");
		gpio_direction_input(buttons[i]);

		delay = 5;
		printf("\n--------Press SW%i: %2d ", sws[i], delay);
		while (delay--) {
			for (i = 0; i < 100; i++) {
				value = gpio_get_value(buttons[i]);
				if (value != 0)
					break;
				udelay(10000);
			}
			printf("\b\b\b%2d ", delay);
		}
		if (value != 0)
			puts("\b\bOK");
		else {
			result = -1;
			puts("\b\bfailed");
		}

		gpio_free(buttons[i]);
	}

	puts("\n");

	return result;
}
