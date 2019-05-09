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

Device (GMUX)
{
    Name (_HID, EisaId ("APP000B"))
    Name (_CID, "gmux")
    Name (_STA, 0x0B)
    Name (_CRS, ResourceTemplate ()
    {
	IO (Decode16,
	    0x0700, // Range Minimum
	    0x07FF, // Range Maximum
	    0x01,   // Alignment
	    0xFF    // Length
	    )
    })
    Name (_PRW, Package (0x02) { 0x16, 0x03 })
    Scope (\_GPE)
    {
	Method (_L16, 0, NotSerialized)
	{
	    Notify (\_SB.PCI0.LPCB.GMUX, 0x80)
	}
    }

    Name (GMGP, 0x16)
    Method (GMSP, 1, NotSerialized)
    {
	If (Arg0 == 0)
	{
	    \GP06 |= Arg0
	}
    }

    Method (GMLV, 0, NotSerialized)
    {
	Return (\GP06)
    }
}
