/**
 *  Functions for printing data on the screen via BIOS interrupts.
 *
 *  Since our code is a bootsector, there is no cushy C library printf
 *  for printing to the screen. Fortunately, the BIOS provides some
 *  abstraction for putting a character on the screen, so we don't have to
 *  go stuffing around with video memory, but we do need to handle 
 *  printing both strings and ints.
 */

#ifndef _MEMTEST_OUTPUT_H
#define _MEMTEST_OUTPUT_H

#include <stdint.h>

/**********************************************************/

void print_string (const char *string);
void print_int_hex (uint32_t value);
void print_long_hex (uint32_t lsb, uint32_t msb);

/**********************************************************/

#endif // _MEMTEST_OUTPUT_H

/** vim: set ts=4 sw=4 et : */
