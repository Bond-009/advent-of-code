#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX_INPUT_WIDTH 128
#define MAX_INPUT_HEIGTH 128
#define MAX_INPUT MAX_INPUT_WIDTH * MAX_INPUT_HEIGTH

int count_char(const char *source, char search)
{
    int oc = 0;
    do {
        oc += *source == search;
    } while (*++source);

    return oc;
}

void replace_char(char *destination, const char *source, char original, char replace)
{
    do {
        if (*source == original) {
            *destination = replace;
        }
        else {
            *destination = *source;
        }
    } while (++destination && *++source);
    *destination = 0;
}

char get_char(const char *source, size_t width, size_t y, size_t x) {
    return source[y * width + x];
}

int sur_oc_seats(const char *source, size_t width, size_t height, size_t index_y, size_t index_x)
{
    int num = 0;
    // Check upwards
    size_t y = index_y;
    size_t x = index_x;
    while (--y < height) {
        char c = get_char(source, width, y, x);
        if (c == '.') {
            continue;
        }

        num += c == '#';
        break;
    }

    // Check downwards
    y = index_y;
    while (++y < height) {
        char c = get_char(source, width, y, x);
        if (c == '.') {
            continue;
        }

        num += c == '#';
        break;
    }

    // Check left
    y = index_y;
    x = index_x;
    while (--x < width) {
        char c = get_char(source, width, y, x);
        if (c == '.') {
            continue;
        }

        num += c == '#';
        break;
    }

    // Check right
    x = index_x;
    while (++x < width) {
        char c = get_char(source, width, y, x);
        if (c == '.') {
            continue;
        }

        num += c == '#';
        break;
    }

    // Check left upwards
    y = index_y;
    x = index_x;
    while (--y < height && --x < width) {
        char c = get_char(source, width, y, x);
        if (c == '.') {
            continue;
        }

        num += c == '#';
        break;
    }

    // Check left downwards
    y = index_y;
    x = index_x;
    while (++y < height && --x < width) {
        char c = get_char(source, width, y, x);
        if (c == '.') {
            continue;
        }

        num += c == '#';
        break;
    }

    // Check right upwards
    y = index_y;
    x = index_x;
    while (--y < height && ++x < width) {
        char c = get_char(source, width, y, x);
        if (c == '.') {
            continue;
        }

        num += c == '#';
        break;
    }

    // Check right downwards
    y = index_y;
    x = index_x;
    while (++y < height && ++x < width ) {
        char c = get_char(source, width, y, x);
        if (c == '.') {
            continue;
        }

        num += c == '#';
        break;
    }

    return num;
}

int solve(const char *filename)
{
    FILE *file = fopen(filename, "r");

    // Include space for newline and string terminator
    char buffer[128] = { 0 };

    char input[MAX_INPUT] = { 0 };
    size_t height = 1;
    fgets(buffer, 128, file);
    size_t width = strchr(buffer, '\n') - buffer;
    replace_char(input, buffer, 'L', '#');

    while (fgets(buffer, 128, file)) {
        // Round 1
        replace_char(&input[height++ * width], buffer, 'L', '#');
    }

    fclose(file);

    size_t size = height * width;

    // Zero terminate
    input[size] = 0;

    char input2[MAX_INPUT] = { 0 };
    do {
        for (size_t i = 0; i < size; i++) {
            if (input[i] == '.') {
                input2[i] = '.';
            }
            else if (input[i] == 'L') {
                if (sur_oc_seats(input, width, height, i / width, i % width) == 0) {
                    input2[i] = '#';
                }
                else {
                    input2[i] = 'L';
                }
            }
            else if (input[i] == '#') {
                if (sur_oc_seats(input, width, height, i / width, i % width) >= 5) {
                    input2[i] = 'L';
                }
                else {
                    input2[i] = '#';
                }
            }
        }
    } while (memcmp(input, input2, size) && memcpy(input, input2, size));

    return count_char(input, '#');
}

int main(int argc, char *argv[])
{
    printf("%i\n", solve(argv[argc - 1]));
}
