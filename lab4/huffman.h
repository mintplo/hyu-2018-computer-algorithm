#ifndef __huffman_h__
#define __huffman_h__

#define ASCII_MAX 255
#define MAX_TREE_HT 255

struct huffman_node {
	int freq;
	char ch;

	struct huffman_node* l;
	struct huffman_node* r;
	struct huffman_node* next;
};

// 각 문자의 Dynamic Size Codeword를 기억하기 위한 노드
struct codeword_node {
	int size;
	int* codeword;
};

/**
  Bit manipulation macros.
*/
// Get y-th bit in the buffer pointed by x
#define GET_BIT(x, y) (((x)[(y)/8] & (1 << (7 - ((y)%8)))) != 0)
// Set y-th bit in the buffer pointed by x
#define SET_BIT(x, y) do{\
	(x)[(y)/8] |= (1 << (7 - ((y)%8)));\
}while(0)
// Reset y-th bit in the buffer pointed by x
#define RESET_BIT(x, y) do{\
	(x)[(y)/8] &= (~(1 << (7 - ((y)%8))));\
}while(0)

int encode_huffman(char *src, int src_byte_size, struct huffman_node **dst_tree, char *dst);
int decode_huffman(char *src, int src_bit_size, struct huffman_node *dst_tree, char *dst);
#endif /* __huffman_h__ */
