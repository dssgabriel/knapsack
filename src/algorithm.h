#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "types.h"
#include "common.h"

typedef struct matrix_s {
    i32 **matrix;
    u32 weight;
    u32 size;
} matrix_t;

typedef struct csr_s {
    i32 *values;
    u32 *columns;
    u32 *rows;
    u32 size;
    u32 nb_col;
    u32 nb_row;
} csr_t;

//
matrix_t *fifo(arr_t *a, u32 max_weight);

//
matrix_t *big_ones_first(arr_t *a, u32 max_weight);

//
matrix_t *optimized(arr_t *a, u32 max_weight);

//
csr_t *fifo_csr(arr_t *a, u32 max_weight);

//
csr_t *big_ones_first_csr(arr_t *a, u32 max_weight);

//
csr_t *optimized_csr(arr_t *a, u32 max_weight);

//
void print_matrix(matrix_t *m);

//
void print_result(matrix_t *m);

//
void print_csr(csr_t *c);

//
void print_matrix_perf(matrix_t *m);

//
void print_csr_perf(csr_t *c);

//
void destroy_matrix(matrix_t *m);

//
void destroy_csr(csr_t *c);

#endif
