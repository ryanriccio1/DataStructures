#include <stdlib.h>
#include <stdint.h>
#include "Queue.h"
#include "LinkedList.h"

uint8_t enqueue(Queue *queue, void *data, size_t dataSize)
{
    if (queue == NULL)
    {
        errno = 1;
        return EXIT_FAILURE;
    }
    // add to end of queue
    return queue->list->append(queue->list, data, dataSize);
}
void *dequeue(Queue *queue)
{
    if (queue == NULL)
    {
        errno = 1;
        return NULL;
    }
    // get the item on the top of the queue
    void *data = queue->peekQueue(queue);

    // try to remove it and return the data we removed
    if (queue->list->removeAtPosition(queue->list, 0, KeepAllocated) == (uint8_t)EXIT_SUCCESS)
    {
        return data;
    }
    return NULL;
}
void *peekQueue(Queue *queue)
{
    if (queue == NULL)
    {
        errno = 1;
        return NULL;
    }
    // get the item on the top of the queue without removing it
    return queue->list->getByIndex(queue->list, 0);
}

uint8_t cleanQueue(Queue *queue)
{
    if (queue == NULL)
    {
        errno = 1;
        return EXIT_FAILURE;
    }
    // remove all the items in the queue
    queue->list->clear(queue->list);
    free(queue->list);
    return EXIT_SUCCESS;
}

uint8_t setupQueue(Queue *queue, DataType dataType)
{
    if (queue == NULL)
    {
        errno = 1;
        return EXIT_FAILURE;
    }
    queue->list = (LinkedList *)malloc(sizeof(LinkedList));
    setupLinkedList(queue->list, dataType);

    queue->enqueue = enqueue;
    queue->dequeue = dequeue;
    queue->peekQueue = peekQueue;

    queue->cleanQueue = cleanQueue;

    return EXIT_SUCCESS;
}