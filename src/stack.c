#include <stdlib.h>
#include <stdint.h>
#include "stack.h"
#include "linked_list.h"

uint8_t push(STACK *stack, void *data, size_t dataSize)
// inserts value at the top of the stack
{
    return stack->list->insert(stack->list, 0, data, dataSize);
}
void *pop(STACK *stack)
{
    // pulls and remove value at pointer and freeing up space for new value
    void *data = stack->peekStack(stack);

    if (stack->list->removeAtPosition(stack->list, 0, KeepAllocated) == (uint8_t)EXIT_SUCCESS)
    {
        return data;
    }
    return NULL;
}

void *peekStack(STACK *stack)
{
    // peeks at the top of the stack and let user know what value is currently being held there
    return stack->list->getByIndex(stack->list, 0);
}

uint8_t cleanStack(STACK *stack)
{
    // delete stack and allocate memory
    stack->list->clear(stack->list);
    free(stack->list);
    return EXIT_SUCCESS;
}

uint8_t setupStack(STACK *stack)
{
    // setup stack for general use
    stack->list = (LINKED_LIST *)malloc(sizeof(LINKED_LIST));
    setupLinkedList(stack->list);

    stack->push = push;
    stack->pop = pop;
    stack->peekStack = peekStack;

    stack->cleanStack = cleanStack;

    return EXIT_SUCCESS;
}