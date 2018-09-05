// Estefania Pitol Martinez 	A01551688
// Fernanda Montano Rios 		A01730440
// 15 November 2017
// Mathematical Expression Binary Tree
// Arithmetic Expression Binary Tree

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct treeNode {
	char key;
	unsigned long int value;
	struct treeNode *left;
	struct treeNode *right;
};

typedef struct treeNode treeNode;

// Creates a tree node and returns a pointer to it
treeNode *createTreeNode(char key, unsigned long int value) {
	treeNode *temp = malloc(sizeof(treeNode));
	temp -> key = key;
	temp -> value = value;
	temp -> left = NULL;
	temp -> right = NULL;
	return temp;
}

// Prints the tree as prefix
void prefix(struct treeNode *root) {
	if(root) {
		if(root -> key == 'x')
			printf("%lu ", root -> value);
		else
			printf("%c ", root -> key);
		prefix(root -> left);
		prefix(root -> right);
	}
}
// Prints the tree as infix
void infix(struct treeNode *root) {
	if(root) {
		if(root -> key == '+' || root -> key == '-' || root -> key == '*' || root -> key == '/')
			printf("(");
		infix(root -> left);
		if(root -> key == 'x')
			printf("%lu", root -> value);
		else
			printf("%c", root -> key);
		infix(root -> right);
		if(root -> key == '+' || root -> key == '-' || root -> key == '*' || root -> key == '/')
			printf(")");
	}
}

// Prints the tree as postfix
void postfix(struct treeNode *root) {
	if(root) {
		postfix(root -> left);
		postfix(root -> right);
		if(root -> key == 'x')
			printf("%lu ", root -> value);
		else
			printf("%c ", root -> key);
	}
}

int ind;

// Converts a string and returns the number pointing to the firs digit
unsigned long int toNumber(char line[]) {
	unsigned long int n;
	n = 0;
	while(line[ind] >= '0' && line[ind] <= '9') {
		n *= 10;
		n += (unsigned long int)line[ind] - '0';
		ind++;
	}
	return n;
}

// Converts a string and returns the number pointing to the last digit
unsigned long int toNumberReversed(char line[]) {
	unsigned long int n;
	int i;
	n = 0;
	while(line[ind] >= '0' && line[ind] <= '9')
		ind--;
	i = ind + 1;
	while(line[i] >= '0' && line[i] <= '9') {
		n *= 10;
		n += (unsigned long int)line[i] - '0';
		i++;
	}
	return n;
}

// Builds a tree out of a prefix input and returns a pointer to the root
treeNode *buildTreePrefix(char line[]) {
	if(line[ind] != '\0') {
		if(line[ind] == ' ')
			ind++;
		if(line[ind] == '+' || line[ind] == '-' || line[ind] == '*' || line[ind] == '/') {
			treeNode *temp = createTreeNode(line[ind], 0);
			ind++;
			temp -> left = buildTreePrefix(line);
			temp -> right = buildTreePrefix(line);
			return temp;
		}
		if(line[ind] >= '0' && line[ind] <= '9')
			return createTreeNode('x', toNumber(line));
		return NULL;
	}
	return NULL;
}

// Builds a tree out of a infix input and returns a pointer to the root
treeNode *buildTreeInfix(char line[]) {
	if(line[ind] != '\0') {
		if(line[ind] == '(') {
			treeNode *temp = createTreeNode('x', 0);
			ind++;
			temp -> left = buildTreeInfix(line);
			temp -> key = line[ind];
			ind++;
			temp -> right = buildTreeInfix(line);
			while(line[ind] == ')') {
				ind++;
				return temp;
			}
		}
		if(line[ind] >= '0' && line[ind] <= '9')
			return createTreeNode('x', toNumber(line));
		return NULL;
	}
	return NULL;
}

// Builds a tree out of a postfix input and returns a pointer to the root
treeNode *buildTreePostfix(char line[]) {
	if(ind >= 0) {
		if(line[ind] == ' ')
			ind--;
		if(line[ind] == '+' || line[ind] == '-' || line[ind] == '*' || line[ind] == '/') {
			treeNode *temp = createTreeNode(line[ind], 0);
			ind--;
			temp -> right = buildTreePostfix(line);
			temp -> left = buildTreePostfix(line);
			return temp;
		}
		if(line[ind] >= '0' && line[ind] <= '9')
			return createTreeNode('x', toNumberReversed(line));
		return NULL;
	}
	return NULL;
}

// Returns the final result of the Mathematical Expression Binary Tree given a pointer to the root
unsigned long int calculate(treeNode *root) {
	if(root -> key != 'x') {
		switch(root -> key) {
			case '+':
				return calculate(root -> left) + calculate(root -> right);
			case '-':
				return calculate(root -> left) - calculate(root -> right);
			case '*':
				return calculate(root -> left) * calculate(root -> right);
			case '/':
				return calculate(root -> left) / calculate(root -> right);
		}
	}
	return root -> value;
}

int main() {
	int cases, i;
	treeNode *root;
	char line[1025];
	scanf("%d", &cases);
	scanf("\n");
	for(i = 0; i < cases; i++) {
		fgets(line, 1024, stdin);
		line[strlen(line) - 1] = '\0';
		ind = 0;
		if(line[0] == '+' || line[0] == '-' || line[0] == '*' || line[0] == '/')
			root = buildTreePrefix(line);
		else
			if(line[0] == '(')
				root = buildTreeInfix(line);
			else {
				ind = strlen(line) - 1;
				root = buildTreePostfix(line);
			}
		printf("\nPrefix:  ");
		prefix(root);
		printf("\nInfix:   ");
		infix(root);
		printf("\nPostfix: ");
		postfix(root);
		printf("\nResult:  %lu\n", calculate(root));
	}
}