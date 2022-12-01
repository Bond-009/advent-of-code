#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <immintrin.h>

#define INPUT_LEN 200
#define SEARCH 2020

#ifdef USE_ASM
int repair_avx_inner(const int *arr, __m256i search);
#else
int repair_avx_inner(const int *arr, __m256i search)
{
    for (int k = 0; k < INPUT_LEN; k += 8) {
        __m256i new = _mm256_loadu_si256((__m256i *)(&arr[k]));
        if (_mm256_movemask_epi8(_mm256_cmpeq_epi32(new, search))) {
            return _mm256_extract_epi32(search, 0);
        }
    }

    return 0;
}
#endif

int repair_avx(const int *arr)
{
    __m256i search = _mm256_set1_epi32(SEARCH);
    for (int i = 0; i < INPUT_LEN; i++) {
        __m256i start = _mm256_set1_epi32(arr[i]);
        for (int j = 0; j < INPUT_LEN; j += 8) {
            __m256i new = _mm256_loadu_si256((__m256i *)(&arr[j]));
            new = _mm256_add_epi32(start, new);
            unsigned int mask = (unsigned int)_mm256_movemask_epi8(_mm256_cmpgt_epi32(new, search));
            if (mask == 0xffffffff) {
                continue;
            }

            switch (__lzcnt32(mask) / 4) {
                case 0:
                    {
                        __m256i cmp = _mm256_sub_epi32(search, _mm256_permutevar8x32_epi32(new, _mm256_set1_epi32(7)));
                        int tmp = repair_avx_inner(arr, cmp);
                        if (tmp) {
                            return tmp * arr[i] * arr[j + 7];
                        }
                    }
                case 1:
                    if ((mask & 0x0f000000) == 0) {
                        __m256i cmp = _mm256_sub_epi32(search, _mm256_permutevar8x32_epi32(new, _mm256_set1_epi32(6)));
                        int tmp = repair_avx_inner(arr, cmp);
                        if (tmp) {
                            return tmp * arr[i] * arr[j + 6];
                        }
                    }
                case 2:
                    if ((mask & 0x00f00000) == 0 ){
                        __m256i cmp = _mm256_sub_epi32(search, _mm256_permutevar8x32_epi32(new, _mm256_set1_epi32(5)));
                        int tmp = repair_avx_inner(arr, cmp);
                        if (tmp) {
                            return tmp * arr[i] * arr[j + 5];
                        }
                    }
                case 3:
                    if ((mask & 0x000f0000) == 0) {
                        __m256i cmp = _mm256_sub_epi32(search, _mm256_permutevar8x32_epi32(new, _mm256_set1_epi32(4)));
                        int tmp = repair_avx_inner(arr, cmp);
                        if (tmp) {
                            return tmp * arr[i] * arr[j + 4];
                        }
                    }
                case 4:
                    if ((mask & 0x0000f000) == 0) {
                        __m256i cmp = _mm256_sub_epi32(search, _mm256_permutevar8x32_epi32(new, _mm256_set1_epi32(3)));
                        int tmp = repair_avx_inner(arr, cmp);
                        if (tmp) {
                            return tmp * arr[i] * arr[j + 3];
                        }
                    }
                case 5:
                    if ((mask & 0x00000f00) == 0) {
                        __m256i cmp = _mm256_sub_epi32(search, _mm256_permutevar8x32_epi32(new, _mm256_set1_epi32(2)));
                        int tmp = repair_avx_inner(arr, cmp);
                        if (tmp) {
                            return tmp * arr[i] * arr[j + 2];
                        }
                    }
                case 6:
                    if ((mask & 0x000000f0) == 0) {
                        __m256i cmp = _mm256_sub_epi32(search, _mm256_permutevar8x32_epi32(new, _mm256_set1_epi32(1)));
                        int tmp = repair_avx_inner(arr, cmp);
                        if (tmp) {
                            return tmp * arr[i] * arr[j + 1];
                        }
                    }
                case 7:
                    if ((mask & 0x0000000f) == 0) {
                        __m256i cmp = _mm256_sub_epi32(search, _mm256_permutevar8x32_epi32(new, _mm256_setzero_si256()));
                        int tmp = repair_avx_inner(arr, cmp);
                        if (tmp) {
                            return tmp * arr[i] * arr[j];
                        }
                    }
            }
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[argc - 1], "r");
    if (!file) {
        return 1;
    }

    char buffer[8] = { 0 };
    int input[INPUT_LEN] = { 0 };
    for (int i = 0; i < 200; i++) {
        fgets(buffer, 8, file);
        input[i] = atoi(buffer);
    }

    fclose(file);

    printf("%i\n", repair_avx(input));
}
