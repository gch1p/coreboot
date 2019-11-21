/* SPDX-License-Identifier: GPL-2.0-only */

#include <device/pci_def.h>
#include <device/pci_ops.h>
#include "me.h"
#include "pch.h"

void set_global_reset(bool enable)
{
#ifdef __SIMPLE_DEVICE__
	u32 etr3 = pci_read_config32(PCH_LPC_DEV, ETR3);
#else
	struct device *lpc = pcidev_on_root(0x1f, 0);
	u32 etr3 = pci_read_config32(lpc, ETR3);
#endif

	/* Clear CF9 Without Resume Well Reset Enable */
	etr3 &= ~ETR3_CWORWRE;

	/* CF9GR indicates a Global Reset */
	if (enable)
		etr3 |= ETR3_CF9GR;
	else
		etr3 &= ~ETR3_CF9GR;

#ifdef __SIMPLE_DEVICE__
	pci_write_config32(PCH_LPC_DEV, ETR3, etr3);
#else
	pci_write_config32(lpc, ETR3, etr3);
#endif
}
