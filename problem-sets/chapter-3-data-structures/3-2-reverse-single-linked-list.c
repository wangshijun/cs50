/**
 * @author	wangshijun
 * @copyright wangshijun2010@gmail.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
	int value;
	struct node *next;
} node;

void generate_list(node **list, int size);
void reverse_list(node **list);
void printf_list(node **list, char *label);

int main(int argc, char *argv[]) {
	node *list = NULL;

	generate_list(&list, 10);
	printf_list(&list, "Before Reverse");
	
	reverse_list(&list);
	printf_list(&list, "After Reverse");
}

void generate_list(node **list, int size) {
	srand(time(NULL));

	while (size > 0) {
		node *nodeptr = malloc(sizeof(node));
		if (nodeptr == NULL) {
			printf("Out of memory!\n");
			exit(1);
		}

		nodeptr->next = NULL;
		nodeptr->value = rand() % 100;

		if (*list == NULL) {
			*list = nodeptr;
		} else {
			nodeptr->next = *list;
			*list = nodeptr;
		}

		size--;
	}

}

void reverse_list(node **list) {
	node *previous = NULL;
	node *current = *list;

	while (current != NULL) {
		node *tmp = current->next;
		current->next = previous;
		previous = current;
		current = tmp;
	}

	*list = previous;
}

void printf_list(node **list, char *label) {
	printf("%s: ", label);
	node *ptr = *list;
	while (ptr != NULL) {
		printf(ptr->next == NULL ? "(%d)" : "(%d)->", ptr->value);
		ptr = ptr->next;
	}
	printf("\n");
}
