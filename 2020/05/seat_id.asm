global seat_id

section .text

seat_id:
    xor         eax, eax            ; set up return value
    cmp         BYTE [rdi], 'B'
    sete        al
    xor         ecx, ecx
%assign i 1
%rep    6
    shl         eax, 1
    cmp         BYTE [rdi + i], 'B'
    sete        cl
    or          eax, ecx
%assign i i+1
%endrep
%rep    3
    shl         eax, 1
    cmp         BYTE [rdi + i], 'R'
    sete        cl
    or          eax, ecx
%assign i i+1
%endrep
    ret
