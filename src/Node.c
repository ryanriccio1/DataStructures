#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

#include "Node.h"

uint8_t setupNode(Node *node, void *newData, size_t dataSize)
{
    assert(node);
    node->next = NULL;
    node->prev = NULL;
    node->data = newData;
    node->dataSize = dataSize;
    node->cleanup = cleanup;
    return EXIT_SUCCESS;
}

uint8_t cleanup(Node *node)
{
    assert(node);
    free(node->data);
    return EXIT_SUCCESS;
}