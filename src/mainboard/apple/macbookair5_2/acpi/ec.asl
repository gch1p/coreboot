/*
 * This file is part of the coreboot project.
 *
 * Copyright (c) 2019-2020 Evgeny Zinoviev <me@ch1p.io>
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

#define LIDS_OFFSET 0x60
#define HPAC_OFFSET 0x60
#define WKLD_OFFSET 0x68

#include <ec/apple/acpi/ec.asl>
#include <ec/apple/acpi/ac.asl>
#include <ec/apple/acpi/lid.asl>
