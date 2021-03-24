#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array.h"

//
arr_t *init_arr(u32 size)
{
    arr_t *a = malloc(sizeof(arr_t));

    if (a)
    {
        a->size = size;
        a->array = malloc(a->size * sizeof(i32));

        if (a->array)
        {
                return a;
        }
        else
        {
            return printf("Error: cannot allocate memory for arr_t array\n"), NULL;
        }
    }
    else
    {
        return printf("Error: cannot allocate memory for arr_t\n"), NULL;
    }
}

//
arr_t *init_rand_arr(u32 size, u32 max_weight)
{
    arr_t *a = init_arr(size);

    if (a)
    {
        srand(time(NULL));
        for (u32 i = 0; i < a->size; i++)
        {
            a->array[i] = rand() % max_weight + 1;
        }

        return a;
    }
    else
    {
        return NULL;
    }
}

//
arr_t *copy_arr(arr_t *a)
{
    if (a)
    {
        arr_t *tmp = malloc(sizeof(arr_t));

        if (tmp)
        {
            tmp->size = a->size;
            tmp->array = calloc(a->size * sizeof(i32), sizeof(i32));

            if (tmp->array)
            {
                for (u32 i = 0; i < a->size; i++)
                {
                    tmp->array[i] = a->array[i];
                }

                return tmp;
            }
            else
            {
                return printf("Error: cannot allocate memory for copy of arr_t array\n"), NULL;
            }
        }
        else
        {
            return printf("Error: cannot allocate memory for copy of arr_t\n"), NULL;
        }
    }
    else
    {
        return printf("Error: arr_t pointer is NULL\n"), NULL;
    }
}

//
void print_arr(arr_t *a)
{
    if (a)
    {
        printf("{ ");
        for (u32 i = 0; i < a->size; i++)
        {
            printf("%d ", a->array[i]);
        }
        printf("}\n");
    }
    else
    {
        printf("Error: arr_t pointer is NULL\n");
    }
}

//
void swap(i32 *x, i32 *y)
{
    i32 tmp = *x;
    *x = *y;
    *y = tmp;
}

//
i32 partition(i32 *arr, i32 low, i32 high)
{
    i32 pivot = arr[high];
    i32 i = (low - 1);

    for (i32 j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);

    return (i + 1);
}

//
void quick_sort(i32 *arr, i32 low, i32 high)
{
    if (arr)
    {
        if (low < high)
        {
            i32 part_index = partition(arr, low, high);
            quick_sort(arr, low, part_index - 1);
            quick_sort(arr, part_index + 1, high);
        }
    }
    else
    {
        printf("Error: arr_t pointer is already NULL\n");
    }
}

//
void reverse_arr(arr_t *a)
{
    if (a)
    {
        u32 i = a->size - 1;
        for (u32 j = 0; j < a->size / 2; j++)
        {
            swap(&a->array[i], &a->array[j]);
            i--;
        }
    }
    else
    {
        printf("Error: arr_t pointer is already NULL\n");
    }
}

//
void remove_and_resize(arr_t *a, u32 index)
{
    if (a)
    {
        swap(&a->array[index], &a->array[a->size - 1]);
        a->array = realloc(a->array, (a->size - 1) * sizeof(i32));
        a->size = a->size - 1;
        quick_sort(a->array, 0, a->size - 1);
        reverse_arr(a);
    }
    else
    {
        printf("Error: arr_t pointer is already NULL\n");
    }
}

//
void destroy_arr(arr_t *a)
{
    if (a)
    {
        free(a->array);
        free(a);
    }
    else
    {
        printf("Error: arr_t pointer is NULL\n");
    }
}
