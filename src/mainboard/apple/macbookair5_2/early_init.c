/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2019-2020 Evgeny Zinoviev <me@ch1p.io>
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

#include <northbridge/intel/sandybridge/sandybridge.h>
#include <northbridge/intel/sandybridge/raminit_native.h>
#include <southbridge/intel/bd82x6x/pch.h>
#include <cbfs.h>

const struct southbridge_usb_port mainboard_usb_ports[] = {
	{ 1, 0,  0 }, /* Ext A (XHCI/EHCI) */
	{ 1, 0,  1 }, /* Ext B (XHCI) */
	{ 1, 0,  2 }, /* Ext C (XHCI/EHCI) */
	{ 1, 0,  3 }, /* Ext D (XHCI) */
	{ 0, 0, -1 }, /* Unused */
	{ 1, 0, -1 }, /* SD */
	{ 1, 0, -1 }, /* Wi-Fi */
	{ 1, 0, -1 }, /* USB Hub (All LS/FS Devices) */
	{ 1, 0, -1 }, /* Camera */
	{ 1, 0,  4 }, /* Ext B (EHCI) */
	{ 1, 0,  5 }, /* Ext D (EHCI) */
	{ 1, 0, -1 }, /* BT */
	{ 0, 0, -1 }, /* Unused */
	{ 0, 0, -1 }, /* Unused */
};

void mainboard_get_spd(spd_raw_data *spd, bool id_only)
{
	void *spd_file;
	size_t spd_file_len = 0;
	spd_file = cbfs_boot_map_with_leak("spd.bin", CBFS_TYPE_SPD,
						&spd_file_len);
	if (spd_file && spd_file_len >= 512) {
		memcpy(&spd[0], spd_file, 128);
		memcpy(&spd[2], spd_file + 256, 128);
	}
}
