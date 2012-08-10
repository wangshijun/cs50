/*
 * =====================================================================================
 *
 *       Filename:  3-1-parentheses-detect.c
 *
 *    Description:  Determine whether the parentheses in a string are balanced and properly nested
 *
 *        Version:  1.0
 *        Created:  08/03/2012 04:28:29 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (http://www.weibo.com/wangshijun2010), wangshijun2010@gmail.com
 *   Organization:  Beijing Institute of Technology
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

#define MAX_STRING_LENGTH 128
#define MAX_STACK_SIZE 64

#define true 1
#define false 0

typedef int bool;

typedef struct stack {
	int length;
	int items[MAX_STACK_SIZE];
} stack;

char *get_string(char *prompt);
int is_equal(char *source, char *match);
void push(stack **stackpp, int value);
int pop(stack **stackpp);
void clear(stack **stackpp);
int is_empty(stack **stackpp);
void print_stack(stack **stackpp, char *label);
void flush_stdin(void);

int main (int argc, char *argv[]) {
	printf("Welcome using parentheses spellchecker!\n\n");

	stack *stackp = malloc(sizeof(stack));

	do {
		// get some string from user
		char *string = get_string("Input a string");

		// detect user quit
		if (is_equal(string, "quit")) {
			break;
		}

		// empty the stack for next run
		clear(&stackp);

		// analyze: push when meet "(" while pop when meed ")"
		int i = 0, error = 0;
		while (string[i] != '\0') {
			if (string[i] == '(') {
				push(&stackp, i);	
			} else if (string[i] == ')') {
				int match = pop(&stackp);
				// error in the middle
				if (match == -1) {
					printf("Parenthesis not match at %d(M)\n", i);
					error = 1;
					break;
				}
			}
		
			// move to next char
			i++;
		}

		// if the stack is not empty, there must be mismatch
		if (!error) {
			if (is_empty(&stackp)) {
				printf("Congratulations! all parenthesis are match!\n");
			} else {
				printf("Parenthesis not match at %d(E)\n", i-1);
			}
		}

		// free string memory
		free(string);

		printf("\n");

	} while (true);

	free(stackp);
}

// Get string from user input
char *get_string(char *prompt) {
    printf("%s: ", prompt);
    
    // growable buffer for chars
    char *buffer = NULL;

    // capacity of buffer
    unsigned int capacity = 0;

    // number of chars actually in buffer
    unsigned int n = 0;

    // character read or EOF
    int c;

    // iteratively get chars from standard input
    while ((c = fgetc(stdin)) != '\n' && c != EOF) {
        // grow buffer if necessary
        if (n + 1 > capacity) {
            // determine new capacity: start at 32 then double
            if (capacity == 0)
                capacity = 32;
            else if (capacity <= (INT_MAX / 2))
                capacity *= 2;
            else {
                free(buffer);
                return NULL;
            }

            // extend buffer's capacity
            char *temp = realloc(buffer, capacity * sizeof(char));
            if (temp == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = temp;
        }

        // append current character to buffer
        buffer[n++] = c;
    }

    // return NULL if user provided no input
    if (n == 0 && c == EOF)
        return NULL;

    // minimize buffer
    char *minimal = malloc((n + 1) * sizeof(char));
    strncpy(minimal, buffer, n);
    free(buffer);

    // terminate string
    minimal[n] = '\0';

    // return string
    return minimal;
}

// Detect two string is equal
int is_equal(char *source, char *match) {
	int i = 0;
	while (source[i] == match[i] && i < strlen(source)) {
		i++;
	}

	if (source[i] == '\0' && match[i] == '\0') {
		return 1;
	}

	return 0;
}

// Push a pair of parenthese on to the stack
void push(stack **stackpp, int value) {
	if ((*stackpp)->length + 1 >= MAX_STACK_SIZE) {
		printf("Sorry, the parentheses stack is out of size!\n");
		exit(1);
	}

	(*stackpp)->items[(*stackpp)->length] = value;
	(*stackpp)->length = (*stackpp)->length + 1;

	print_stack(stackpp, "push");
}


// Pop an element off the stack
int pop(stack **stackpp) {
	if (is_empty(stackpp)) {
		return -1;
	}

	(*stackpp)->length = (*stackpp)->length - 1;
	(*stackpp)->items[(*stackpp)->length] = -1;

	print_stack(stackpp, "pop");

	return (*stackpp)->items[(*stackpp)->length - 1];
}

// Clear the stack
void clear(stack **stackpp) {
	(*stackpp)->length = 0;
	for (int i=0; i<MAX_STACK_SIZE; i++) {
		(*stackpp)->items[i] = -1;
	}
}

// if the stack is empty
int is_empty(stack **stackpp) {
	return (*stackpp)->length == 0 ? 1 : 0;
}

// Print the stack in line
void print_stack(stack **stackpp, char *label) {
	printf("%s: ", label);
	for (int i=0; i<(*stackpp)->length; i++) {
		printf("(%d),", (*stackpp)->items[i]);
	}
	printf("\n");
}

// Flush strin
void flush_stdin(void) {
	while (getc(stdin) != '\n');
}
