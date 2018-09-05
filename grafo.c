/*
Tabatha Tabeli Acosta Pastrana      |   A01550280
Daniel Carramiñana Carrasco         |   A01731006
*/

#include <stdio.h>
#include <stdlib.h>

int adjMatrix[100][100];
struct nodeQueue * headQueue;
struct nodeQueue * tailQueue;

struct nodeQueue{
	int value;
	struct nodeQueue * next;
};

struct node{
	int value;
	struct node * nextValue;
	struct adjNode * adjacent;
};

struct adjNode{
	int weight;
	struct node * ref;
	struct adjNode * next;
};
/*Function that creates and returns a new node*/
struct node * createNode(int newValue){
	struct node * tmp;
	tmp = (struct node *)malloc(sizeof(struct node));
	tmp -> value = newValue;
	tmp -> nextValue = NULL;
	tmp -> adjacent = NULL;
}
/*Function that creates and returns a new adjacent Node*/
struct adjNode * createAdj(int w){
	struct adjNode * tmp;
	tmp = (struct adjNode *)malloc(sizeof(struct adjNode));
	tmp -> weight = w;
	tmp -> ref =NULL;
	tmp -> next= NULL;
	return tmp;
}
/*Function that creates a list of lists, by reading the adjacency matrix. The main list is composed of the number of nodes, and each node
contains a pointer to each adjacent nodes, and the weight is saved in the adjacent nodes*/
struct node * createGraph(int n){
	struct node * runner;
	struct node * runner2;
	struct node * tmp;
	struct node * head;
	struct adjNode * aysi;
	struct adjNode * otro;
	head = NULL;
	for(int i = 0; i < n; i++){
		tmp = createNode(i);
		if(head==NULL)head=tmp;
		else{
			runner = head;
			while( runner -> nextValue != NULL){
				runner = runner -> nextValue;
			}
			runner -> nextValue = tmp;
		}
	}
	runner = head;
	for(int i = 0; i < n;i++){
		aysi = NULL;
		runner2 = head;
		for(int j = 0; j < n; j++){
			if(adjMatrix[i][j] != (-1)){
				otro = createAdj(adjMatrix[i][j]);
				otro -> ref = runner2;

				if(aysi == NULL){
					runner -> adjacent = otro;
					aysi = otro;
				}
				else{
					aysi -> next = otro;
					aysi = otro;
				}
			}
			runner2 = runner2 -> nextValue;
		}
		runner = runner -> nextValue;
	}
	return head;
}
/*Implementation of the BFS algorithm in a function that recieves the starting node of the travel and an array with the already visited nodes
it implents the use of a Queue in order to make the visits to each node in order*/
void BFS(int n,int actual,int visited[]){
	if(visited[actual] == 0){
		printf("%d ", actual);
		visited[actual] = 1;
		struct nodeQueue * tmp = headQueue;
		headQueue = headQueue -> next;
		if(headQueue == NULL)
			tailQueue = NULL;
		free(tmp);
		for(int i = 0; i < n; i++){
			if(adjMatrix[actual][i] != -1 && visited[i] == 0){
				struct nodeQueue* temp= (struct nodeQueue *)malloc(sizeof(struct nodeQueue));
				temp -> value = i;
				temp -> next = NULL;
				if(headQueue == NULL){
					headQueue = temp;
					tailQueue = temp;
				}
				else{
					tailQueue -> next = temp;
					tailQueue = temp;
				}
			}
		}
	}
	else{
		struct nodeQueue * tmp = headQueue;
		headQueue = headQueue -> next;
		if(headQueue == NULL)
			tailQueue = NULL;
		free(tmp);
	}
}
/*Function that uses the list of lists to print the adjacency list*/
void printAdjacencyList(struct node * head){
	struct adjNode * tmp = createAdj(0);
	struct node * runner = createNode(0);
	runner = head;
	printf("Adjacency list:\n\n");
	while(runner != NULL){
		tmp = runner -> adjacent;
		while(tmp!=NULL){
			printf("Node %d connects with node %d(weight: %d)\n", runner->value, tmp->ref->value, tmp->weight);
			tmp = tmp->next;
		}
		runner = runner ->nextValue;
	}
	printf("\n");
}
/*Function that usses the list of lists to print de edge list*/
void printEdgeList(struct node * head, int n){
	struct adjNode * tmp = createAdj(0);
	struct node * runner = createNode(0);
	runner = head;
	int edge = 0;
	printf("Edge list: \n\n");
	for(int i = 0; i < n;i++){
		for(int j = 0; j < n; j++){
			if(adjMatrix[i][j] != -1){
				while(runner != NULL){
					tmp = runner -> adjacent;
					while(tmp != NULL){
						printf("Edge %d connects node %d  with node %d with a weight %d\n", edge, runner -> value, tmp -> ref -> value, tmp -> weight);
						tmp = tmp -> next;
						edge++;
					}
					runner = runner -> nextValue;
				}
			}
		}
	}
	printf("\n");
}
/*Implementation of the DFS algorithm in a recursive function, uses the same data as the BFS function*/
void DFS(int n,int actual,int visited[]){
	if(visited[actual] == 0){
		visited[actual] = 1;
		printf("%d ", actual);
		for(int i = 0; i < n ; i++){
			if(adjMatrix[actual][i] != -1 && visited[i] == 0)
				DFS(n,i,visited);
		}
	}
}
/*Implementation of the Dijkstra algorithm given a starting node, it finds the shortest distance from one node to every node*/
void dijkstra(int n,int startnode){
    int cost[n][n], distance[n], pred[n];
    int visited[n], count, mindistance, nextnode, i, j;
    for( i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            if(adjMatrix[i][j] == -1)
                cost[i][j] = 1000000000;
            else
                cost[i][j] = adjMatrix[i][j];
    for( i = 0; i < n; i++){
        distance[i] = cost[startnode][i];
        pred[i] = startnode;
        visited[i] = 0;
    }
    
    distance[startnode] = 0;
    visited[startnode] = 1;
    count = 1;
    
    while(count < n-1){
        mindistance = 1000000000;
        for( i = 0; i < n; i++)
            if(distance[i] < mindistance && !visited[i]){
                mindistance = distance[i];
                nextnode = i;
            }         
            visited[nextnode] = 1;
        for( i = 0; i < n; i++)
            if(!visited[i])
                if(mindistance + cost[nextnode][i] < distance[i]){
                    distance[i] = mindistance+cost[nextnode][i];
                    pred[i] = nextnode;
                }
        count++;
    }
    for( i = 0; i < n; i++)
        if(i != startnode){
        	if(distance[i] < 1000000000)
            	printf("From node %d to node %d: %d\n", startnode, i, distance[i]);            
    	}
}
/*Implementation of the Floyd algorithm, it creates and prints the adjacency matrix*/
void floyd(int n){
	int floyd[n][n];
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(adjMatrix[i][j] != -1)
				floyd[i][j] = adjMatrix[i][j];
			else floyd[i][j] = 1000000000;
		}
	}
	for(int k = 0; k < n; k++)
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n;j++)
				if(floyd[i][k] + floyd[k][j] < floyd[i][j])
					floyd[i][j] = floyd[i][k]+floyd[k][j];
	printf("\nFloyd \n\nAdjacency Matrix:\n");
	printf("    ");
	for (int i = 0; i < n; ++i){
		printf("%d  ", i);
	}
	printf("\n");
	printf("  +-");
	for( int i = 0; i < n; i++)
		printf("---");
	printf("\n");
	for( int i = 0; i < n; i++){
		printf("%d | ", i);
		for( int j = 0; j < n; j++){
			printf("%d  ", floyd[i][j]);
		}
		printf("\n\n");
	}

}

int main(int argc, char const *argv[]){
	struct node * head = createNode(0);
	struct node * headCola;
	int n;
	//Reading input
	scanf("%d", &n);
	int visited[n];
	for(int i = 0; i < n; i++){
		for( int j = 0; j < n; j++)
			scanf("%d", &adjMatrix[i][j]);
	}
	//Creation of the graph by creating the list of lists
	head = createGraph(n);
	//Printing the adjacency matrix
	printf("    ");
	for( int i = 0; i < n; i++)
		printf("%d  ", i);
	printf("\n");
	printf("  +");
	for( int i = 0; i < n; i++)
		printf("---");
	printf("\n");
	for(int i = 0; i < n; i++){
		printf("%d | ", i);
		for(int j = 0; j < n; j++){
			printf("%d ", adjMatrix[i][j]);
		}
		printf("\n\n");
	}
	//Printing the edge list
	printEdgeList(head, n);
	//Printing the adjacency list
	printAdjacencyList(head);
	//Executing the BFS function with the use of Queues, and printing the result
	printf("BFS:\n");
	for( int i = 0; i < n; i++){
		for( int j = 0; j < n; j++)
			visited[j]=0;
		headQueue = (struct nodeQueue *)malloc(sizeof(struct nodeQueue));
		tailQueue = (struct nodeQueue *)malloc(sizeof(struct nodeQueue));
		headQueue -> value = tailQueue -> value = i;
		headQueue -> next = NULL;
		tailQueue -> next = NULL;
		printf("BFS starting in %d: ", i);
		while(headQueue != NULL){
			BFS(n, headQueue -> value, visited);
		}
		printf("\n");
	}
	//Executing the DFS function with each nodo of the graph
	printf("\nDFS:\n");
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n ; j++)
			visited[j] = 0;
		printf("DFS starting in %d: ", i);
		DFS(n, i, visited);
		printf("\n");
	}
	printf("\n");
	//Executing the Dijkstra algorithm for each node of the graph
	for( int i = 0;i < n ;i++)
		dijkstra(n, i);
	//Executing the Floy algorithm
	floyd(n);
				
	return 0;
}