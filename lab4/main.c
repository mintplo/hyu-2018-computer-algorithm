#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "huffman.h"

#define MAX_PRINT_SIZE 300

/**
  Print bit array

  @param[in]	encoded_str			Source bit array
  @param[in]	encoded_bit_size	Length of bit array, in bits
*/
void print_bit_array(const char *encoded_str, const int encoded_bit_size){
	int i;
	printf("encoded huffman code: ");
	if (encoded_bit_size > MAX_PRINT_SIZE){
		for (i = 0; i < (MAX_PRINT_SIZE+1) / 2; i++){
			printf("%d", GET_BIT(encoded_str, i));
		}
		printf(" ... ");
		for (i = encoded_bit_size - MAX_PRINT_SIZE / 2; i < encoded_bit_size; i++){
			printf("%d", GET_BIT(encoded_str, i));
		}
	}
	else{
		for (i = 0; i < encoded_bit_size; i++){
			printf("%d", GET_BIT(encoded_str, i));
		}
	}
	printf("\n");
}

/**
  Print string

  @param[in]	str			Source string
  @param[in]	str_size	Length of string, in bytes
*/
void print_string(const char *str, const int str_size){
	int i;
	printf("decoded string: ");
	if (str_size > MAX_PRINT_SIZE){
		for (i = 0; i < (MAX_PRINT_SIZE+1) / 2; i++){
			printf("%c", str[i]);
		}
		printf(" ... ");
		for (i = str_size - MAX_PRINT_SIZE / 2; i < str_size; i++){
			printf("%c", str[i]);
		}
	}
	else{
		printf("%s", str);
	}
	printf("\n");
}

int main(int argc, char *argv[]){
	int input_byte_size;
	int encoded_bit_size;
	int decoded_byte_size;
	char *input_str;
	char *encoded_str;
	char *decoded_str;
	struct huffman_node *root;

	// Check arguments of main
	if (argc != 2){
		fprintf(stderr, "Usage : %s <input-text-file>\n", argv[0]);
		return 1;
	}
	
	// Open input file
	FILE *in = fopen(argv[1], "r");
	if (in == NULL){
		fprintf(stderr, "fopen failed!\n");
		return 1;
	}

	// Get string size from file size
	fseek(in, 0L, SEEK_END);
	input_byte_size = ftell(in);
	fseek(in, 0L, SEEK_SET);

	// Allocate buffer space for string
	input_str = (char*)malloc(sizeof(char) * (input_byte_size + 1));
	encoded_str = (char*)malloc(sizeof(char) * (input_byte_size + 1));
	decoded_str = (char*)malloc(sizeof(char) * (input_byte_size + 1));

	// Read string from the input file
	if (fread(input_str, 1, input_byte_size, in) != input_byte_size){
		fprintf(stderr, "fread failed!\n");
		return 1;
	}
	if (input_str[input_byte_size - 1] == '\n'){
		input_str[--input_byte_size] = '\0';
	}
	fclose(in);

	// Encode input string to encoded bit array
	encoded_bit_size =
		encode_huffman(input_str, input_byte_size, &root, encoded_str);
	print_bit_array(encoded_str, encoded_bit_size);

	// Decode bit array to decoded string
	decoded_byte_size =
		decode_huffman(encoded_str, encoded_bit_size, root, decoded_str);
	print_string(decoded_str, decoded_byte_size);

	// Verify the result
	if (input_byte_size != decoded_byte_size ||
			strcmp(input_str, decoded_str) != 0){
		fprintf(stderr, "input string is not equal to decoded string\n");
	}
	// Print Compression ratio
	printf("Space Savings: %.2lf %%\n",
			(input_byte_size - ((encoded_bit_size - 1) / 8 + 1))
			* 100.0 / input_byte_size);
	return 0;
}
