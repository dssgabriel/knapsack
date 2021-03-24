#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "types.h"
#include "array.h"
#include "matrix.h"
#include "csr.h"

// First in, first out type of algorithm (matrices)
matrix_t *fifo(arr_t *a, u32 max_weight);

// Order the array top down and then use fifo algorithm (matrices)
matrix_t *big_ones_first(arr_t *a, u32 max_weight);

// Optimize the filling of each batch (matrices)
matrix_t *optimized(arr_t *a, u32 max_weight);

// First in, first out type of algorithm (CSR representation)
csr_t *fifo_csr(arr_t *a, u32 max_weight);

// Order the array top down and then use fifo algorithm (CSR representation)
csr_t *big_ones_first_csr(arr_t *a, u32 max_weight);

// Optimize the filling of each batch (CSR representation)
csr_t *optimized_csr(arr_t *a, u32 max_weight);

#endif
