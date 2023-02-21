# Sections
1. [Linked List Functions](#linked-list-functions)
1. [Stack Functions](#stack-functions)
1. [Queue Functions](#queue-functions)
1. [Node Functions](#node-functions)
<br>

# Linked List Functions

Member Variables
```c
uint8_t isEmpty (bool)
size_t length;
```

`void setLength(LinkedList *list, size_t length);` 
<br>
Manually override the length of the list. Shortening the list will not remove the links to nodes in the list, but it will shorten the list when traversing the list. It will automatically update the `isEmpty` flag when the length is changed.

`uint8_t insert(LinkedList *list, size_t newPosition, void *newData, size_t dataSize);`
<br>
Inserts new node containing pointer to allocated data at an index in the linked list. Data size can be used later when referencing the data either to sort by size or when storing a pointer to an array.

`uint8_t insertBefore(LinkedList *list, size_t index, void *newData, size_t dataSize);`
<br>
Same as insert, just semantically different.

`uint8_t insertAfter(LinkedList *list, size_t index, void *newData, size_t dataSize);`
<br>
Insert at a position after an index. For example, inserting after index 4 will insert at index 5.

`uint8_t append(LinkedList *list, void *newData, size_t dataSize);`
<br>
Add a new node pointing to allocated data at the end of the linked list. 

`uint8_t removeAtPosition(LinkedList *list, size_t position, DeallocateFlag deallocatePointer);`
<br>
Remove a node from the list based on its position. `deallocatePointer` can either be `KeepAllocated` or `Deallocate` depending on how the list should handle the removed data.

`uint8_t removeAtValue(LinkedList *list, void *value, DeallocateFlag deallocatePointer);`
<br>
Remove a node from the list based on its address. Uses pointer comparison to see if the pointer we are searching for exists in the list. `deallocatePointer` can either be `KeepAllocated` or `Deallocate` depending on how the list should handle the removed data.

`uint8_t clear(LinkedList *list);`
<br>
Deallocate all nodes and all data in the nodes for the entire list. Reset the list to empty without needed to reallocate the list. 

`uint8_t contains(LinkedList *list, void *data);`
<br>
Check to see if a pointer exists in any of our nodes in the list. Will return (size_t)-1 (64-bit INT_MAX) if value does not exist.

`uint8_t replace(LinkedList *list, size_t position, void *data, size_t dataSize);`
<br>
Replace the pointer in one of the nodes at an index rather than having to remove a node and than insert a new one. Very similar to getting a node and accessing the actual data, except more abstracted. 


`Node *getNodeByIndex(LinkedList *list, size_t position);`
<br>
Get a pointer to a node stored in the list based on its index.

`Node *getNodeByValue(LinkedList *list, void *value);`
<br>
Get a pointer to a node stored in the list based on pointer comparison (see if the pointer we want exists in the list and return that node).

`void *getByIndex(LinkedList *list, size_t position);`
<br>
Get a pointer to the data located in a node at a specific index.

`size_t indexOf(LinkedList *list, void *value);`
<br>
Get the index of the first instance of a specific pointer in a node in the list. Returns (size_t)-1 (64-bit INT_MAX) if value is not found.

`void print(LinkedList *list);`
<br>
Print the data in the list.

`void sortByAddress(LinkedList *list);`
<br>
Use merge sort to sort the data by the address. 

`void sortByValue(LinkedList *list);`
<br>
Assuming data can be cast to `int64_t *`, compare the data stored and sort using merge sort.  

`void sortBySize(LinkedList *list);`
<br>
Sort by the size stored in the node. 


# Stack Functions
`uint8_t push(Stack *stack, void *data, size_t dataSize)` 
<br> 
Put data onto the top of the stack.

`void *pop(Stack *stack)` 
<br>
Remove the data on the top of the stack and return a pointer to the data. Does not deallocate the data.

`void *peekStack(Stack *stack)` 
<br>
Gets the data on the top of the stack without removing it from the stack.

`uint8_t cleanStack(Stack *stack)` 
<br>
Deletes all data in stack.

# Queue Functions

`uint8_t enqueue(Queue *queue, void *data, size_t dataSize)`
<br>
Put data into queue.

`void *dequeue(Queue *queue)`
<br>
Removes the data on the top of the queue and return a pointer to the data. Does not deallocate the data.

`void *peekQueue(Queue *queue)` 
<br>
Gets the data on the top of the queue without removing it from the queue.

`uint8_t cleanQueue(Queue *queue)`
<br>
Deletes all data in queue.

# Node Functions

Member Variables
```c
void *data;
size_t dataSize;
```

`uint8_t cleanup(Node *node);`
<br>
Will free the memory pointed to by the node.

# Enums
Enum definitions in 'LinkedList.h'
```c
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
```
