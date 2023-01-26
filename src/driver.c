#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "console_util.h"

int main()
{
    LINKED_LIST list;
    setupLinkedList(&list);
    // char *data = NULL;
    // for (size_t i = 0; i < 3; i++)
    // {
    //     printf("Enter something to add to list: ");
    //     data = get_line_dynamic();
    //     list.insert(&list, i, data, sizeof(data));
    // }
    char *testData1 = (char *)malloc(sizeof(char) * 24);
    strcpy(testData1, "this is a test2");
    list.insert(&list, 0, testData1, sizeof(testData1));

    char *testData2 = (char *)malloc(sizeof(char) * 24);
    strcpy(testData2, "this is a test4");
    list.insert(&list, 1, testData2, sizeof(testData2));

    char *testData3 = (char *)malloc(sizeof(char) * 24);
    strcpy(testData3, "this is a test1");
    list.insertAfter(&list, 1, testData3, sizeof(testData3));

    char *testData4 = (char *)malloc(sizeof(char) * 24);
    strcpy(testData4, "this is a test0");
    list.insertBefore(&list, 2, testData4, sizeof(testData4));

    // char *storedData = list.getByIndex(&list, 0);

    // printf("HEAD: %s\tLENGTH:%lld\n", storedData, list.length);
    list.printString(&list);
    list.printPointer(&list);
    list.sortByAddress(&list);
    list.printString(&list);
    list.clear(&list);
    // printf("CLEARED!\tLENGTH=%lld", list.length);
}