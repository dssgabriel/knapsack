#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../algorithm.h"

int main(int argc, char **argv)
{
    if (argc < 5)
    {
        return printf("Error: not enough arguments\n"), 1;
    }

    const u32 NB_PACKAGES = atoi(argv[2]);
    const u32 MAX_WEIGHT = atoi(argv[3]);
    const u32 MAX_BATCH_WEIGHT = atoi(argv[4]);

    //printf("\nNumber of packages:\t\t\t%d\nMaximum weight of a package:\t\t%d\nMaximum weight per batch of packages:\t%d\n", NB_PACKAGES, MAX_WEIGHT, MAX_BATCH_WEIGHT);

    arr_t *packages = init_rand_arr(NB_PACKAGES, MAX_WEIGHT);
    //printf("Initial array:\n");
    //print_arr(packages);

    if (!strcmp(argv[1], "matrix"))
    {
        printf("matrix\n");
        printf("\nFirst in, first out:\n");
        matrix_t *first_algo = fifo(packages, MAX_BATCH_WEIGHT);
        //print_matrix(first_algo);
        print_matrix_perf(first_algo);

        printf("Big ones first:\n");
        arr_t *packages_copy_one = copy_arr(packages);
        matrix_t *second_algo = big_ones_first(packages_copy_one, MAX_BATCH_WEIGHT);
        //print_matrix(second_algo);
        print_matrix_perf(second_algo);

        printf("Optimal:\n");
        arr_t *packages_copy_two = copy_arr(packages);
        matrix_t *third_algo = optimized(packages_copy_two, MAX_BATCH_WEIGHT);
        //print_matrix(third_algo);
        print_matrix_perf(third_algo);

        destroy_arr(packages);
        destroy_arr(packages_copy_one);
        destroy_arr(packages_copy_two);

        destroy_matrix(first_algo);
        destroy_matrix(second_algo);
        destroy_matrix(third_algo);
    }
    else if (!strcmp(argv[1], "csr"))
    {
        printf("\nFirst in, first out:\n");
        csr_t *first_algo = fifo_csr(packages, MAX_BATCH_WEIGHT);
        //print_csr(first_algo);
        print_csr_perf(first_algo);

        printf("Big ones first:\n");
        arr_t *packages_copy_one = copy_arr(packages);
        csr_t *second_algo = big_ones_first_csr(packages_copy_one, MAX_BATCH_WEIGHT);
        //print_csr(second_algo);
        print_csr_perf(second_algo);

        printf("Optimal:\n");
        arr_t *packages_copy_two = copy_arr(packages);
        csr_t *third_algo = optimized_csr(packages_copy_two, MAX_BATCH_WEIGHT);
        //print_csr(third_algo);
        print_csr_perf(third_algo);

        destroy_arr(packages);
        destroy_arr(packages_copy_one);
        destroy_arr(packages_copy_two);

        destroy_csr(first_algo);
        destroy_csr(second_algo);
        destroy_csr(third_algo);
    }
    else
    {
        printf("Error: unknown argument %s", argv[1]);
    }

    return 0;
}
