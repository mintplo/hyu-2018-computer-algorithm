#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "huffman.h"
#include "queue.h"

/**
 * Huffman Node를 새로 생성하여 리턴 하는 함수
 */
struct huffman_node* node(char ch, int freq)
{
  struct huffman_node* node = (struct huffman_node*)malloc(sizeof(struct huffman_node));
  node->ch = ch;
  node->freq = freq;
  node->l = NULL;
  node->r = NULL;
  node->next = NULL;

  return node;
}

/** 
 * Huffman Tree에 Node를 추가하는 함수
 * Ascending Order Priority Queue로 구성했기 때문에 삽입할 때 자신의 자리를 찾는 로직이 존재한다.
 */
void push(struct huffman_node **tree, struct huffman_node *node)
{
  struct huffman_node* start = (*tree);

  // Huffman Tree에 노드가 아예 없는 경우 Root Node로 삽입
  if ((*tree) == NULL) {
    (*tree) = node;
    return;
  }

  // Root Node의 Frequency가 삽입 하려는 노드의 Frequency보다 작은 경우 바로 Root Node를 교체한다.
  if ((*tree)->freq > node->freq) {
    node->next = *tree;
    (*tree) = node;

    return;
  }

  // 마지막 노드까지 왔거나 삽입하려는 노드의 frequency가 기존 노드의 frequency보다 작은 것을 찾을 때까지 순회한다.
  while (start->next != NULL && start->next->freq < node->freq)
    start = start->next;

  // 목적지에 도착했을 때 노드를 삽입하는 로직
  node->next = start->next;
  start->next = node;
}

/**
 * Priority Queue로 구성된 Huffman Tree에서 가장 작은 Frequency를 갖는 Node부터 빼는 함수
 */
struct huffman_node* pop(struct huffman_node **tree)
{
  struct huffman_node* temp = *tree;
  (*tree) = (*tree)->next;

  return temp;
}

/**
 * Huffman Node가 Leaf인지 아닌지를 확인하는 함수
 * : Leaf인지 아닌지를 확인하는 이유는 확인하려는 노드가 단순히 Frequency를 더해 만들어진 특별한 노드인지 아닌지를 확인하고자 한다.
 */
int isLeaf(struct huffman_node *node)
{
  return !(node->l) && !(node->r);
}
