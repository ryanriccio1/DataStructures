#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdint.h>
#include "node.h"

typedef enum DeallocateFlag
{
    KeepAllocated,
    Deallocate
} DeallocateFlag;

typedef enum MergeSortComparison
{
    PointerCompare,
    ValueCompare,
    SizeCompare
} MergeSortComparison;

/**
 * @brief Linked list implementation
 *
 */
typedef struct LinkedList
{
    uint8_t isEmpty;

    NODE *head;
    NODE *tail;
    size_t length;
    void (*setLength)(struct LinkedList *list, size_t length);

    uint8_t (*insert)(struct LinkedList *list, size_t newPosition, void *newData, size_t dataSize);
    uint8_t (*insertBefore)(struct LinkedList *list, size_t index, void *newData, size_t dataSize);
    uint8_t (*insertAfter)(struct LinkedList *list, size_t index, void *newData, size_t dataSize);

    uint8_t (*append)(struct LinkedList *list, void *newData, size_t dataSize);

    uint8_t (*removeAtPosition)(struct LinkedList *list, size_t position, DeallocateFlag deallocatePointer);
    uint8_t (*removeAtValue)(struct LinkedList *list, void *value, DeallocateFlag deallocatePointer);

    uint8_t (*clear)(struct LinkedList *list);
    uint8_t (*contains)(struct LinkedList *list, void *data);
    uint8_t (*replace)(struct LinkedList *list, size_t position, void *data, size_t dataSize);

    NODE *(*getNodeByIndex)(struct LinkedList *list, size_t position);
    NODE *(*getNodeByValue)(struct LinkedList *list, void *value);
    void *(*getByIndex)(struct LinkedList *list, size_t position);
    size_t (*indexOf)(struct LinkedList *list, void *value);

    void (*printString)(struct LinkedList *list);
    void (*printInt)(struct LinkedList *list);
    void (*printInt64)(struct LinkedList *list);
    void (*printUint64)(struct LinkedList *list);
    void (*printDouble)(struct LinkedList *list);
    void (*printPointer)(struct LinkedList *list);

    void (*sortByAddress)(struct LinkedList *list);
    void (*sortByValue)(struct LinkedList *list);
    void (*sortBySize)(struct LinkedList *list);

} LINKED_LIST;

/**
 * @brief Set the Length object
 *
 * @param list List to perform operation on
 * @param length Length of list to update to
 */
void setLength(LINKED_LIST *list, size_t length);

/**
 * @brief Insert data at given index
 *
 * @param list List to perform operation on
 * @param newPosition Position to insert data into
 * @param newData Data to insert into index
 * @param dataSize Size of data to insert (can be used for precedence sorting too)
 * @return uint8_t
 */
uint8_t insert(LINKED_LIST *list, size_t newPosition, void *newData, size_t dataSize);
/**
 * @brief Insert data before given index
 *
 * @param list List to perform operation on
 * @param index Index to use in insert
 * @param newData Data to insert
 * @param dataSize Size of data to insert (can be used for precedence sorting too)
 * @return uint8_t
 */
uint8_t insertBefore(LINKED_LIST *list, size_t index, void *newData, size_t dataSize);
/**
 * @brief Insert data after given index
 *
 * @param list List to perform operation on
 * @param index Index to use in insert
 * @param newData Data to insert
 * @param dataSize Size of data to insert (can be used for precedence sorting too)
 * @return uint8_t
 */
uint8_t insertAfter(LINKED_LIST *list, size_t index, void *newData, size_t dataSize);

/**
 * @brief Add item to end of list
 *
 * @param list List to perform operation on
 * @param newData Data to append to list
 * @param dataSize Size of data to insert (can be used for precedence sorting too)
 * @return uint8_t
 */
uint8_t append(LINKED_LIST *list, void *newData, size_t dataSize);

/**
 * @brief Remove item at index
 *
 * @param list List to perform operation on
 * @param position Position of item to remove
 * @param deallocatePointer Set flag to 1 to deallocate
 * @return uint8_t
 */
uint8_t removeAtPosition(LINKED_LIST *list, size_t position, DeallocateFlag deallocatePointer);
/**
 * @brief Search for first occurance of a pointer to remove
 *
 * @param list List to perform operation on
 * @param value Will search to see if pointers are the same, if we can find a pointer in our list, remove it
 * @param deallocatePointer Set flag to 1 to deallocate
 * @return uint8_t
 */
uint8_t removeAtValue(LINKED_LIST *list, void *value, DeallocateFlag deallocatePointer);

/**
 * @brief Free all data and nodes in list
 *
 * @param list List to perform operation on
 * @return uint8_t
 */
uint8_t clear(LINKED_LIST *list);
/**
 * @brief Search for first occurance of pointer in list
 *
 * @param list List to perform operation on
 * @param data Performs pointer comparison using this pointer
 * @return uint8_t
 */
uint8_t contains(LINKED_LIST *list, void *data);
/**
 * @brief Replace the data at a given position with new data
 *
 * @param list List to perform operation on
 * @param position Position to replace data of
 * @param data Data to insert
 * @param dataSize New data size
 * @return uint8_t
 */
uint8_t replace(LINKED_LIST *list, size_t position, void *data, size_t dataSize);

/**
 * @brief Get the Node pointer by its index
 *
 * @param list List to perform operation on
 * @param position Position to search for node at
 * @return NODE*
 */
NODE *getNodeByIndex(LINKED_LIST *list, size_t position);
/**
 * @brief Search for first occurance of data and return the node
 *
 * @param list List to perform operation on
 * @param value Uses pointer comparison to see if pointer exists in list
 * @return NODE*
 */
NODE *getNodeByValue(LINKED_LIST *list, void *value);
/**
 * @brief Return pointer to data referenced at index
 *
 * @param list List to perform operation on
 * @param position Index to use
 * @return void*
 */
void *getByIndex(LINKED_LIST *list, size_t position);
/**
 * @brief Get the index of a value by its pointer
 *
 * @param list List to perform operation on
 * @param value Pointer to search for in list
 * @return size_t
 */
size_t indexOf(LINKED_LIST *list, void *value);

/**
 * @brief Print list data formatted as string
 *
 * @param list List to perform operation on
 */
void printString(LINKED_LIST *list);
/**
 * @brief Print list data formatted as int
 *
 * @param list List to perform operation on
 */
void printInt(LINKED_LIST *list);
/**
 * @brief Print list data formatted as int64_t
 *
 * @param list List to perform operation on
 */
void printInt64(LINKED_LIST *list);
/**
 * @brief Print list data formatted as uint64_t
 *
 * @param list List to perform operation on
 */
void printUint64(LINKED_LIST *list);
/**
 * @brief Print list data formatted as double
 *
 * @param list List to perform operation on
 */
void printDouble(LINKED_LIST *list);
/**
 * @brief Print list data formatted as pointer
 *
 * @param list List to perform operation on
 */
void printPointer(LINKED_LIST *list);

/**
 * @brief Merge sort by address
 *
 * @param list List to perform operation on
 */
void sortByAddress(LINKED_LIST *list);
/**
 * @brief Merge sort by value
 *
 * @param list List to perform operation on
 */
void sortByValue(LINKED_LIST *list);
/**
 * @brief Merge sort by size
 *
 * @param list List to perform operation on
 */
void sortBySize(LINKED_LIST *list);

/**
 * @brief Recursive merge function
 *
 * @param first First node to compare
 * @param second Second node to compare
 * @param compareFunc Type of comparison for merge
 * @return NODE*
 */
NODE *merge(NODE *first, NODE *second, MergeSortComparison compareFunc);
/**
 * @brief Recursive sorting algorithm
 *
 * @param head Starting pointer for mergeSort
 * @param compareFunc Type of comparison for merge
 * @return NODE*
 */
NODE *mergeSort(NODE *head, MergeSortComparison compareFunc);
/**
 * @brief Get the pointer to the middle node and unlink chain
 *
 * @param head Starting location to calculate split location from
 * @return NODE*
 */
NODE *split(NODE *head);
/**
 * @brief Swap two pointers
 *
 * @param A First pointer
 * @param B Second pointer
 */
void swap(void *A, void *B);

/**
 * @brief Initialize memory at given list
 *
 * @param list List to setup
 * @return uint8_t
 */
uint8_t setupLinkedList(LINKED_LIST *list);

#endif