#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "monty.h"

#define MAX_LINE_LENGTH 256

/**
 * main - Entry point of the Monty ByteCode interpreter
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int main(int argc, char *argv[])
{
    FILE *file;
    char line[MAX_LINE_LENGTH];
    stack_t *stack = NULL;
    unsigned int line_number = 1;

    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), file))
    {
        char *opcode = strtok(line, " \n\t");
        if (opcode == NULL)
        {
            line_number++;
            continue;  // Skip empty lines
        }

        if (strcmp(opcode, "push") == 0)
        {
            char *arg = strtok(NULL, " \n\t");
            if (arg == NULL || atoi(arg) == 0 && strcmp(arg, "0") != 0)
            {
                fprintf(stderr, "L%u: usage: push integer\n", line_number);
                fclose(file);
                exit(EXIT_FAILURE);
            }
            int value = atoi(arg);
            push(&stack, line_number, value);
        }
        else if (strcmp(opcode, "pall") == 0)
        {
            pall(&stack);
        }
        else if (strcmp(opcode, "pint") == 0)
        {
            pint(&stack, line_number);
        }
        else
        {
            fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
            fclose(file);
            exit(EXIT_FAILURE);
        }
        line_number++;
    }

    fclose(file);
    return (EXIT_SUCCESS);
}
