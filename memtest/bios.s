/**
 *  Function that allows C programs to make use of BIOS services.
 */

.code16
.include "const.s"

.section .text

/**********************************************************/

/**
 *  int fetch_memory_list (struct memory_region *list)
 *
 *  Gets all of the memory descriptors from int 0x15 eax=0xE820 and stores
 *  them in an array. Return value is the length of the array of
 *  descriptors.
 */
    .globl _fetch_memory_list
_fetch_memory_list:
    push    %ebp
    mov     %esp, %ebp
    subl    $4, %esp

    movl    8(%ebp), %edi
    xorl    %ebx, %ebx
    movl    $0x00, -4(%ebp)         # number of descriptors loaded.

loop:
    movl    $0x534D4150, %edx
    movl    $0xE820, %eax
    movl    $24, %ecx               # size of the structure.
    int     $0x15

# The carry flag should not be set, and eax should be set to the magic
# "SMAP" to indicate success. If this is not so, we will return whatever
# descriptors were successfully loaded.
    jc      error
    cmpl    $0x534D4150, %eax
    jne     error

# Increment edi to point to the next entry in the buffer of descriptors,
# and increment the count of the number of descriptors loaded.
    addl    $24, %edi
    movl    -4(%ebp), %edx
    incl    %edx
    movl    %edx, -4(%ebp)

# Test the continuation value in ebx. If the interrupt has cleared this
# register, it means that there are no more regions.
    cmpl    $0x00, %ebx
    jne     loop

error:
    movl    -4(%ebp), %eax          # return the number of descriptors.

    movl    %ebp, %esp
    pop     %ebp
    retl

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

# 4 byte saved ebp + 4 byte saved return address means char to be 
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
