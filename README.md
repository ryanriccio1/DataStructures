# C DATA STRUCTURES

### This projects allows the utilization of doubly Linked List, Queue, and Stack Structures.

## LINKED LIST
This library is a full implementation of a doubly linked list.<br>
To create a new linked list:
```c
#include "linked_list.h"

LINKED_LIST *list = (STACK *)malloc(sizeof(LINKED_LIST));
setupList(list);
```
The data in the list should be dynamically allocated as well. The programmer can select whether the data is deallocated on removal from the list or not. 

## STACK
This library is a full implementation of a Stack structure (First In/Last Out).<br>
To create a new stack:
```c
#include "stack.h"

STACK *stack = (STACK *)malloc(sizeof(STACK));
setupStack(stack);
```
Data being pushed on the stack should be dynamically allocated before being pushed on the stack. Data is not deallocated when it is popped off the stack.

## QUEUE
This library is a full implementation of a Queue structure (First In/First Out).<br>
To create a new queue:
```c
#include "queue.h"

QUEUE *queue = (QUEUE *)malloc(sizeof(QUEUE));
setupQueue(queue);
```
The data in the queue should be dynamically allocated as well before being enqueued. Data is not deallocated when it is dequeued.


### NESTED LIST
Both the stack and queue libraries allow the programmer to have access to the underlying linked list. There is a pointer to the linked list stored in each of the data structures.

For example:
```c
queue->list->printInt(queue->list);
```