#include "monty.h"

/**
 * free_stack - Frees a doubly linked list (stack).
 * @stack: Pointer to the head of the stack.
 */
void free_stack(stack_t *stack)
{
    stack_t *temp;

    while (stack)
    {
        temp = stack;
        stack = stack->next;
        free(temp);
    }
}
