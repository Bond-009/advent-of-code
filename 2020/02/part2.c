#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_valid_password(char *pass, char *policy)
{
    int pos1 = atoi(policy) - 1;
    char *minP = strchr(policy, '-');
    int pos2 = atoi(++minP) - 1;
    char c = *(strchr(minP, ' ') + 1);

    return (pass[pos1] == c) != (pass[pos2] == c);
}

int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[argc - 1], "r");
    if (!file) {
        return 1;
    }

    char buffer[128] = { 0 };
    int valid = 0;
    while (fgets(buffer, 128, file)) {
        if (is_valid_password(strchr(buffer, ':') + 2, buffer)) {
            valid++;
        }
    }

    fclose(file);

    printf("%i", valid);
}
