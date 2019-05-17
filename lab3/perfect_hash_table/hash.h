#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

/* TODO: Implement your own node and hash table if needed */
typedef struct HashNode {
    int key;
    int value;
    int deleted;
} HashNode;

typedef struct HashTable {
    int size;
    int collision;
    HashNode** list;
} HashTable;

/* Support those below interfaces (used in main.c) */
HashTable* makeHashTable(int size);
HashTable** makeHash2Table(int size, int* collisionDist);
void insertHashNode(HashTable* ht, int key, int value, HashTable** ht2);
HashNode* findHashNode(HashTable* ht, int key, HashTable** ht2);
void deleteHashNode(HashTable* ht, int key, HashTable** ht2);
int hashing(int key, int size);
int hashingWithProbing(int, int, int);

#endif /* __HASHTABLE_H__ */
