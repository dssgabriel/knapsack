#ifndef COMMON_H
#define COMMON_H

#include "types.h"

typedef struct arr_s {
    // Array size
    u32 size;
    // Integer array
    i32 *array;
} arr_t;

// Allocates the specified memory for an arr_t
// Initializes it with 0s
arr_t *init_arr(u32 size);

// Allocates the specified memory for an arr_t
// Initializes it with random values between 1 and the specified maximum weight
arr_t *init_rand_arr(u32 size, u32 max_weight);

// Creates a copy of the specified arr_t
arr_t *copy_arr(arr_t *a);

// Prints the specified arr_t
void print_arr(arr_t *a);

// Sorts the specified integer array using the quicksort algorithm
void quick_sort(i32 *arr, i32 low, i32 high);

// Reverses the order of the specified arr_t
void reverse_arr(arr_t *a);

// Removes the specified index and shrinks the arr_t to fit
void remove_and_resize(arr_t *a, u32 index);

// De-allocates the memory for the specified arr_t
void destroy_arr(arr_t *a);

#endif
