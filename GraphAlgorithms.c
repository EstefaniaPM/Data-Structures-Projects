// Estefania Pitol Martinez		A01551688
// Fernanda Montano Rios		A01730440
// 27 November 2017
#include <stdio.h>
#include <stdlib.h>

// Prints the adjacency matrix
void printAdjacencyMatrix(int n, int m[n][n]) {
	int i, j;
	printf("\nAdjacency matrix:\n\n     ");
	for(i = 0; i < n; i++)
		printf("%2d ", i);
	printf("\n   +");
	for(i = 0; i < n; i++)
		printf("---");
	printf("\n");
	for(i = 0; i < n; i++) {
		printf("%2d | ", i);
		for(j = 0; j < n; j++)
			printf("%2d ", m[i][j]);
		printf("\n");
	}
}

struct edgeNode {
	int node1;
	int node2;
	int weight;
	struct edgeNode *next;
};

typedef struct edgeNode edgeNode;

// Creates an edge node and returns a pointer to it
edgeNode *createEdgeNode(int n1, int n2, int w) {
	edgeNode *temp;
	temp = malloc(sizeof(edgeNode));
	temp -> node1 = n1;
	temp -> node2 = n2;
	temp -> weight = w;
	temp -> next = NULL;
}

// Inserts an edge node to the list
void insertEdgeNode(edgeNode **head, int n1, int n2, int w) {
	if(!(*head))
		(*head) = createEdgeNode(n1, n2, w);
	else {
		while((*head) -> next)
			head = &(*head) -> next;
		(*head) -> next = createEdgeNode(n1, n2, w);
	}
}

// Creates an edge list
void createEdgeList(edgeNode **head, int n, int m[n][n]) {
	int i, j;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			if(m[i][j] != -1)
				insertEdgeNode(head, i, j, m[i][j]);
}

// Prints an edge list
void printEdgeList(edgeNode *head) {
	int i;
	i = 0;
	printf("\nEdge list:\n\n");
	while(head) {
		printf("Edge %d connects node %d with node %d with a weight %d\n", i++, head -> node1, head -> node2, head -> weight);
		head = head -> next;
	}
}

struct node {
	int value;
	int visited;
	struct connection *head;
	struct node *next;
};

struct connection {
	int weight;
	struct node *node;
	struct connection *next;
};

typedef struct node node;
typedef struct connection connection;

// Creates a node and returns a pointer to it
node *createNode(int v) {
	node *temp;
	temp = malloc(sizeof(node));
	temp -> value = v;
	temp -> visited = 0;
	temp -> head = NULL;
	temp -> next = NULL;
}

// Inserts a node to the list
void insertNode(node **head, int v) {
	if(!(*head))
		(*head) = createNode(v);
	else {
		while((*head) -> next)
			head = &(*head) -> next;
		(*head) -> next = createNode(v);
	}
}

// Creates a connection node and returns a pointer to it
connection *createConnection(int w, node *n) {
	connection *temp;
	temp = malloc(sizeof(connection));
	temp -> weight = w;
	temp -> node = n;
	temp -> next = NULL;
}

// Inserts a connection node to the list
void insertConnection(connection **head, int w, node *n) {
	if(!(*head))
		(*head) = createConnection(w, n);
	else {
		while((*head) -> next)
			head = &(*head) -> next;
		(*head) -> next = createConnection(w, n);
	}
}


// Returns the pointer to the node with a given value
node *find(node *head, int v) {
	if(head) {
		if(head -> value == v)
			return head;
		return find(head -> next, v);
	}
	return NULL;
}

// Creates an adjacency list
void createAdjacencyList(node **head, int n, int m[n][n]) {
	int i, j;
	for(i = 0; i < n; i++)
		insertNode(head, i);
	for(i = 0; i < n; i++) {
		connection *h;
		h = NULL;
		for(j = 0; j < n; j++)
			if(m[i][j] != -1)
				insertConnection(&h, m[i][j], find(*head, j));
		find(*head, i) -> head = h;
	}
}

// Prints an adjacency list
void printAdjacencyList(node *head) {
	printf("\nAdjacency list:\n\n");
	while(head) {
		while(head -> head) {
			printf("Node %d connects with node %d(weight: %d)\n", head -> value, head -> head -> node ->value, head -> head -> weight);
			head -> head = head -> head -> next;
		}
		head = head -> next;
	}
}

// Prints the matrix using a format 
// Parameter dist - distance
// Parameter source - principal node
int printDijkstra(int n, int dist[], int source) {
   for (int i = 0; i < n; i++){
      printf("From node %d to node %d: dist %d\n", source,i, dist[i]);
   }
}

// Finds the minimum distance
// Parameter dist - distancec to node source
// Parameter path - nodes that has already pass througth 
// Returns - the minimum 
int mDist(int n, int dist[], int path[]) {
   int min, mini;
   min = 1000000000;
   for(int a = 0; a < n; a++) {
     if(path[a] == 0 && dist[a] <= min)
         min = dist[a], mini = a;
   }
   return mini;
}

// Uses dijkstra algorithm 
// Parameter source - principal node 
// Parameter graph - gets the node 
void dijkstra(int n, int m[n][n], int source){
     int dist[n], path[n];
     for (int i = 0; i < n; i++){
        dist[i] = 1000000000, path[i] = 0;
     }
     dist[source] = 0;

     for (int count = 0; count < n-1; count++){
       int b = mDist(n, dist, path);
  
       path[b] = 1;
  
       for (int a = 0; a < n; a++){
         if (m[b][a] != -1 && !path[a] && m[b][a] && dist[b] != 1000000000 && dist[b] + m[b][a] < dist[a])
            dist[a] = dist[b] + m[b][a];
       }
     }
     printDijkstra(n, dist, source);
}

// Principal method for the program execution
// Returns - 0
int main() {
	int n, i, j;
	scanf("%d", &n);
	int matrix[n][n];
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			scanf("%d", &matrix[i][j]);
	printAdjacencyMatrix(n, matrix);
	edgeNode *headEdgeList;
	headEdgeList = NULL;
	createEdgeList(&headEdgeList, n, matrix);
	printEdgeList(headEdgeList);
	node *headAdjacencyList;
	headAdjacencyList = NULL;
	createAdjacencyList(&headAdjacencyList, n, matrix);
	printAdjacencyList(headAdjacencyList);
	printf("\nDijkstra:\n\n");
	for(i = 0; i < n; i++)
		dijkstra(n, matrix, i);
}