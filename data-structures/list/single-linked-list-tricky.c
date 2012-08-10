/*
 * =====================================================================================
 *
 *       Filename:  single-linked-list.c
 *
 *    Description:  My single linked sorted list
 *
 *        Version:  1.0
 *        Created:  08/01/2012 10:19:21 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (http://www.weibo.com/wangshijun2010), wangshijun2010@gmail.com
 *   Organization:  Beijing Institute of Technology
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node *next;
} node;


void insert(void);
void delete(void);
void iterate(void);
void search(void);
void flush_stdin(void);

node *list = NULL;

int main(int argc, char *argv[]) {
	int command;

	do {
		printf("Avaliable commands\n\n"
				"1 - Insert\n"
				"2 - Delete\n"
				"3 - Search\n"
				"0 - Quit\n\n");

		printf("Your command: ");

		scanf("%d", &command);
		flush_stdin();

		printf("\n");

		switch (command) {
			case 1: insert(); break;
			case 2: delete(); break;
			case 3: search(); break;
		}

		iterate();
	
	} while (command != 0);

	// free the list
	node *ptr = list;
	while (ptr != NULL) {
		node *previous = ptr;
		ptr = ptr->next;
		free(previous);
	}

	return 0;
}

// Insert a node into list
void insert(void) {

	node *new = malloc(sizeof(node));
	if (new == NULL) {
		fprintf(stderr, "Out of memory!\n");
		exit(1);
	}
	new->next = NULL;

	printf("Value to insert: ");
	scanf("%d", &(new->value));
	flush_stdin();

	// empty list
	if (list == NULL) {
		list = new;
		return;
	}

	// at the middle of list
	node **lpp;
	for (lpp = &list; *lpp != NULL; lpp = &(*lpp)->next) {
		node *lp = *lpp;
		if (new->value < lp->value) {
			new->next = lp;
			*lpp = new;
			return;
		} else if (lp->value == new->value) {
			free(new);
			return;
		}
	}

	// at the end of list
	*lpp = new;
}

// delete an node from list
void delete(void) {

	int value;
	printf("Value to delete: ");
	scanf("%d", &value);
	flush_stdin();

	for (node **lpp = &list; *lpp != NULL; lpp = &(*lpp)->next) {
		node *lp = *lpp;
		if ((*lpp)->value == value) {
			*lpp = (*lpp)->next;
			free(lp);
			break;
		}
	}
}


// search for an item in the list
void search(void) {
	int value;
	printf("Value to search: ");
	scanf("%d", &value);
	flush_stdin();

	node *ptr = list;
	while (ptr != NULL) {
		if (ptr->value == value) {
			printf("%d was found in list!\n", value);
			return;
		}

		ptr = ptr->next;
	}
	
	printf("%d was not found in list!\n", value);
}

// iterate the list
void iterate(void) {
	node *ptr = list;

	for(int i=0; i<80; i++, printf("-"));
	printf("\n");
	
	while (ptr != NULL) {
		printf((ptr->next == NULL) ? "(%d)" : "(%d)->", ptr->value);
		ptr = ptr->next;
	}
	
	printf("\n");
	for(int i=0; i<80; i++, printf("-"));
	printf("\n");
}

void flush_stdin(void) {
	while (getc(stdin) != '\n');
}
