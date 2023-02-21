#include "Queue.h"
#include <stdlib.h>
#include <stdint.h>
#include "Stack.h"

int main()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    setupStack(stack, Int64);

    int64_t *data = (int64_t *)malloc(sizeof(int64_t));
    *data = 500;
    stack->push(stack, data, sizeof(int64_t));

    stack->list->print(stack->list);
}