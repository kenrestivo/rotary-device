/*
 * rotary_device.c
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

static int arr_argc = 0;
static int rotary_1[2] = { -1, -1};
static int rotary_2[2] = { -1, -1};



module_param_array(rotary_1, int, &arr_argc, 0000);
MODULE_PARM_DESC(a_lines, "GPIO lines for rotary 1 a,b");

module_param_array(rotary_2, int, &arr_argc, 0000);
MODULE_PARM_DESC(a_lines, "GPIO lines for rotary 2 a,b");




static void rotary_device_pdev_release(struct device *dev)
{
/* Needed to silence this message:
   Device 'xxx' does not have a release() function, it is broken and must be fixed
*/
}


// TODO: kzalloc these, support rotaries 1 < n 
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
			.gpio_a         = -1,
			.gpio_b         = -1,
			.inverted_a     = 0, 
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
			.gpio_a         = -1,
			.gpio_b         = -1,
			.inverted_a     = 0, 
			.inverted_b     = 0,
		}
	}
};


static int __init rotary_init(void)
{
	int ret;
	struct rotary_encoder_platform_data * pdata;

	// TODO: int platform_add_devices(struct platform_device **pdevs, int ndev);
	
	pr_info("initing first rotary device A=%d B=%d\n", rotary_1[0], rotary_1[1]);
	pdata = (struct rotary_encoder_platform_data *) rotary_device_1.dev.platform_data;
	pdata->gpio_a = rotary_1[0];
	pdata->gpio_b = rotary_1[1];
	ret = platform_device_register(&rotary_device_1);
	if (ret < 0) {
		pr_err(DRV_NAME \
		       ":    platform_device_register(1) returned %d\n",
		       ret);
		return ret;
	}

	// TODO: use linked list and nevermind all this boilerplate
	if(arr_argc > 1){
		pr_info("initing second rotary device A=%d B=%d\n", rotary_2[0], rotary_2[1]);
		pdata = (struct rotary_encoder_platform_data *) rotary_device_2.dev.platform_data;
		pdata->gpio_a = rotary_2[0];
		pdata->gpio_b = rotary_2[1];
		ret = platform_device_register(&rotary_device_2);
		if (ret < 0) {
			pr_err(DRV_NAME \
			       ":    platform_device_register(2) returned %d\n",
			       ret);
			return ret;
		}
	}
	return 0;
}

static void __exit rotary_exit(void)
{
	platform_device_unregister(&rotary_device_1);
	if(arr_argc > 1){
		platform_device_unregister(&rotary_device_2);
	}
}



arch_initcall(rotary_init);
module_exit(rotary_exit);

MODULE_ALIAS("platform:" DRV_NAME);
MODULE_DESCRIPTION("Rotary device hack");
MODULE_AUTHOR("Daniel Mack <daniel@caiaq.de>, Johan Hovold, Ken Restivo <ken@restivo.org>");
MODULE_LICENSE("GPL v2");
