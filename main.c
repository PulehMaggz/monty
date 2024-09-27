#include "monty.h"

/**
 * main - Entry point for the Monty interpreter
 * @argc: Argument count
 * @argv: Argument vector
 *
 * Return: Always 0 on success
 */
int main(int argc, char **argv)
{
    FILE *file;
    char *line = NULL;
    size_t len = 0; /* Set initial length to 0 for fgets */
    unsigned int line_number = 0;
    stack_t *stack = NULL; /* Initialize the stack */
    char *opcode;
    char *arg;
    int value; /* Declare value here */

    /* Check for correct usage */
    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }

    /* Open the Monty bytecode file */
    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    /* Read the file line by line using fgets */
    while (fgets(line, len, file) != NULL)
    {
        line_number++;
        opcode = strtok(line, " \n\t");
        if (opcode == NULL || opcode[0] == '#') /* Skip empty lines and comments */
            continue;

        if (strcmp(opcode, "push") == 0)
        {
            arg = strtok(NULL, " \n\t");
            if (arg == NULL || !atoi(arg))
            {
                fprintf(stderr, "L%u: usage: push integer\n", line_number);
                free(line);
                fclose(file);
                exit(EXIT_FAILURE);
            }
            value = atoi(arg); /* Convert string argument to integer */
            push(&stack, line_number, value); /* Call push function */
        }
        else if (strcmp(opcode, "pall") == 0)
        {
            pall(&stack); /* Call pall function */
        }
        else
        {
            fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
            free(line);
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }

    /* Clean up */
    free(line);
    fclose(file);
    /* Free the stack (to be implemented) */
    return 0;
}
