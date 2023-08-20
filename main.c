#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linkedlist.h"

#define LIST_TAG int_list
#define LIST_ITEM_TYPE int
#include "genericlist.h"


#define ARRAYLIST_TAG int_arraylist
#define ARRAYLIST_ITEM_TYPE int
#include "genericArrayList.h"

#define ARRAYLIST_TAG 

// int generic linked list tests

void appendTest() {
    printf("appendTest:");
    struct int_list ll = { .next = NULL, .value = 0 };

    // test appending to list
    // starting  {0} -> NULL
    // expecting {0} -> {1} -> NULL 
    // printf("list 1: ");
    // int_list_printList(&ll);
    int ret = int_list_appendValue(&ll, 1);

    assert(ret == 0);
    assert(ll.value == 0);
    assert(ll.next != NULL);
    assert(ll.next->value == 1);
    assert(ll.next->next == NULL);

    if (
        ret == 0 &&
        ll.value == 0 &&
        ll.next != NULL &&
        ll.next->value == 1 &&
        ll.next->next == NULL 
    ) {
        printf("passed\n");
        free(ll.next);
    } else {
        printf("failed\n");
    }
}

void freeTest() {
    printf("freeTest:");
    struct int_list ll = { .next = NULL, .value = 0 };
    int_list_appendValue(&ll, 1);

    // test to free last entry
    // starting  {0} -> {1} -> NULL 
    // expecting {0} -> NULL
    // printf("list 1: ");
    // int_list_printList(&ll);
    int ret = int_list_removeLast(&ll);
    // printf("list 1: ");
    // int_list_printList(&ll);

    if (
        ret == 0 &&
        ll.value == 0 &&
        ll.next == NULL
    ) {
        printf("passed\n");
    } else {
        printf("failed\n");
    }
}

void concatTest() {
    printf("concatTest:");
    struct int_list ll = { .next = NULL, .value = 0 };
    struct int_list ll2 = { .next = NULL, .value = 1 };
    int_list_appendValue(&ll2, 2);

    // test to concat two lists
    // starting
    // {0} -> NULL
    // {1} -> {2} -> NULL
    // expecting {0} -> {1} -> {2} -> NULL
    // printf("list 1: ");
    // int_list_printList(&ll);
    // printf("list 2: ");
    // int_list_printList(&ll2);

    int ret = int_list_appendValue(&ll2, 2);
    int ret2 = int_list_concat(&ll, &ll2);

    // printf("list 1: ");
    // int_list_printList(&ll);
    // printf("list 2: ");
    // int_list_printList(&ll2);

    if (
        ret == 0 &&
        ret2 == 0 &&
        ll.value == 0 &&
        ll.next != NULL &&
        ll.next->value == 1 &&
        ll.next->next != NULL &&
        ll.next->next->value == 2
    ) {
        printf("passed\n");
        int_list_removeLast(&ll2);
    } else {
        printf("failed\n");
    }
}

void getAtTest() {
    printf("getAtTest:");
    struct int_list ll = { .next = NULL, .value = 0 };
    int_list_appendValue(&ll, 1);
    int_list_appendValue(&ll, 2);

    // test to get node at index
    // starting
    // index 1
    // {0} -> {1} -> {2} -> NULL
    // expecting {1}
    int index = 1;
    struct int_list* resultNode = int_list_getAt(&ll, index);
    // int_list_printList(&ll);

    if (
        resultNode != NULL &&
        resultNode->value == 1
    ) {
        printf("passed\n");
    } else {
        printf("failed\n");
        printf("resultNode != NULL: %d\n", resultNode == NULL);
        if (resultNode != NULL) {
            printf("resultNode->value == 1: %d\n", resultNode->value == 1);
            int_list_removeLast(&ll);
            int_list_removeLast(&ll);
        } else {
            printf("resultNode->value == 1: 0\n");
        }
    }
}

void func1 (int* v) {
    (*v)++;
}
void iterApplyTest() {
    printf("iterApplyTest:");
    struct int_list ll = { .next = NULL, .value = 0 };
    int_list_appendValue(&ll, 1);
    int_list_appendValue(&ll, 2);
    
    // test to apply func to list
    // starting
    // apply (int* v) => {*v++;}
    // {0} -> {1} -> {2} -> NULL
    // expecting
    // {1} -> {2} -> {3} -> NULL
    int_list_iterApply(&ll, func1);

    if (
        ll.value == 1 &&
        ll.next != NULL &&
        ll.next->value == 2 &&
        ll.next->next != NULL &&
        ll.next->next->value == 3
    ) {
        printf("passed\n");
        int_list_removeLast(&ll);
        int_list_removeLast(&ll);
    } else {
        printf("failed\n");
    }
}

void detectCycleTest() {
    printf("detectCycleTest:");
    struct int_list ll = { .next = NULL, .value = 0 };
    int_list_appendValue(&ll, 1);
    int_list_appendValue(&ll, 2);
    int_list_appendValue(&ll, 3);
    int_list_concat(&ll, &ll);

    // test to detect cycle in a list
    // starting
    // {0} -> {1} -> {2} -> {0}
    // expecting cycle detected

    int ret = int_list_detectCycle(&ll);

    if (ret) {
        printf("passed\n");
    } else {
        printf("failed\n");
    }
}

void toArrayTest() {
    printf("iterApplyTest:");
    struct int_list ll = { .next = NULL, .value = 0 };
    int_list_appendValue(&ll, 1);
    int_list_appendValue(&ll, 2);

    // test to create array from list
    // starting
    // {0} -> {1} -> {2} -> NULL
    // expecting
    // [0,1,2]
    struct int_list_Array* ll_array = int_list_toArray(&ll);

    if (
        ll_array != NULL &&
        ll_array->data[0] == 0 &&
        ll_array->data[1] == 1 &&
        ll_array->data[2] == 2
    ) {
        printf("passed\n");
        free(ll_array->data);
        free(ll_array);
        int_list_removeLast(&ll);
        int_list_removeLast(&ll);
    } else {
        printf("failed\n");
        printf("%d\n", ll_array->data[0]);        
        printf("%d\n", ll_array->data[1]);
        printf("%d\n", ll_array->data[2]);
    }
}

void testGenericLinkedList() {
    appendTest();
    freeTest();
    concatTest();
    getAtTest();
    iterApplyTest();
    detectCycleTest();
    toArrayTest();
}

// int normal linked list tests

void testLinkedList() {

    // test appending to list
    // starting  {0} -> NULL
    // expecting {0} -> {1} -> NULL 
    Node ll = { .next = NULL, .value = 0 };
    int ret = appendValue(&ll, 1);

    if (
        ret == 0 &&
        ll.value == 0 &&
        ll.next != NULL &&
        ll.next->value == 1 &&
        ll.next->next == NULL 
    ) {
        printf("LL Append1 passed\n");
    } else {
        printf("LL Append1 failed\n");
    }

    // test to free last entry
    // starting  {0} -> {1} -> NULL 
    // expecting {0} -> NULL
    ret = removeLast(&ll);

    if (
        ret == 0 &&
        ll.value == 0 &&
        ll.next == NULL
    ) {
        printf("LL RemoveLast1 passed\n");
    } else {
        printf("LL RemoveLast1 failed\n");
    }

    // test to concat two lists
    // starting
    // {0} -> NULL
    // {1} -> {2} -> NULL
    // expecting {0} -> {1} -> {2} -> NULL
    ret = 0;
    Node ll2 = {.next = NULL, .value = 1};
    ret += appendValue(&ll2, 2);
    ret += concat(&ll, &ll2);

    if (
        ret == 0 &&
        ll.value == 0 &&
        ll.next != NULL &&
        ll.next->value == 1 &&
        ll.next->next != NULL &&
        ll.next->next->value == 2
    ) {
        printf("LL Concat1 passed\n");
    } else {
        printf("LL Concat1 failed\n");
    }
}

// int Arraylist test
void IntArraylist_createTest() {
    printf("createTest:");
    int capacity = 5;
    struct int_arraylist* al = int_arraylist_create(capacity);
    assert(al != NULL);
    assert(al->capacity == 5);
    assert(al->length == 0);
    assert(al->data != NULL);
    assert(*(al->data) == 0);
    assert(*(al->data + 1) == 0);
    assert(*(al->data + 2) == 0);
    assert(*(al->data + 3) == 0);
    assert(*(al->data + 4) == 0);
    int_arraylist_free(al);
    printf("passed\n");
}

void IntArraylist_pushTest() {
    printf("pushTest:");
    int capacity = 5;
    struct int_arraylist* al = int_arraylist_create(capacity);
    assert(int_arraylist_push(al, 3) == 0);
    assert(al->capacity == 5);
    assert(al->length == 1);
    assert(*(al->data) == 3);
    assert(*(al->data + 1) == 0);
    assert(*(al->data + 2) == 0);
    assert(*(al->data + 3) == 0);
    assert(*(al->data + 4) == 0);
    int_arraylist_free(al);

    al = int_arraylist_create(1);

    assert(al->capacity == 1);

    int_arraylist_push(al, 1);
    int_arraylist_push(al, 2);
    
    assert(al->capacity == 2);
    assert(al->length == 2);

    int_arraylist_push(al, 3);

    assert(al->capacity == 4);
    assert(al->length == 3);

    int_arraylist_free(al);

    printf("passed\n");
}

void IntArraylist_popTest() {
    printf("popTest:");
    int capacity = 3;
    struct int_arraylist* al = int_arraylist_create(capacity);
    int_arraylist_push(al, 3);
    int_arraylist_push(al, 4);
    int_arraylist_push(al, 5);
    assert(al->capacity == capacity);
    assert(al->length == 3);
    assert(*(al->data) == 3);
    assert(*(al->data + 1) == 4);
    assert(*(al->data + 2) == 5);
    assert(5 == int_arraylist_pop(al));
    assert(al->capacity == capacity);
    assert(al->length == 2);
    assert(*(al->data) == 3);
    assert(*(al->data + 1) == 4);
    assert(*(al->data + 2) == 0);
    assert(4 == int_arraylist_pop(al));
    assert(al->length == 1);
    assert(*(al->data) == 3);
    assert(*(al->data + 1) == 0);
    assert(*(al->data + 2) == 0);
    assert(3 == int_arraylist_pop(al));
    assert(al->length == 0);
    assert(*(al->data) == 0);
    assert(*(al->data + 1) == 0);
    assert(*(al->data + 2) == 0);
    int_arraylist_free(al);
    printf("passed\n");
}

void IntArraylist_setAtTest() {
    printf("setAtTest:");
    int capacity = 5;
    struct int_arraylist* al = int_arraylist_create(capacity);
    for (int i = 0; i < capacity; i++) {
        int_arraylist_push(al, i);
    }
    assert(al->capacity == capacity);
    assert(al->length == capacity);
    assert(int_arraylist_setAt(al, 0, 1) == 0);
    assert(*(al->data + 0) == 1);
    assert(int_arraylist_setAt(al, 1, 2) == 0);
    assert(*(al->data + 1) == 2);
    assert(int_arraylist_setAt(al, 4, 0) == 0);
    assert(*(al->data + 4) == 0);
    int_arraylist_free(al);
    printf("passed\n");
}

void IntArraylist_getAtTest() {
    printf("getAtTest:");
    int capacity = 5;
    struct int_arraylist* al = int_arraylist_create(capacity);
    for (int i = 0; i < capacity; i++) {
        int_arraylist_push(al, i);
        assert(*(al->data + i) == int_arraylist_getAt(al, i));
    }
    int_arraylist_free(al);
    printf("passed\n");
}

int cmp(int a, int b) {
    return a - b;
}
void testIntArraylist_binsearch() {
    printf("binsearchTest:");
    int capacity = 5;
    struct int_arraylist* al = int_arraylist_create(capacity);
    assert(int_arraylist_binsearch(al, 6, cmp) == -1);
    for (int i = 0; i < capacity; i++) {
        int_arraylist_push(al, i);
        assert(int_arraylist_binsearch(al, i, cmp) == i);
    }
    assert(int_arraylist_binsearch(al, 6, cmp) == -1);
    printf("passed\n");
}

void testIntArraylist() {
    IntArraylist_createTest();
    IntArraylist_pushTest();
    IntArraylist_popTest();
    IntArraylist_setAtTest();
    IntArraylist_getAtTest();
    testIntArraylist_binsearch();
}

int main() {
    // testLinkedList();
    testGenericLinkedList();
    testIntArraylist();
}