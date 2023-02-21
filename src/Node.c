#include <stdlib.h>
#include <stdint.h>
#include "Node.h"

uint8_t setupNode(Node *node, void *newData, size_t dataSize)
{
    if (node == NULL)
    {
        errno = 1;
        return EXIT_FAILURE;
    }
    node->next = NULL;
    node->prev = NULL;
    node->data = newData;
    node->dataSize = dataSize;
    node->cleanup = cleanup;
    return EXIT_SUCCESS;
}

uint8_t cleanup(Node *node)
{
    if (node == NULL)
    {
        errno = 1;
        return EXIT_FAILURE;
    }
    free(node->data);
    return EXIT_SUCCESS;
}