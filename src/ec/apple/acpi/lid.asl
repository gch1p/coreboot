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
		Offset(LIDS_OFFSET),
		LIDS, 1,   /* Lid status */

		Offset(WKLD_OFFSET),
		WKLD, 1,   /* Lid wake */
	}

	Device(LID)
	{
		Name(_HID, "PNP0C0D")

		Method(_LID, 0, NotSerialized)
		{
			Return(LIDS)
		}

		Method(_PRW, 0, NotSerialized)
		{
#if LIDS_OFFSET == 0x01
			Return(Package() { 0x1d, 0x03 })
#else
			Return(Package() { 0x23, 0x04 })
#endif
		}

		Method(_PSW, 1, NotSerialized)
		{
			if (Arg0) {
				WKLD = 1
			} else {
				WKLD = 0
			}
		}
	}
}
