/*
 * This file is part of the coreboot project.
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
	0x106b2800, /* Subsystem ID */

	11, /* Number of 4 dword sets */

	AZALIA_SUBVENDOR(0, 0x106b2800),
	AZALIA_PIN_CFG(0, 0x09, 0x002b4020),
	AZALIA_PIN_CFG(0, 0x0a, 0x90100112),
	AZALIA_PIN_CFG(0, 0x0b, 0x90100110),
	AZALIA_PIN_CFG(0, 0x0c, 0x400000f0),
	AZALIA_PIN_CFG(0, 0x0d, 0x400000f0),
	AZALIA_PIN_CFG(0, 0x0e, 0x90a60100),
	AZALIA_PIN_CFG(0, 0x0f, 0x400000f0),
	AZALIA_PIN_CFG(0, 0x10, 0x004be030),
	AZALIA_PIN_CFG(0, 0x12, 0x400000f0),
	AZALIA_PIN_CFG(0, 0x15, 0x400000f0),
};

const u32 pc_beep_verbs[0] = {};

AZALIA_ARRAY_SIZES;
