#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include "../utils.h"

int solve(const char *filename)
{
    FILE *file = fopen(filename, "r");

    // Include space for newline and string terminator
    char buffer[8] = { 0 };

    int w_x = 10;
    int w_y = 1;
    int y = 0;
    int x = 0;
    while (fgets(buffer, 8, file)) {
        int n = atoi(buffer + 1);
        switch (buffer[0]) {
            case 'N':
                w_y += n;
                break;
            case 'E':
                w_x += n;
                break;
            case 'S':
                w_y -= n;
                break;
            case 'W':
                w_x -= n;
                break;
            case 'F':
                for (int i = 0; i < n; i++) {
                    x += w_y;
                    y += w_x;
                }
                break;
            case 'R':
                for (int i = 0; i < n / 90; i++) {
                    SWAP(w_y, w_x);
                    w_y = -w_y;
                }
                break;
            case 'L':
                for (int i = 0; i < n / 90; i++) {
                    SWAP(w_y, w_x);
                    w_x = -w_x;
                }
                break;
            default:
                break;
        }
    }

    fclose(file);

    return abs(x) + abs(y);
}

int main(int argc, char *argv[])
{
    printf("%i\n", solve(argv[argc - 1]));
}
