#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hash.h"

#define A ((sqrt(5) - 1) / 2)

int checkNodeIfValid(HashNode*, int);

// Level 1 Hash Table 생성 함수
HashTable* makeHashTable(int size)
{
    int i;

    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));

    ht->size = size;
    ht->list = (HashNode**)malloc(sizeof(HashNode*) * size);

    for (i = 0; i < size; i++)
        ht->list[i] = NULL;

    return ht;
}

// Level 2 Hash Table 생성 함수
HashTable** makeHash2Table(int size, int* collisionDist)
{
    int i, j;

    HashTable** ht = (HashTable**)malloc(sizeof(HashTable*) * size);

    for (i = 0; i < size; i++) {
        ht[i] = (HashTable*)malloc(sizeof(HashTable));
        ht[i]->collision = (collisionDist[i] > 0) ? collisionDist[i] - 1 : 0;
        ht[i]->size = (int)pow(ht[i]->collision, 2);
        ht[i]->list = (HashNode**)malloc(sizeof(HashNode*) * ht[i]->size);

        for (j = 0; j < ht[i]->size; j++)
            ht[i]->list[j] = NULL;
    }

    return ht;
}

// 해시 노드 추가 함수
void insertHashNode(HashTable* ht, int key, int value, HashTable** ht2)
{
    int hashed, secondLvHashed, i, collision = 0;
    HashNode* node;
    HashNode* secondNode;

    hashed = hashing(key, ht->size);
    node = ht->list[hashed];
    if (node != NULL && ht2[hashed]->size > 0) {
        secondLvHashed = hashingWithProbing(key, ht2[hashed]->size, collision);
        while (ht2[hashed]->list[secondLvHashed] != NULL)
            secondLvHashed = hashingWithProbing(key, ht2[hashed]->size, ++collision);

        secondNode = (HashNode*)malloc(sizeof(HashNode));
        secondNode->key = key;
        secondNode->value = value;
        secondNode->deleted = 0;

        ht2[hashed]->list[secondLvHashed] = secondNode;
        return;
    }

    node = (HashNode*)malloc(sizeof(HashNode));
    node->key = key;
    node->value = value;
    node->deleted = 0;

    ht->list[hashed] = node;
}

HashNode* findHashNode(HashTable* ht, int key, HashTable** ht2)
{
    int hashed, secondLvHashed, collision = 0;
    HashNode* node;

    hashed = hashing(key, ht->size);
    node = ht->list[hashed];
    if (node != NULL && node->key != key && ht2[hashed]->size > 0) {
        //
        secondLvHashed = hashingWithProbing(key, ht2[hashed]->size, collision);
        while(ht2[hashed]->list[secondLvHashed] == NULL || ht2[hashed]->list[secondLvHashed]->key != key || ht2[hashed]->collision == collision)
            secondLvHashed = hashingWithProbing(key, ht2[hashed]->size, ++collision);

        //
        if (!checkNodeIfValid(ht2[hashed]->list[secondLvHashed], key)) {
            return NULL;
        }

        return ht2[hashed]->list[secondLvHashed];
    }

    //
    if (!checkNodeIfValid(node, key)) {
        return NULL;
    }

    return node;
}

int checkNodeIfValid(HashNode* node, int key)
{
    return (node != NULL && !node->deleted && node->key == key);
}

void deleteHashNode(HashTable* ht, int key, HashTable** ht2)
{
    int hashed, secondLvHashed, collision = 0;
    HashNode* node;

    hashed = hashing(key, ht->size);
    node = ht->list[hashed];
    if (node != NULL && node->key != key && ht2[hashed]->size > 0) {
        //
        secondLvHashed = hashingWithProbing(key, ht2[hashed]->size, collision);
        while(ht2[hashed]->list[secondLvHashed] == NULL || ht2[hashed]->list[secondLvHashed]->key != key || ht2[hashed]->collision == collision)
            secondLvHashed = hashingWithProbing(key, ht2[hashed]->size, ++collision);

        //
        if (ht2[hashed]->list[secondLvHashed] != NULL && ht2[hashed]->list[secondLvHashed]->key == key) {
            ht2[hashed]->list[secondLvHashed]->deleted = 1;
        }
    }

    //
    if (node != NULL && node->key == key) {
        node->deleted = 1;
    }
}

int hashing(int key, int size)
{
    int hashed;
    hashed = (int)floor(size * (key * A - floor(key * A)));

    return (hashed) % size;
}

int hashingWithProbing(int key, int size, int collision)
{
    int hashed, probing;
    hashed = ((int)floor(size * (key * A - floor(key * A))));

    if (collision == 0)
        probing = 0;
    else
        probing = (int)pow(collision, 2);

    return (hashed + probing) % size;
}
