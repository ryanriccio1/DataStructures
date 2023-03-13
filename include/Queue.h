#pragma once
#include <stdint.h>
#include <stddef.h>

#include "LinkedList.h"

/**
 * @brief Queue implementation
 *
 */
typedef struct Queue
{
    LinkedList *list;

    uint8_t (*enqueue)(struct Queue *queue, void *data, size_t dataSize);
    void *(*dequeue)(struct Queue *queue);
    void *(*peekQueue)(struct Queue *queue);

    uint8_t (*cleanQueue)(struct Queue *queue);
} Queue;

/**
 * @brief Add data to the queue
 *
 * @param queue Queue to perform operation on
 * @param data Data to push onto queue
 * @param dataSize Size of data being pushed on queue
 * @return uint8_t
 */
uint8_t enqueue(Queue *queue, void *data, size_t dataSize);

/**
 * @brief Remove data from the queue and get the data
 *
 * @param queue Queue to perform operation on
 * @return void*
 */
void *dequeue(Queue *queue);

/**
 * @brief See what is at the top of the queue without removing it
 *
 * @param queue Queue to perform operation on
 * @return void*
 */
void *peekQueue(Queue *queue);

/**
 * @brief Clean all data inside queue
 *
 * @param queue Queue to perform operation on
 * @return uint8_t
 */
uint8_t cleanQueue(Queue *queue);

/**
 * @brief Setup and initialize all data needed for queue
 *
 * @param queue Queue to perform operation on
 * @param dataType Type of data being stored in queue
 * @return uint8_t
 */
uint8_t setupQueue(Queue *queue, DataType dataType);
