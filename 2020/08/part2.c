#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define INPUT_LEN 650

struct Operation
{
    char opcode;
    int arg;
    char has_been_executed;
};

int execute(struct Operation *ops, size_t opcount)
{
    struct Operation *cur_op = ops;
    int acc = 0;
    do {
        if (cur_op->has_been_executed) {
            return -1;
        }

        cur_op->has_been_executed = 1;
        switch (cur_op->opcode)
        {
            case 0:
                cur_op++;
                break;
            case 1:
                acc += cur_op->arg;
                cur_op++;
                break;
            case 2:
                cur_op += cur_op->arg;
                break;
        }
    } while (cur_op < ops + opcount);

    return acc;
}

int exe_program(const char *filename)
{
    FILE *file = fopen(filename, "r");

    // Include space for newline and string terminator
    char buffer[16] = { 0 };

    struct Operation ops[INPUT_LEN];
    size_t opcount = 0;

    while (fgets(buffer, 16, file)) {
        struct Operation *op = &ops[opcount++];
        op->has_been_executed = 0;
        switch (buffer[0])
        {
            // nop
            case 'n':
                op->opcode = 0;
                break;
            // acc
            case 'a':
                op->opcode = 1;
                break;
            // jmp
            case 'j':
                op->opcode = 2;
                break;
        }

        op->arg = atoi(&buffer[4]);
    }

    fclose(file);

    struct Operation *cur_op = ops;
    int flip_previous = 0;
    do {
        if (flip_previous) {
            (cur_op - 1)->opcode ^= 2;
            flip_previous = 0;
        }

        if (cur_op->opcode == 1
            || (cur_op->opcode == 0 && cur_op->arg <= 0)
            || (cur_op->opcode == 2 && cur_op->arg >= 0)) {
            continue;
        }

        cur_op->opcode ^= 2;
        flip_previous = 1;

        for (size_t i = 0; i < opcount; i++) {
            ops[i].has_been_executed = 0;
        }

        int acc = execute(ops, opcount);
        if (acc != -1) {
            return acc;
        }
    } while (++cur_op < ops + opcount);

    return -1;
}

int main(int argc, char *argv[])
{
    printf("%i\n", exe_program(argv[argc - 1]));
}
