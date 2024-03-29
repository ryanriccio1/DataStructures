#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

#include "Stack.h"
#include "LinkedList.h"

uint8_t push(Stack *stack, void *data, size_t dataSize)
// inserts value at the top of the stack
{
    assert(stack);
    return stack->list->insert(stack->list, 0, data, dataSize);
}
void *pop(Stack *stack)
{
    assert(stack);
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
    assert(stack);
    // peeks at the top of the stack and let user know what value is currently being held there
    return stack->list->getByIndex(stack->list, 0);
}

uint8_t cleanStack(Stack *stack)
{
    assert(stack);
    // delete stack and allocate memory
    stack->list->clear(stack->list);
    free(stack->list);
    return EXIT_SUCCESS;
}

uint8_t setupStack(Stack *stack, DataType dataType)
{
    assert(stack);
    // setup stack for general use
    stack->list = (LinkedList *)malloc(sizeof(LinkedList));
    setupLinkedList(stack->list, dataType);

    stack->push = push;
    stack->pop = pop;
    stack->peekStack = peekStack;

    stack->cleanStack = cleanStack;

    return EXIT_SUCCESS;
}