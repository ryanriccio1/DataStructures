#include <stdlib.h>
#include <stdint.h>
#include "queue.h"
#include "linked_list.h"

uint8_t enqueue(QUEUE *queue, void *data, size_t dataSize)
{
    // add to end of queue
    return queue->list->append(queue->list, data, dataSize);
}
void *dequeue(QUEUE *queue)
{
    // get the item on the top of the queue
    void *data = queue->peekQueue(queue);

    // try to remove it and return the data we removed
    if (queue->list->removeAtPosition(queue->list, 0, KeepAllocated) == (uint8_t)EXIT_SUCCESS)
    {
        return data;
    }
    return NULL;
}
void *peekQueue(QUEUE *queue)
{
    // get the item on the top of the queue without removing it
    return queue->list->getByIndex(queue->list, 0);
}

uint8_t cleanQueue(QUEUE *queue)
{
    // remove all the items in the queue
    queue->list->clear(queue->list);
    free(queue->list);
    return EXIT_SUCCESS;
}

uint8_t setupQueue(QUEUE *queue)
{
    queue->list = (LINKED_LIST *)malloc(sizeof(LINKED_LIST));
    setupLinkedList(queue->list);

    queue->enqueue = enqueue;
    queue->dequeue = dequeue;
    queue->peekQueue = peekQueue;

    queue->cleanQueue = cleanQueue;

    return EXIT_SUCCESS;
}