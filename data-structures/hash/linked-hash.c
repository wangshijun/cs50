/**
 * Simple hash implemented using char array
 *
 * @author wangshijun
 * @copyright wangshijun2010@gmail.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

#define HASH_SIZE 5

// function prototypes
int hash(char c);
void print_hash(char hash_table[]);

// main
int main (int argc, char *argv[]) {
	char hash_table[HASH_SIZE];
	int cmd = -1;
	char value = '0';

	// Initialize hash table to 0
	for (int i=0; i<HASH_SIZE; hash_table[i]='0', i++)

	do {
		printf("\nAvalibale commands: \n\n"
				"\t1 - Insert an element\n"
				"\t2 - Delete an element\n"
				"\t0 - Quit\n\n");

		printf("Your command: ");
		cmd = GetInt();

		switch (cmd) {
			case 1:
				printf("Char to insert: ");
				value = GetChar();
				hash_table[hash(value)] = value;
				break;
			case 2:
				printf("Char to delete: ");
				value = GetChar();
				hash_table[hash(value)] = '0';
				break;
			case 0:
				return 0;
		}

		print_hash(hash_table);

	} while (true);

	return 0;
}

// calculate hash value
int hash(char c) {
	return (int) c % HASH_SIZE;
}

// print out the hash table
void print_hash(char hash_table[]) {
	printf("\n");
	for (int i=0; i<HASH_SIZE; i++) {
		printf("\t%d => %c\n", i, hash_table[i]);
	}
	printf("\n");
}

