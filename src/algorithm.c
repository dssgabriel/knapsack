#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "algorithm.h"

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
matrix_t *fifo(arr_t *a, u32 max_weight)
{
    if (a)
    {
        matrix_t *res = init_matrix(a->size, max_weight);

        if (res)
        {
            u32 sum = 0;
            u32 x = 0;
            u32 y = 0;
            for (u32 i = 0; i < a->size; i++)
            {
                if (sum + a->array[i] <= max_weight)
                 {
                    sum += a->array[i];
                    res->matrix[x][y] = a->array[i];
                    y++;
                }
                else
                {
                    sum = 0;
                    i--;
                    y = 0;
                    x++;
                }
            }

            return res;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return printf("Error: arr_t pointer is NULL\n"), NULL;
    }
}

//
matrix_t *big_ones_first(arr_t *a, u32 max_weight)
{
    if (a)
    {
        quick_sort(a->array, 0, a->size - 1);
        reverse_arr(a);

        return fifo(a, max_weight);
    }
    else
    {
        return NULL;
    }
}

//
matrix_t *optimized(arr_t *a, u32 max_weight)
{
    if (a)
    {
        quick_sort(a->array, 0, a->size - 1);
        reverse_arr(a);

        matrix_t *res = init_matrix(a->size, max_weight);

        if (res)
        {
            u32 x = 0;
            u32 y = 0;

            for (u32 i = 0; i < a->size; i++)
            {
                if (a->array[i] == 0)
                {
                    continue;
                }
                u32 sum = 0;
                for (u32 j = i + 1; j < a->size; j++)
                {
                    if (a->array[j] == 0)
                    {
                        continue;
                    }
                    if (sum == 0)
                    {
                        res->matrix[x][y] = a->array[i];
                        sum += a->array[i];
                        a->array[i] = 0;
                        y++;
                    }
                    if (sum + a->array[j] <= max_weight)
                    {
                        res->matrix[x][y] = a->array[j];
                        sum += a->array[j];
                        a->array[j] = 0;
                        y++;
                    }
                }
                y = 0;
                x++;
            }

            return res;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
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

void print_perf(matrix_t *m)
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
        f64 perf = (f64)count/m->size * 100.0;
        printf("%.2lf%%\n", perf);
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
