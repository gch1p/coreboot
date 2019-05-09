/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2017 Patrick Rudolph <siro@das-labor.org>
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
#include <console/console.h>
#include "hybrid_graphics.h"
#include "chip.h"
#include "gmux.h"

void early_hybrid_graphics(bool *enable_igd, bool *enable_peg)
{
	const struct device *dev;
	enum hybrid_graphics_req mode = HYBRID_GRAPHICS_DEFAULT_GPU;

	/* TODO: Use generic device instead of dummy PNP device */
	dev = dev_find_slot_pnp(HYBRID_GRAPHICS_PORT, HYBRID_GRAPHICS_DEVICE);

	if (!dev || !dev->chip_info) {
		printk(BIOS_ERR, "Hybrid graphics: ERROR\n");
		*enable_igd = true;
		*enable_peg = false;
		return;
	}

	get_option(&mode, "hybrid_graphics_mode");

	if (mode == HYBRID_GRAPHICS_DISCRETE) {
		printk(BIOS_DEBUG, "Hybrid graphics:"
			   " Disabling integrated GPU.\n");

		*enable_igd = false;
		*enable_peg = true;
	} else if (mode == HYBRID_GRAPHICS_INTEGRATED) {
		printk(BIOS_DEBUG, "Hybrid graphics:"
			   " Disabling discrete GPU.\n");

		*enable_igd = true;
		*enable_peg = false;
	}

	gmux_dgpu_power_enable(dev, *enable_peg);
}
