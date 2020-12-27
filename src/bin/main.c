#include <stdio.h>
#include <stdlib.h>
#include "../algorithm.h"

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        return printf("Error: not enough arguments\n"), 1;
    }

    const u32 NB_PACKAGES = atoi(argv[1]);
    const u32 MAX_WEIGHT = atoi(argv[2]);
    const u32 MAX_BATCH_WEIGHT = atoi(argv[3]);

    printf("\nNumber of packages:\t\t\t%d\nMaximum weight of a package:\t\t%d\nMaximum weight per batch of packages:\t%d\n", NB_PACKAGES, MAX_WEIGHT, MAX_BATCH_WEIGHT);

    arr_t *packages = init_rand_arr(NB_PACKAGES, MAX_WEIGHT);
    //printf("Initial array:\n");
    //print_arr(packages);

    // First algorithm
    printf("\nFirst in, first out:\t");
    matrix_t *first_res = fifo(packages, MAX_BATCH_WEIGHT);
    //print_result(first_res);
    print_perf(first_res);

    // Second algorithm
    printf("Big ones first:\t\t");
    arr_t *copy_one = copy_arr(packages);
    matrix_t *second_res = big_ones_first(copy_one, MAX_BATCH_WEIGHT);
    //print_result(second_res);
    print_perf(second_res);

    // Third algorithm
    printf("Optimized:\t\t");
    arr_t *copy_two = copy_arr(packages);
    matrix_t *third_res = optimized(copy_two, MAX_BATCH_WEIGHT);
    //print_result(third_res);
    print_perf(third_res);

    destroy_arr(packages);
    destroy_arr(copy_one);
    destroy_arr(copy_two);

    destroy_matrix(first_res);
    destroy_matrix(second_res);
    destroy_matrix(third_res);

    return 0;
}
