# Sections
1. [Linked List Functions](#linked-list-functions)
1. [Stack Functions](#stack-functions)
1. [Queue Functions](#queue-functions)
<br>

# Linked List Functions

`void setLength(LINKED_LIST *list, size_t length);` 
<br>
Manually override the length of the list. Shortening the list will not remove the links to nodes in the list, but it will shorten the list when traversing the list. It will automatically update the `isEmpty` flag when the length is changed.

`uint8_t insert(LINKED_LIST *list, size_t newPosition, void *newData, size_t dataSize);`
<br>
Inserts new node containing pointer to allocated data at an index in the linked list. Data size can be used later when referencing the data either to sort by size or when storing a pointer to an array.

`uint8_t insertBefore(LINKED_LIST *list, size_t index, void *newData, size_t dataSize);`
<br>
Same as insert, just semantically different.

`uint8_t insertAfter(LINKED_LIST *list, size_t index, void *newData, size_t dataSize);`
<br>
Insert at a position after an index. For example, inserting after index 4 will insert at index 5.

`uint8_t append(LINKED_LIST *list, void *newData, size_t dataSize);`
<br>
Add a new node pointing to allocated data at the end of the linked list. 

`uint8_t removeAtPosition(LINKED_LIST *list, size_t position, DeallocateFlag deallocatePointer);`
<br>
Remove a node from the list based on its position. `deallocatePointer` can either be `KeepAllocated` or `Deallocate` depending on how the list should handle the removed data.

`uint8_t removeAtValue(LINKED_LIST *list, void *value, DeallocateFlag deallocatePointer);`
<br>
Remove a node from the list based on its address. Uses pointer comparison to see if the pointer we are searching for exists in the list. `deallocatePointer` can either be `KeepAllocated` or `Deallocate` depending on how the list should handle the removed data.

`uint8_t clear(LINKED_LIST *list);`
<br>
Deallocate all nodes and all data in the nodes for the entire list. Reset the list to empty without needed to reallocate the list. 

`uint8_t contains(LINKED_LIST *list, void *data);`
<br>
Check to see if a pointer exists in any of our nodes in the list. 

`uint8_t replace(LINKED_LIST *list, size_t position, void *data, size_t dataSize);`
<br>
Replace the pointer in one of the nodes at an index rather than having to remove a node and than insert a new one. Very similar to getting a node and accessing the actual data, except more abstracted. 


`NODE *getNodeByIndex(LINKED_LIST *list, size_t position);`
<br>
Get a pointer to a node stored in the list based on its index.

`NODE *getNodeByValue(LINKED_LIST *list, void *value);`
<br>
Get a pointer to a node stored in the list based on pointer comparison (see if the pointer we want exists in the list and return that node).

`void *getByIndex(LINKED_LIST *list, size_t position);`
<br>
Get a pointer to the data located in a node at a specific index.

`size_t indexOf(LINKED_LIST *list, void *value);`
<br>
Get the index of the first instance of a specific pointer in a node in the list. 

`void printString(LINKED_LIST *list);`
<br>
Print the data in the list as `char *`.

`void printInt(LINKED_LIST *list);`
<br>
Print the data in the list as 32-bit ints.

`void printInt64(LINKED_LIST *list);`
<br>
Print the data in the list as 64-bit ints.

`void printUint64(LINKED_LIST *list);`
<br>
Print the data in the list as 64-bit unsigned ints. 

`void printDouble(LINKED_LIST *list);`
<br>
Print the data in the list as doubles.

`void printPointer(LINKED_LIST *list);`
<br>
Print the address of the data in the list. 


`void sortByAddress(LINKED_LIST *list);`
<br>
Use merge sort to sort the data by the address. 

`void sortByValue(LINKED_LIST *list);`
<br>
Assuming data can be cast to `int64_t *`, compare the data stored and sort using merge sort.  

`void sortBySize(LINKED_LIST *list);`
<br>
Sort by the size stored in the node. 


# Stack Functions
`uint8_t push(STACK *stack, void *data, size_t dataSize)` 
<br> 
Put data onto the top of the stack.

`void *pop(STACK *stack)` 
<br>
Remove the data on the top of the stack and return a pointer to the data. Does not deallocate the data.

`void *peekStack(STACK *stack)` 
<br>
Gets the data on the top of the stack without removing it from the stack.

`uint8_t cleanStack(STACK *stack)` 
<br>
Deletes all data in stack.

# Queue Functions

`uint8_t enqueue(QUEUE *queue, void *data, size_t dataSize)`
<br>
Put data into queue.

`void *dequeue(QUEUE *queue)`
<br>
Removes the data on the top of the queue and return a pointer to the data. Does not deallocate the data.

`void *peekQueue(QUEUE *queue)` 
<br>
Gets the data on the top of the queue without removing it from the queue.

`uint8_t cleanQueue(QUEUE *queue)`
<br>
Deletes all data in queue.