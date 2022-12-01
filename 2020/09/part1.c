#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define INPUT_LEN 1000
#define SEARCH_LEN 25

bool has_sum(uint64_t *cur_num)
{
    uint64_t search = *cur_num;
    uint64_t *p1 = cur_num - SEARCH_LEN;
    do {
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

    uint64_t nums[INPUT_LEN];
    size_t num_size = 0;

    while (fgets(buffer, 24, file)) {
        nums[num_size++] = strtoull(buffer, NULL, 10);
    }

    fclose(file);

    uint64_t *cur_num = nums + SEARCH_LEN;
    do {
        if (!has_sum(cur_num)) {
            return *cur_num;
        }
    } while (++cur_num < nums + num_size);

    return -1;
}

int main(int argc, char *argv[])
{
    printf("%i\n", exe_program(argv[argc - 1]));
}
