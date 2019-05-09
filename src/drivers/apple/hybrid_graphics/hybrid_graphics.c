/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2019 Evgeny Zinoviev <me@ch1p.io>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <types.h>
#include <option.h>
#include <device/device.h>

#include <southbridge/intel/common/gpio.h>
#include <console/console.h>
#include "chip.h"
#include "gmux.h"

static void enable_dev(struct device *dev)
{
	const struct drivers_lenovo_hybrid_graphics_config *config;
	enum hybrid_graphics_req mode;
	u8 ver_major, ver_minor, ver_release;
	u32 version, max_brightness, brightness;

	/* Don't confuse anyone else and disable the fake device */
	dev->enabled = 0;

	config = dev->chip_info;
	if (!config) {
		printk(BIOS_INFO, "Hybrid graphics: Not installed\n");
		return;
	}

	version = gmux_index_read32(GMUX_PORT_VERSION_MAJOR);
	ver_major = (version >> 24) & 0xff;
	ver_minor = (version >> 16) & 0xff;
	ver_release = (version >> 8) & 0xff;
	max_brightness = gmux_index_read32(GMUX_PORT_MAX_BRIGHTNESS);
	brightness = gmux_index_read32(GMUX_PORT_BRIGHTNESS)
		& GMUX_BRIGHTNESS_MASK;

	printk(BIOS_INFO, "gmux version: %d.%d.%d\n",
		ver_major, ver_minor, ver_release);
	printk(BIOS_INFO, "gmux max brightness: %d\n", max_brightness);
	printk(BIOS_INFO, "gmux brightness: %d\n", brightness);

	mode = HYBRID_GRAPHICS_DEFAULT_GPU;
	get_option(&mode, "hybrid_graphics_mode");

	gmux_switch(dev, mode == HYBRID_GRAPHICS_DISCRETE);
}

struct chip_operations drivers_apple_hybrid_graphics_ops = {
	CHIP_NAME("Apple hybrid graphics driver")
	.enable_dev = enable_dev
};
