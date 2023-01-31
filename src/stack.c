#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "stack.h"
#include "linked_list.h"

uint8_t push(STACK *stack, void *data, size_t dataSize)
{
    return stack->list->insert(stack->list, 0, data, dataSize);
}
void *pop(STACK *stack)
{
    void *data = stack->list->getByIndex(stack->list, 0);

    if (stack->list->removeAtPosition(stack->list, 0) == (uint8_t)EXIT_SUCCESS)
    {
        return data;
    }
    return NULL;
}

void *peek(STACK *stack)
{
    return stack->list->getByIndex(stack->list, 0);
}

uint8_t clean(STACK *stack)
{
    stack->list->clear(stack->list);
    free(stack->list);
    return EXIT_SUCCESS;
}

uint8_t setupStack(STACK *stack)
{
    stack->list = (LINKED_LIST *)malloc(sizeof(LINKED_LIST));
    setupLinkedList(stack->list);

    stack->push = push;
    stack->pop = pop;
    stack->peek = peek;

    stack->clean = clean;

    return EXIT_SUCCESS;
}