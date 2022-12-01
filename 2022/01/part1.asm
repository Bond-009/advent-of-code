%include "unistd.asm"
%include "utils.asm"

stdout equ 1

global _start

section .text
_start:
    mov     rcx, [rsp]              ; Get number of arguments
    mov     rdi, [rsp + rcx * 8]    ; Get last argument

    mov     rax, SYS_access         ; Check if file exists and is readable
    mov     esi, R_OK
    syscall
    test    rax, rax
    jnz     .exit_err

    mov     rax, SYS_open
    xor     esi, esi
    xor     edx, edx
    syscall

    mov     r8d, eax                ; Move fd into r8
    mov     rax, SYS_mmap
    xor     edi, edi                ; Let the kernel choose the address
    mov     rsi, 12288
    mov     rdx, PROT_READ
    mov     r10d, MAP_PRIVATE
    xor     r9d, r9d
    syscall

    cmp     rax, -1                 ; Exit on error
    je      .exit_err

    xor     r12d, r12d              ; current count for elf
    xor     r13d, r13d              ; Max # cal for one elf
    mov     rdi, rax
.loop:
    cmp     byte [rdi], 0
    je      .exit
    call    atoi
    add     r12d, eax
    cmp     byte [rdi], 0
    inc     rdi
    je      .exit
    cmp     byte [rdi], `\n`
    je      .next_elf
    jmp     .loop

.next_elf:
    cmp     r13d, r12d
    cmovl   r13d, r12d
    xor     r12d, r12d
    add     rdi, 1
    jmp     .loop

.exit:
    mov     edi, stdout
    mov     esi, r13d
    call    write_ulong

    mov     rax, SYS_exit
    xor     edi, edi
    syscall

.exit_err:
    mov     rax, SYS_exit
    mov     edi, 1
    syscall
