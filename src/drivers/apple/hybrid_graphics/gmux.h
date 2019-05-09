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

#ifndef DRIVERS_APPLE_GMUX_H
#define DRIVERS_APPLE_GMUX_H

#define GMUX_PORT_VERSION_MAJOR     0x04
#define GMUX_PORT_VERSION_MINOR     0x05
#define GMUX_PORT_VERSION_RELEASE   0x06

#define GMUX_PORT_SWITCH_DISPLAY    0x10
#define GMUX_PORT_SWITCH_DDC        0x28
#define GMUX_PORT_DISCRETE_POWER    0x50
#define GMUX_PORT_MAX_BRIGHTNESS    0x70
#define GMUX_PORT_BRIGHTNESS        0x74
#define GMUX_PORT_VALUE             0xc2
#define GMUX_PORT_READ              0xd0
#define GMUX_PORT_WRITE             0xd4

#define GMUX_PORT_INTERRUPT_ENABLE  0x14
#define GMUX_INTERRUPT_ENABLE       0xff
#define GMUX_INTERRUPT_DISABLE      0x00

#define GMUX_BRIGHTNESS_MASK        0x00ffffff
#define GMUX_MAX_BRIGHTNESS         GMUX_BRIGHTNESS_MASK

#define GMUX_IOSTART                0x700

u8 gmux_index_read8(u8 port);
u8 gmux_pio_read8(u8 port);
u8 gmux_read8(const struct device *dev, u8 port);

void gmux_index_write8(u8 port, u8 val);
void gmux_pio_write8(u8 port, u8 val);
void gmux_write8(const struct device *dev, u8 port, u8 val);

u32 gmux_index_read32(u8 port);
u32 gmux_pio_read32(u8 port);
u32 gmux_read32(const struct device *dev, u8 port);

void gmux_switch(const struct device *dev, bool dgpu);
void gmux_dgpu_power_enable(const struct device *dev, bool enable);

#endif /* DRIVERS_APPLE_GMUX_H */
