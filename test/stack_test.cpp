#include <gtest/gtest.h>
#include <stdlib.h>
#include <cstdint>
extern "C"
{
#include "stack.h"
}

STACK *setupStackTest()
{
    STACK *stack = (STACK *)malloc(sizeof(STACK));
    setupStack(stack);

    for (size_t idx = 0; idx < 5; idx++)
    {
        int *data = (int *)malloc(sizeof(int));
        *data = idx * 5;
        stack->push(stack, data, sizeof(int));
    }

    return stack;
}

TEST(stack, push_withValidData_returnsSuccess)
{
    STACK *stack = setupStackTest();

    int *data = (int *)malloc(sizeof(int));
    *data = 500;
    uint8_t result = stack->push(stack, data, sizeof(int));

    EXPECT_EQ(result, (uint8_t)EXIT_SUCCESS);
    EXPECT_EQ(500, *(int *)stack->list->getByIndex(stack->list, 0));

    stack->clean(stack);
    free(stack);
}

TEST(stack, pop_withValidData_returnsData)
{
    STACK *stack = setupStackTest();

    int data1 = *(int *)stack->pop(stack);
    int data2 = *(int *)stack->pop(stack);
    int data3 = *(int *)stack->pop(stack);

    EXPECT_EQ(data1, 20);
    EXPECT_EQ(data2, 15);
    EXPECT_EQ(data3, 10);

    stack->clean(stack);
    free(stack);
}

TEST(stack, peek_withValidData_returnsData)
{
    STACK *stack = setupStackTest();

    int data = *(int *)stack->peek(stack);
    EXPECT_EQ(data, 20);

    stack->clean(stack);
    free(stack);
}