#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>

#define SEARCH_NAME "shiny gold"
#define MAX_NAMES 1024
#define MAX_SIZE 600
#define MAX_INNER_BAGS 4

struct Bag
{
    size_t inner_bags_size;
    char *inner_bags[MAX_INNER_BAGS];
    char *bag_color;
};

char *insert_name(char **names, size_t *names_size, char *new_name)
{
    long long low = 0, high = *names_size;
    while (low < high) {
        int m = low + (high - low) / 2;
        int c = strcmp(names[m], new_name);
        if (c == 0) {
            /* Name already exists,
                return pointer to the already existsing string and free the new one.
            */
            free(new_name);
            return names[m];
        }
        else if (c < 0) {
            low = m + 1;
        }
        else {
            high = m;
        }
    }

    for (long long i = *names_size - 1; i >= low; i--) {
        names[i + 1] = names[i];
    }

    (*names_size)++;
    return names[low] = new_name;
}

void insert_name2(char **names, size_t *names_size, char *new_name)
{
    long long low = 0, high = *names_size;
    while (low < high) {
        int m = low + (high - low) / 2;
        int c = strcmp(names[m], new_name);
        if (c == 0) {
            return;
        }
        else if (c < 0) {
            low = m + 1;
        }
        else {
            high = m;
        }
    }

    for (long long i = *names_size - 1; i >= low; i--) {
        names[i + 1] = names[i];
    }

    (*names_size)++;
    names[low] = new_name;
    return;
}

char *get_and_insert_name(char *bufstart, char *bufend, char **names, size_t *names_size)
{
    size_t bag_name_len = bufend - bufstart;
    char *new_name = malloc((bag_name_len + 1) * sizeof(char));
    memcpy(new_name, bufstart, bag_name_len);
    new_name[bag_name_len] = 0; // null terminate string
    return insert_name(names, names_size, new_name);
}

int bags_count(const char *filename)
{
    FILE *file = fopen(filename, "r");

    // Include space for newline and string terminator
    char buffer[128] = { 0 };

    struct Bag *bags = malloc(MAX_SIZE * sizeof(struct Bag));
    struct Bag *cur_bag = bags;
    char **names = malloc(MAX_NAMES * sizeof(char *));

    // Already add the name we're searching
    char *search_name = names[0] = SEARCH_NAME;
    size_t names_size = 1;

    while (fgets(buffer, 128, file)) {
        char *end_bag_name = strstr(buffer, " bags");
        if (!end_bag_name) {
            break;
        }

        char* new_name = get_and_insert_name(buffer, end_bag_name, names, &names_size);

        cur_bag++;
        cur_bag->bag_color = new_name;
        if (strncmp(end_bag_name, " bags contain no", 16) == 0) {
            cur_bag->inner_bags_size = 0;
            continue;
        }

        char *string_end = strchr(end_bag_name, '.');
        char *start_bag_name = end_bag_name + 16;
        while ((end_bag_name = strstr(start_bag_name, " bag"))) {
            new_name = get_and_insert_name(start_bag_name, end_bag_name, names, &names_size);
            cur_bag->inner_bags[cur_bag->inner_bags_size++] = new_name;
            start_bag_name = end_bag_name + (strncmp(end_bag_name, " bags", 5) ? 8 : 9);
            if (start_bag_name > string_end) {
                // We're outside the buffer, stop
                break;
            }
        }
    }

    fclose(file);

    char **outer_bags = malloc(MAX_SIZE * sizeof(char *));

    // Start search with SEARCH_NAME
    outer_bags[0] = search_name;
    size_t outer_bags_size = 1;

    size_t old_size = 0;
    while (old_size != outer_bags_size) {
        old_size = outer_bags_size;
        for (size_t i = 0; i < outer_bags_size; i++) {
            struct Bag *p = bags;
            while (p <= cur_bag) {
                for (size_t j = 0; j < p->inner_bags_size; j++) {
                    if (p->inner_bags[j] == outer_bags[i]) {
                        insert_name2(outer_bags, &outer_bags_size, p->bag_color);
                        break;
                    }
                }

                p++;
            }
        }
    }

    // Don't count SEARCH_NAME
    return outer_bags_size - 1;
}

int main(int argc, char *argv[])
{
    printf("%i\n", bags_count(argv[argc - 1]));
}
