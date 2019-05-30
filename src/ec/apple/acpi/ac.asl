/*
 * This file is part of the coreboot project.
 *
 * Copyright (c) 2019-2020 Evgeny Zinoviev <me@ch1p.io>
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

Scope(\_SB.PCI0.LPCB.EC)
{
	Field(ERAM, ByteAcc, NoLock, Preserve)
	{
		Offset(HPAC_OFFSET),
			, 1,
		HPAC, 1,  /* AC status */
	}

	Device(AC)
	{
		Name(_HID, "ACPI0003")
		Name(_UID, 0x00)
		Name(_PCL, Package() { \_SB } )

		Method(_PSR, 0, NotSerialized)
		{
			Return(HPAC)
		}

		Method(_STA, 0, NotSerialized)
		{
			Return(0x0f)
		}
	}
}
