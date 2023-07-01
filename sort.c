// Tyler Taormina 
//
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/*  gcc -g -Wall -o sort sort.c   */

int array[] = {52, 7, 10, 100, 3, 200, 1, 30};
int length = 8; 

int select_sort(int *, int);
int print_array(int *, int);

int
main(void)
{
    print_array(array, length);
    select_sort(array, length);
    print_array(array, length);

    return 0;
}

int
print_array(int *arr, int len)
{
    int i;

    printf("%d ->", arr[0]);
    for (i = 1; i < len -1; i++) {
        printf(" %d ->", arr[i]);
    }
    printf(" %d\n", arr[i]);
    return 0;
}

int select_sort(int *arr, int len)
{
    int i, j;
    for (i = 0; i < len; i++) {
        for (j = i + 1; j < len; j++) {
            int temp;
            if (arr[j] < arr[i]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    return 0;
}

