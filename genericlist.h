#include <stdio.h>
#include <stdlib.h>

#if !defined(LIST_TAG) || !defined(LIST_ITEM_TYPE)
#define LIST_TAG int_list
#define LIST_ITEM_TYPE int
// #error Missing type or tag definition
#endif

#define LIST_CONCAT(tag, method) tag##_##method
#define LIST_METHOD2(tag, method) LIST_CONCAT(tag, method)
#define LIST_METHOD(method) LIST_METHOD2(LIST_TAG, method)

struct LIST_TAG {
  LIST_ITEM_TYPE value;
  struct LIST_TAG *next;
} LIST_TAG;

struct LIST_METHOD(Array) {
    LIST_ITEM_TYPE* data;
    int length;
} LIST_METHOD(Array);

int LIST_METHOD(concat)(struct LIST_TAG *root, struct LIST_TAG *other);
int LIST_METHOD(listLen)(struct LIST_TAG *root);
int LIST_METHOD(appendValue)(struct LIST_TAG *root, LIST_ITEM_TYPE v);
int LIST_METHOD(removeLast)(struct LIST_TAG *root);
int LIST_METHOD(detectCycle)(struct LIST_TAG *root);
void LIST_METHOD(printList)(struct LIST_TAG *root);
struct LIST_TAG *LIST_METHOD(getAt)(struct LIST_TAG *root, int index);
void LIST_METHOD(iterApply)(struct LIST_TAG *root, void (*f)(LIST_ITEM_TYPE *));

int LIST_METHOD(concat)(struct LIST_TAG *root, struct LIST_TAG *other) {
  if (root == NULL || other == NULL)
    return 1;

  if (LIST_METHOD(detectCycle)(root) || LIST_METHOD(detectCycle)(other)) {
    return 1;
  }

  while (root->next != NULL) {
    root = root->next;
  }

  root->next = other;
  return 0;
}

int LIST_METHOD(listLen)(struct LIST_TAG *root) {
  if (LIST_METHOD(detectCycle)(root)) {
    return -1;
  }

  int count = 0;
  while (root != NULL) {
    root = root->next;
    count++;
  }
  return count;
}

int LIST_METHOD(appendValue)(struct LIST_TAG *root, LIST_ITEM_TYPE v) {
  if (root == NULL) {
    return 1;
  }
  while (root->next != NULL) {
    root = root->next;
  }

  if (LIST_METHOD(detectCycle)(root)) {
    return 1;
  }

  struct LIST_TAG *newObj = (struct LIST_TAG *)malloc(sizeof(struct LIST_TAG));
  if (newObj == NULL)
    return 1;
  newObj->value = v;
  newObj->next = NULL;
  root->next = newObj;
  return 0;
}

int LIST_METHOD(removeLast)(struct LIST_TAG *root) {
  if (root == NULL)
    return 1;
  if (root->next == NULL) {
    free(root);
    return 0;
  }

  if (LIST_METHOD(detectCycle)(root)) {
    return 1;
  }

  while (root->next->next != NULL) {
    root = root->next;
  }
  free(root->next);
  root->next = NULL;
  return 0;
}

int LIST_METHOD(detectCycle)(struct LIST_TAG *root) {
  if (root == NULL)
    return 0;
  struct LIST_TAG *ptr_slow = root;
  struct LIST_TAG *ptr_fast = root;

  while (ptr_slow->next != NULL && ptr_fast->next != NULL &&
         ptr_fast->next->next != NULL) {
    ptr_slow = ptr_slow->next;
    ptr_fast = ptr_fast->next->next;
    if (ptr_slow == ptr_fast)
      return 1;
  }
  return 0;
}

void LIST_METHOD(printList)(struct LIST_TAG *root) {
  printf("List:");

  if (root == NULL){
    printf("NULL\n");
    return;
  }

  if (LIST_METHOD(detectCycle)(root)) {
    printf("Cycle");
    return;
  }

  while(root->next != NULL) {
    printf("{%d} -> ", root->value);
    root = root->next;
  }

  printf("{%d}\n", root->value);
}

struct LIST_TAG *LIST_METHOD(getAt)(struct LIST_TAG *root, int index) {
  if (root == NULL)
    return NULL;
  int i = 0;
  while (root != NULL && i < index) {
    root = root->next;
    i++;
  }
  return root;
}

void LIST_METHOD(iterApply)(struct LIST_TAG *root, void (*f)(LIST_ITEM_TYPE *)) {
  if (root == NULL)
    return;

  if (LIST_METHOD(detectCycle)(root)) {
    return;
  }

  while (root != NULL) {
    (*f)(&(root->value));
    root = root->next;
  }
}

struct LIST_METHOD(Array)* LIST_METHOD(toArray)(struct LIST_TAG* root) {
    if (root == NULL) return NULL;
    int len = LIST_METHOD(listLen)(root);
    if (len == -1) return NULL;
    struct LIST_METHOD(Array)* ptr = (struct LIST_METHOD(Array)*) malloc(sizeof(struct LIST_METHOD(Array)));
    if (ptr == NULL) return NULL;
    LIST_ITEM_TYPE* innerptr = (LIST_ITEM_TYPE*) malloc(sizeof(LIST_ITEM_TYPE) * len);
    if (innerptr == NULL) {
        free(ptr);
        return NULL;
    }
    ptr->data = innerptr;
    ptr->length = len;
    int i = 0;
    while (root) {
        *(ptr->data + i) = root->value;
        i++;
        root=root->next;
    }
    return ptr;
}

#undef LIST_TAG
#undef LIST_ITEM_TYPE

#undef STACK_CONCAT
#undef STACK_METHOD2
#undef STACK_METHOD