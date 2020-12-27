#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "types.h"
#include "common.h"

typedef struct matrix_s {
    i32 **matrix;
    u32 weight;
    u32 size;
} matrix_t;

//
matrix_t *fifo(arr_t *a, u32 max_weight);

//
matrix_t *big_ones_first(arr_t *a, u32 max_weight);

//
matrix_t *optimized(arr_t *a, u32 max_weight);

//
void print_matrix(matrix_t *m);

//
void print_result(matrix_t *m);

//
void print_perf(matrix_t *m);

//
void destroy_matrix(matrix_t *m);

#endif
