#include <stdlib.h>
#include <stdint.h>
#include "Node.h"

uint8_t setupNode(Node *node, void *newData, size_t dataSize)
{
    node->next = NULL;
    node->prev = NULL;
    node->data = newData;
    node->dataSize = dataSize;
    node->cleanup = cleanup;
    return EXIT_SUCCESS;
}

uint8_t cleanup(Node *node)
{
    free(node->data);
    return EXIT_SUCCESS;
}