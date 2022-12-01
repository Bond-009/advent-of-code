global atoi, write_ulong

%include "unistd.asm"

section .text
atoi:
    mov     ecx, 10
    xor     eax, eax
.loop:
    movzx   r8d, byte [rdi]
    xor     r8d, '0'
    cmp     r8d, ecx                ; minor optimization, comparing with a register generates smaller machine code then comparing with an immediate
    jnl     .return
    xor     edx, edx
    mul     rcx
    add     eax, r8d
    inc     rdi                     ; Move ptr to next character
    jmp     .loop
.return:
    ret

write_ulong:
    push    rdi                     ; Push fd onto stack
    mov     rax, rsi
    lea     rcx, [rsp - 1]
    mov     byte [rcx], 0
    mov     rsi, rcx
    mov     edi, 10                 ; Divisor
.loop:
    xor     edx, edx
    div     rdi
    xor     edx, '0'
    dec     rsi
    mov     byte [rsi], dl
    test    rax, rax
    jnz     .loop

    mov     rax, SYS_write
    pop     rdi                     ; Pop fd from stack
    mov     rdx, rcx
    sub     rdx, rsi
    syscall
    ret
