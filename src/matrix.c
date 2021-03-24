#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

matrix_t *init_matrix(u32 size, u32 weight)
{
    matrix_t *m = malloc(sizeof(matrix_t));

    if (m)
    {
        m->size = size;
        m->weight = weight;
        m->matrix = calloc(m->size * sizeof(i32*), sizeof(i32*));

        if (m->matrix)
        {
            for (u32 i = 0; i < m->size; i++)
            {
                m->matrix[i] = calloc(m->weight * sizeof(i32), sizeof(i32));
            }

            if (*m->matrix)
            {
                return m;
            }
            else
            {
                return printf("Error: cannot allocate memory for *m->matrix\n"), NULL;
            }
        }
        else
        {
            return printf("Error: cannot allocate memory for m->matrix\n"), NULL;
        }
    }
    else
    {
        return printf("Error: cannot allocate memory for matrix_t\n"), NULL;
    }
}

//
void print_matrix(matrix_t *m)
{
    if (m)
    {
        for (u32 i = 0; i < m->size; i++)
        {
            printf("( ");
            for (u32 j = 0; j < m->weight; j++)
            {
                printf("%d ", m->matrix[i][j]);
            }
            printf(")\n");
        }
    }
    else
    {
        printf("Error: matrix_t pointer is NULL\n");
    }
}

//
void print_result(matrix_t *m)
{
    if (m)
    {
        for (u32 i = 0; i < m->size; i++)
        {
            if (m->matrix[i][0])
            {
                printf("( ");
                for (u32 j = 0; j < m->weight; j++)
                {
                    if(m->matrix[i][j])
                    {
                        printf("%d ", m->matrix[i][j]);
                    }
                }
                printf(")\n");
            }
        }
    }
    else
    {
        printf("Error: matrix_t pointer is NULL\n");
    }
}

//
void print_matrix_perf(matrix_t *m)
{
    if (m)
    {
        u32 count = 0;
        for (u32 i = 0; i < m->size; i++)
        {
            if (m->matrix[i][0])
            {
                count++;
            }
        }
        f32 perf = (f32)count/m->size * 100.0;
        printf("%.2f%%\n", perf);
    }
    else
    {
        printf("Error: matrix_t pointer is NULL\n");
    }
}

//
void destroy_matrix(matrix_t *m)
{
    if (m)
    {
        for (u32 i = 0; i < m->size; i++)
        {
            free(m->matrix[i]);
        }
        free(m->matrix);
        free(m);
    }
    else
    {
        printf("Error: matrix pointer is NULL\n");
    }
}
