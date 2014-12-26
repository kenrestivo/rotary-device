/*
 * rotary_encoder.c
 *
 * (c) 2009 Daniel Mack <daniel@caiaq.de>
 * Copyright (C) 2011 Johan Hovold <jhovold@gmail.com>
 * Copyright (C) 2013, Noralf Tronnes
 * Copyright (c) 2014 ken restivo <ken@restivo.org>
 * 
 * A device-adding hack for systems which do not support device tree,
 * inspired by the fbtft_device driver.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */


#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/input.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/rotary_encoder.h>
#include <linux/slab.h>
#include <linux/input.h>


#define DRV_NAME "rotary-device"


#define GPIO_ROTARY_1A 4
#define GPIO_ROTARY_1B 17
#define GPIO_ROTARY_2A 27
#define GPIO_ROTARY_2B 18


static void rotary_device_pdev_release(struct device *dev)
{
/* Needed to silence this message:
   Device 'xxx' does not have a release() function, it is broken and must be fixed
*/
}


static struct platform_device rotary_device_1 = 
{
	.name = "rotary-encoder", // the DRIVER name, not the device name.
	.id = 0, 
	.dev = {
                .release = rotary_device_pdev_release,
		.platform_data =  &(struct rotary_encoder_platform_data) {
			.steps          = 24,
			.axis           = REL_X,
			.relative_axis  = 1,
			.gpio_a         = GPIO_ROTARY_1A,
			.gpio_b         = GPIO_ROTARY_1B,
			.inverted_a     = 0, // TODO: try 1?
			.inverted_b     = 0,
		}
	}
};


static struct platform_device rotary_device_2 = 
{
	.name = "rotary-encoder", // the DRIVER name, not the device name.
	.id = 1, 
	.dev = {
                .release = rotary_device_pdev_release,
		.platform_data =  &(struct rotary_encoder_platform_data) {
			.steps          = 24,
			.axis           = REL_X,
			.relative_axis  = 1,
			.gpio_a         = GPIO_ROTARY_2A,
			.gpio_b         = GPIO_ROTARY_2B,
			.inverted_a     = 0, // TODO: try 1?
			.inverted_b     = 0,
		}
	}
};


static int __init rotary_init(void)
{
	int ret;
	pr_info("initing rotary device\n");
	request_module("rotary-encoder"); // TODO: not really necessary?
	ret = platform_device_register(&rotary_device_1);
	if (ret < 0) {
		pr_err(DRV_NAME \
		       ":    platform_device_register(1) returned %d\n",
		       ret);
		return ret;
	}
	// TODO: add_platform_devices() instead
	ret = platform_device_register(&rotary_device_2);
	if (ret < 0) {
		pr_err(DRV_NAME \
		       ":    platform_device_register(2) returned %d\n",
		       ret);
		return ret;
	}

	return 0;
}

static void __exit rotary_exit(void)
{
	platform_device_unregister(&rotary_device_1);
	platform_device_unregister(&rotary_device_2);
}



arch_initcall(rotary_init);
module_exit(rotary_exit);

MODULE_ALIAS("platform:" DRV_NAME);
MODULE_DESCRIPTION("Rotary device hack");
MODULE_AUTHOR("Daniel Mack <daniel@caiaq.de>, Johan Hovold, Ken Restivo <ken@restivo.org>");
MODULE_LICENSE("GPL v2");
