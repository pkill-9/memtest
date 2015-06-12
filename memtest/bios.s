/**
 *  Function that allows C programs to make use of BIOS services.
 */

.code16
.include "const.s"

.section .text

/**********************************************************/

/**
 *  bios_interrupt (struct cpu_registers *r, int code)
 *
 *  Raise BIOS interrupt code, with the values specified in the registers
 *  struct in the general purpose registers. Once the interrupt returns,
 *  values of the registers will be stored back into the struct for the
 *  caller to analyse.
 */
    .globl _bios_interrupt
_bios_interrupt:
    push    %ebp
    mov     %esp, %ebp
    pusha

# get the values for the general purpose registers from the struct.
    mov     12(%ebp), %eax
    mov     EBX(%eax), %ebx
    mov     ECX(%eax), %ecx
    mov     EDX(%eax), %edx
    mov     ES(%eax), %es
    mov     ESI(%eax), %esi
    mov     EDI(%eax), %edi
    mov     EAX(%eax), %eax

# test which interrupt we are to raise.
    cmp     $0x16, 8(%ebp)
    je      int_16
    cmp     $0x15, 8(%ebp)
    je      int_15
    cmp     $0x13, 8(%ebp)
    je      int_13
    cmp     $0x10, 8(%ebp)
    je      int_10
    jmp     error

# Interrupt 0x16, keyboard services, eg read next key press.
int_16:
    int     $0x16
    jmp     restore

# Interrupt 0x15, Misc, including fetching a detailed memory map.
int_15:
    int     $0x15
    jmp     restore

# Interrupt 0x13, Disk services. Read blocks, write blocks
int_13:
    int     $0x13
    jmp     restore

# Interrupt 0x10, Display services. Print characters, move cursor.
int_10:
    int     $0x10
    jmp     restore

error:
    mov     $-1, %eax

# fall through to restore.

restore:
    push    %eax
    mov     12(%ebp), %eax
    mov     %ebx, EBX(%eax)
    mov     %ecx, ECX(%eax)
    mov     %edx, EDX(%eax)
    mov     %esi, ESI(%eax)
    mov     %edi, EDI(%eax)
    mov     %es, ES(%eax)
    pushf
    pop     %ebx
    mov     %ebx, EFLAGS(%eax)
    popl    %ebx
    mov     %ebx, EAX(%eax)

    popa

    mov     %ebp, %esp
    popl    %ebp
    ret

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
