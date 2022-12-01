#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

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

int solve(const char *filename)
{
    FILE *file = fopen(filename, "r");

    // Include space for newline and string terminator
    char buffer[128] = { 0 };

    int input[MAX_INPUT_LEN] = { 0 };
    size_t input_size = 1; // 0 is our start value

    while (fgets(buffer, 128, file)) {
        insert_value_sorted(input, &input_size, atoi(buffer));
    }

    fclose(file);

    int diff1 = 0;
    int diff3 = 1; // Diff with adapter

    for (size_t i = 1; i < input_size; i++)
    {
        int diff = input[i] - input[i - 1];
        if (diff == 1) {
            diff1++;
        }
        else if (diff == 3) {
            diff3++;
        }
    }

    return diff1 * diff3;
}

int main(int argc, char *argv[])
{
    printf("%i\n", solve(argv[argc - 1]));
}
