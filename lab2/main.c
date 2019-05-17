#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

int verbose = 0;
enum sortingType { BUBBLESORT, QUICKSORT, COUNTSORT };

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
    puts("Usage: ./main [sorting-type] [input-file]");
    puts("sorting-type");
    puts("  b\tbubble sort");
    puts("  q\tquick sort");
    puts("  c\tcount sort");
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

    if (argc < 2 || argc >= 4) {
        usage();
        return 0;
    }

    ch = *argv[1];
    switch(ch) {
        case 'b':
            st = BUBBLESORT;
            break;
        case 'q':
            st = QUICKSORT;
            break;
        case 'c':
            st = COUNTSORT;
            break;
        default:
            usage();
            return 0;
    }

    // read input file
    if (argc == 3) {
        inputFile = fopen(argv[2], "r");
    } else {
        verbose = 1; 
        inputFile = fopen("input-small.txt", "r");
    }
    
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
        case QUICKSORT:
            printf("Quick Sort Starts!\n");
            quickSort(arr, size);
            break;
        case COUNTSORT:
            printf("Count Sort Starts!\n");
            countSort(arr, size);
            break;
        default:
            printf("Wrong Sort Type..\n");
            return 0;
    }

    if (verbose) {
        printArr(arr, size);
    }

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
