/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) Canonical Ltd. <seth.forshee@canonical.com>
 * Copyright (C) 2010-2012 Andreas Heider <andreas@meetr.de>
 * Copyright (C) 2015 Lukas Wunner <lukas@wunner.de>
 * Copyright (C) 2019 Evgeny Zinoviev <me@ch1p.io>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; version 2 of
 * the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <delay.h>
#include <arch/io.h>
#include <device/device.h>
#include "gmux.h"
#include "chip.h"

static int gmux_index_wait_ready(void)
{
	int i = 200;
	u8 gwr = inb(GMUX_IOSTART + GMUX_PORT_WRITE);

	while (i && (gwr & 0x01)) {
		inb(GMUX_IOSTART + GMUX_PORT_READ);
		gwr = inb(GMUX_IOSTART + GMUX_PORT_WRITE);
		udelay(100);
		i--;
	}

	return !!i;
}

static int gmux_index_wait_complete(void)
{
	int i = 200;
	u8 gwr = inb(GMUX_IOSTART + GMUX_PORT_WRITE);

	while (i && !(gwr & 0x01)) {
		gwr = inb(GMUX_IOSTART + GMUX_PORT_WRITE);
		udelay(100);
		i--;
	}

	if (gwr & 0x01)
		inb(GMUX_IOSTART + GMUX_PORT_READ);

	return !!i;
}

u8 gmux_pio_read8(u8 port)
{
	return inb(GMUX_IOSTART + port);
}

u8 gmux_index_read8(u8 port)
{
	u8 val;

	gmux_index_wait_ready();
	outb(port, GMUX_IOSTART + GMUX_PORT_READ);
	gmux_index_wait_complete();
	val = inb(GMUX_IOSTART + GMUX_PORT_VALUE);

	return val;
}

void gmux_pio_write8(u8 port, u8 val)
{
	outb(val, GMUX_IOSTART + port);
}

void gmux_index_write8(u8 port, u8 val)
{
	outb(val, GMUX_IOSTART + GMUX_PORT_VALUE);
	gmux_index_wait_ready();
	outb(port, GMUX_IOSTART + GMUX_PORT_WRITE);
	gmux_index_wait_complete();
}

u32 gmux_pio_read32(u8 port)
{
	return inl(GMUX_IOSTART + port);
}

u32 gmux_index_read32(u8 port)
{
	u32 val;

	gmux_index_wait_ready();
	outb(port, GMUX_IOSTART + GMUX_PORT_READ);
	gmux_index_wait_complete();
	val = inl(GMUX_IOSTART + GMUX_PORT_VALUE);

	return val;
}

u8 gmux_read8(const struct device *dev, u8 port)
{
	const struct drivers_apple_hybrid_graphics_config
		*config = dev->chip_info;
	if (config->gmux_indexed)
		return gmux_index_read8(port);
	else
		return gmux_pio_read8(port);
}

void gmux_write8(const struct device *dev, u8 port, u8 val)
{
	const struct drivers_apple_hybrid_graphics_config
		*config = dev->chip_info;
	if (config->gmux_indexed)
		gmux_index_write8(port, val);
	else
		gmux_pio_write8(port, val);
}

u32 gmux_read32(const struct device *dev, u8 port)
{
	const struct drivers_apple_hybrid_graphics_config
		*config = dev->chip_info;
	if (config->gmux_indexed)
		return gmux_index_read32(port);
	else
		return gmux_pio_read32(port);
}

void gmux_dgpu_power_enable(const struct device *dev, bool enable)
{
	if (enable) {
		gmux_write8(dev, GMUX_PORT_DISCRETE_POWER, 1);
		gmux_write8(dev, GMUX_PORT_DISCRETE_POWER, 3);
	} else {
		gmux_write8(dev, GMUX_PORT_DISCRETE_POWER, 1);
		gmux_write8(dev, GMUX_PORT_DISCRETE_POWER, 0);
	}
}

void gmux_switch(const struct device *dev, bool dgpu)
{
	if (dgpu) {
		gmux_write8(dev, GMUX_PORT_SWITCH_DDC, 2);
		gmux_write8(dev, GMUX_PORT_SWITCH_DISPLAY, 3);
	} else {
		gmux_write8(dev, GMUX_PORT_SWITCH_DDC, 1);
		gmux_write8(dev, GMUX_PORT_SWITCH_DISPLAY, 2);
	}
}
