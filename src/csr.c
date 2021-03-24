#include <stdlib.h>
#include <stdio.h>
#include "csr.h"

csr_t *init_csr(u32 size, u32 weight)
{
    csr_t *c = malloc(sizeof(csr_t));

    if (c)
    {
        c->size = size;
        c->nb_col = weight;
        c->nb_row = size;
        c->values = calloc(c->size * sizeof(i32), sizeof(i32));

        if (c->values)
        {
            c->columns = calloc(c->nb_col * sizeof(u32), sizeof(u32));

            if (c->columns)
            {
                c->rows = calloc(c->nb_row * sizeof(u32), sizeof(u32));

                if (c->rows)
                {
                    return c;
                }
                else
                {
                    return printf("Error: cannot allocate memory for c->rows\n"), NULL;
                }
            }
            else
            {
                return printf("Error: cannot allocate memory for c->colums\n"), NULL;
            }
        }
        else
        {
            return printf("Error: cannot allocate memory for c->values\n"), NULL;
        }
    }
    else
    {
        return printf("Error: cannot allocate memory for csr_t\n"), NULL;
    }
}

//
void shrink_to_fit(csr_t *c)
{
    if (c)
    {
        u32 new_nb_col = 1;
        u32 new_nb_row = 1;

        while (c->columns[new_nb_col])
        {
            new_nb_col++;
        }
        c->columns = realloc(c->columns, new_nb_col * sizeof(u32));
        c->nb_col = new_nb_col;

        while (c->rows[new_nb_row])
        {
            new_nb_row++;
        }
        c->rows = realloc(c->rows, new_nb_row * sizeof(u32));
        c->nb_row = new_nb_row;
    }
    else
    {
        printf("Error: csr_t pointer is NULL\n");
    }
}

//
void print_csr(csr_t *c)
{
    if (c)
    {
        printf("Values:\t [ ");
        for (u32 i = 0; i < c->size; i++)
        {
            printf("%d ", c->values[i]);
        }
        printf("]\nColumns: [ ");
        for (u32 i = 0; i < c->nb_col; i++)
        {
            printf("%d ", c->columns[i]);
        }
        printf("]\nRows:\t [ ");
        for (u32 i = 0; i < c->nb_row; i++)
        {
            printf("%d ", c->rows[i]);
        }
        printf("]\n");
    }
    else
    {
        printf("Error: csr_t pointer is NULL\n");
    }
}

//
void print_csr_perf(csr_t *c)
{
    if (c)
    {
        f32 perf = (f32)c->nb_row/(f32)c->size * 100.0;
        printf("%.2f%%\n", perf);
    }
    else
    {
        printf("Error: csr_t pointer is NULL\n");
    }
}

void destroy_csr(csr_t *c)
{
    if (c)
    {
        free(c->values);
        free(c->columns);
        free(c->rows);
        free(c);
    }
    else
    {
        printf("Error: csr_t pointer is NULL\n");
    }
}
