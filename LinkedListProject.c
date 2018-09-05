// Estefania Pitol Martinez 	A01551688
// Fernanda Montano Rios 		A01730440
// 18 October 2017
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	char data[1025];
	struct node *next;
};

// Creates and returns a pointer a pointer to a new node
// Parameter data - string of the new node
struct node * createNode(char data[]) {
	struct node * temp = malloc(sizeof(struct node));
	strcpy(temp -> data, data);
	temp -> next = NULL;
	return temp;
}

// Inserts a node after other in the list
// Parameter data - string of the new node
// Parameter head - pointer to the first node of the list
void insertNode(struct node *head, char data[]) {
	struct node *temp;
	temp = createNode(data);
	temp -> next = head -> next;
	head -> next = temp;
}

// Deletes a node after other in the list
// Parameter head - pointer to the first node of the list
void deleteNode(struct node *head) {
	struct node *temp;
	temp = head -> next;
	head -> next = head -> next -> next;
	free(temp);
}

// Returns the length of a list
// Parameter head - pointer to the first node of the list
int findLength(struct node *head) {
	int counter;
	counter = 0;
	while(head) {
		counter++;
		head = head -> next;
	}
	return counter;
}

// Returns the index of the node to search in the list
// Parameter data - string of the node to search
// Parameter head - pointer to the first node of the list
int search(struct node *head, char data[]) {
	int counter;
	counter = 0;
	while(head && strcmp(head -> data, data) != 0) {
		head = head -> next;
		counter++;
	}
	if(!head)
		return -1;
	return counter;
}

// Inserts a node at the beginning of the list
// Parameter data - string of the new node
// Parameter head - pointer to the pointer to the first node of the list
void insertAtTheBeginning(struct node **head, char data[]){
	struct node *temp;
	temp = createNode(data);
	temp -> next = *head;
	*head = temp;
}

// Inserts a node at the end of the list
// Parameter data - string of the new node
// Parameter head - pointer to the first node of the list
void insertAtTheEnd(struct node *head, char data[]) {
	while(head -> next)
		head = head -> next;
	insertNode(head, data);
}

// Inserts a node before another in the list
// Parameter data - string of the new node
// Parameter ref - string of the node to search
// Parameter head - pointer to the first node of the list
void insertBefore(struct node *head, char ref[], char data[]) {
	while(head -> next) {
		if(!strcmp(head -> next -> data, ref)) {
			insertNode(head, data);
			return;
		}
		else
			head = head -> next;
	}
}

// Inserts a node after another in the list
// Parameter data - string of the new node
// Parameter ref - string of the node to search
// Parameter head - pointer to the first node of the list
void insertAfter(struct node *head, char ref[], char data[]) {
	while(head) {
		if(!strcmp(head -> data, ref)) {
			insertNode(head, data);
			return;
		}
		else
			head = head -> next;
	}
}

// Inserts a node n nodes before another in the list
// Parameter data - string of the new node
// Parameter ref - string of the node to search
// Parameter head - pointer to the first node of the list
// Parameter n - number of nodes
int insertNBefore(struct node *head, int n, char ref[], char data[]) {
	int number, i;
	number = search(head, ref);
	number -= n;
	if(number <= 0)
		return number;
	for(i = 0; i < number - 1; i++)
		head = head -> next;
	insertNode(head, data);
	return number;
}

// Inserts a node n nodes after another in the list
// Parameter data - string of the new node
// Parameter ref - string of the node to search
// Parameter head - pointer to the first node of the list
// Parameter n - number of nodes
void insertNAfter(struct node *head, int n, char ref[], char data[]) {
	int number, length, i;
	number = search(head, ref);
	length = findLength(head);
	length = length - n - number;
	if(length <= 0)
		return;
	for(i = 0; i < number + n; i++)
		head = head -> next;
	insertNode(head, data);
}

// Deletes a node at the beginning of the list
// Parameter head - pointer to the pointer to the first node of the list
void deleteAtTheBeginning(struct node **head) {
	struct node *temp;
	temp = *head;
	*head = (*head) -> next;
	free(temp);
}

// Deletes a node at the end of the list
// Parameter head - pointer to the first node of the list
void deleteAtTheEnd(struct node *head) {
	while(head -> next -> next)
		head = head -> next;
	deleteNode(head);
}

// Deletes a node at the end of the list
// Parameter ref - string of the node to search
// Parameter head - pointer to the first node of the list
void deleteBefore(struct node *head, char ref[]) {
	while(head -> next -> next) {
		if(!strcmp(head -> next -> next -> data, ref)) {
			deleteNode(head);
			return;
		}
		else
			head = head -> next;
	}
}

// Deletes a node before another in the list
// Parameter ref - string of the node to search
// Parameter head - pointer to the first node of the list
void deleteAfter(struct node *head, char ref[]) {
	while(head -> next) {
		if(!strcmp(head -> data, ref)) {
			deleteNode(head);
			return;
		}
		else
			head = head -> next;
	}
}

// Deletes a node n nodes before another in the list
// Parameter ref - string of the node to search
// Parameter head - pointer to the first node of the list
// Parameter n - number of nodes
int deleteNBefore(struct node *head, int n, char ref[]) {
	int number, i;
	number = search(head, ref);	
	number = number - n - 1;
	if(number <= 0)
		return number;
	for(i = 0; i < number - 1; i++)
		head = head -> next;
	deleteNode(head);
	return number;
}

// Deletes a node n nodes after another in the list
// Parameter ref - string of the node to search
// Parameter head - pointer to the first node of the list
// Parameter n - number of nodes
void deleteNAfter(struct node *head, int n, char ref[]) {
	int number, length, i;
	number = search(head, ref);
	length = findLength(head);
	length = length - n - number -1;
	if(length <= 0)
		return;
	for(i = 0; i < number + n; i++)
		head = head -> next;
	deleteNode(head);
}

// Prints the list
// Parameter head - pointer to the first node of the list
void print(struct node *head) {
	while(head) {
		printf("%s", head -> data);
		head = head -> next;
		if(head)
			printf(" -> ");
	}
	printf("\n");
}

// Prints the list backwards
// Parameter head - pointer to the first node of the list
void printBackwards(struct node *head) {
	char *stack[1024];
	int counter, i;
	counter = 0;
	while(head) {
		stack[counter++] = head -> data;
		head = head -> next;
	}
	for(i = counter - 1; i >= 0; i--) {
		printf("%s", stack[i]);
		if(i != counter && i != 0)
			printf(" -> ");
	}
	printf("\n");
}

// Prints the list using recursion
// Parameter head - pointer to the first node of the list
void recursivePrint(struct node *head) {
	if(head) {
		printf("%s ", head -> data);
		if(head -> next)
			printf("-> ");
		else
			printf("\n");
		recursivePrint(head -> next);
	}
}

// Prints the list backwards using recursion
// Parameter head - pointer to the first node of the list
void recursiveBackwardsPrint(struct node *head) {
	if(head) {
		recursiveBackwardsPrint(head -> next);
		printf("%s  ", head -> data);
	}
}

// Returns the index of the node to search form the last to the first node
// Parameter data - string of the node to search
// Parameter head - pointer to the first node of the list
int searchFromLastToFirst(struct node *head, char data[]) {
	char *stack[1024];
	int counter, i;
	counter = 0;
	while(head) {
		stack[counter++] = head -> data;
		head = head -> next;
	}
	for(i = counter - 1; i >= 0; i--)
		if(!strcmp(stack[i], data))
			break;
	return i;
}

// Returns the index of the node to search using recursion
// Parameter data - string of the node to search
// Parameter head - pointer to the first node of the list
int recursiveSearch(struct node *head, char data[]) {
	if(head) {
		if(!strcmp(head -> data, data))
			return 0;
		return 1 + recursiveSearch(head -> next, data);
	}
	return 0;
}

// Returns the index of the node to search form the last to the first node using recursion
// Parameter data - string of the node to search
// Parameter head - pointer to the first node of the list
int recursiveSearchFromLastToFirst(struct node *head, char data[]) {
	if(!head)
		return -1;
	int i;
	i = recursiveSearchFromLastToFirst(head -> next, data);
	if(i != -1)
		return 1 + i;
	if(!strcmp(head -> data, data))
		return 0;
	return -1;
}

// Swaps the data of two nodes
// Parameter a - pointer to the first node
// Parameter b - pointer to the second node
void swap(struct node *a, struct node *b) {
	char temp[1025];
    strcpy(temp, a -> data);
    strcpy(a -> data, b -> data);
    strcpy(b -> data, temp);
}

// Sorts the list in ascending order
// Parameter head - pointer to the first node of the list
void ascendingSort(struct node *head) {
	struct node *aux;
	int swapped;
	do {
		aux = head;
		swapped = 0;
		while(aux -> next) {
			if(strcmp(aux -> data, aux -> next -> data) > 0) {
				swap(aux, aux -> next);
				swapped = 1;
			}
			aux = aux -> next;
		}
	} while(swapped);
}

// Sorts the list in descending order
// Parameter head - pointer to the first node of the list
void descendingSort(struct node *head) {
	struct node *aux;
	int swapped;
	do {
		aux = head;
		swapped = 0;
		while(aux -> next) {
			if(strcmp(aux -> data, aux -> next -> data) < 0) {
				swap(aux, aux -> next);
				swapped = 1;
			}
			aux = aux -> next;
		}
	} while(swapped);
}

// Main method for the program execution
int main() {
	int op, n, test;
	op = -1;
	struct node *head = NULL;
	char newData[1025], reference[1025];
	while(op != 0) {
		printf(" 1. Insert at the beginning\n");
		printf(" 2. Insert at the end\n");
		printf(" 3. Insert before\n");
		printf(" 4. Insert after\n");
		printf(" 5. Insert n before\n");
		printf(" 6. Insert n after\n");
		printf(" 7. Delete at the beginning\n");
		printf(" 8. Delete at the end\n");
		printf(" 9. Delete before\n");
		printf("10. Delete after\n");
		printf("11. Delete n before\n");
		printf("12. Delete n after\n");
		printf("13. Print\n");
		printf("14. Print backwards\n");
		printf("15. Recursive print\n");
		printf("16. Recursive backwards print\n");
		printf("17. Search\n");
		printf("18. Search from last to first\n");
		printf("19. Recursive search\n");
		printf("20. Recursive search from last to first\n");
		printf("21. Ascending sort the elements\n");
		printf("22. Descending sort the elements\n");
		printf(" 0. Quit\n");
		scanf("%d", &op);
		switch(op) {
			case 1:
				printf("Write down the string to insert:\n");
				scanf("\n");
				fgets(newData, 1024, stdin);
				newData[strlen(newData) - 1]= '\0';
				insertAtTheBeginning(&head, newData);
				break;
			case 2:
				printf("Write down the string to insert:\n");
				scanf("\n");
				fgets(newData, 1024, stdin);
				newData[strlen(newData) - 1]= '\0';
				if(head)
					insertAtTheEnd(head, newData);
				else
					insertAtTheBeginning(&head, newData);
				break;
			case 3:
				if(head) {
					printf("Write down the string of the node:\n");
					scanf("\n");
					fgets(reference, 1024, stdin);
					reference[strlen(reference) - 1] = '\0';
					printf("Write down the string to insert:\n");
					scanf("\n");
					fgets(newData, 1024, stdin);
					newData[strlen(newData) - 1]= '\0';
					if(!strcmp(head -> data, reference))
						insertAtTheBeginning(&head, newData);
					else
						insertBefore(head, reference, newData);
				}
				break;
			case 4:
				if(head) {
					printf("Write down the string of the node:\n");
					scanf("\n");
					fgets(reference, 1024, stdin);
					reference[strlen(reference) - 1] = '\0';
					printf("Write down the string to insert:\n");
					scanf("\n");
					fgets(newData, 1024, stdin);
					newData[strlen(newData) - 1]= '\0';
					insertAfter(head, reference, newData);
				}
				break;
			case 5:
				if(head) {
					printf("Write down n:\n");
					scanf("%d", &n);
					printf("Write down the string of the node:\n");
					scanf("\n");
					fgets(reference, 1024, stdin);
					reference[strlen(reference) - 1] = '\0';
					printf("Write down the string to insert:\n");
					scanf("\n");
					fgets(newData, 1024, stdin);
					newData[strlen(newData) - 1]= '\0';
					test = insertNBefore(head, n, reference, newData);
					if(!test)
						insertAtTheBeginning(&head, newData);				
				}
				break;
			case 6:
				if(head) {
					printf("Write down n:\n");
					scanf("%d", &n);
					printf("Write down the string of the node:\n");
					scanf("\n");
					fgets(reference, 1024, stdin);
					reference[strlen(reference) - 1] = '\0';
					printf("Write down the string to insert:\n");
					scanf("\n");
					fgets(newData, 1024, stdin);
					newData[strlen(newData) - 1]= '\0';
					insertNAfter(head, n, reference, newData);		
				}
				break;
			case 7:
				if(head)
					deleteAtTheBeginning(&head);
				break;
			case 8:
				if(head) {
					if(head -> next)
						deleteAtTheEnd(head);
					else
						deleteAtTheBeginning(&head);
				}
				break;
			case 9:
				if(head && head -> next) {
					printf("Write down the string of the node:\n");
					scanf("\n");
					fgets(reference, 1024, stdin);
					reference[strlen(reference) - 1] = '\0';
					if(!strcmp(head -> next -> data, reference))
						deleteAtTheBeginning(&head);
					else
						deleteBefore(head, reference);
				}
				break;
			case 10:
				if(head && head -> next) {
					printf("Write down the string of the node:\n");
					scanf("\n");
					fgets(reference, 1024, stdin);
					reference[strlen(reference) - 1] = '\0';
					deleteAfter(head, reference);
				}
				break;
			case 11:
				if(head && head -> next) {
					printf("Write down n:\n");
					scanf("%d", &n);
					printf("Write down the string of the node:\n");
					scanf("\n");
					fgets(reference, 1024, stdin);
					reference[strlen(reference) - 1] = '\0';
					test = deleteNBefore(head, n, reference);
					if(!test)
						deleteAtTheBeginning(&head);
				}
				break;
			case 12:
				if(head && head -> next) {
					printf("Write down n:\n");
					scanf("%d", &n);
					printf("Write down the string of the node:\n");
					scanf("\n");
					fgets(reference, 1024, stdin);
					reference[strlen(reference) - 1] = '\0';
					deleteNAfter(head, n, reference);
				}
				break;
			case 13:
				if(head)
					print(head);
				break;
			case 14:
				if(head)
					printBackwards(head);
				break;
			case 15:
				if(head)
					recursivePrint(head);
				break;
			case 16:
				if(head)
					recursiveBackwardsPrint(head);
					printf("\n");
				break;
			case 17:
				if(head) {
					printf("Write down the string of the node:\n");
					scanf("\n");
					fgets(reference, 1024, stdin);
					reference[strlen(reference) - 1] = '\0';
					test = search(head, reference);
					if(test >= 0)
						printf("String found at the number %d node\n", test);
					else
						printf("String not found\n");
				}
				break;
			case 18:
				if(head) {
					printf("Write down the string of the node:\n");
					scanf("\n");
					fgets(reference, 1024, stdin);
					reference[strlen(reference) - 1] = '\0';
					test = searchFromLastToFirst(head, reference);
					if(test >= 0)
						printf("String found at the number %d node\n", test);
					else
						printf("String not found\n");
				}
				break;
			case 19:
				if(head) {
					printf("Write down the string of the node:\n");
					scanf("\n");
					fgets(reference, 1024, stdin);
					reference[strlen(reference) - 1] = '\0';
					test = recursiveSearch(head, reference);
					if(test == findLength(head))
						printf("String not found\n");
					else
						printf("String found at the number %d node\n", test);
				}
				break;
			case 20:
				if(head) {
					printf("Write down the string of the node:\n");
					scanf("\n");
					fgets(reference, 1024, stdin);
					reference[strlen(reference) - 1] = '\0';
					test = recursiveSearchFromLastToFirst(head, reference);
					if(test >= 0)
						printf("String found at the number %d node\n", test);
					else
						printf("String not found\n");
				}
				break;
			case 21:
				if(head)
					ascendingSort(head);
				break;
			case 22:
				if(head)
					descendingSort(head);
				break;
		}
	}
}