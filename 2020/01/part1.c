#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_LEN 200

int repair(const int * arr)
{
    for (int i = 0; i < INPUT_LEN; i++) {
        for (int j = 0; j < INPUT_LEN; j++) {
            if (arr[i] + arr[j] == 2020) {
                return arr[i] * arr[j];
            }
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[argc - 1], "r");
    if (!file) {
        return 1;
    }

    char buffer[8] = { 0 };
    int input[INPUT_LEN] = { 0 };
    for (int i = 0; i < 200; i++) {
        fgets(buffer, 8, file);
        input[i] = atoi(buffer);
    }

    fclose(file);

    printf("%i", repair(input));
}
