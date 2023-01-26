#include <gtest/gtest.h>
#include <stdlib.h>
#include <cstdint>
extern "C"
{
#include "linked_list.h"
}

LINKED_LIST *setupList()
{
    LINKED_LIST *list = (LINKED_LIST *)malloc(sizeof(LINKED_LIST));
    setupLinkedList(list);

    for (size_t idx = 0; idx < 5; idx++)
    {
        int *data = (int *)malloc(sizeof(int));
        *data = idx * 5;
        list->insert(list, idx, data, sizeof(int));
    }
    return list;
}

TEST(linked_list, setLength_withValidLength_returnsSuccess)
{
    LINKED_LIST *list = setupList();
    list->setLength(list, 6);
    EXPECT_EQ(list->length, (size_t)6);
    EXPECT_EQ(list->isEmpty, (size_t)0);

    list->clear(list);
    free(list);
}

TEST(linked_list, insert_atValidPosition_returnsSuccess)
{
    LINKED_LIST *list = setupList();

    int *data = (int *)malloc(sizeof(int));
    *data = 500;
    uint8_t result = list->insert(list, 0, data, sizeof(int));

    EXPECT_EQ(result, (uint8_t)EXIT_SUCCESS);
    EXPECT_EQ(list->length, (size_t)6);
    int newData = *(int *)list->getByIndex(list, 0);
    EXPECT_EQ(newData, 500);

    list->clear(list);
    free(list);
}
TEST(linked_list, insert_atInvalidPosition_returnsFailure)
{
    LINKED_LIST *list = setupList();

    int *data = (int *)malloc(sizeof(int));
    *data = 500;
    uint8_t result = list->insert(list, 8, data, sizeof(int));
    EXPECT_EQ(result, (uint8_t)EXIT_FAILURE);

    list->clear(list);
    free(list);
}
TEST(linked_list, insertBefore_atValidPosition_returnsSuccess)
{
    LINKED_LIST *list = setupList();

    int *data1 = (int *)malloc(sizeof(int));
    *data1 = 500;
    uint8_t result = list->insertBefore(list, 0, data1, sizeof(int));

    int *data2 = (int *)malloc(sizeof(int));
    *data2 = 200;
    list->insertBefore(list, 3, data2, sizeof(int));

    EXPECT_EQ(result, (uint8_t)EXIT_SUCCESS);
    EXPECT_EQ(*(int *)list->getByIndex(list, 0), 500);
    EXPECT_EQ(*(int *)list->getByIndex(list, 3), 200);

    list->clear(list);
    free(list);
}
TEST(linked_list, insertBefore_atInvalidPosition_returnsFailure)
{
    LINKED_LIST *list = setupList();

    int *data1 = (int *)malloc(sizeof(int));
    *data1 = 500;
    uint8_t result = list->insertBefore(list, 10, data1, sizeof(int));

    EXPECT_EQ(result, (uint8_t)EXIT_FAILURE);

    list->clear(list);
    free(list);
}
TEST(linked_list, insertAfter_atValidPosition_returnsSuccess)
{
    LINKED_LIST *list = setupList();

    int *data1 = (int *)malloc(sizeof(int));
    *data1 = 500;
    uint8_t result = list->insertAfter(list, 0, data1, sizeof(int));

    int *data2 = (int *)malloc(sizeof(int));
    *data2 = 200;
    list->insertAfter(list, 3, data2, sizeof(int));

    EXPECT_EQ(result, (uint8_t)EXIT_SUCCESS);
    EXPECT_EQ(*(int *)list->getByIndex(list, 1), 500);
    EXPECT_EQ(*(int *)list->getByIndex(list, 4), 200);

    list->clear(list);
    free(list);
}
TEST(linked_list, insertAfter_atInvalidPosition_returnsFailure)
{
    LINKED_LIST *list = setupList();

    int *data1 = (int *)malloc(sizeof(int));
    *data1 = 500;
    uint8_t result = list->insertAfter(list, 10, data1, sizeof(int));

    EXPECT_EQ(result, (uint8_t)EXIT_FAILURE);

    list->clear(list);
    free(list);
}

TEST(linked_list, append_returnsSuccess)
{
    LINKED_LIST *list = setupList();

    int *data1 = (int *)malloc(sizeof(int));
    *data1 = 500;
    uint8_t result = list->append(list, data1, sizeof(int));

    EXPECT_EQ((int *)list->getByIndex(list, 5), data1);
    EXPECT_EQ(list->length, (size_t)6);
    EXPECT_EQ(result, (uint8_t)EXIT_SUCCESS);

    list->clear(list);
    free(list);
}

TEST(linked_list, removeAtPosition_atValidPosition_returnsSuccess)
{
    LINKED_LIST *list = setupList();

    uint8_t result = list->removeAtPosition(list, 3);

    EXPECT_EQ(result, (uint8_t)EXIT_SUCCESS);
    EXPECT_EQ(list->length, (size_t)4);
    EXPECT_EQ(*(int *)list->getByIndex(list, 3), 20);

    list->clear(list);
    free(list);
}
TEST(linked_list, removeAtPosition_atInvalidPosition_returnsFailure)
{
    LINKED_LIST *list = setupList();

    uint8_t result = list->removeAtPosition(list, 10);

    EXPECT_EQ(result, (uint8_t)EXIT_FAILURE);
    EXPECT_EQ(list->length, (size_t)5);
    EXPECT_EQ(*(int *)list->getByIndex(list, 3), 15);

    list->clear(list);
    free(list);
}
TEST(linked_list, removeAtValue_withExistingValue_returnsSuccess)
{
    LINKED_LIST *list = setupList();

    void *data = list->getByIndex(list, 3);

    uint8_t result = list->removeAtValue(list, data);

    EXPECT_EQ(result, (uint8_t)EXIT_SUCCESS);
    EXPECT_EQ(list->length, (size_t)4);
    EXPECT_EQ(*(int *)list->getByIndex(list, 3), 20);

    list->clear(list);
    free(list);
}
TEST(linked_list, removeAtValue_withNonExistingValue_returnsFailure)
{
    LINKED_LIST *list = setupList();

    void *data = list->getByIndex(list, 10);

    uint8_t result = list->removeAtValue(list, data);

    EXPECT_EQ(result, (uint8_t)EXIT_FAILURE);
    EXPECT_EQ(list->length, (size_t)5);
    EXPECT_EQ(*(int *)list->getByIndex(list, 3), 15);

    list->clear(list);
    free(list);
}

TEST(linked_list, clear_returnsSuccess)
{
    LINKED_LIST *list = setupList();

    uint8_t result = list->clear(list);

    EXPECT_EQ(result, (uint8_t)EXIT_SUCCESS);
    EXPECT_EQ(list->length, (size_t)0);
    EXPECT_EQ((uint64_t)list->head, (uint64_t)NULL);
    EXPECT_EQ((uint64_t)list->tail, (uint64_t)NULL);

    list->clear(list);
    free(list);
}
TEST(linked_list, contains_withExistingValue_returnsSuccess)
{
    LINKED_LIST *list = setupList();

    void *data = list->getByIndex(list, 3);
    uint8_t listContains = list->contains(list, data);

    EXPECT_EQ(listContains, (uint8_t)1);

    list->clear(list);
    free(list);
}
TEST(linked_list, contains_withNonExistingValue_returnsFailure)
{
    LINKED_LIST *list = setupList();

    void *data = list->getByIndex(list, 10);
    uint8_t listContains = list->contains(list, data);

    EXPECT_EQ(listContains, (uint8_t)0);

    list->clear(list);
    free(list);
}
TEST(linked_list, replace_withValidPosition_returnsSuccess)
{
    LINKED_LIST *list = setupList();

    int *data = (int *)malloc(sizeof(int));
    *data = 300;
    uint8_t result = list->replace(list, 3, data, sizeof(int));

    EXPECT_EQ(result, (uint8_t)EXIT_SUCCESS);
    EXPECT_EQ(*(int *)list->getByIndex(list, 3), 300);

    list->clear(list);
    free(list);
}
TEST(linked_list, replace_withInvalidPosition_returnsFailure)
{
    LINKED_LIST *list = setupList();

    int *data = (int *)malloc(sizeof(int));
    *data = 300;
    uint8_t result = list->replace(list, 10, data, sizeof(int));

    EXPECT_EQ(result, (uint8_t)EXIT_FAILURE);
    EXPECT_EQ(*(int *)list->getByIndex(list, 3), 15);

    list->clear(list);
    free(list);
}

TEST(linked_list, getNodeByIndex_atValidPosition_returnsNode)
{
    LINKED_LIST *list = setupList();

    NODE *node = list->getNodeByIndex(list, 3);

    EXPECT_EQ(*(int *)node->data, 15);

    list->clear(list);
    free(list);
}
TEST(linked_list, getNodeByIndex_atInvalidPosition_returnsNull)
{
    LINKED_LIST *list = setupList();

    NODE *node = list->getNodeByIndex(list, 10);

    EXPECT_EQ(node, (NODE *)NULL);

    list->clear(list);
    free(list);
}
TEST(linked_list, getNodeByValue_withExistingValue_returnsNode)
{
    LINKED_LIST *list = setupList();

    void *data = list->getByIndex(list, 3);
    NODE *node = list->getNodeByValue(list, data);

    EXPECT_EQ(*(int *)node->data, 15);

    list->clear(list);
    free(list);
}
TEST(linked_list, getNodeByValue_withNonExistingValue_returnsNull)
{
    LINKED_LIST *list = setupList();

    void *data = list->getByIndex(list, 10);
    NODE *node = list->getNodeByValue(list, data);

    EXPECT_EQ(node, (NODE *)NULL);

    list->clear(list);
    free(list);
}
TEST(linked_list, getByIndex_withValidIndex_returnsPointer)
{
    LINKED_LIST *list = setupList();

    int data = *(int *)list->getByIndex(list, 3);
    EXPECT_EQ(data, 15);

    list->clear(list);
    free(list);
}
TEST(linked_list, getByIndex_withInvalidIndex_returnsNull)
{
    LINKED_LIST *list = setupList();

    int *data = (int *)list->getByIndex(list, 10);
    EXPECT_EQ(data, (int *)NULL);

    list->clear(list);
    free(list);
}
TEST(linked_list, indexOf_withExistingValue_returnsIndex)
{
    LINKED_LIST *list = setupList();

    void *data = list->getByIndex(list, 3);
    size_t index = list->indexOf(list, data);

    EXPECT_EQ(index, (size_t)3);

    list->clear(list);
    free(list);
}
TEST(linked_list, indexOf_withNonExistingValue_returnsSentinel)
{
    LINKED_LIST *list = setupList();

    void *data = list->getByIndex(list, 10);
    size_t index = list->indexOf(list, data);

    EXPECT_EQ(index, (size_t)-1);

    list->clear(list);
    free(list);
}

TEST(linked_list, sortByAddress_withValidInput_yieldsSortedList)
{
    LINKED_LIST *list = setupList();

    int *data = (int *)malloc(sizeof(int));
    *data = 500;
    list->insert(list, 0, data, sizeof(int));

    list->sortByAddress(list);

    void *prevPtr = nullptr;
    for (size_t idx = 0; idx < list->length; idx++)
    {
        void *curPtr = list->getByIndex(list, idx);
        EXPECT_GT(curPtr, prevPtr);
        prevPtr = curPtr;
    }
}

TEST(linked_list, sortBySize_withValidInput_yieldsSortedList)
{
    LINKED_LIST *list = setupList();

    int *data = (int *)malloc(sizeof(int));
    *data = 500;
    list->insert(list, 0, data, 5000);

    list->sortBySize(list);

    int expectedData[8] = {20, 15, 10, 5, 0, 500};
    for (size_t idx = 0; idx < list->length; idx++)
    {
        int resultData = *(int *)list->getByIndex(list, idx);
        EXPECT_EQ(expectedData[idx], resultData);
    }
}

TEST(linked_list, sortByValue_withValidInput_yieldsSortedList)
{
    LINKED_LIST *list = setupList();

    int *data = (int *)malloc(sizeof(int));
    *data = 500;
    list->insert(list, 0, data, 5000);

    list->sortByValue(list);

    int expectedData[8] = {0, 5, 10, 15, 20, 500};
    for (size_t idx = 0; idx < list->length; idx++)
    {
        int resultData = *(int *)list->getByIndex(list, idx);
        EXPECT_EQ(expectedData[idx], resultData);
    }
}