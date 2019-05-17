#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "hash.h"

// 크누스 상수
#define A ((sqrt(5) - 1) / 2)

// 해시 함수
int hashing(int, int, int);

// 해시 테이블 생성 함수
HashTable* makeHashTable(int size)
{
    int i;

    // 해시 테이블 초기화
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));

    // 이미 SIZE * 3으로 입력 받은 값으로 해시 테이블을 초기화한다.
    ht->size = size;
    ht->list = (HashNode**)malloc(sizeof(HashNode*) * size);

    // FOR LOOP으로 해시 테이블의 목록을 NULL로 초기화
    for (i = 0; i < size; i++)
        ht->list[i] = NULL;

    return ht;
}

// 해시 노드 추가 함수
void insertHashNode(HashTable* ht, int key, int value)
{
    int collision = 0, hashed;

    // Linear Probing으로 Collision을 피해 비어있는 곳을 찾는다. (주요 단점: Primary Clustering)
    while(ht->list[hashing(key, ht->size, collision)] != NULL && !ht->list[hashing(key, ht->size, collision)]->deleted)
        collision++;

    // 비어있는 곳을 찾으면 해시 값을 이용해 할당한다.
    hashed = hashing(key, ht->size, collision);
    ht->list[hashed] = (HashNode*)malloc(sizeof(HashNode));
    ht->list[hashed]->key = key;
    ht->list[hashed]->value = value;
    ht->list[hashed]->deleted = 0;
}

// 해시 노드 찾기 함수
HashNode* findHashNode(HashTable* ht, int key)
{
    int collision = 0, hashed;

    // collision이 해시 테이블의 사이즈 만큼 날때까지 (linear probing limit size), 해당 키값을 갖는 해시 노드를 찾는다.
    do {
        if (collision == ht->size) {
            return NULL;
        }

        hashed = hashing(key, ht->size, collision++);
    } while(ht->list[hashed] != NULL && ht->list[hashed]->key != key);

    // 찾은 결과가 NULL이거나 주어진 키 값이 아니거나 지워졌다면(deleted 플래그를 두어서 판단) NULL을 반환한다.
    if (ht->list[hashed] == NULL ||  ht->list[hashed]->key != key || ht->list[hashed]->deleted) {
        return NULL;
    }

    // 그 외의 경우는 조건에 맞는 해시를 찾았다고 판단
    return ht->list[hashed];
}

// 해시 노드 삭제 함수
void deleteHashNode(HashTable* ht, int key)
{
    int collision = 0, hashed;
    HashNode* node;

    // 해시 노드 찾기 함수와 마찬가지로 collision이 해시 테이블의 사이즈 만큼 날때까지 (linear probing limit size), 해당 키 값을 갖는 해시 노드를 찾는다.
    do {
        if (collision == ht->size) {
            return;
        }

        hashed = hashing(key, ht->size, collision++);
    } while(ht->list[hashed] != NULL && ht->list[hashed]->key != key);

    // 해시 노드를 찾았다면 deleted 플래그를 1로 설정한다.
    if (ht->list[hashed] != NULL &&  ht->list[hashed]->key == key) {
        ht->list[hashed]->deleted = 1;
    }
}

// 해싱 함수
int hashing(int key, int size, int collision)
{
    // Mutliplication Method를 이용함. A값은 크누스 상수를 이용
    int hashed;
    hashed = (int)floor(size * (key * A - floor(key * A)));

    // Collision이 난 만큼 linear probing
    return (hashed + collision) % size;
}
