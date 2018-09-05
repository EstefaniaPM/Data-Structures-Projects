#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

typedef struct node node;

node * createNode(int data) {
	node *newNode = (node *)malloc(sizeof(node));
	newNode -> data = data;
	newNode -> next = NULL;
	return newNode;
}

void appendToTail(node *head, int data) {
	node *newNode = createNode(data);
	while(head -> next != NULL)
		head = head -> next;
	head -> next = newNode;
}

void deleteTail(node *head) {

}

void printList(node *head) {
	while(head != NULL) {
		printf("%d", head -> data);
		if(head -> next != NULL)
			printf(" -> ");
		else
			printf("\n");
		head = head -> next;
	}
}

void printListRecursive(node *head) {
	printf("%d", head -> data);
	if(head -> next != NULL) {
		printf(" -> ");
		printListRecursive(head -> next);
	}
	else
		printf("\n");
}

int main() {
	int op;
	op = -1;
	while(op != 0) {
		printf(" 1. Insert at the beginning (cabeza, newData)\n");
		printf(" 2. Insert at the end (cabeza, newData)\n");
		//printf(" 3. insertar antes (cabeza, referencia, newData)\n");
		//printf(" 4. insertar después (cabeza, referencia, newData)\n");
		//printf(" 5. insertar n antes (cabeza, n, referencia, newData)\n");
		//printf(" 6. insertar n después (cabeza, n, referencia, newData)\n");
		printf(" 7. Delete at the beginning (cabeza)\n");
		printf(" 8. Delete at the end (cabeza)\n");
		//printf(" 9. borrar antes (cabeza, referencia)\n");
		//printf("10. borrar después (cabeza, referencia)\n");
		//printf("11. borrar n antes (cabeza, n, referencia)\n");
		//printf("12. borrar n después (cabeza, n, referencia)\n");
		printf("13. Print (cabeza)\n");
		printf("14. Reversed print (cabeza)\n");
		printf("15. Recursive print (cabeza)\n");
		printf("16. Recursive reversed print (cabeza)\n");
		printf("17. Search (cabeza, datos)\n");
		printf("18. Recursive search (cabeza, datos)\n");
		//printf("19. Sort ascendent (cabeza)\n");
		//printf("20. Sort descendent (cabeza)\n");
		printf(" 0. Exit\n");
		scanf("%d", &op);

		switch(op) {
			case 1:
			break;
			case 2:
			break;
			case 3:
			break;
			case 4:
			break;
			case 5:
			break;
			case 6:
			break;
			case 7:
			break;
			case 8:
			break;
			case 9:
			break;
			case 10:
			break;
			case 11:
			break;
			case 12:
			break;
			case 13:
			break;
			case 14:
			break;
			case 15:
			break;
			case 16:
			break;
			case 17:
			break;
			case 18:
			break;
			case 19:
			break;
			case 20:
			break;
		}
	}
}