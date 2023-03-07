#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "LinkedList.h"
#include "Node.h"

void setLength(LinkedList *list, size_t length)
{
    if (list == NULL)
    {
        errno = 1;
        return;
    }
    // use setLength so isEmpty is always current
    list->length = length;
    if (length == 0)
    {
        list->isEmpty = 1;
    }
    else
    {
        list->isEmpty = 0;
    }
}

uint8_t insert(LinkedList *list, size_t newPosition, void *newData, size_t dataSize)
{
    if (list == NULL)
    {
        errno = 1;
        return EXIT_FAILURE;
    }
    // make sure newPosition is in proper range (size_t dictates it cannot be negative)
    uint8_t ableToInsert = newPosition <= list->length;
    if (ableToInsert)
    {
        // Create a new node containing the new entry
        Node *newNodePtr = (Node *)malloc(sizeof(Node));
        setupNode(newNodePtr, newData, dataSize);

        // if we are inserting at the head or tail
        if (newPosition == 0 || newPosition == list->length)
        {
            // set head
            if (newPosition == 0)
            {
                // link our new node to previous head
                newNodePtr->next = list->head;

                // as long as this is not our first item
                // link the previous head to our new node
                if (list->length > 0)
                {
                    list->head->prev = newNodePtr;
                }

                // set the head to our new node
                list->head = newNodePtr;
            }
            // set tail
            if (newPosition == list->length)
            {
                // doubly linked tail
                newNodePtr->prev = list->tail;
                list->tail = newNodePtr;
            }
        }

        // as long as we are not at the head of the list
        if (newPosition > 0)
        {
            Node *prevPtr = NULL;
            Node *nextPtr = NULL;

            // if there is no previous node, do nothing
            prevPtr = getNodeByIndex(list, newPosition - 1);
            if (prevPtr != NULL)
            { // link previous node with our new node
                newNodePtr->next = prevPtr->next;
                prevPtr->next = newNodePtr;
            }

            // if there is no next node, do nothing
            nextPtr = getNodeByIndex(list, newPosition + 1);
            if (nextPtr != NULL)
            { // link our next node with our new node
                newNodePtr->prev = nextPtr->prev;
                nextPtr->prev = newNodePtr;
            }
        }
        // increment length
        setLength(list, list->length + 1);
    }

    return !ableToInsert;
}
uint8_t insertBefore(LinkedList *list, size_t index, void *newData, size_t dataSize)
{
    if (list == NULL)
    {
        errno = 1;
        return EXIT_FAILURE;
    }
    // make sure we are inserting before tail
    if (index < list->length)
    { // a normal insert should be the same as insertBefore
        return insert(list, index, newData, dataSize);
    }
    return EXIT_FAILURE;
}
uint8_t insertAfter(LinkedList *list, size_t index, void *newData, size_t dataSize)
{
    if (list == NULL)
    {
        errno = 1;
        return EXIT_FAILURE;
    }
    // make sure we are only inserting within the range of the list
    if (index < list->length)
    { // insert one index after current index
        return insert(list, index + 1, newData, dataSize);
    }
    return EXIT_FAILURE;
}

uint8_t append(LinkedList *list, void *newData, size_t dataSize)
{
    if (list == NULL)
    {
        errno = 1;
        return EXIT_FAILURE;
    }
    // add data to end of list
    return insert(list, list->length, newData, dataSize);
}

uint8_t removeAtPosition(LinkedList *list, size_t position, DeallocateFlag deallocatePointer)
{
    if (list == NULL)
    {
        errno = 1;
        return EXIT_FAILURE;
    }
    // check to make sure position is within the length of the list
    uint8_t ableToRemove = position <= list->length;
    if (ableToRemove)
    {
        Node *curPtr = getNodeByIndex(list, position);
        Node *nextPtr = curPtr->next;
        Node *prevPtr = curPtr->prev;
        // removes entry at head and making the next entry the new head
        if (position == 0)
        {
            list->head = nextPtr;
        }
        // removes entry at tail and makes the previous entry the new tail
        if (position == list->length - 1)
        {
            list->tail = prevPtr;
        }
        // relink adjacent pointers
        if (prevPtr)
        {
            prevPtr->next = nextPtr;
        }
        if (nextPtr)
        {
            nextPtr->prev = prevPtr;
        }

        // cleanup the entry and frees allocated memory
        if (deallocatePointer == Deallocate)
        {
            curPtr->cleanup(curPtr);
        }
        free(curPtr);

        list->setLength(list, list->length - 1);
    }

    return !ableToRemove;
}
uint8_t removeAtValue(LinkedList *list, void *value, DeallocateFlag deallocatePointer)
{
    if (list == NULL)
    {
        errno = 1;
        return EXIT_FAILURE;
    }
    Node *curPtr = NULL;
    // search to see if our pointers match
    if ((curPtr = getNodeByValue(list, value)) != NULL)
    {
        Node *nextPtr = curPtr->next;
        Node *prevPtr = curPtr->prev;
        size_t index = indexOf(list, value);
        // if we are removing the head, set the next head
        if (index == 0)
        {
            list->head = nextPtr;
        }
        // if we are removing the tail, set the new tail
        if (index == list->length - 1)
        {
            list->tail = prevPtr;
        }
        // relink adjacent points
        if (prevPtr)
        {
            prevPtr->next = nextPtr;
        }
        if (nextPtr)
        {
            nextPtr->prev = prevPtr;
        }

        // cleanup data and node
        if (deallocatePointer == Deallocate)
        {
            curPtr->cleanup(curPtr);
        }
        free(curPtr);

        list->setLength(list, list->length - 1);
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

uint8_t clear(LinkedList *list)
{
    if (list == NULL)
    {
        errno = 1;
        return EXIT_FAILURE;
    }
    // clear/free all nodes and their associated data
    Node *curPtr = list->tail;
    for (size_t idx = 0; idx < list->length; idx++)
    {
        if (curPtr != NULL)
        {
            Node *rmPtr = curPtr;
            curPtr = curPtr->prev;
            rmPtr->cleanup(rmPtr);
            free(rmPtr);
        }
    }
    list->head = NULL;
    list->tail = NULL;
    list->setLength(list, 0);
    return EXIT_SUCCESS;
}
uint8_t contains(LinkedList *list, void *data)
{
    if (list == NULL)
    {
        errno = 1;
        return EXIT_FAILURE;
    }
    // check to see if a pointer exists in any of our nodes
    return getNodeByValue(list, data) != NULL ? 1 : 0;
}
uint8_t replace(LinkedList *list, size_t position, void *data, size_t dataSize)
{
    if (list == NULL)
    {
        errno = 1;
        return EXIT_FAILURE;
    }
    // just swap out the data pointer at a given position

    // position must be an index (len - 1)
    uint8_t abletoReplace = position <= list->length - 1;
    if (abletoReplace)
    {
        Node *curPtr = getNodeByIndex(list, position);
        free(curPtr->data);
        curPtr->dataSize = dataSize;
        curPtr->data = data;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

Node *getNodeByIndex(LinkedList *list, size_t position)
{
    if (list == NULL)
    {
        errno = 1;
        return NULL;
    }
    // iterate until our index == position
    uint8_t ableToGet = position <= list->length - 1;
    if (ableToGet)
    {
        Node *curPtr = list->head;
        for (size_t skip = 0; skip < position; skip++)
        {
            curPtr = curPtr->next;
        }
        return curPtr;
    }
    return NULL;
}
Node *getNodeByValue(LinkedList *list, void *value)
{
    if (list == NULL)
    {
        errno = 1;
        return NULL;
    }
    // search to see if pointers are equivalent
    Node *curPtr = list->head;
    for (size_t idx = 0; idx < list->length; idx++)
    {
        if (curPtr->data == value)
        {
            return curPtr;
        }
        curPtr = curPtr->next;
    }
    return curPtr;
}
void *getByIndex(LinkedList *list, size_t position)
{
    if (list == NULL)
    {
        errno = 1;
        return NULL;
    }
    // get the pointer to the data at a given position
    Node *node = getNodeByIndex(list, position);
    if (node != NULL)
    {
        return node->data;
    }
    return NULL;
}
size_t indexOf(LinkedList *list, void *value)
{
    if (list == NULL)
    {
        errno = 1;
        return (size_t)-1;
    }
    // get the index of a entry based on its pointer
    for (size_t idx = 0; idx < list->length; idx++)
    {
        if (value == getNodeByIndex(list, idx)->data)
        {
            return idx;
        }
    }
    return (size_t)-1; // document
}

void print(LinkedList *list)
{
    if (list == NULL)
    {
        errno = 1;
        return;
    }
    for (size_t idx = 0; idx < list->length; idx++)
    {
        Node *node = getNodeByIndex(list, idx);
        switch (list->dataType)
        {
        case String:
            printf("[%lld]:\t%s\n", idx, (char *)node->data);
            break;
        case Int8:
            printf("[%lld]:\t%d\n", idx, *(int8_t *)node->data);
            break;
        case Int16:
            printf("[%lld]:\t%d\n", idx, *(int16_t *)node->data);
            break;
        case Int32:
            printf("[%lld]:\t%d\n", idx, *(int32_t *)node->data);
            break;
        case Int64:
            printf("[%lld]:\t%lld\n", idx, *(int64_t *)node->data);
            break;
        case Uint8:
            printf("[%lld]:\t%u\n", idx, *(uint8_t *)node->data);
            break;
        case Uint16:
            printf("[%lld]:\t%u\n", idx, *(uint16_t *)node->data);
            break;
        case Uint32:
            printf("[%lld]:\t%u\n", idx, *(uint32_t *)node->data);
            break;
        case Uint64:
            printf("[%lld]:\t%llu\n", idx, *(uint64_t *)node->data);
            break;
        case Double:
            printf("[%lld]:\t%F\n", idx, *(double *)node->data);
            break;
        case Float:
            printf("[%lld]:\t%F\n", idx, *(float *)node->data);
            break;
        case Pointer:
            printf("[%lld]:\t%p\n", idx, node->data);
            break;
        }
    }
}

void sortByAddress(LinkedList *list)
{
    if (list == NULL)
    {
        errno = 1;
        return;
    }
    // merge sort where we compare addresses
    list->head = mergeSort(list, list->head, PointerCompare);
}
void sortByValue(LinkedList *list)
{
    if (list == NULL)
    {
        errno = 1;
        return;
    }
    // merge sort where we compare the value at the addresses (As int64_t)
    list->head = mergeSort(list, list->head, ValueCompare);
}
void sortBySize(LinkedList *list)
{
    if (list == NULL)
    {
        errno = 1;
        return;
    }
    // merge sort where we use the size to compare
    list->head = mergeSort(list, list->head, SizeCompare);
}

Node *merge(LinkedList *list, Node *first, Node *second, MergeSortComparison compareFunc)
{
    // if we have reached a single side, return it to the sorter
    if (!first)
        return second;

    if (!second)
        return first;

    // if first < second (with multiple methods of comparing)
    if ((compareFunc == PointerCompare && first->data < second->data) ||
        (compareFunc == ValueCompare && compare(list->dataType, first->data, second->data) == 1) ||
        (compareFunc == SizeCompare && first->dataSize < second->dataSize))
    {
        // get the next node in the proper order recursively
        first->next = merge(list, first->next, second, compareFunc);
        // link to the proper next node (doubly)
        first->next->prev = first;
        first->prev = NULL;
        return first;
    }
    else
    {
        // get the next node that is greater than first recursively
        second->next = merge(list, first, second->next, compareFunc);
        // link to proper node doubly
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}
Node *mergeSort(LinkedList *list, Node *head, MergeSortComparison compareFunc)
{ // head of merge sort, not of list TODO
    // Once we run out of things to sort, return
    if (!head || !head->next)
    {
        return head;
    }
    Node *second = split(head);

    // recursively sort the two sides
    head = mergeSort(list, head, compareFunc);
    second = mergeSort(list, second, compareFunc);

    // once the sides are sorted, merge the two (recursively as well)
    return merge(list, head, second, compareFunc);
}
Node *split(Node *head)
{
    Node *A = head;
    Node *B = head;
    // A gets incremented twice as fast as B
    // As long as A->next->next is not null,
    // we haven't reached the middle yet
    while (A->next && A->next->next)
    {
        A = A->next->next;
        B = B->next;
    }
    // Once we reach the middle, our new head is
    // the next item in the chain
    // (to prevent issues when there are odd amounts of data)
    Node *temp = B->next;
    B->next = NULL; // unlink the nodes
    return temp;
}
void swap(void *A, void *B)
{
    void *temp = A;
    A = B;
    B = temp;
}
uint8_t compare(DataType dataType, void *A, void *B)
{
    switch (dataType)
    {
    case String:
        if (strcmp(A, B) < 0)
        {
            return 1;
        }
        return 0;
    case Int8:
        if (*(int8_t *)A < *(int8_t *)B)
        {
            return 1;
        }
        return 0;
    case Int16:
        if (*(int16_t *)A < *(int16_t *)B)
        {
            return 1;
        }
        return 0;
    case Int32:
        if (*(int32_t *)A < *(int32_t *)B)
        {
            return 1;
        }
        return 0;
    case Int64:
        if (*(int64_t *)A < *(int64_t *)B)
        {
            return 1;
        }
        return 0;
    case Uint8:
        if (*(uint8_t *)A < *(uint8_t *)B)
        {
            return 1;
        }
        return 0;
    case Uint16:
        if (*(uint16_t *)A < *(uint16_t *)B)
        {
            return 1;
        }
        return 0;
    case Uint32:
        if (*(uint32_t *)A < *(uint32_t *)B)
        {
            return 1;
        }
        return 0;
    case Uint64:
        if (*(uint64_t *)A < *(uint64_t *)B)
        {
            return 1;
        }
        return 0;
    case Double:
        if (*(double *)A < *(double *)B)
        {
            return 1;
        }
        return 0;
    case Float:
        if (*(float *)A < *(float *)B)
        {
            return 1;
        }
        return 0;
    default:
        return 0;
    }
}

uint8_t setupLinkedList(LinkedList *list, DataType dataType)
{
    if (list == NULL)
    {
        errno = 1;
        return EXIT_FAILURE;
    }
    // initialize all the memory and link the struct funcs to actual funcs
    list->isEmpty = 1;

    list->head = NULL;
    list->tail = NULL;
    list->dataType = dataType;
    list->length = 0;

    list->setLength = setLength;

    list->insert = insert;
    list->insertBefore = insertBefore;
    list->insertAfter = insertAfter;

    list->append = append;

    list->removeAtPosition = removeAtPosition;
    list->removeAtValue = removeAtValue;

    list->clear = clear;
    list->contains = contains;
    list->replace = replace;

    list->getNodeByIndex = getNodeByIndex;
    list->getNodeByValue = getNodeByValue;
    list->getByIndex = getByIndex;
    list->indexOf = indexOf;

    list->print = print;

    list->sortByAddress = sortByAddress;
    list->sortByValue = sortByValue;
    list->sortBySize = sortBySize;

    return EXIT_SUCCESS;
}
