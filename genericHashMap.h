#include <string.h>
#include <stddef.h>


#if !defined (HASHMAP_TAG) || !defined(HASHMAP_ITEM_TYPE)
#define HASHMAP_TAG int_HashMap
#define HASHMAP_ITEM_TYPE int
#define HASHMAP_KEY_TYPE int
#endif

#define HASHMAP_CONCAT(tag, suffix) tag##_##suffix
#define HASHMAP_SUBSTITUTION_STEP(tag, suffix) HASHMAP_CONCAT(tag, suffix)
#define HASHMAP_METHOD(method) HASHMAP_SUBSTITUTION_STEP(HASHMAP_TAG, method)
#define HASHMAP_ENTRY() HASHMAP_SUBSTITUTION_STEP(HASHMAP_TAG, Entry)
#define HASHMAP_ARRAYLIST() HASHMAP_SUBSTITUTION_STEP(HASHMAP_ENTRY(), arraylist)
#define HASHMAP_ARRAYLIST_METHOD(method) HASHMAP_SUBSTITUTION_STEP(HASHMAP_ARRAYLIST(), method)

//should be larger than the number of unique characters [https://www.codingninjas.com/studio/library/string-hashing-2425]
#define HASHMAP_PRIME 277

typedef struct HASHMAP_ENTRY() {
    HASHMAP_KEY_TYPE key;
    size_t hash;
    HASHMAP_ITEM_TYPE value;
} HASHMAP_ENTRY();

#define ARRAYLIST_TAG HASHMAP_ARRAYLIST()
#define ARRAYLIST_ITEM_TYPE HASHMAP_ENTRY()*
#include "genericArrayList.h"

typedef struct HASHMAP_TAG {
    int length;
    struct HASHMAP_ARRAYLIST()** data;
    size_t (*hash_func)(HASHMAP_ITEM_TYPE);
} HASHMAP_TAG;

// hash functions 

size_t GenericHashMap__hash_int(int key) {
    return (size_t) key;
}

size_t GenericHashMap__hash_char(char key) {
    return (size_t) key;
}

size_t GenericHashMap__hash_string(char* str) {
    size_t l = strlen(str);
    size_t hash = 0;
    size_t prime = 1;
    for (size_t i = 0; i < l; i++) {
        hash += str[i] * prime;
        prime *= HASHMAP_PRIME;
    }
    return hash;
}

size_t GenericHashMap__hash_pointer(void* key) {
    return (size_t) key;
}

// figure out buckets and keys 

// backing with an arraylist + binary search for insertion and lookup
HASHMAP_TAG* HASHMAP_METHOD(create)(int length, size_t (*hash_func)(HASHMAP_ITEM_TYPE)) {
    HASHMAP_TAG* obj = (HASHMAP_TAG*) malloc(sizeof(HASHMAP_TAG));
    if (obj == NULL) return NULL;
    struct HASHMAP_ARRAYLIST()** data = (struct HASHMAP_ARRAYLIST()**) malloc(sizeof(struct HASHMAP_ARRAYLIST()*) * length);
    for (int i = 0; i < length; i++) {
        struct HASHMAP_ARRAYLIST()* list = HASHMAP_ARRAYLIST_METHOD(create)(5);
        if (list == NULL) {
            for (int j = 0; j < i; j++) {
                HASHMAP_ARRAYLIST_METHOD(free)(*(data + j));
            }
            free(data);
            free(obj);
            return NULL; //TODO deal with previously allocated resources obj and lists
        }
        *(data + i) = list;
    }
    obj->data = data;
    obj->hash_func = hash_func;
    return obj;
}

int HASHMAP_METHOD(add)(HASHMAP_TAG* obj, HASHMAP_KEY_TYPE key, HASHMAP_ITEM_TYPE value) {
    HASHMAP_ENTRY()* entry = (HASHMAP_ENTRY()*) malloc(sizeof(HASHMAP_ENTRY()));
    if (entry == NULL) return 1;
    entry->value = value;
    entry->key = key;
    entry->hash = obj->hash_func(key);
    int bucket_index = entry->hash % obj->length;
    struct HASHMAP_ARRAYLIST()* bucket = *(obj->data + bucket_index);
    if (HASHMAP_ARRAYLIST_METHOD(push)(bucket, entry) == 1) return 1;
    return 0;
}

HASHMAP_ITEM_TYPE HASHMAP_METHOD(get)(HASHMAP_TAG* obj, HASHMAP_KEY_TYPE key) {
    size_t hash = obj->hash_func(key);
    int bucket_index = hash % obj->length;
    struct HASHMAP_ARRAYLIST()* bucket = *(obj->data + bucket_index);
    for (int i = 0; i < bucket->length; i++) {
        if ((*(bucket->data + i))->value == key) {
            return (*(bucket->data + i))->value;
        }
    }
    return (HASHMAP_ITEM_TYPE) NULL;
}