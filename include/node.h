#ifndef NODE_H
#define NODE_H
#include <stdint.h>

typedef struct Node
{
    struct Node *next;
    struct Node *prev;

    void *data;
    size_t dataSize;
    uint8_t (*cleanup)(struct Node *node);
} NODE;

/**
 * @brief Setup and initialize data in node
 *
 * @param node Node to setup
 * @param newData Data to initialize it to
 * @param dataSize Size of data to use (can be used for precedence sorting too)
 * @return uint8_t
 */
uint8_t setupNode(NODE *node, void *newData, size_t dataSize);
/**
 * @brief Free data in node
 *
 * @param node Node to free
 * @return uint8_t
 */
uint8_t cleanup(NODE *node);

#endif