#include <stdio.h>

int plane_count(const char *filename)
{
    FILE *file = fopen(filename, "r");

    // Include space for newline and string terminator
    char buffer[32] = { 0 };

    int tot = 0;
    unsigned int current = 0;

    while (fgets(buffer, 32, file)) {
        if (buffer[0] == '\n') {
            tot += __builtin_popcount(current);
            current = 0;

            continue;
        }

        char *p = buffer;
        do {
            current |= 1 << (*p - 97);
        } while (*++p != '\n');
    }

    tot += __builtin_popcount(current);

    fclose(file);

    return tot;
}

int main(int argc, char *argv[])
{
    printf("%i\n", plane_count(argv[argc - 1]));
}
