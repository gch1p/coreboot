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

#include <device/pci_ops.h>
#include <northbridge/intel/sandybridge/sandybridge.h>
#include <northbridge/intel/sandybridge/raminit_native.h>
#include <southbridge/intel/bd82x6x/pch.h>
#include <drivers/apple/hybrid_graphics/hybrid_graphics.h>
#include <cbfs.h>

void mainboard_pch_lpc_setup(void)
{
	pci_write_config16(PCH_LPC_DEV, LPC_EN, 0x3f0f);
	pci_write_config32(PCH_LPC_DEV, LPC_GEN1_DEC, 0x000c0681);
	pci_write_config32(PCH_LPC_DEV, LPC_GEN2_DEC, 0x000c1641);
	pci_write_config32(PCH_LPC_DEV, LPC_GEN3_DEC, 0x001c0301);
	pci_write_config32(PCH_LPC_DEV, LPC_GEN4_DEC, 0x00fc0701);
	pci_write_config16(PCH_LPC_DEV, LPC_IO_DEC, 0x0070);
}

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

void mainboard_early_init(int s3resume)
{
	bool igd, peg;
	u32 reg32;

	early_hybrid_graphics(&igd, &peg);

	/* Hide disabled devices */
	reg32 = pci_read_config32(PCI_DEV(0, 0, 0), DEVEN);
	reg32 &= ~(DEVEN_PEG10 | DEVEN_IGD);

	if (peg)
		reg32 |= DEVEN_PEG10;

	if (igd) {
		reg32 |= DEVEN_IGD;
	} else {
		/* Disable IGD VGA decode, no GTT or GFX stolen */
		pci_write_config16(PCI_DEV(0, 0, 0), GGC, 2);
	}

	pci_write_config32(PCI_DEV(0, 0, 0), DEVEN, reg32);
}

void mainboard_get_spd(spd_raw_data *spd, bool id_only)
{
	void *spd_file;
	size_t spd_file_len = 0;
	spd_file = cbfs_boot_map_with_leak("spd.bin", CBFS_TYPE_SPD, &spd_file_len);

	if (!spd_file || spd_file_len < 128)
		die("Missing SPD data.");

	memcpy(&spd[0], spd_file, 128);
	memcpy(&spd[2], spd_file, 128);
}
