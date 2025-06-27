#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>
#include <string.h>

typedef struct {
    void* data;         // Pointer to the array data
    size_t elem_size;   // Size of each element
    size_t size;        // Number of elements in use
    size_t capacity;    // Allocated capacity
} DynamicArray;

DynamicArray* da_create(size_t elem_size, size_t capacity);
void da_free(DynamicArray* arr);
void da_push(DynamicArray* arr, void* element);
void* da_get(DynamicArray* arr, size_t index);
void da_set(DynamicArray* arr, size_t index, void* element);
void da_remove(DynamicArray* arr, size_t index);

#endif