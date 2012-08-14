/**
 * Simple hash implemented using char array
 *
 * @author wangshijun
 * @copyright wangshijun2010@gmail.com
 * @TODO free allocated memory before quit
 */

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

#define HASH_SIZE 5

typedef struct node {
	char value;
	struct node *next;
} Node;

// function prototypes
int hash(char c);
void print_hash(Node *hash_table[]);
void print_list(Node *list);
Node *delete_list(Node *current, char value);

// main
int main (int argc, char *argv[]) {
	Node *hash_table[HASH_SIZE];
	int cmd = -1, slot = -1;
	char value = '0';

	// Initialize hash table to 0
	for (int i=0; i<HASH_SIZE; hash_table[i]=NULL, i++);
	// print_hash(hash_table);

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
				
				Node *ptr = malloc(sizeof(Node));
				if (ptr == NULL) {
					fprintf(stderr, "Out of memory!\n");
					exit(1);
				}

				ptr->value = value;
				ptr->next = NULL;

				slot = hash(value);
				
				if (hash_table[slot] == NULL) {
					hash_table[slot] = ptr;
				} else {
					// do not insert duplicate values
					bool exists = false;
					Node *current = hash_table[slot];
					while (current != NULL) {
						if (current->value == value) {
							exists = true;
							break;
						}
						current = current->next;
					}

					if (exists == false) {
						ptr->next = hash_table[slot];
						hash_table[slot] = ptr;
					} else {
						free(ptr);
					}
				}

				break;
			
			case 2:
				printf("Char to delete: ");
				value = GetChar();
				
				slot = hash(value);

				if (hash_table[slot] == NULL) {
					printf("%d does not exists in hash table!\n", value);
				} else {
					hash_table[slot] = delete_list(hash_table[slot], value);
				}

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
void print_hash(Node *hash_table[]) {
	printf("\n");
	for (int i=0; i<HASH_SIZE; i++) {
		printf("\t%d => ", i);
		if (hash_table[i] == NULL) {
			printf("NULL");
		} else {
			print_list(hash_table[i]);
		}
		printf("\n");
	}
	printf("\n");
}

// print singly linked list
void print_list(Node *list) {
	while (list != NULL) {
		printf((list->next == NULL) ? "%c" : "%c -> ", list->value);
		list = list->next;
	}
}

// Delete an item from a list (Using recursive approuch)
Node *delete_list(Node *current, char value) {
	if (current == NULL) {
		return NULL;
	}

	if (current->value == value) {
		Node *tmp = current->next;
		free(current);
		return tmp;
	}

	current->next = delete_list(current->next, value);

	return current;
}

