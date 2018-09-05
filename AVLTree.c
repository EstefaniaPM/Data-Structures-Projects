#include <stdio.h>
#include <stdlib.h>

struct treeNode {
	int key;
	struct treeNode *left;
	struct treeNode *right;
};

typedef struct treeNode treeNode;

treeNode *createNode(int data) {
	treeNode *temp;
	temp = malloc(sizeof(treeNode));
	temp -> key = data;
	temp -> left = NULL;
	temp -> right = NULL;
	return temp;
}

treeNode *exists(treeNode *root, int data) {
	if(root) {
		if(root -> key == data)
			return root;
		treeNode *temp;
		temp = exists(root -> left, data);
		if(temp)
			return temp;
		temp = exists(root -> right, data);
		if(temp)
			return temp;
		return NULL;
	}
	return NULL;
}

void insertNode(treeNode **root, int data) {
	if(!*root)
		*root = createNode(data);
	else
		if(data < (*root) -> key)
			insertNode(&(*root) -> left, data);
		else
			insertNode(&(*root) -> right, data);
}

int height(treeNode *node) {
    if(node) {
        int lheight, rheight;
        lheight = height(node -> left);
        rheight = height(node -> right);
        if(lheight > rheight)
            return lheight + 1;
        return rheight + 1;
    }
    return 0;
}

void printGivenLevel(treeNode *root, int level) {
    if(root) {
	    if(level == 1)
	        printf("%d ", root -> key);
	    else 
	    	if(level > 1) {
		        printGivenLevel(root -> left, level - 1);
		        printGivenLevel(root -> right, level - 1);
	    	}
    }
}

void levelOrderTraversal(treeNode *root) {
    int h, i;
    h = height(root);
    for(i = 1; i <= h; i++)
        printGivenLevel(root, i);
}

treeNode *isBalanced(treeNode *root) {
	if(root) {
		treeNode *temp = isBalanced(root -> left);
		if(!temp)
			temp = isBalanced(root -> right);
		if(abs(height(root -> left) - height(root -> right)) > 1 && !temp)
			return temp = root;
		return temp;
	}
	return NULL;
}

int countNodes(treeNode *root) {
	if(root) {
		int leftNodes, rightNodes;
		leftNodes = countNodes(root -> left);
		rightNodes = countNodes(root -> right);
		return leftNodes + rightNodes + 1;
	}
	return 0;
}

treeNode *zyxRotation(treeNode *root) {
	treeNode *c, *y;
	c = root -> left -> right;
	y = root -> left;
	y -> right = root;
	y -> right -> left = c;
	return y;
}

treeNode *zxyRotation(treeNode *root) {
	treeNode *b, *c, *y;
	b = root -> left -> right -> left;
	c = root -> left -> right -> right;
	y = root -> left -> right;
	y -> left = root -> left;
	y -> right = root;
	y -> left -> right = b;
	y -> right -> left = c;
	return y;
}

treeNode *xzyRotation(treeNode *root) {
	treeNode *b, *c, *y;
	b = root -> right -> left -> left;
	c = root -> right -> left -> right;
	y = root -> right -> left;
	y -> left = root;
	y -> right = root -> right;
	y -> left -> right = b;
	y -> right -> left = c;
	return y;
}

treeNode *xyzRotation(treeNode *root) {
	treeNode *b, *y;
	b = root -> right -> left;
	y = root -> right;
	y -> left = root;
	y -> left -> right = b;
	return y;
}

treeNode *parentNode(treeNode *root, int n) {
	if(root) {
		if(root -> key == n)
			return NULL;
		if((root -> left && root -> left -> key == n) || (root -> right && root -> right -> key == n)) {
			return root;
		}
		if(n < root -> key)
			return parentNode(root -> left, n);
		else 
			return parentNode(root -> right, n);
		return NULL;
	}
	return NULL;
}

void balanceTree(treeNode **root) {
	treeNode *problem, *parent, *balanced;
	problem = isBalanced(*root);
	if(problem) {
		parent = parentNode(*root, problem -> key);
		if(countNodes(problem -> left) > countNodes(problem -> right))
			if(countNodes(problem -> left -> left) > countNodes(problem -> left -> right))
				balanced = zyxRotation(problem);
			else
				balanced = zxyRotation(problem);
		else
			if(countNodes(problem -> right -> left) > countNodes(problem -> right -> right))
				balanced = xzyRotation(problem);
			else
				balanced = xyzRotation(problem);
		if(parent)
			if(parent -> left -> key == problem -> key)
				parent -> left = balanced;
			else
				parent -> right = balanced;
		else
			*root = balanced;
	}
}

int main() {
	int n, key, i;
	scanf("%d", &n);
	treeNode *root;
	root = NULL;
	for(i = 0; i < n; i++) {
		scanf("%d", &key);
		if(!exists(root, key))
			insertNode(&root, key);
		balanceTree(&root);
	}
	levelOrderTraversal(root);
	printf("\n");
}