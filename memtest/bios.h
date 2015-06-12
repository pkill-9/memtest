/**
 *  Function to invoke BIOS interrupts from C.
 */

#ifndef _MEMTEST_BIOS_H
#define _MEMTEST_BIOS_H

#include <stdint.h>
#include "types.h"

void bios_putchar (uint8_t ch);
int fetch_memory_list (struct memory_region *list);
void idle (void);

#endif

/** vim: set ts=4 sw=4 et : */
