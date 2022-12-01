#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256
#define MAX_INPUT_LEN 128

int solve(const char *filename)
{
    FILE *file = fopen(filename, "r");

    char buffer[BUFFER_SIZE] = { 0 };
    fgets(buffer, BUFFER_SIZE, file);
    int depart = atoi(buffer);
    fgets(buffer, BUFFER_SIZE, file);
    int bus_ids[MAX_INPUT_LEN] = { 0 };
    bus_ids[0] = atoi(buffer);
    int i = 1;
    char *p = buffer;
    while ((p = strchr(p, ','))) {
        // x is never the last value, just keep looping we find a valid input
        while (*++p == 'x') {
            p += 1;
        }

        bus_ids[i++] = atoi(p);
    }

    int bus_id = 0;
    int wait = INT32_MAX;
    for (int j = 0; j < i; j++) {
        int id = bus_ids[j];
        int tmprem = id - (depart % id);
        if (tmprem < wait) {
            bus_id = id;
            wait = tmprem;
        }
    }

    fclose(file);
    return bus_id * wait;
}

int main(int argc, char *argv[])
{
    printf("%i\n", solve(argv[argc - 1]));
}
