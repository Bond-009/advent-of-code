#include <stdio.h>

int plane_count(const char *filename)
{
    FILE *file = fopen(filename, "r");

    // Include space for newline and string terminator
    char buffer[32] = { 0 };

    int tot = 0;
    unsigned int current = 0xffffffff;

    while (fgets(buffer, 32, file)) {
        if (buffer[0] == '\n') {
            if (current != 0xffffffff) {
                tot += __builtin_popcount(current);
                current = 0xffffffff;
            }

            continue;
        }

        unsigned int tmp = 0;
        char *p = buffer;
        do {
            tmp |= 1 << (*p - 97);
        } while (*++p != '\n');

        current &= tmp;
    }

    fclose(file);

    if (current != 0xffffffff) {
        tot += __builtin_popcount(current);
    }

    return tot;
}

int main(int argc, char *argv[])
{
    printf("%i\n", plane_count(argv[argc - 1]));
}
