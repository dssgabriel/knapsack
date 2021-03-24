#ifndef CSR_H
#define CSR_H

#include "types.h"

typedef struct csr_s {
    i32 *values;
    u32 *columns;
    u32 *rows;
    u32 size;
    u32 nb_col;
    u32 nb_row;
} csr_t;

//
csr_t *init_csr(u32 size, u32 weight);

//
void shrink_to_fit(csr_t *c);

//
void print_csr(csr_t *c);

//
void print_csr_perf(csr_t *c);

//
void destroy_csr(csr_t *c);

#endif
