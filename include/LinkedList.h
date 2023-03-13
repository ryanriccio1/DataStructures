#pragma once
#include <stdint.h>
#include <stddef.h>

#include "Node.h"

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

typedef enum DataType
{
    String,
    Int8,
    Int16,
    Int32,
    Int64,
    Uint8,
    Uint16,
    Uint32,
    Uint64,
    Double,
    Float,
    Pointer
} DataType;

/**
 * @brief Linked list implementation
 *
 */
typedef struct LinkedList
{
    uint8_t isEmpty;

    Node *head;
    Node *tail;
    DataType dataType;
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

    Node *(*getNodeByIndex)(struct LinkedList *list, size_t position);
    Node *(*getNodeByValue)(struct LinkedList *list, void *value);
    void *(*getByIndex)(struct LinkedList *list, size_t position);
    size_t (*indexOf)(struct LinkedList *list, void *value);

    void (*print)(struct LinkedList *list);

    void (*sortByAddress)(struct LinkedList *list);
    void (*sortByValue)(struct LinkedList *list);
    void (*sortBySize)(struct LinkedList *list);

} LinkedList;

/**
 * @brief Set the Length object
 *
 * @param list List to perform operation on
 * @param length Length of list to update to
 */
void setLength(LinkedList *list, size_t length);

/**
 * @brief Insert data at given index
 *
 * @param list List to perform operation on
 * @param newPosition Position to insert data into
 * @param newData Data to insert into index
 * @param dataSize Size of data to insert (can be used for precedence sorting too)
 * @return uint8_t
 */
uint8_t insert(LinkedList *list, size_t newPosition, void *newData, size_t dataSize);
/**
 * @brief Insert data before given index
 *
 * @param list List to perform operation on
 * @param index Index to use in insert
 * @param newData Data to insert
 * @param dataSize Size of data to insert (can be used for precedence sorting too)
 * @return uint8_t
 */
uint8_t insertBefore(LinkedList *list, size_t index, void *newData, size_t dataSize);
/**
 * @brief Insert data after given index
 *
 * @param list List to perform operation on
 * @param index Index to use in insert
 * @param newData Data to insert
 * @param dataSize Size of data to insert (can be used for precedence sorting too)
 * @return uint8_t
 */
uint8_t insertAfter(LinkedList *list, size_t index, void *newData, size_t dataSize);

/**
 * @brief Add item to end of list
 *
 * @param list List to perform operation on
 * @param newData Data to append to list
 * @param dataSize Size of data to insert (can be used for precedence sorting too)
 * @return uint8_t
 */
uint8_t append(LinkedList *list, void *newData, size_t dataSize);

/**
 * @brief Remove item at index
 *
 * @param list List to perform operation on
 * @param position Position of item to remove
 * @param deallocatePointer Set flag to 1 to deallocate
 * @return uint8_t
 */
uint8_t removeAtPosition(LinkedList *list, size_t position, DeallocateFlag deallocatePointer);
/**
 * @brief Search for first occurance of a pointer to remove
 *
 * @param list List to perform operation on
 * @param value Will search to see if pointers are the same, if we can find a pointer in our list, remove it
 * @param deallocatePointer Set flag to 1 to deallocate
 * @return uint8_t
 */
uint8_t removeAtValue(LinkedList *list, void *value, DeallocateFlag deallocatePointer);

/**
 * @brief Free all data and nodes in list
 *
 * @param list List to perform operation on
 * @return uint8_t
 */
uint8_t clear(LinkedList *list);
/**
 * @brief Search for first occurance of pointer in list
 *
 * @param list List to perform operation on
 * @param data Performs pointer comparison using this pointer
 * @return uint8_t
 */
uint8_t contains(LinkedList *list, void *data);
/**
 * @brief Replace the data at a given position with new data
 *
 * @param list List to perform operation on
 * @param position Position to replace data of
 * @param data Data to insert
 * @param dataSize New data size
 * @return uint8_t
 */
uint8_t replace(LinkedList *list, size_t position, void *data, size_t dataSize);

/**
 * @brief Get the Node pointer by its index
 *
 * @param list List to perform operation on
 * @param position Position to search for node at
 * @return Node*
 */
Node *getNodeByIndex(LinkedList *list, size_t position);
/**
 * @brief Search for first occurance of data and return the node
 *
 * @param list List to perform operation on
 * @param value Uses pointer comparison to see if pointer exists in list
 * @return Node*
 */
Node *getNodeByValue(LinkedList *list, void *value);
/**
 * @brief Return pointer to data referenced at index
 *
 * @param list List to perform operation on
 * @param position Index to use
 * @return void*
 */
void *getByIndex(LinkedList *list, size_t position);
/**
 * @brief Get the index of a value by its pointer
 *
 * @param list List to perform operation on
 * @param value Pointer to search for in list
 * @return size_t
 */
size_t indexOf(LinkedList *list, void *value);

/**
 * @brief Print list data
 *
 * @param list List to perform operation on
 */
void print(LinkedList *list);

/**
 * @brief Merge sort by address
 *
 * @param list List to perform operation on
 */
void sortByAddress(LinkedList *list);
/**
 * @brief Merge sort by value
 *
 * @param list List to perform operation on
 */
void sortByValue(LinkedList *list);
/**
 * @brief Merge sort by size
 *
 * @param list List to perform operation on
 */
void sortBySize(LinkedList *list);

/**
 * @brief Recursive merge function
 *
 * @param first First node to compare
 * @param second Second node to compare
 * @param compareFunc Type of comparison for merge
 * @return Node*
 */
Node *merge(LinkedList *list, Node *first, Node *second, MergeSortComparison compareFunc);
/**
 * @brief Recursive sorting algorithm
 *
 * @param head Starting pointer for mergeSort
 * @param compareFunc Type of comparison for merge
 * @return Node*
 */
Node *mergeSort(LinkedList *list, Node *head, MergeSortComparison compareFunc);
/**
 * @brief Get the pointer to the middle node and unlink chain
 *
 * @param head Starting location to calculate split location from
 * @return Node*
 */
Node *split(Node *head);
/**
 * @brief Swap two pointers
 *
 * @param A First pointer
 * @param B Second pointer
 */
void swap(void *A, void *B);
/**
 * @brief Compare two items.
 *
 * @param dataType Data type of items to compare
 * @param A Pointer of first item to compare
 * @param B Pointer of second item to compare
 */
uint8_t compare(DataType dataType, void *A, void *B);

/**
 * @brief Initialize memory at given list
 *
 * @param list List to setup
 * @param dataType Type of data being stored in list
 * @return uint8_t
 */
uint8_t setupLinkedList(LinkedList *list, DataType dataType);
