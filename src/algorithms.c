#include <stdio.h>
#include <stdlib.h>
#include "algorithms.h"

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
csr_t *fifo_csr(arr_t *a, u32 max_weight)
{
    if (a)
    {
        csr_t *res = init_csr(a->size, max_weight);

        if (res)
        {
            u32 sum = 0;
            u32 x = 0;
            u32 y = 0;
            u32 z = 0;

            for (u32 i = 0; i < a->size; i++)
            {
                if (sum + a->array[i] <= max_weight)
                 {
                    sum += a->array[i];
                    res->values[x] = a->array[i];
                    res->columns[y] = y;
                    res->rows[z] = z;
                    x++;
                    y++;
                }
                else
                {
                    sum = 0;
                    i--;
                    y = 0;
                    z++;
                }
            }

            shrink_to_fit(res);
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
csr_t *big_ones_first_csr(arr_t *a, u32 max_weight)
{
    if (a)
    {
        quick_sort(a->array, 0, a->size - 1);
        reverse_arr(a);

        return fifo_csr(a, max_weight);
    }
    else
    {
        return NULL;
    }
}

//
csr_t *optimized_csr(arr_t *a, u32 max_weight)
{
    if (a)
    {
        quick_sort(a->array, 0, a->size - 1);
        reverse_arr(a);

        csr_t *res = init_csr(a->size, max_weight);

        if (res)
        {
            u32 x = 0;
            u32 y = 0;
            u32 z = 0;

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
                        sum += a->array[i];
                        res->values[x] = a->array[i];
                        res->columns[y] = y;
                        res->rows[z] = z;
                        a->array[i] = 0;
                        x++;
                        y++;
                    }
                    if (sum + a->array[j] <= max_weight)
                    {
                        sum += a->array[j];
                        res->values[x] = a->array[j];
                        res->columns[y] = y;
                        res->rows[z] = z;
                        a->array[j] = 0;
                        x++;
                        y++;
                    }
                }
                y = 0;
                z++;
            }

            shrink_to_fit(res);
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
