#include "stdlib.h"
#include "stdio.h"
#include "dynamic_array.h"

DynamicArray* da_create(size_t elem_size, size_t capacity) {
    DynamicArray* arr = malloc(sizeof(DynamicArray));
    arr->data = malloc(elem_size * capacity);
    arr->elem_size = elem_size;
    arr->size = 0;
    arr->capacity = capacity;
    return arr;
}

void da_free(DynamicArray* arr) {
    free(arr->data);
    free(arr);
}

void da_push(DynamicArray* arr, void* element) {
    if (arr->size == arr->capacity) {
        arr->capacity *= 2;
        arr->data = realloc(arr->data, arr->elem_size * arr->capacity);
    }
    memcpy((char*)arr->data + arr->size * arr->elem_size, element, arr->elem_size);
    arr->size++;
}

void* da_get(DynamicArray* arr, size_t index) {
    if (index >= arr->size) return NULL;
    return (char*)arr->data + index * arr->elem_size;
}

void da_set(DynamicArray* arr, size_t index, void* element) {
    if (index >= arr->size) return;
    memcpy((char*)arr->data + index * arr->elem_size, element, arr->elem_size);
}

void da_remove(DynamicArray* arr, size_t index) {
    if (index >= arr->size) return;
    // Shift elements left to fill the gap
    if (index < arr->size - 1) {
        memmove(
            (char*)arr->data + index * arr->elem_size,
            (char*)arr->data + (index + 1) * arr->elem_size,
            (arr->size - index - 1) * arr->elem_size
        );
    }
    arr->size--;
}