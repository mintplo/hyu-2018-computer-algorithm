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
    HashNode** list;
} HashTable;

/* Support those below interfaces (used in main.c) */
HashTable* makeHashTable(int size);
void insertHashNode(HashTable* ht, int key, int value);
HashNode* findHashNode(HashTable* ht, int key);
void deleteHashNode(HashTable* ht, int key);

#endif /* __HASHTABLE_H__ */
