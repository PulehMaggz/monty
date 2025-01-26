#include "monty.h"

/**
 * push - Pushes an integer onto the stack.
 * @stack: Double pointer to the head of the stack.
 * @line_number: Line number in the file.
 * @arg: The argument to push onto the stack.
 */
void push(stack_t **stack, unsigned int line_number, char *arg)
{
    stack_t *new_node;
    int value;

    if (!arg || (value = atoi(arg)) == 0 && strcmp(arg, "0") != 0)
    {
        fprintf(stderr, "L%u: usage: push integer\n", line_number);
        exit(EXIT_FAILURE);
    }

    new_node = malloc(sizeof(stack_t));
    if (!new_node)
    {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    new_node->n = value;
    new_node->prev = NULL;
    new_node->next = *stack;

    if (*stack)
        (*stack)->prev = new_node;
    *stack = new_node;
}
