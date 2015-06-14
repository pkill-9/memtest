/**
 *  Struct declarations for a simple program to query the BIOS for memory
 *  information.
 */

#ifndef _MEMTEST_TYPES_H
#define _MEMTEST_TYPES_H

#include <stdint.h>

/**********************************************************/

/**
 *  The BIOS call to query the system memory information returns 
 *  information about a single contiguous chunk of memory in a descriptor
 *  that fits this struct. It contains the base address and length, both
 *  of which are 64 bit numbers, and also whether the region is usable or
 *  reserved for some other purpose.
 */
struct memory_region
{
    uint32_t base_low;
    uint32_t base_hi;
    uint32_t length_low;
    uint32_t length_hi;
    uint32_t type;
    uint32_t unused;
};

/**********************************************************/

#endif // _MEMTEST_TYPES_H

/** vim: set ts=4 sw=4 et : */
