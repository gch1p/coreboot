/*
 * This file is part of the coreboot project.
 *
 * Copyright (c) 2019 Evgeny Zinoviev <me@ch1p.io>
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

Device(EC)
{
	Name(_HID, EISAID("PNP0C09"))
	Name(_UID, 0)

	Name(_GPE, 0x17)
	Mutex(ECLK, 0)

	OperationRegion(ERAM, EmbeddedControl, 0x00, 0x100)

	/* LID status change. */
	Method(_Q20, 0, NotSerialized)
	{
		Notify(LID, 0x80)
	}

	/* AC status change. */
	Method(_Q21, 0, NotSerialized)
	{
		Notify(AC, 0x80)
	}

	Method(_CRS, 0)
	{
		Name(ECMD, ResourceTemplate()
		{
			IO(Decode16, 0x62, 0x62, 1, 1)
			IO(Decode16, 0x66, 0x62, 1, 1)
		})
		Return(ECMD)
	}

	Method(_PRW, 0, NotSerialized)
	{
		Return(Package () { 0x23, 0x04 })
	}

	Method(_INI, 0, NotSerialized)
	{
	}

#include "battery.asl"
}
