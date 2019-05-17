#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "huffman.h"
#include "queue.h"

void buildCodewordMap(struct huffman_node *node, struct codeword_node **codeword_map);
void traversal(struct huffman_node *node, struct codeword_node **codeword_map, int level, int codeword[]);

struct huffman_node** huffman(struct huffman_node **tree, int t_size);

/**
  Encode string to bit array using huffman coding algorithm

  @param[in]	src				Source raw string
  @param[in]	src_byte_size	Length of source string, in bytes
  @param[out]	dst_tree		Root node of huffman tree
  @param[out]	dst				Destination encoded bit array
  @return Length of encoded bit array, in bits (e.g. 0100 => 4)
*/
int encode_huffman(char *src, int src_byte_size, struct huffman_node **dst_tree, char *dst)
{
  int i, j, bit_size = 0, t_size = 0;
  int* freq_map;
  struct codeword_node** codeword_map;

  /**
   * Huffman Codes를 만들기 전 각 문자의 사용 빈도수를 계산하기 위해 frequency map을 만든다.
   */
  freq_map = (int*)calloc(ASCII_MAX, sizeof(int));
  for (i = 0; i < src_byte_size; i++)
    freq_map[(int)src[i]]++;

  /**
   * Ascending Ordered Priority Queue로 구현된
   * Huffman Tree에 각 문자의 사용 빈도 수 정보와 문자 데이터를 저장한 Node를 삽입한다.
   */
  for (i = 0; i < ASCII_MAX; i++) {
    // 사용되지 않는 문자는 Node에서 제외한다.
    if (freq_map[i] == 0)
      continue;

    // 처음 시작할 때 Huffman Tree에 할당된 Root Node가 없기 때문에 특별하게 할당한다.
    if (t_size == 0) {  
      t_size++;
      (*dst_tree) = node((char)i, freq_map[i]);
      continue;
    }

    t_size++;
    // 이미 Root Node가 있는 Huffman Tree에 새로운 노드를 삽입한다.
    push(dst_tree, node((char)i, freq_map[i]));
  }

  /** 
   * Ascending Ordered Priority Queue가 구성된 Huffman Tree를 이용해 Huffman Codes를 만든다.
   */
  dst_tree = huffman(dst_tree, t_size);

  /**
   * Huffman Codes를 계산할 수 있도록 구성된 Huffman Tree를 이용해
   * 각 문자의 Codeword를 미리 계산해 저장해놓는 용도로 Codeword Map을 만든다.
   */
  codeword_map = (struct codeword_node**)malloc(sizeof(struct codeword_node*) * ASCII_MAX);
  for (i = 0; i < ASCII_MAX; i++)
    codeword_map[i] = (struct codeword_node*)malloc(sizeof(struct codeword_node));

  // Codeword Map 생성
  buildCodewordMap(*dst_tree, codeword_map);

  // Huffman Codes 정보를 위해 만들어진 Codeword Map을 이용해 Source Text를 Encoding하는 로직
  for (i = 0; i < src_byte_size; i++) {
    // bit_size가 압축으로 나갈 dst의 current offset 역할을 하면서 또한 bit_size 자체 정보도 가지고 있는 역할도 수행한다.
    for (j = 0; j < codeword_map[src[i]]->size; j++) {
      // BIT를 1로 설정하는 경우가 아닌 0으로 설정하는 경우는 그대로 놔두기 때문에 해당 로직은 제외
      if (codeword_map[src[i]]->codeword[j])
        SET_BIT(dst, bit_size + j);
    }

    // 실제 BIT SIZE 반영
    bit_size += codeword_map[src[i]]->size;
  }

  return bit_size;
}

/**
 * 각 문자 별로 Huffman Codes를 기록하기 위한 Codeword Map을 구성하는 함수
 */
void buildCodewordMap(struct huffman_node *tree, struct codeword_node **codeword_map)
{
  int codeword[MAX_TREE_HT];
  traversal(tree, codeword_map, 0, codeword);
}

/**
 * Huffman Tree가 구성된 노드를 순회하면서 codeword 정보를 기록한다.
 */
void traversal(struct huffman_node *node, struct codeword_node **codeword_map, int level, int codeword[])
{
  if (node) {
    // 왼쪽 노드는 0
    if (node->l) {
      codeword[level] = 0;
      traversal(node->l, codeword_map, level + 1, codeword);
    }
    
    // 오른쪽 노드는 1
    if (node->r) {
      codeword[level] = 1;
      traversal(node->r, codeword_map, level + 1, codeword);
    }

    // Huffman Codes가 기록되어야하는 Leaf인 경우
    if (isLeaf(node)) {
      // Call By Value로 들어온 codeword 배열을 복사한다.
      codeword_map[(int)node->ch]->codeword = (int*)malloc(sizeof(int) * level);
      memcpy(codeword_map[(int)node->ch]->codeword, codeword, sizeof(int) * level);

      // Level이 곧 Codeword의 BIT SIZE
      codeword_map[(int)node->ch]->size = level;
    }
  }
}

/**
 * Huffman Tree를 구성하기 위한 함수
 */
struct huffman_node** huffman(struct huffman_node **tree, int t_size)
{
  int i;
  struct huffman_node* node;

  for (i = 0; i < t_size - 1; i++) {
    // Leaf의 frequency 정보만을 담고 있는 특별한 노드를 생성한다.
    node = (struct huffman_node*)malloc(sizeof(struct huffman_node));
    node->ch = '\0';

    // Huffman Tree가 Priority Queue 개념도 들어가 있기 때문에 Tree를 구성할 때 필요없는 next node 정보는 삭제한다.
    node->l = pop(tree);
    node->l->next = NULL;

    node->r = pop(tree);
    node->r->next = NULL;

    // L과 R Leaf 노드의 frequency 정보를 저장
    node->freq = node->l->freq + node->r->freq;
    push(tree, node);
  }

  return tree;
}

/**
  Decode bit array to string using huffman coding algorithm

  @param[in]	src				Source bit array
  @param[in]	src_bit_size	Length of bit array, in bits
  @param[in]	dst_tree		Root node of huffman tree
  @param[out]	dst				Destination string
  @return Length of decoded string, in bytes
*/
int decode_huffman(char *src, int src_bit_size, struct huffman_node *dst_tree, char *dst)
{
	int i, s_size = 0;
  struct huffman_node *node;

  /**
   * Decode Algorithm:
   * 
   * 인코딩된 Bit Size만큼 돌면서 Huffman Tree Path를 순회한다.
   * Leaf를 만날때 까지 1이면 R, 0이면 L로 순회하며
   * Leaf를 만나면 dst char array에 원래 문자를 할당한다.
   */
  node = dst_tree;
  for (i = 0; i < src_bit_size; i++) {
    node = (GET_BIT(src, i)) ? node->r : node->l;

    if (!isLeaf(node)) {
      continue;
    }

    // s_size가 string의 current offset 역할도 하며 총 문자열의 갯수 정보를 저장하는 역할도 한다.
    dst[s_size++] = node->ch;
    // Leaf를 찾았으면 다시 Root Node로 돌아가 순회할 준비를 한다.
    node = dst_tree;
  }

  /**
   * 위의 순서가 완료되었다고 모두 끝난 것이 아닌 CHAR ARRAY에 맨 마지막에 NULL 문자를 넣어줘야 한다.
   * 그래야 원래 문자열과 디코딩한 문자열을 제대로 비교할 수 있다.
   */
  dst[s_size] = '\0';

	return s_size;
}
