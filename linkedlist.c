#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

int concat(Node* root, Node* other) {
    if (root == NULL || other == NULL) return 1;
    while (root->next != NULL) {
        root = root->next;
    }
    root->next = other;
    return 0;
}

int listLen(Node* root) {
    int count = 0;
    while (root != NULL) {
        root = root->next;
        count++;
    }
    return count;
}

int appendValue(Node* root, int v) {
    if (root == NULL) {
        return 1;
    }
    while (root->next != NULL) {
        root = root->next;
    }
    Node* newNode = malloc(sizeof(Node));
    if (newNode == NULL) return 1;
    newNode->value = v;
    root->next = newNode;
    return 0;
}

int removeLast(Node* root) {
    if (root == NULL) return 1;
    if (root->next == NULL) {
        free(root);
        return 0;
    }
    while (root->next->next != NULL) {
        root = root->next;
    }
    free(root->next);
    root->next = NULL;
    return 0;
}