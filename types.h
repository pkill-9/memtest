/**
 *  Struct declarations for a simple program to query the BIOS for memory
 *  information.
 */

#ifndef _MEMTEST_TYPES_H
#define _MEMTEST_TYPES_H

/**********************************************************/

/**
 *  We interact with the BIOS using interrupts. Each interrupt needs 
 *  certain parameters, which must be stored in specific CPU registers.
 *  This presents a challenge, since we are not able to explicitly
 *  manipulate registers in C, yet assembly language is unpleasant to use
 *  for large ammounts of code, as it is not easy for humans to 
 *  understand.
 *
 *  The solution that is used here is that we will have an assembly
 *  language function that will take values out of specific fields of this
 *  struct and load the values into the corresponding registers, before
 *  triggering the interrupt. When the interrupt returns, the new register
 *  states will be loaded back into this struct, and the assembly function
 *  returns control to the C code. So our C code can now effectively make
 *  BIOS interrupt calls. Nice, huh?
 */
struct cpu_registers
{
    // all registers are 32 bits wide, we assume.
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t esi;
    uint32_t edi;
    uint32_t es;
    uint32_t eflags;
};

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
};

/**********************************************************/

#endif // _MEMTEST_TYPES_H

/** vim: set ts=4 sw=4 et : */
