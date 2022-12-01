#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_trees(int inc_right, int inc_down, const char *filename)
{
    FILE *file = fopen(filename, "r");

    // Include space for newline and string terminator
    char buffer[64] = { 0 };
    // Start is always safe
    fgets(buffer, 64, file);
    // strlen includes the newline
    int width = strchr(buffer, '\n') - buffer;

    int pos = inc_right;
    int hit = 0;
    for (int i = 1; fgets(buffer, 64, file); i++) {
        if (inc_down != 1 && i % inc_down != 0) {
            continue;
        }

        if (buffer[pos] == '#') {
            hit++;
        }

        pos = (pos + inc_right) % width;
    }

    fclose(file);

    return hit;
}

int main(int argc, char *argv[])
{
    char *arg = argv[argc - 1];
    long mul = (long)count_trees(1, 1, arg) * count_trees(3, 1, arg) * count_trees(5, 1, arg) * count_trees(7, 1, arg) * count_trees(1, 2, arg);
    printf("%li\n", mul);
}
