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

#ifndef _APPLE_HYBRID_GRAPHICS_CHIP_H_
#define _APPLE_HYBRID_GRAPHICS_CHIP_H_

enum hybrid_graphics_req {
	HYBRID_GRAPHICS_INTEGRATED = 0,
	HYBRID_GRAPHICS_DISCRETE = 1
};

#define HYBRID_GRAPHICS_DEFAULT_GPU HYBRID_GRAPHICS_INTEGRATED

struct drivers_apple_hybrid_graphics_config {
	bool gmux_indexed;
};

#endif /* _APPLE_HYBRID_GRAPHICS_CHIP_H_ */
