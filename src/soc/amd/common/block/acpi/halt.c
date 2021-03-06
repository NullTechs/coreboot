/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2018 Google Inc.
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

#include <arch/acpi.h>
#include <soc/southbridge.h>
#include <amdblocks/acpimmio.h>
#include <halt.h>

void poweroff(void)
{
	acpi_write32(MMIO_ACPI_PM1_CNT_BLK,
			  (SLP_TYP_S5 << SLP_TYP_SHIFT) | SLP_EN);

	/*
	 * Setting SLP_TYP_S5 in PM1 triggers SLP_SMI, which is handled by SMM
	 * to transition to S5 state. If halt is called in SMM, then it prevents
	 * the SMI handler from being triggered and system never enters S5.
	 */
	if (!ENV_SMM)
		halt();
}
