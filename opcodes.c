#include "monty.h"

/**
 * push - Pushes an integer onto the stack
 * @stack: Double pointer to the stack
 * @line_number: The current line number in the bytecode file (for error messages)
 * @value: The integer value to push onto the stack
 */
void push(stack_t **stack, unsigned int line_number, int value)
{
    stack_t *new_node = malloc(sizeof(stack_t));
    if (new_node == NULL)
    {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->n = value;
    new_node->next = *stack; /* Point to the current top */
    new_node->prev = NULL;

    if (*stack != NULL)
        (*stack)->prev = new_node; /* Link back to new node */
    *stack = new_node; /* Update the stack to the new top */

    /* Suppress the unused parameter warning */
    (void)line_number; 
}

/**
 * pall - Prints all values on the stack
 * @stack: Double pointer to the stack
 */
void pall(stack_t **stack)
{
    stack_t *current = *stack;

    while (current != NULL)
    {
        printf("%d\n", current->n);
        current = current->next;
    }
}
