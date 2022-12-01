global possible_seq

section .rodata
    TRIB:   dq 1, 1, 2, 4, 7                ; tribonacci sequence (without first 2 zeroes)

section .text

possible_seq:
    mov         eax, 1                      ; set up return value
    xor         ecx, ecx                    ; # of connected elements counter
    lea         rdx, [rdi + 4 * rsi - 4]    ; pointer to the last element
    lea         r8, [rel TRIB]
    jmp         .loop
.ncon:
    imul        rax, qword [r8 + 8 * rcx]
    xor         ecx, ecx
    add         rdi, 4
    cmp         rdi, rdx
    jae         .return
.loop:
    mov         esi, dword [rdi + 4]
    sub         esi, dword [rdi]
    cmp         esi, 1
    jne         .ncon
    inc         ecx
    add         rdi, 4
    cmp         rdi, rdx
    jb          .loop
.return:
    ret
