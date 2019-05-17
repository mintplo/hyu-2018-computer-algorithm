#ifndef __queue_h__
#define __queue_h__

/**
 * Huffman Node를 위한 Priority Queue.h
 */
struct huffman_node* node(char ch, int freq);
struct huffman_node* pop(struct huffman_node **tree);
void push(struct huffman_node **tree, struct huffman_node *node);
int isLeaf(struct huffman_node *node);
#endif /* __queue_h__ */