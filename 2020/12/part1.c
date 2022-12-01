#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX_INPUT_WIDTH 128
#define MAX_INPUT_HEIGTH 128
#define MAX_INPUT MAX_INPUT_WIDTH * MAX_INPUT_HEIGTH

enum direction {
    North,
    East,
    South,
    West
};

int solve(const char *filename)
{
    FILE *file = fopen(filename, "r");

    // Include space for newline and string terminator
    char buffer[8] = { 0 };

    enum direction dir = East;
    int hor = 0;
    int ver = 0;
    while (fgets(buffer, 8, file)) {
        int n = atoi(buffer + 1);
        switch (buffer[0]) {
            case 'N':
                ver += n;
                break;
            case 'E':
                hor += n;
                break;
            case 'S':
                ver -= n;
                break;
            case 'W':
                hor -= n;
                break;
            case 'F':
                switch (dir) {
                    case North:
                        ver += n;
                        break;
                    case East:
                        hor += n;
                        break;
                    case South:
                        ver -= n;
                        break;
                    case West:
                        hor -= n;
                        break;
                }
                break;
            case 'R':
                dir = (enum direction)(((int)dir + (n / 90)) % 4);
                break;
            case 'L':
                dir = (enum direction)((abs(4 + ((int)dir - (n / 90))) % 4));
                break;
            default:
                break;
        }
    }

    fclose(file);

    return abs(ver) + abs(hor);
}

int main(int argc, char *argv[])
{
    printf("%i\n", solve(argv[argc - 1]));
}
