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

    pushl   NUMSECTORS
    call    _cboot

/**
 *  void get_drive_parameters (uint16_t *cx, uint8_t *dh)
 *
 *  Queries the BIOS for drive parameters. After the interrupt, the cx
 *  register contains the number of cylinders and sectors and dh has the
 *  number of heads. It is left to the caller to unpack these values.
 */
    .globl  _get_drive_parameters
_get_drive_parameters:
    push    %ebp
    mov     %esp, %ebp

    mov     $0x08, %ah
    mov     $0x80, %dl
    int     $0x13

    mov     8(%ebp), %ebx
    mov     %dh, (%bx)
    mov     12(%ebp), %ebx
    mov     %cx, (%bx)

    pop     %ebp
    ret

/**
 *  void read_sectors (uint16_t cx, uint16_t dx, void *buffer)
 *
 *  Read a sector from the disk into memory. cx is the value to be put
 *  in the cx register for the interrupt, and should be the cylinder and
 *  sector index. The dx register should have the head number.
 */
    .globl  _read_sectors
read_sectors:
    push    %ebp
    mov     %esp, %ebp

    mov     8(%ebp), %ebx
    mov     12(%ebp), %dx
    mov     14(%ebp), %cx
    mov     $0x0201, %ax
    int     $0x13

    pop     %ebp
    ret

/** vim: set ts=4 sw=4 et : */
