#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hash.h"

#define BILLION 1000000000L

void usage(void)
{
    puts("Usage: ./main [input-file]");
}

int main(int argc, const char* argv[])
{
    int size;
    FILE* inputFile;
    FILE* outputFile;
    int i = 0;
    struct timespec begin_ts;
    struct timespec end_ts;
    unsigned long long time_diff;
    char optype;
    int key;
    int val;
    HashNode* node;

    if (argc > 2) {
        usage();
        return 0;
    }

    // open input file
    if (argc == 2) {
        inputFile = fopen(argv[1], "r");
    } else {
        inputFile = fopen("input.txt", "r");
    }
    if (inputFile == NULL) {
        printf("input file fopen error\n");
        return -1;
    }
    
    // open output file
    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("fopen error\n");
        return -1;
    }

    // get input size
    fscanf(inputFile, "%d\n", &size);
    printf("size = %d\n", size);

    // TODO: make hash table
    HashTable* ht = makeHashTable(size*3);

    // test measure start
    clock_gettime(CLOCK_MONOTONIC, &begin_ts);
    
    // TODO: insert tuples to hash table
    for (i = 0; i < size; i++) {
        fscanf(inputFile, "%c %d %d\n", &optype, &key, &val);
        if (optype == 'I') { 
            // TODO: insert
            insertHashNode(ht, key, val);
        } else {
            // error
            printf("input file error\n");
            return -1;
        }
    }

    while (1) {
        fscanf(inputFile, "%c %d\n", &optype, &key);
        switch (optype) {
            case 'F': // TODO: find
                node = findHashNode(ht, key);
                if (node == NULL) {
                    fprintf(outputFile, "Not Found\n");
                } else {
                    fprintf(outputFile, "%d\n", node->value);
                }
                break;
            case 'D': // TODO: delete
                deleteHashNode(ht, key);
                break;
            case 'Q': // end of test
                clock_gettime(CLOCK_MONOTONIC, &end_ts);
                goto done;
            default:
                fprintf(stderr, "invalid operation\n");
                goto done;
        }
    }

done:
    time_diff = (end_ts.tv_sec - begin_ts.tv_sec) * BILLION + 
        (end_ts.tv_nsec - begin_ts.tv_nsec);
    printf("Test Elapsed Time: %lf sec\n", (time_diff*1.0)/BILLION);
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
