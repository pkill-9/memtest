/**
 *  Bootsector that loads a second stage stored in sectors immediately
 *  following the bootsector.
 */

.code16
.section            .text

    .globl  _start
_start:
    cli
    xor     %ax, %ax
    mov     %ax, %ds
    mov     %ax, %es
    mov     %ax, %ss

# Stack will start before the bootsector in memory, and grow downwards,
# away from the bootsector.
    mov     $0x7BFF, %bp
    mov     %bp, %sp
    sti

# The first sector of the second stage is going to be immediately after
# the bootsector, so it is pretty safe to assume that sector=2, cylinder=0
# and head=0.
    mov     $0x00, %ch          # cylinder = 0
    mov     $0x00, %dh          # head = 0
    mov     $0x02, %cl          # sector = 2
    mov     $0x02, %ah          # ah=0x2, read sectors.
    mov     $0x7E00, %bx
    mov     NUMSECTORS, %al
    int     $0x13

    jmp     0x7E00


.section .params

/**
 *  Number of sectors to load. This value will be filled in by the program
 *  that copies memtest onto the disk image.
 */
NUMSECTORS:
.byte

/** vim: set ts=4 sw=4 et : */
