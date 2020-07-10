/* SPDX-License-Identifier: GPL-2.0-only */

#include <stdint.h>
#include <arch/bootblock.h>
#include <arch/cpu.h>
#include <cpu/x86/msr.h>
#include <arch/io.h>
#include <option.h>
#include <halt.h>

#include "model_206ax.h"

#if CONFIG(SOUTHBRIDGE_INTEL_BD82X6X) || \
	CONFIG(SOUTHBRIDGE_INTEL_C216)
/* Needed for RCBA access to set Soft Reset Data register */
#include <southbridge/intel/bd82x6x/pch.h>
#else
#error "CPU must be paired with Intel BD82X6X or C216 southbridge"
#endif

static u32 set_flex_ratio_to_tdp_nominal(u32 soft_reset)
{
	msr_t flex_ratio, msr;
	u8 nominal_ratio;

	/* Minimum CPU revision for configurable TDP support */
	if (cpuid_eax(1) < IVB_CONFIG_TDP_MIN_CPUID)
		return soft_reset;

	/* Check for Flex Ratio support */
	flex_ratio = rdmsr(MSR_FLEX_RATIO);
	if (!(flex_ratio.lo & FLEX_RATIO_EN))
		return soft_reset;

	/* Check for >0 configurable TDPs */
	msr = rdmsr(MSR_PLATFORM_INFO);
	if (((msr.hi >> 1) & 3) == 0)
		return soft_reset;

	/* Use nominal TDP ratio for flex ratio */
	msr = rdmsr(MSR_CONFIG_TDP_NOMINAL);
	nominal_ratio = msr.lo & 0xff;

	/* Set flex ratio to nominal TDP ratio */
	flex_ratio.lo &= ~0xff00;
	flex_ratio.lo |= nominal_ratio << 8;
	flex_ratio.lo |= FLEX_RATIO_LOCK;
	wrmsr(MSR_FLEX_RATIO, flex_ratio);

	/* Set flex ratio in soft reset data register bits 11:6.
	 * RCBA region is enabled in southbridge bootblock */
	soft_reset &= ~(0x3f << 6);
	soft_reset |= (nominal_ratio & 0x3f) << 6;
	return soft_reset;
}

static u32 set_hyperthreading_option(u32 soft_reset)
{
	int ht_requested = 0;
	int cmos_result;
	struct cpuid_result result;

	cmos_result = get_option(&ht_requested, "hyper_threading");
	if (cmos_result != CB_SUCCESS)
		return soft_reset;

	/* Make sure the CPU has more than one logical processor per core */
	result = cpuid_ext(0xb, 1);
	if ((result.ebx & 0xff) == 1)
		return soft_reset;

	soft_reset &= ~1;
	soft_reset |= !ht_requested; /* Bit 0 is HT disable */
	return soft_reset;
}

static void soft_reset_settings(void)
{
	int need_reset;
	u32 soft_reset;

	soft_reset = RCBA32(SOFT_RESET_DATA);
	soft_reset = set_flex_ratio_to_tdp_nominal(soft_reset);
	soft_reset = set_hyperthreading_option(soft_reset);

	/* Check if we didn't already request these settings */
	need_reset = !(RCBA32(SOFT_RESET_CTRL) & 1) ||
		     RCBA32(SOFT_RESET_DATA) != soft_reset;

	if (need_reset) {
		/* Set current requests */
		RCBA32(SOFT_RESET_DATA) = soft_reset;

		/* Use them instead of defaults */
		RCBA32_OR(SOFT_RESET_CTRL, 1);

		outb(0x0, 0xcf9);
		outb(0x6, 0xcf9);
		halt();
	} else {
		RCBA32_OR(SOFT_RESET_LOCK, 1);
	}
}

void bootblock_early_cpu_init(void)
{
	soft_reset_settings();
}
