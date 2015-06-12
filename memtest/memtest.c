/**
 *  C component of a demo bootsector. This does not actually load any
 *  operating system, but rather it will run in 16 bit real mode, and
 *  use BIOS calls to obtain and print information about what memory is
 *  available on the system.
 */

#include "types.h"
#include "bios.h"
#include "output.h"
#include "utils.h"

/**********************************************************/

PRIVATE void print_descriptor (struct memory_region *descriptor);
PRIVATE void print_header (void);
PRIVATE void print_footer (void);

/**********************************************************/

/**
 *  This is the first function to run after start.s has set up a function
 *  call stack.
 */
    PUBLIC void
startc (void)
{
    // this allows us to set the values of specific registers for a BIOS
    // call.
    struct cpu_registers registers;

    // Each contiguous region of memory is described by several fields, a
    // base address, length, and what type of memory it is.
    struct memory_region descriptor;
    
    // print table header, and make sure the ebx register is zero for the
    // first BIOS call.
    print_header ();
    registers.ebx = 0;

    do
    {
        // set up the registers for the BIOS call. eax contains an opcode,
        // si points to the descriptor structure.
        registers.eax = 0xE8280;
        registers.es = 0x00;
        registers.esi = (uint32_t) &descriptor;
        registers.ecx = sizeof (descriptor);
        registers.edx = 0x534D4150;

        // invoke the BIOS to get the next memory descriptor.
        bios_interrupt (&registers, 0x15);

        // check the register states after the call to make sure that no
        // errors occurred.
        if ((registers.eflags & EFLAGS_CARRY) || 
          (registers.eax != 0x534D4150))
        {
            print_string ("Error reading memory.\n");
            break;
        }

        // now print out the details about the memory region.
        print_descriptor (&descriptor);
    }
    while (registers.ebx != 0);

    print_footer ();
    idle ();
}

/**********************************************************/

/**
 *  Print the contents of a given memory descriptor, forming a single row
 *  of a table of memory region information displayed on the screen.
 */
    PRIVATE void
print_descriptor (descriptor)
    struct memory_region *descriptor;
{
    print_int_hex (descriptor->base_hi);
    print_string (" : ");
    print_int_hex (descriptor->base_low);
    print_string (" | ");

    print_int_hex (descriptor->length_hi);
    print_string (" : ");
    print_int_hex (descriptor->length_low);
    print_string (" | ");

    switch (descriptor->type)
    {
    case 1:
        print_string ("Available memory.\n");
        break;

    case 2:
        print_string ("Reserved memory.\n");
        break;

    default:
        print_string ("Undefined memory block.\n");
    }
}

/**********************************************************/

/**
 *  Prints the header for a table of memory information.
 */
    PRIVATE void
print_header (void)
{
    print_string ("System memory:\n\n");
    print_string ("Base Address (high:low) | Length (high:low)       "
      "| Type\n");
    print_string ("===================================================\n");
}

/**********************************************************/

/**
 *  Prints the bottom border for the table of memory information.
 */
    PRIVATE void
print_footer (void)
{
    print_string ("===================================================\n");
}

/**********************************************************/

/** vim: set ts=4 sw=4 et : */
