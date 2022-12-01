#include <stdio.h>

#define COLUMNS 8
#define ROWS 128

int seat_id(const char *seat)
{
    int row = 0;
    int row_lower = 0;
    int row_upper = ROWS - 1;
    int column = 0;
    int column_lower = 0;
    int column_upper = COLUMNS - 1;
    int i = 0;
    for (; i < 6; i++) {
        switch (seat[i]) {
            case 'F':
                row_upper -= (row_upper - row_lower + 1) / 2;
                break;
            case 'B':
                row_lower += (row_upper - row_lower + 1) / 2;
                break;
        }
    }

    switch (seat[i++]) {
        case 'F':
            row = row_lower;
            break;
        case 'B':
            row = row_upper;
            break;
    }

    for (; i < 9; i++) {
        switch (seat[i]) {
            case 'L':
                column_upper -= (column_upper - column_lower + 1) / 2;
                break;
            case 'R':
                column_lower += (column_upper - column_lower + 1) / 2;
                break;
        }
    }

    switch (seat[i++]) {
        case 'L':
            column = column_lower;
            break;
        case 'R':
            column = column_upper;
            break;
    }

    return row * COLUMNS + column;
}

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

    fclose(file);

    for (int i = min + 1; i < max; i++) {
        if (table[i] == 0) {
            return i;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    printf("%i", missing_seat_id(argv[argc - 1]));
}
