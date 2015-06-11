/**
 *  Functions for printing data on the screen via BIOS interrupts.
 *
 *  Since our code is a bootsector, there is no cushy C library printf
 *  for printing to the screen. Fortunately, the BIOS provides some
 *  abstraction for putting a character on the screen, so we don't have to
 *  go stuffing around with video memory, but we do need to handle 
 *  printing both strings and ints.
 */

#include "output.h"
#include "types.h"
#include "bios.h"
#include "utils.h"

/**********************************************************/

PRIVATE void bios_putchar (char c);

/**********************************************************/

/**
 *  Function for printing a 32 bit integer in hexadecimal form. This 
 *  function will also print the leading 0x prefix.
 */
    PUBLIC void
print_int_hex (value)
    uint32_t value;             // value to be printed.
{
    const char *alphabet = "0123456789ABCDEF";
    uint32_t mask;
    int nibble_index = 32 - 4;
    int nibble;

    print_string ("0x");

    for (mask = 0xF0000000; mask != 0; mask >>= 4)
    {
        // mask out the next 4 bit part of the int, starting with the
        // most significant part.
        nibble = (value & mask) >> nibble_index;
        bios_putchar (alphabet [nibble]);

        nibble_index -= 4;
    }
}

/**********************************************************/

/**
 *  Prints a string. This is pretty standard, although probably could be
 *  optimised in assembly language.
 */
    PUBLIC void
print_string (string)
    const char *string;         // string to be printed.
{
    while (*string != '\0')
        bios_putchar (*string ++);
}

/**********************************************************/

/**
 *  Invoke the BIOS to print a single character on the screen.
 */
    PRIVATE void
bios_putchar (c)
    char c;             // character to be printed.
{
    struct cpu_registers registers;

    // turn any newline char into a carriage return line feed pair.
    if (c == '\n')
        bios_putchar ('\r');

    // print a character using BIOS interrupt 0x10. To do this, the ax
    // register must contain the opcode 0x0E in the high byte, and the
    // character to print in the low byte. bx register contains either
    // the attribute (colour) or page number in text mode.
    registers.eax = (0x0E << 8) | (c & 0x00FF);
    registers.ebx = 0;

    bios_interrupt (&registers, 0x10);
}

/**********************************************************/

/** vim: set ts=4 sw=4 et : */
