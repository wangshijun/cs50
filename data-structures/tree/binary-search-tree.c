/*
 * =====================================================================================
 *
 *       Filename:  binary-search-tree.c
 *
 *    Description:  Binary search trees
 *
 *        Version:  1.0
 *        Created:  08/02/2012 02:19:23 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (http://www.weibo.com/wangshijun2010), wangshijun2010@gmail.com
 *   Organization:  Beijing Institute of Technology
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>

typedef struct tree {
	int value;
	struct tree *parent;
	struct tree *left;
	struct tree *right;
} tree;

tree *search(tree *parent, int value);
tree *min(tree *parent);
tree *max(tree *parent);

void traverse(tree *parent);
void insert(tree **root, int value, tree *parent);
void delete(tree **root, int value);

int get_int(char *prompt);
void flush_stdin(void);

int main(int argc, char *argv[]) {
	int cmd = 0, value = 0;
	tree *root = NULL;
	
	do {
		printf("Avaliable commands\n\n"
				"1 - Insert\n"
				"2 - Search\n"
				"3 - Delete\n"
				"4 - Minimum\n"
				"5 - Maximum\n"
				"0 - Quit\n\n");

		cmd = get_int("Command");

		switch (cmd) {
			case 1:
				value = get_int("value to insert");
				insert(&root, value, NULL);
				break;
			case 2:
				value = get_int("value to find");
				if (search(root, value) == NULL) {
					printf("%d is not found in tree!\n", value);
				} else {
					printf("%d is found in tree!\n", value);
				}
				break;
			case 3:
				value = get_int("value to delete");
				delete(&root, value);
				break;
		}
	
		printf("\n");
		for (int i=0; i<120; i++, printf("-"));
		printf("\n");
		
		traverse(root);
		
		printf("\n");
		for (int i=0; i<120; i++, printf("-"));
		printf("\n\n");

	} while (cmd != 0);

	return 0;
}

// Binary search in a tree
tree *search(tree *parent, int value) {
	if (parent == NULL) {
		return NULL;
	}

	if (value == parent->value) {
		return parent;
	}

	if (value < parent->value) {
		return search(parent->left, value);
	} else {
		return search(parent->right, value);
	}
}

// Find minimum item in the tree
tree *min(tree *parent) {
	if (parent == NULL) {
		return NULL;
	}

	tree *min = parent;
	while (min->left != NULL) {
		min = min->left;
	}

	return min;
}

// Find maximum item in the tree
tree *max(tree *parent) {
	if (parent == NULL) {
		return NULL;
	}

	tree *max = parent;
	while (max->right != NULL) {
		max = max->right;
	}

	return max;
}

// Walk through the tree using In-Order
void traverse(tree *parent) {
	if (parent != NULL) {
		traverse(parent->left);
		printf("(%d)->", parent->value);
		traverse(parent->right);
	}
}

// Insert an element in the tree
void insert(tree **root, int value, tree *parent) {
	tree *p = NULL;

	// Insert to an empty tree
	if (*root == NULL) {
		p = malloc(sizeof(tree));

		p->value = value;
		p->left = NULL;
		p->right = NULL;
		p->parent = parent;

		*root = p;

		return;
	}

	if (value < (*root)->value) {
		insert(&((*root)->left), value, *root);
	} else {
		insert(&((*root)->right), value, *root);
	}
}

void delete(tree **root, int value) {
	// Nothing to do if empty tree
	if (*root == NULL) {
		return;
	}

	tree *parent = *root, 
		 *current = *root;

	while (current != NULL) {
		// value was found on a node
		if (value == current->value) {

			// delete a leaf node OR an empty tree
			if (current->left == NULL && current->right == NULL) {
				if (current == *root) {
					free(*root);
					*root = NULL;
				} else {
					if (current->value < parent->value) {
						parent->left = NULL;	
					} else {
						parent->right = NULL;
					}
					free(current);
				}
			}
			
			// delete a single-child node
			else if (current->left == NULL || current->right == NULL) {
				if (current->value < parent->value) {
					if (current->left == NULL) {
						parent->left = current->right;
						current->right->parent = parent;
					} else {
						parent->left = current->left;
						current->left->parent = parent;
					}
				} else {
					if (current->left == NULL) {
						parent->right = current->right;
						current->right->parent = parent;
					} else {
						parent->right = current->left;
						current->left->parent = parent;
					}
				}
				free(current);
			}
			
			// delete a double-child node, (ROOT that has two child cannot be deleted)
			else {
				if (current == *root) {
					printf("Sorry, cannot delete root node that has both left and right child!\n");
				} else {
					tree *submin = min(current->right);

					// make a clone of min in right subtree
					tree *clone = malloc(sizeof(tree));

					clone->value = submin->value;
					clone->parent = parent;
					clone->left = current->left;

					if (submin == current->right) {
						clone->right = NULL;
					} else {
						clone->right = current->right;
					}

					// assign clone to parent left/right
					if (current->value < parent->value) {
						parent->left = clone;
					} else {
						parent->right = clone;
					}

					// update parent of the lifted node
					if (submin->value < submin->parent->value) {
						submin->parent->left = NULL;
					} else {
						submin->parent->right = NULL;
					}

					// free min AND current
					free(current);
					free(submin);
				}
			}

			return;
		
		// continue search for value
		} else {
			parent = current;
			if (value < current->value) {
				current = current->left;
			} else {
				current	= current->right;
			}
		}
	}

	printf("%d is not found in tree\n", value);

}

// Get int
int get_int(char *prompt) {
	int value = 0;

	printf("%s: ", prompt);
	scanf("%d", &value);
	
	flush_stdin();

	return value;
}

// Flush input buffer
void flush_stdin(void) {
	while (getc(stdin) != '\n');
}

