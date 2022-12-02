%include "unistd.asm"
%include "utils.asm"

stdout equ 1

global _start

section .rodata
    JMP_TABLE:   dq  _start.lose, _start.draw, _start.win

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

    xor     r8d, r8d              ; score
.loop:
    cmp     byte [rax], 0
    je      .exit
    mov     ecx, [rax]
    add     rax, 4
    mov     edx, ecx
    and     ecx, 0xff
    shr     edx, 2 * 8
    and     edx, 0xff
    sub     ecx, 'A' - 1
    lea     rdi, [JMP_TABLE]
    jmp     [rdi + rdx * 8 - 'X' * 8]

.lose:
%rep    2
    inc     ecx
    mov     edi, ecx
    shr     edi, 2
    or      ecx, edi
    and     ecx, 0b11
%endrep
    add     r8d, ecx

    jmp     .loop

.win:
    inc     ecx
    mov     edi, ecx
    shr     edi, 2
    or      ecx, edi
    and     ecx, 0b11

    add     r8d, 6
    add     r8d, ecx

    jmp     .loop

.draw:
    add     r8d, ecx
    add     r8d, 3
    jmp     .loop

.exit:
    mov     edi, stdout
    mov     esi, r8d
    call    write_ulong

    mov     rax, SYS_exit
    xor     edi, edi
    syscall

.exit_err:
    mov     rax, SYS_exit
    mov     edi, 1
    syscall
