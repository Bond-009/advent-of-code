global repair_avx_inner

section .text

repair_avx_inner:
%assign i 0
%rep    25
    vpcmpeqd        ymm1, ymm0, [rdi + i]
;    vptest          ymm1, ymm1              ; slower then vpmovmskb + test
    vpmovmskb       eax, ymm1
    test            eax, eax
    jne             .found
%assign i i+32
%endrep
    xor             eax, eax                ; not found, return 0
    vzeroupper                              ; eliminate performance penalties caused by false dependencies when transitioning between AVX and legacy SSE instructions
    ret
.found:
    vzeroupper                              ; eliminate performance penalties caused by false dependencies when transitioning between AVX and legacy SSE instructions
    movd            eax, xmm0               ; smaller then putting a vmovd before the vzeroupper and no measurable performance difference
    ret
