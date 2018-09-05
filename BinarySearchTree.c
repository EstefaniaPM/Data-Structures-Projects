// Estefania Pitol Martinez		A01551688
// Fernanda Montano Rios		A01730440
#include <stdio.h>
#include <stdlib.h>

struct treeNode {
	int key;
	struct treeNode *left;
	struct treeNode *right;
};

// Returns a pointer to the new BST node
// Creates and returns a pointer a pointer to a new BST node
// Parameter data - int for the key value
struct treeNode * createNode(int data) {
	struct treeNode *temp;
	temp = malloc(sizeof(struct treeNode));
	temp -> key = data;
	temp -> left = NULL;
	temp -> right = NULL;
	return temp;
}

// Returns 1 if a key with a certain value exists or 0 if not
// Parameter data - int for the key value to search
// Parameter root - pointer to the root of the BST
int exists(struct treeNode *root, int data) {
	if(root) {
		if(root -> key == data)
			return 1;
		if(exists(root -> left, data))
			return 1;
		if(exists(root -> right, data))
			return 1;
		return 0;
	}
	return 0;
}

// Inserts a node in the BST
// Parameter data - int for the key value
// Parameter root - pointer to pointer to the root of the BST
void insertNode(struct treeNode **root, int data) {
	if(!*root)
		*root = createNode(data);
	else
		if(data < (*root) -> key)
			insertNode(&(*root) -> left, data);
		else
			insertNode(&(*root) -> right, data);
}

// Prints the pre-order traversal of the BST
// Parameter root - pointer to the root of the BST
void preOrderTraversal(struct treeNode *root) {
	if(root) {
		printf("%d ", root -> key);
		preOrderTraversal(root -> left);
		preOrderTraversal(root -> right);
	}
}

// Prints the in-order traversal of the BST
// Parameter root - pointer to the root of the BST
void inOrderTraversal(struct treeNode *root) {
	if(root) {
		inOrderTraversal(root -> left);
		printf("%d ", root -> key);
		inOrderTraversal(root -> right);
	}
}

// Prints the post-order traversal of the BST
// Parameter root - pointer to the root of the BST
void postOrderTraversal(struct treeNode *root) {
	if(root) {
		postOrderTraversal(root -> left);
		postOrderTraversal(root -> right);
		printf("%d ", root -> key);
	}
}

// Returns the number of nodes along the longest path from the root node down to the farthest leaf node
// Parameter node - pointer to a node of the BST
int height(struct treeNode *node) {
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

// Prints nodes at a given level
// Parameter root - pointer to the root of the BST
// Parameter level - level number to print
void printGivenLevel(struct treeNode* root, int level) {
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

// Prints the level-order traversal of the BST
// Parameter root - pointer to the root of the BST
void levelOrderTraversal(struct treeNode* root) {
    int h, i;
    h = height(root);
    for(i = 1; i <= h; i++)
        printGivenLevel(root, i);
}

int main() {
	int n, key, i;
	scanf("%d", &n);
	struct treeNode *root;
	root = NULL;
	for(i = 0; i < n; i++) {
		scanf("%d", &key);
		if(!exists(root, key))
			insertNode(&root, key);
	}
	printf("\nPre-order Traversal:\n");
	preOrderTraversal(root);
	printf("\nIn-order Traversal:\n");
	inOrderTraversal(root);
	printf("\nPost-order Traversal:\n");
	postOrderTraversal(root);
	printf("\nLevel-order Traversal:\n");
	levelOrderTraversal(root);
	printf("\n");
}