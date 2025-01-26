ssize_t getline(char **lineptr, size_t *n, FILE *stream)
{
    size_t pos;
    int c;

    if (lineptr == NULL || n == NULL || stream == NULL)
        return -1;

    if (*lineptr == NULL)
    {
        *n = 128; /* Default initial size */
        *lineptr = malloc(*n);
        if (*lineptr == NULL)
            return -1;
    }

    pos = 0;
    while ((c = fgetc(stream)) != EOF)
    {
        if (pos + 1 >= *n)
        {
            *n *= 2;
            *lineptr = realloc(*lineptr, *n);
            if (*lineptr == NULL)
                return -1;
        }
        (*lineptr)[pos++] = c;
        if (c == '\n')
            break;
    }

    if (pos == 0 && c == EOF)
        return -1;

    (*lineptr)[pos] = '\0';
    return pos;
}

#include "monty.h"

/**
 * main - Entry point for the Monty ByteCode interpreter.
 * @argc: Number of arguments.
 * @argv: Array of arguments.
 * Return: 0 on success.
 */
int main(int argc, char *argv[])
{
    FILE *file;
    char *line = NULL, *opcode, *arg;
    size_t len = 0;
    stack_t *stack = NULL;
    unsigned int line_number = 0;

    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");
    if (!file)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while (getline(&line, &len, file) != -1)
    {
        line_number++;
        opcode = strtok(line, " \t\n");
        if (!opcode || opcode[0] == '#') /* Skip comments and empty lines */
            continue;

        if (strcmp(opcode, "push") == 0)
        {
            arg = strtok(NULL, " \t\n");
            push(&stack, line_number, arg);
        }
        else if (strcmp(opcode, "pall") == 0)
        {
            pall(&stack, line_number);
        }
        else
        {
            fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
            free(line);
            free_stack(stack);
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }

    free(line);
    free_stack(stack);
    fclose(file);
    return (0);
}
