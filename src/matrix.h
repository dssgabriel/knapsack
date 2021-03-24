#ifndef MATRIX_H
#define MATRIX_H

#include "types.h"

typedef struct matrix_s {
    i32 **matrix;
    u32 weight;
    u32 size;
} matrix_t;

//
matrix_t *init_matrix(u32 size, u32 weight);

//
void print_matrix(matrix_t *m);

//
void print_result(matrix_t *m);

//
void print_matrix_perf(matrix_t *m);

//
void destroy_matrix(matrix_t *m);

#endif
