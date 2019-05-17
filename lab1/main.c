#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"
// #define LARGE_TEST

enum sortingType { BUBBLESORT, MERGESORT, HEAPSORT };

/*************************************************
 * NOTE: Don't modify below code !!! *
 ************************************************/
// print all elements in array
void printArr(int *arr, int n) 
{
    int i;
    for (i = 0; i < n; i++) {
        printf("%d\n", arr[i]);
    }
}

void usage(void)
{
    puts("Sorting program");
    puts("Usage: ./main [sorting-type]");
    puts("sorting-type");
    puts("  b\tbubble sort");
    puts("  m\tmerge sort");
    puts("  h\theap sort");
}

int main(int argc, const char* argv[])
{
    int *arr;
    int size;
    FILE* inputFile;
    FILE* outputFile;
    int i = 0;
    char ch;
    enum sortingType st;

    if (argc != 2) {
        usage();
        return 0;
    }

    ch = *argv[1];
    switch(ch) {
        case 'b':
            st = BUBBLESORT;
            break;
        case 'm':
            st = MERGESORT;
            break;
        case 'h':
            st = HEAPSORT;
            break;
        default:
            usage();
            return 0;
    }

    // read input file
#ifdef LARGE_TEST
    inputFile = fopen("input-large.txt", "r");
#else
    inputFile = fopen("input-small.txt", "r");
#endif
    if (inputFile == NULL) {
        printf("fopen error\n");
    }

    fscanf(inputFile, "%d", &size);
    printf("size = %d\n", size);
    arr = (int *) malloc(sizeof(int)*size);
    while (i < size) {
        fscanf(inputFile, "%d", &arr[i]);
        i++;
    }

    // Sorting begin
    switch (st) {
        case BUBBLESORT:
            printf("Bubble Sort Starts!\n");
            bubbleSort(arr, size);
            break;
        case MERGESORT:
            printf("Merge Sort Starts!\n");
            mergeSort(arr, size);
            break;
        case HEAPSORT:
            printf("Heap Sort Starts!\n");
            heapSort(arr, size);
            break;
        default:
            printf("Wrong Sort Type..\n");
            return 0;
    }

#ifndef LARGE_TEST
    printArr(arr, size);
#endif

    // write output file
    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("fopen error\n");
    }

    fprintf(outputFile, "%d\n", size);
    for (i = 0; i < size; i++) {
        fprintf(outputFile, "%d\n", arr[i]);
    }

    return 0;
}
