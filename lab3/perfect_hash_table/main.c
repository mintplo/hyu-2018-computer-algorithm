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
    FILE* inputKeysFile;
    int* inputKeys;
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
    int* collisionDist;

    if (argc != 3) {
        usage();
        return 0;
    }

    // open input key set file
    inputKeysFile = fopen(argv[1], "r");
    if (inputKeysFile == NULL) {
        printf("input key file fopen error\n");
        return -1;
    }

    // open input file
    inputFile = fopen(argv[2], "r"); 
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

    // get input key set
    fscanf(inputKeysFile, "%d\n", &size);
    printf("size = %d\n", size);
    inputKeys = (int *) calloc(size, sizeof(int));
    for (i = 0; i < size; i++) {
        fscanf(inputKeysFile, "%d\n", &inputKeys[i]);
    }

    // TODO: with given key set, 
    // you can design your perfect hash table
    collisionDist = (int*)calloc(size, sizeof(int));
    for (i = 0; i < size; i++) {
        collisionDist[hashing(inputKeys[i], size)]++;
    }

    // get input size
    fscanf(inputFile, "%d\n", &size);
    
    // TODO: make hash table
    HashTable* ht = makeHashTable(size);
    HashTable** ht2 = makeHash2Table(size, collisionDist);

    // test measure start
    clock_gettime(CLOCK_MONOTONIC, &begin_ts);
    
    // TODO: insert tuples to hash table
    for (i = 0; i < size; i++) {
        fscanf(inputFile, "%c %d %d\n", &optype, &key, &val);
        if (optype == 'I') { 
            // TODO: insert
            insertHashNode(ht, key, val, ht2);
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
                node = findHashNode(ht, key, ht2);
                if (node == NULL) {
                    fprintf(outputFile, "Not Found\n");
                } else {
                    fprintf(outputFile, "%d\n", node->value);
                }
                break;
            case 'D': // TODO: delete
                deleteHashNode(ht, key, ht2);
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
