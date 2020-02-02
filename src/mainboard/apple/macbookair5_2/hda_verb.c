/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2008-2009 coresystems GmbH
 * Copyright (C) 2014 Vladimir Serbinenko
 * Copyright (C) 2019-2020 Evgeny Zinoviev
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

#include <device/azalia_device.h>

const u32 cim_verb_data[] = {
	0x10134206, /* Codec Vendor / Device ID: Cirrus CS4206 */
	0x106b5600, /* Subsystem ID */

	11, /* Number of 4 dword sets */

	AZALIA_SUBVENDOR(0, 0x106b5600),
	AZALIA_PIN_CFG(0, 0x09, 0x0e2b4030),
	AZALIA_PIN_CFG(0, 0x0a, 0x400000f0),
	AZALIA_PIN_CFG(0, 0x0b, 0x90100120),
	AZALIA_PIN_CFG(0, 0x0c, 0x400000f0),
	AZALIA_PIN_CFG(0, 0x0d, 0x90a00110),
	AZALIA_PIN_CFG(0, 0x0e, 0x400000f0),
	AZALIA_PIN_CFG(0, 0x0f, 0x400000f0),
	AZALIA_PIN_CFG(0, 0x10, 0x400000f0),
	AZALIA_PIN_CFG(0, 0x12, 0x400000f0),
	AZALIA_PIN_CFG(0, 0x15, 0x400000f0),

	0x80862806, /* Codec Vendor / Device ID: Intel */
	0x80860101, /* Subsystem ID */

	4, /* Number of 4 dword sets */

	AZALIA_SUBVENDOR(3, 0x80860101),
	AZALIA_PIN_CFG(3, 0x05, 0x18560010),
	AZALIA_PIN_CFG(3, 0x06, 0x18560010),
	AZALIA_PIN_CFG(3, 0x07, 0x18560010),
};

const u32 pc_beep_verbs[] = {
	0x00270500, /* Set PS to D0 on DAC1 */
	0x00470500, /* Set PS to D0 on DAC3 */
	0x00270650, /* Set converter stream on DAC1 */
	0x00470650, /* Set converted stream on DAC3 */
};

AZALIA_ARRAY_SIZES;
