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

#ifndef _DRIVERS_APPLE_HYBRID_GRAPHICS_H_
#define _DRIVERS_APPLE_HYBRID_GRAPHICS_H_

#define HYBRID_GRAPHICS_PORT 0xff
#define HYBRID_GRAPHICS_DEVICE 0xf

void early_hybrid_graphics(bool *enable_igd, bool *enable_peg);

#endif /* _DRIVERS_APPLE_HYBRID_GRAPHICS_CHIP_H_ */
