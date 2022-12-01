#include <stdio.h>

#define COLUMNS 8
#define ROWS 128

int row(const char *seat)
{
    int end_res = 0;
    for (int i = 0; i < 7; i++) {
        if (seat[i] == 'B') {
            end_res |= 0x40 >> i;
        }
    }

    return end_res;
}

int column(const char *seat)
{
    int end_res = 0;
    for (int i = 7; i < 10; i++) {
        if (seat[i] == 'R') {
            end_res |= 0x200 >> i;
        }
    }

    return end_res;
}

#ifdef USE_ASM
int seat_id(const char *seat);
#else
int seat_id(const char *seat)
{
    int end_res = 0;
    int i = 0;
    for (; i < 7; i++) {
        if (seat[i] == 'B') {
            end_res |= 0x200 >> i;
        }
    }

    for (; i < 10; i++) {
        if (seat[i] == 'R') {
            end_res |= 0x200 >> i;
        }
    }

    return end_res;
}
#endif

int missing_seat_id(const char *filename)
{
    FILE *file = fopen(filename, "r");

    char table[COLUMNS * ROWS] = { 0 };

    // Include space for newline and string terminator
    char buffer[16] = { 0 };

    int min = __INT_MAX__;
    int max = 0;
    while (fgets(buffer, 16, file)) {
        int tmp = seat_id(buffer);
        if (tmp < min) {
            min = tmp;
        }
        else if (tmp > max) {
            max = tmp;
        }

        table[tmp] = 1;
    }

    for (int i = min + 1; i < max; i++) {
        if (table[i] == 0) {
            return i;
        }
    }

    fclose(file);

    return 0;
}

int main(int argc, char *argv[])
{
    printf("%i", missing_seat_id(argv[argc - 1]));
}
