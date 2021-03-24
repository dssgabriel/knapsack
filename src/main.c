#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algorithms.h"

int main(int argc, char **argv)
{
    // Check for correct number of arguments
    if (argc < 2)
    {
        printf("Error: not enough arguments\n");
        printf("Usage: %s -[m | c] [NB_PACKAGES] [MAX_PACKAGE_WEIGHT] [MAX_TRUCK_WEIGHT]\n", argv[0]);
        printf("Run with option `-h` for help");
        return 1;
    }

    if (!strcmp(argv[1], "-h"))
    {
        printf("Usage: %s [OPTIONS] [NB_PACKAGES] [MAX_PACKAGE_WEIGHT] [MAX_TRUCK_WEIGHT]\n", argv[0]);
        printf("Available options:\n");
        printf("\t-m: run using matrices to store the result\n");
        printf("\t-c: run using CSR representation to store the result\n");
        printf("\t-h: print this help\n");
    }

    if (!strcmp(argv[1], "-m") && argc == 5)
    {
        const u32 NB_PACKAGES = atoi(argv[2]);
        const u32 MAX_WEIGHT = atoi(argv[3]);
        const u32 MAX_BATCH_WEIGHT = atoi(argv[4]);

        if (MAX_WEIGHT <= MAX_BATCH_WEIGHT) {
            arr_t *packages = init_rand_arr(NB_PACKAGES, MAX_WEIGHT);

            printf("\tMatrix:\n");
            printf("First in, first out: ");
            matrix_t *first_algo = fifo(packages, MAX_BATCH_WEIGHT);
            //print_matrix(first_algo);
            print_matrix_perf(first_algo);

            printf("Big ones first: ");
            arr_t *packages_copy_one = copy_arr(packages);
            matrix_t *second_algo = big_ones_first(packages_copy_one, MAX_BATCH_WEIGHT);
            //print_matrix(second_algo);
            print_matrix_perf(second_algo);

            printf("Optimal: ");
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
        else
        {
            return printf("Error: MAX_PACKAGE_WEIGHT needs to be lower than or equal to MAX_TRUCK_WEIGHT\n"), 1;
        }
    }
    else if (!strcmp(argv[1], "-c") && argc == 5)
    {
        const u32 NB_PACKAGES = atoi(argv[2]);
        const u32 MAX_WEIGHT = atoi(argv[3]);
        const u32 MAX_BATCH_WEIGHT = atoi(argv[4]);

        if (MAX_WEIGHT <= MAX_BATCH_WEIGHT) {
            arr_t *packages = init_rand_arr(NB_PACKAGES, MAX_WEIGHT);

            printf("\tCSR:\n");
            printf("First in, first out: ");
            csr_t *first_algo = fifo_csr(packages, MAX_BATCH_WEIGHT);
            //print_csr(first_algo);
            print_csr_perf(first_algo);

            printf("Big ones first: ");
            arr_t *packages_copy_one = copy_arr(packages);
            csr_t *second_algo = big_ones_first_csr(packages_copy_one, MAX_BATCH_WEIGHT);
            //print_csr(second_algo);
            print_csr_perf(second_algo);

            printf("Optimal: ");
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
        else {
            return printf("Error: MAX_PACKAGE_WEIGHT needs to be lower than or equal to MAX_TRUCK_WEIGHT\n"), 1;
        }
    }
    else
    {
        printf("Error: could not parse arguments\n");
        printf("Usage: %s -[m | c | h] [NB_PACKAGES] [MAX_PACKAGE_WEIGHT] [MAX_TRUCK_WEIGHT]\n", argv[0]);
        return 1;
    }

    return 0;
}
