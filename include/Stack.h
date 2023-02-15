#ifndef STACK_H
#define STACK_H
#include "LinkedList.h"
#include <stdint.h>

/**
 * @brief Stack implementation
 *
 */
typedef struct Stack
{
    LinkedList *list;

    uint8_t (*push)(struct Stack *stack, void *data, size_t dataSize);
    void *(*pop)(struct Stack *stack);
    void *(*peekStack)(struct Stack *stack);

    uint8_t (*cleanStack)(struct Stack *stack);
} Stack;

/**
 * @brief Put data onto stack
 *
 * @param stack Stack to perform operation on
 * @param data Data to put on stack
 * @param dataSize Size of data being put on stack
 * @return uint8_t
 */
uint8_t push(Stack *stack, void *data, size_t dataSize);

/**
 * @brief Get the data from the stack and remove it
 *
 * @param stack Stack to perform operation on
 * @return void*
 */
void *pop(Stack *stack);

/**
 * @brief Get the data from the top of the stack without removing it
 *
 * @param stack Stack to perform operation on
 * @return void*
 */
void *peekStack(Stack *stack);

/**
 * @brief Clean all data inside stack
 *
 * @param stack Stack to perform operation on
 * @return uint8_t
 */
uint8_t cleanStack(Stack *stack);

/**
 * @brief Setup and initialize all data needed for stack
 *
 * @param stack Stack to perform operation on
 * @return uint8_t
 */
uint8_t setupStack(Stack *stack);

#endif