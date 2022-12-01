#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include "../utils.h"

#define MAX_INPUT_LEN 128

void insert_value_sorted(int *list, size_t *size, int value)
{
    long long low = 0, high = *size;
    while (low < high) {
        int m = low + (high - low) / 2;
        if (list[m] < value) {
            low = m + 1;
        }
        else if (list[m] > value) {
            high = m;
        }
        else {
            // Value already exists in the list
            return;
        }
    }

    for (long long i = *size - 1; i >= low; i--) {
        list[i + 1] = list[i];
    }

    (*size)++;
    list[low] = value;
}

#ifdef USE_ASM
uint64_t possible_seq(const int *input, size_t input_size);
#else
uint64_t possible_seq(const int *input, size_t input_size)
{
    // Use char to optimize for size
    const static char TRIB[] = { 1, 1, 2, 4, 7 };
    int con = 0;
    uint64_t res = 1;
    const int *prev = input;
    const int *cur = input + 1;
    do {
        if (likely(*cur - *prev == 1)) {
            con++;
        }
        else {
            res *= TRIB[con];
            con = 0;
        }
    } while (++prev && ++cur < input + input_size);

    return res;
}
#endif

uint64_t solve(const char *filename)
{
    FILE *file = fopen(filename, "r");

    // Include space for newline and string terminator
    char buffer[16] = { 0 };

    int input[MAX_INPUT_LEN] = { 0 };
    size_t input_size = 1; // 0 is our start value

    while (fgets(buffer, 16, file)) {
        insert_value_sorted(input, &input_size, atoi(buffer));
    }

    // Add our device's built-in joltage adapter
    input[input_size] = input[input_size - 1] + 3;
    input_size++;

    fclose(file);

    return possible_seq(input, input_size);
}

int main(int argc, char *argv[])
{
    printf("%lu\n", solve(argv[argc - 1]));
}
