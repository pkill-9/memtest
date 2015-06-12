/**
 *  Function that allows C programs to make use of BIOS services.
 */

.code16
.include "const.s"

.section .text

/**********************************************************/

/**
 *  void bios_putchar (uint8_t ch)
 *
 *  print the given 8 bit ASCII character on the screen.
 */
    .globl _bios_putchar
_bios_putchar:
    push    %ebp
    mov     %esp, %ebp

# 4 byte saved ebp + 4 byte saved return address(?) means char to be 
# printed should be at offset 8 from ebp.
    mov     8(%ebp), %al
    mov     $0x0E, %ah
    int     $0x10

    pop     %ebp
    retl

/**********************************************************/

/**
 *  void idle (void)
 *
 *  put the CPU in a low power state once the memtest program has 
 *  finished. This also avoids the CPU going into junk memory after the
 *  end of the main function.
 *
 *  This function will never return.
 */
    .globl _idle
_idle:
    cli
    hlt
    jmp     _idle           # just in case.

/**********************************************************/

# vim: ts=4 sw=4 et
