#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define INPUT_LEN 1000
#define SEARCH_LEN 25

uint64_t min_uint64(const uint64_t *start, const uint64_t *stop)
{
    uint64_t min = *start;
    while (++start <= stop) {
        if (*start < min) {
            min = *start;
        }
    }

    return min;
}

uint64_t max_uint64(const uint64_t *start, const uint64_t *stop)
{
    uint64_t max = *start;
    while (++start <= stop) {
        if (*start > max) {
            max = *start;
        }
    }

    return max;
}

bool has_sum(uint64_t *cur_num)
{
    uint64_t search = *cur_num;
    uint64_t *p1 = cur_num - SEARCH_LEN;
    do {
        if (*p1 >= search)
        {
            continue;
        }

        uint64_t *p2 = cur_num - SEARCH_LEN;
        do {
            if (*p1 + *p2 == search) {
                return true;
            }
        } while (++p2 < cur_num);
    } while (++p1 < cur_num);

    return false;
}

int exe_program(const char *filename)
{
    FILE *file = fopen(filename, "r");

    // Include space for newline and string terminator
    char buffer[24] = { 0 };

    uint64_t nums[INPUT_LEN] = { 0 };
    size_t num_size = 0;

    while (fgets(buffer, 24, file)) {
        nums[num_size++] = strtoull(buffer, NULL, 10);
    }

    fclose(file);

    uint64_t *cur_num = nums + SEARCH_LEN;
    uint64_t search = -1;
    do {
        if (!has_sum(cur_num)) {
            search = *cur_num;
            break;
        }
    } while (++cur_num < nums + num_size);

    cur_num = nums;
    do {
        uint64_t sum = 0;
        uint64_t *p1 = cur_num;
        do {
            sum += *p1;
        } while (++p1 < nums + num_size && sum < search);

        if (sum == search) {
            return min_uint64(cur_num, p1) + max_uint64(cur_num, p1);
        }
    } while (++cur_num < nums + num_size);

    return -1;
}

int main(int argc, char *argv[])
{
    printf("%i\n", exe_program(argv[argc - 1]));
}
