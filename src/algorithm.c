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
