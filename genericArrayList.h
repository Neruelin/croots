#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#if !defined (ARRAYLIST_TAG) || !defined(ARRAYLIST_ITEM_TYPE)
#define ARRAYLIST_TAG int_arraylist
#define ARRAYLIST_ITEM_TYPE int
#endif

#define ARRAYLIST_CONCAT(tag, method) tag##_##method
#define ARRAYLIST_SUBSTITUTION_STEP(tag, method) ARRAYLIST_CONCAT(tag, method)
#define ARRAYLIST_METHOD(method) ARRAYLIST_SUBSTITUTION_STEP(ARRAYLIST_TAG, method)

struct ARRAYLIST_TAG {
    int capacity;
    int length;
    ARRAYLIST_ITEM_TYPE* data;
} ARRAYLIST_TAG;

struct ARRAYLIST_TAG* ARRAYLIST_METHOD(create)(int capacity) {
    if (capacity < 1) return NULL;
    struct ARRAYLIST_TAG* obj = (struct ARRAYLIST_TAG*) malloc(sizeof(struct ARRAYLIST_TAG));
    if (obj == NULL) return NULL;
    obj->capacity = capacity;
    obj->length = 0;
    obj->data = (ARRAYLIST_ITEM_TYPE*) malloc(sizeof(ARRAYLIST_ITEM_TYPE) * capacity);
    if (obj->data == NULL) return NULL;
    memset(obj->data, 0, sizeof(ARRAYLIST_ITEM_TYPE) * capacity);
    // for (int i = 0; i < capacity; i++) {
    //     *(obj->data + i) = (ARRAYLIST_ITEM_TYPE*);
    // }
    return obj;
}

int ARRAYLIST_METHOD(push)(struct ARRAYLIST_TAG* obj, ARRAYLIST_ITEM_TYPE value) {
    if (obj->length == obj->capacity) {
        int newcapacity = obj->capacity * 2;
        ARRAYLIST_ITEM_TYPE* newdata = (ARRAYLIST_ITEM_TYPE*) malloc(sizeof(ARRAYLIST_ITEM_TYPE) * newcapacity);
        if (newdata == NULL) {
            return 1;
        }
        for (int i = 0; i < obj->length; i++) {
            *(newdata + i) = *(obj->data + i);
        }
        *(newdata + obj->length) = value;
        memset(obj->data + obj->length + 1, 0, sizeof(ARRAYLIST_ITEM_TYPE) * (newcapacity - obj->length));
        // for (int i = obj->length + 1; i < newcapacity; i++) {
        //     *(newdata + i) = 0;
        // }
        obj->capacity = newcapacity;
        obj->length += 1;
        free(obj->data);
        obj->data = newdata;
        return 0;
    }

    *(obj->data + obj->length) = value;
    obj->length += 1;
    return 0;
}

ARRAYLIST_ITEM_TYPE ARRAYLIST_METHOD(pop)(struct ARRAYLIST_TAG* obj) {
    assert(obj->length > 0);
    ARRAYLIST_ITEM_TYPE ret = *(obj->data + (obj->length - 1));
    memset(obj->data + obj->length - 1, 0, sizeof(ARRAYLIST_ITEM_TYPE));
    // *(obj->data + (obj->length - 1)) = 0;
    obj->length -= 1;
    return ret;
}

ARRAYLIST_ITEM_TYPE ARRAYLIST_METHOD(getAt)(struct ARRAYLIST_TAG* obj, int index) {
    assert(obj->length > index);
    return *(obj->data + index);
}

int ARRAYLIST_METHOD(setAt)(struct ARRAYLIST_TAG* obj, int index, ARRAYLIST_ITEM_TYPE value) {
    if (obj->length <= index) return 1;
    *(obj->data + index) = value;
    return 0;
}

void ARRAYLIST_METHOD(free)(struct ARRAYLIST_TAG* obj) {
    free(obj->data);
    free(obj);
}

int ARRAYLIST_METHOD(binsearch)(struct ARRAYLIST_TAG* obj, ARRAYLIST_ITEM_TYPE value, int (*cmp)(ARRAYLIST_ITEM_TYPE, ARRAYLIST_ITEM_TYPE)) {
    int lo = 0;
    int hi = obj->length - 1;
    while (lo <= hi) {
        int mid = (hi + lo) / 2;
        ARRAYLIST_ITEM_TYPE item = ARRAYLIST_METHOD(getAt)(obj, mid);
        int cmp_value = (*cmp)(value, item);
        if (cmp_value == 0) {
            return mid;
        } else if (cmp_value > 0) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return -1;
}