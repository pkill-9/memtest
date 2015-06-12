/**
 *  Function to invoke BIOS interrupts from C.
 */

#ifndef _MEMTEST_BIOS_H
#define _MEMTEST_BIOS_H

#include "types.h"

void bios_interrupt (struct cpu_registers *registers, int interrupt);
void idle (void);

#endif

/** vim: set ts=4 sw=4 et : */
