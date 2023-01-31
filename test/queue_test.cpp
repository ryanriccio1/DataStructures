#include <gtest/gtest.h>
#include <stdlib.h>
#include <cstdint>
extern "C"
{
#include "queue.h"
}

QUEUE *setupQueueTest()
{
    QUEUE *queue = (QUEUE *)malloc(sizeof(QUEUE));
    setupQueue(queue);

    for (size_t idx = 0; idx < 5; idx++)
    {
        int *data = (int *)malloc(sizeof(int));
        *data = idx * 5;
        queue->enqueue(queue, data, sizeof(int));
    }

    return queue;
}

TEST(queue, enqueue_withValidData_returnsSuccess)
{
    QUEUE *queue = setupQueueTest();

    int *data = (int *)malloc(sizeof(int));
    *data = 500;
    uint8_t result = queue->enqueue(queue, data, sizeof(int));

    EXPECT_EQ(result, (uint8_t)EXIT_SUCCESS);
    EXPECT_EQ(500, *(int *)queue->list->getByIndex(queue->list, queue->list->length - 1));

    queue->cleanQueue(queue);
    free(queue);
}

TEST(queue, dequeue_withValidData_returnsData)
{
    QUEUE *queue = setupQueueTest();

    int data1 = *(int *)queue->dequeue(queue);
    int data2 = *(int *)queue->dequeue(queue);
    int data3 = *(int *)queue->dequeue(queue);

    EXPECT_EQ(data1, 0);
    EXPECT_EQ(data2, 5);
    EXPECT_EQ(data3, 10);

    queue->cleanQueue(queue);
    free(queue);
}

TEST(queue, peekStack_withValidData_returnsData)
{
    QUEUE *queue = setupQueueTest();

    int data = *(int *)queue->peekQueue(queue);
    EXPECT_EQ(data, 0);

    queue->cleanQueue(queue);
    free(queue);
}