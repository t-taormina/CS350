/* Tyler Taormina - HW 2 Merge Sort */
/* taormina@pdx.edu */

// To compile 
/*  gcc -g -Wall -o hw2 hw2TaorminaTyler.c -lm  */

/* run ->    ./hw2 
 *              this will use a default array size of 10000
 * run ->    ./hw2 -n 10 
 *              this will use the array size specified i.e 10 in this case
 * run ->    ./hw2 -h 
 *              help
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/time.h>


#define OPTIONS "n:h"
#define DEFAULT 10000 // 10 thousand 

int size = DEFAULT;

int process_cmd_line(int, char **);
void create_array(int *); 
void print_array(int *);
void merge_sort(int *, int, int);
void merge(int *arr, int l, int m, int r);

int
main(int argc, char **argv)
{
    process_cmd_line(argc, argv);
    if (0 == size) {
        fprintf(stderr, "empty array\n");
        return EXIT_FAILURE;
    }
    int array[size];
    create_array(array);
    printf("\tOriginal Array\n");
    print_array(array);

    merge_sort(array, 0, size - 1);
    printf("\tSorted Array\n");
    print_array(array);
    return EXIT_SUCCESS;
}

int 
process_cmd_line(int argc, char **argv)
{
    {
        int opt = -1;
        while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
            switch (opt) {
                case 'n': 
                    size = atoi(optarg);
                    if (size == 1) {
                        printf("An array with one item is already sorted!\n");
                    }
                    break;

                case 'h':
                    printf("%s: -n # \n", argv[0]);
                    printf("\t-n #: number of elements in array\n");
                    exit(0);
                    break;

                default: /* '?' */
                    exit(EXIT_FAILURE);
                    break;
            }
        }
    }
    return 0;
}

void create_array(int *arr) 
{
    int i, d;

    srandom(1000); 
    for(i=0; i<size; i++) {
        d = abs(random()) % size; 
        arr[i] = d;
    }
}

void print_array(int *arr)
{
    int i;
    for(i = 0; i < (size-1); i++) {
        printf("%d -> ", arr[i]);
    }
    printf("%d\n", arr[size-1]);
    printf("\n");
}

void
merge_sort(int *arr, int l, int r)
{
    int m;

    if (l < r) {
        m = l + (r -l) / 2; /* middle index */

        merge_sort(arr, l, m);
        merge_sort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

void 
merge(int *arr, int l, int m, int r) 
{
    int i, j, k;
    
    /* Create sub arrays */
    int len_l = m - l + 1;
    int l_sub[len_l];

    int len_r = r - m;
    int r_sub[len_r];

    /* Fill sub arrays */
    for (i = 0; i < len_l; i++) {
        l_sub[i] = arr[l + i];
    }

    for (j = 0; j < len_r; j++) {
        r_sub[j] = arr[(m+1) + j];
    }

    i = j = 0; // reset to fill main array
    k = l;

    /* Fill main array sorted */
    while (i < len_l && j < len_r) {
        if (l_sub[i] < r_sub[j]) {
            arr[k] = l_sub[i];
            i++;
        } else {
            arr[k] = r_sub[j];
            j++;
        }
        k++;
    }

    /* Check sub arrays for remaining elements */
    while (i < len_l) {
        arr[k] = l_sub[i];
        i++;
        k++;
    }

    while (j < len_r) {
        arr[k] = r_sub[j];
        j++;
        k++;
    }
}
