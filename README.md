# C DATA STRUCTURES

### This projects allows the utilization of doubly Linked List, Queue, and Stack Structures.
## BUILDING
Build using the makefile.<br>
In the main directory:
```
make
.\bin\test.exe
```
To build tests:
```
make tests
```
To clean up all build files:
```
make clean
```
## LINKED LIST
This library is a full implementation of a doubly linked list.<br>
To create a new linked list:
```c
#include "LinkedList.h"

LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
setupList(list, Int64);
```
The data in the list should be dynamically allocated as well. The programmer can select whether the data is deallocated on removal from the list or not. 

## STACK
This library is a full implementation of a Stack structure (First In/Last Out).<br>
To create a new stack:
```c
#include "Stack.h"

Stack *stack = (Stack *)malloc(sizeof(Stack));
setupStack(stack, Int64);
```
Data being pushed on the stack should be dynamically allocated before being pushed on the stack. Data is not deallocated when it is popped off the stack.

## QUEUE
This library is a full implementation of a Queue structure (First In/First Out).<br>
To create a new queue:
```c
#include "Queue.h"

Queue *queue = (Queue *)malloc(sizeof(Queue));
setupQueue(queue, Int64);
```
The data in the queue should be dynamically allocated as well before being enqueued. Data is not deallocated when it is dequeued.


### NESTED LIST
Both the stack and queue libraries allow the programmer to have access to the underlying linked list. There is a pointer to the linked list stored in each of the data structures.

For example:
```c
queue->list->print(queue->list);
```

### TESTING
Run tests using the following command.

`.\bin\run_tests.exe --gtest_color=yes`

Filters can be applied with the `--gtest_filter=` command.
For example:

`.\bin\run_tests.exe --gtest_color=yes --gtest_filter=ConsoleUtil*`