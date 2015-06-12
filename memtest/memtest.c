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

/** set the maximum size of the list of memory regions to a large number,
 *  that is unlikely to be exceeded. */
#define MAX_DESCRIPTORS     100

/**********************************************************/

PRIVATE void print_descriptor (struct memory_region *descriptor);
PRIVATE void print_header (void);
PRIVATE void print_separator (void);

/**********************************************************/

/**
 *  This is the first function to run after start.s has set up a function
 *  call stack.
 */
    PUBLIC void
startc (void)
{
    struct memory_region descriptors [MAX_DESCRIPTORS];
    int numdescriptors, i;

    print_string ("It works.\n");
    numdescriptors = fetch_memory_list (descriptors);

    print_header ();

    for (i = 0; i < numdescriptors; i ++)
        print_descriptor (descriptors + i);

    print_separator ();

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
    print_separator ();
}

/**********************************************************/

/**
 *  Prints the bottom border for the table of memory information.
 */
    PRIVATE void
print_separator (void)
{
    print_string ("==================================================="
      "====================\n");
}

/**********************************************************/

/** vim: set ts=4 sw=4 et : */
