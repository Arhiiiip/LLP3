/**
 * dynamic array implementation
 * (c) 2011 @marekweb
 *
 * Uses dynamic extensible arrays.
 */

#include <stdlib.h>
#include <assert.h>
#include "array.h"

#define INITIAL_CAPACITY 4

struct array* create_array() {
    struct array* new_list = malloc(sizeof(struct array));
    assert(new_list);
    new_list->size = 0;
    new_list->capacity = INITIAL_CAPACITY;
    new_list->body = malloc(sizeof(void*) * new_list->capacity);
    assert(new_list->body);
    return new_list;
}


unsigned int get_array_size(struct array* l) {
    return l->size;
}

void add_to_array(struct array* l, void* item) {
    if(l->size+1 > l->capacity) {
        unsigned int new_capacity = l->capacity;
        while (new_capacity < l->size+1) {
            new_capacity *= 2;
        }
        void** new_body = realloc(l->body, sizeof(void*) * new_capacity);
        assert(new_body);
        l->body = new_body;
        l->capacity = new_capacity;
    }    
    l->body[l->size] = item;
    l->size++;
}

void* get_from_array(struct array* l, unsigned int index) {
    assert(index < l->size);
    return l->body[index];
}

void destroy_array(struct array* l) {
    free(l->body);
    free(l);
}