#include <stdlib.h>
#include <stdint.h>
#include "Stack.h"
#include "LinkedList.h"

uint8_t push(Stack *stack, void *data, size_t dataSize)
// inserts value at the top of the stack
{
    if (stack == NULL)
    {
        errno = 1;
        return EXIT_FAILURE;
    }
    return stack->list->insert(stack->list, 0, data, dataSize);
}
void *pop(Stack *stack)
{
    if (stack == NULL)
    {
        errno = 1;
        return NULL;
    }
    // pulls and remove value at pointer and freeing up space for new value
    void *data = stack->peekStack(stack);

    if (stack->list->removeAtPosition(stack->list, 0, KeepAllocated) == (uint8_t)EXIT_SUCCESS)
    {
        return data;
    }
    return NULL;
}

void *peekStack(Stack *stack)
{
    if (stack == NULL)
    {
        errno = 1;
        return NULL;
    }
    // peeks at the top of the stack and let user know what value is currently being held there
    return stack->list->getByIndex(stack->list, 0);
}

uint8_t cleanStack(Stack *stack)
{
    if (stack == NULL)
    {
        errno = 1;
        return EXIT_FAILURE;
    }
    // delete stack and allocate memory
    stack->list->clear(stack->list);
    free(stack->list);
    return EXIT_SUCCESS;
}

uint8_t setupStack(Stack *stack, DataType dataType)
{
    if (stack == NULL)
    {
        errno = 1;
        return EXIT_FAILURE;
    }
    // setup stack for general use
    stack->list = (LinkedList *)malloc(sizeof(LinkedList));
    setupLinkedList(stack->list, dataType);

    stack->push = push;
    stack->pop = pop;
    stack->peekStack = peekStack;

    stack->cleanStack = cleanStack;

    return EXIT_SUCCESS;
}