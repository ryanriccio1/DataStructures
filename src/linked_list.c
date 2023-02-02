#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"
#include "node.h"

void setLength(LINKED_LIST *list, size_t length)
{ // use setLength so isEmpty is always current
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

uint8_t insert(LINKED_LIST *list, size_t newPosition, void *newData, size_t dataSize)
{ // make sure newPosition is in proper range (size_t dictates it cannot be negative)
    uint8_t ableToInsert = newPosition <= list->length;
    if (ableToInsert)
    {
        // Create a new node containing the new entry
        NODE *newNodePtr = (NODE *)malloc(sizeof(NODE));
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
            NODE *prevPtr = NULL;
            NODE *nextPtr = NULL;

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
uint8_t insertBefore(LINKED_LIST *list, size_t index, void *newData, size_t dataSize)
{
    // make sure we are inserting before tail
    if (index < list->length)
    { // a normal insert should be the same as insertBefore
        return insert(list, index, newData, dataSize);
    }
    return EXIT_FAILURE;
}
uint8_t insertAfter(LINKED_LIST *list, size_t index, void *newData, size_t dataSize)
{
    // make sure we are only inserting within the range of the list
    if (index < list->length)
    { // insert one index after current index
        return insert(list, index + 1, newData, dataSize);
    }
    return EXIT_FAILURE;
}

uint8_t append(LINKED_LIST *list, void *newData, size_t dataSize)
{ // add data to end of list
    return insert(list, list->length, newData, dataSize);
}

uint8_t removeAtPosition(LINKED_LIST *list, size_t position, DeallocateFlag deallocatePointer)
{
    // check to make sure position is within the length of the list
    uint8_t ableToRemove = position <= list->length;
    if (ableToRemove)
    {
        NODE *curPtr = getNodeByIndex(list, position);
        NODE *nextPtr = curPtr->next;
        NODE *prevPtr = curPtr->prev;
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
uint8_t removeAtValue(LINKED_LIST *list, void *value, DeallocateFlag deallocatePointer)
{
    NODE *curPtr = NULL;
    // search to see if our pointers match
    if ((curPtr = getNodeByValue(list, value)) != NULL)
    {
        NODE *nextPtr = curPtr->next;
        NODE *prevPtr = curPtr->prev;
        // if we are removing the head, set the next head
        if (indexOf(list, value) == 0)
        {
            list->head = nextPtr;
        }
        // if we are removing the tail, set the new tail
        if (indexOf(list, value) == list->length - 1)
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

uint8_t clear(LINKED_LIST *list)
{ // clear/free all nodes and their associated data
    NODE *curPtr = list->tail;
    for (size_t idx = 0; idx < list->length; idx++)
    {
        if (curPtr != NULL)
        {
            NODE *rmPtr = curPtr;
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
uint8_t contains(LINKED_LIST *list, void *data)
{ // check to see if a pointer exists in any of our nodes
    return getNodeByValue(list, data) != NULL ? 1 : 0;
}
uint8_t replace(LINKED_LIST *list, size_t position, void *data, size_t dataSize)
{ // just swap out the data pointer at a given position

    // position must be an index (len - 1)
    uint8_t abletoReplace = position <= list->length - 1;
    if (abletoReplace)
    {
        NODE *curPtr = getNodeByIndex(list, position);
        curPtr->dataSize = dataSize;
        curPtr->data = data;
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

NODE *getNodeByIndex(LINKED_LIST *list, size_t position)
{ // iterate until our index == position
    uint8_t ableToGet = position <= list->length - 1;
    if (ableToGet)
    {
        NODE *curPtr = list->head;
        for (size_t skip = 0; skip < position; skip++)
        {
            curPtr = curPtr->next;
        }
        return curPtr;
    }
    return NULL;
}
NODE *getNodeByValue(LINKED_LIST *list, void *value)
{ // search to see if pointers are equivalent
    NODE *curPtr = list->head;
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
void *getByIndex(LINKED_LIST *list, size_t position)
{ // get the pointer to the data at a given position
    uint8_t ableToGet = position <= list->length - 1;
    if (ableToGet)
    { // traverse list
        NODE *curPtr = list->head;
        for (size_t idx = 0; idx < position; idx++)
        {
            curPtr = curPtr->next;
        }
        return curPtr->data;
    }
    return NULL;
}
size_t indexOf(LINKED_LIST *list, void *value)
{ // get the index of a entry based on its pointer
    NODE *curPtr = list->head;
    for (size_t idx = 0; idx < list->length; idx++)
    {
        if (value == curPtr->data)
        {
            return idx;
        }
        curPtr = curPtr->next;
    }
    return (size_t)-1;
}

void printString(LINKED_LIST *list)
{ // print data as a string
    for (size_t idx = 0; idx < list->length; idx++)
    {
        NODE *node = getNodeByIndex(list, idx);
        printf("[%lld]:\t%s\n", idx, (char *)node->data);
    }
}
void printInt(LINKED_LIST *list)
{ // print data as an int
    for (size_t idx = 0; idx < list->length; idx++)
    {
        NODE *node = getNodeByIndex(list, idx);
        printf("[%lld]:\t%d\n", idx, *(int32_t *)node->data);
    }
}
void printInt64(LINKED_LIST *list)
{ // print data as an int64_t
    for (size_t idx = 0; idx < list->length; idx++)
    {
        NODE *node = getNodeByIndex(list, idx);
        printf("[%lld]:\t%lld\n", idx, *(int64_t *)node->data);
    }
}
void printUint64(LINKED_LIST *list)
{ // print data as an uint64_t
    for (size_t idx = 0; idx < list->length; idx++)
    {
        NODE *node = getNodeByIndex(list, idx);
        printf("[%lld]:\t%lld\n", idx, *(uint64_t *)node->data);
    }
}
void printDouble(LINKED_LIST *list)
{ // print data as a double
    for (size_t idx = 0; idx < list->length; idx++)
    {
        NODE *node = getNodeByIndex(list, idx);
        printf("[%lld]:\t%F\n", idx, *(double *)node->data);
    }
}
void printPointer(LINKED_LIST *list)
{ // print data as an address
    for (size_t idx = 0; idx < list->length; idx++)
    {
        NODE *node = getNodeByIndex(list, idx);
        printf("[%lld]:\t%p\n", idx, node->data);
    }
}

void sortByAddress(LINKED_LIST *list)
{ // merge sort where we compare addresses
    list->head = mergeSort(list->head, PointerCompare);
}
void sortByValue(LINKED_LIST *list)
{ // merge sort where we compare the value at the addresses (As int64_t)
    list->head = mergeSort(list->head, ValueCompare);
}
void sortBySize(LINKED_LIST *list)
{ // merge sort where we use the size to compare
    list->head = mergeSort(list->head, SizeCompare);
}

NODE *merge(NODE *first, NODE *second, MergeSortComparison compareFunc)
{
    // if we have reached a single side, return it to the sorter
    if (!first)
        return second;

    if (!second)
        return first;

    // if first < second (with multiple methods of comparing)
    if ((compareFunc == PointerCompare && first->data < second->data) ||
        (compareFunc == ValueCompare && *(int64_t *)(first->data) < *(int64_t *)(second->data)) ||
        (compareFunc == SizeCompare && first->dataSize < second->dataSize))
    {
        // get the next node in the proper order recursively
        first->next = merge(first->next, second, compareFunc);
        // link to the proper next node (doubly)
        first->next->prev = first;
        first->prev = NULL;
        return first;
    }
    else
    {
        // get the next node that is greater than first recursively
        second->next = merge(first, second->next, compareFunc);
        // link to proper node doubly
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}
NODE *mergeSort(NODE *head, MergeSortComparison compareFunc)
{
    // Once we run out of things to sort, return
    if (!head || !head->next)
    {
        return head;
    }
    NODE *second = split(head);

    // recursively sort the two sides
    head = mergeSort(head, compareFunc);
    second = mergeSort(second, compareFunc);

    // once the sides are sorted, merge the two (recursively as well)
    return merge(head, second, compareFunc);
}
NODE *split(NODE *head)
{
    NODE *A = head;
    NODE *B = head;
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
    NODE *temp = B->next;
    B->next = NULL; // unlink the nodes
    return temp;
}
void swap(void *A, void *B)
{
    void *temp = A;
    A = B;
    B = temp;
}

uint8_t setupLinkedList(LINKED_LIST *list)
{ // initialize all the memory and link the struct funcs to actual funcs
    list->isEmpty = 1;

    list->head = NULL;
    list->tail = NULL;
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

    list->printString = printString;
    list->printInt = printInt;
    list->printInt64 = printInt64;
    list->printUint64 = printUint64;
    list->printDouble = printDouble;
    list->printPointer = printPointer;

    list->sortByAddress = sortByAddress;
    list->sortByValue = sortByValue;
    list->sortBySize = sortBySize;

    return EXIT_SUCCESS;
}
