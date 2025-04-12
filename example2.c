#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct Graph { 
    int vertices;
    int *visited;
    NODE **adjacencyLists;
} GPH;

NODE *createNode(int v) { 
    NODE *newNode = malloc(sizeof(NODE)); 
    newNode->data = v; 
    newNode->next = NULL;
    return newNode;
}

GPH *createGraph(int vertices) {
    GPH *graph = malloc(sizeof(GPH));
    graph->vertices = vertices;
    graph->adjacencyLists = malloc(vertices * sizeof(NODE *));
    graph->visited = malloc(sizeof(int) * vertices);
    
    for (int i = 0; i < vertices; i++) {
        graph->adjacencyLists[i] = NULL;
        graph->visited[i] = 0;
    } 
    return graph;
}

void addEdge(GPH *graph, int src, int dest) {
    NODE *newNode = createNode(dest);
    newNode->next = graph->adjacencyLists[src];
    graph->adjacencyLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjacencyLists[dest];
    graph->adjacencyLists[dest] = newNode;
}

void insertEdges(int nrOfVertices, int nrOfEdges, GPH *graph) { 
    int src, dest;
    printf("Adauga %d muchii (de la 0 la %d)\n", nrOfEdges, nrOfVertices-1);
    for (int i = 0; i < nrOfEdges; i++) {
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }
}

int isEmpty(NODE *queue) {
    return queue == NULL;
}

void enqueue(NODE **queue, int data) {
    NODE *newNode = createNode(data);
    if (isEmpty(*queue)) {
        *queue = newNode;
    } else {
        NODE *temp = *queue;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

int dequeue(NODE **queue) {
    int data = (*queue)->data;
    NODE *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

void printGraph(GPH *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        printf("Nodul %d: ", i);
        NODE *temp = graph->adjacencyLists[i];
        while (temp) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

void wipeVisitedList(GPH *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}

void DFS(GPH *graph, int vertexNr) {
    NODE *adjList = graph->adjacencyLists[vertexNr];
    NODE *temp = adjList;

    graph->visited[vertexNr] = 1;
    printf("%d ", vertexNr);

    while (temp != NULL) {
        int connectedVertex = temp->data;
        if (!graph->visited[connectedVertex]) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

void BFS(GPH *graph, int start) {
    NODE *queue = NULL;
    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!isEmpty(queue)) {
        int current = dequeue(&queue);
        printf("%d ", current);

        NODE *temp = graph->adjacencyLists[current];
        while (temp) {
            int adjVertex = temp->data;
            if (!graph->visited[adjVertex]) {
                graph->visited[adjVertex] = 1;
                enqueue(&queue, adjVertex);
            }
            temp = temp->next;
        }
    }
}

int main() {
    int nrOfVertices, nrOfEdges, startingVertex;
    
    printf("Cate noduri are graful? ");
    scanf("%d", &nrOfVertices);
    
    printf("Cate muchii are graful? ");
    scanf("%d", &nrOfEdges);
    
    GPH *graph = createGraph(nrOfVertices);
    insertEdges(nrOfVertices, nrOfEdges, graph);
    
    printf("De unde plecam in DFS? ");
    scanf("%d", &startingVertex);
    
    printf("Parcurgere cu DFS: ");
    DFS(graph, startingVertex);
    
    wipeVisitedList(graph);
    printf("\n");
    
    printf("De unde plecam in BFS? ");
    scanf("%d", &startingVertex);
    
    printf("Parcurgere cu BFS: ");
    BFS(graph, startingVertex);
    
    
    for (int i = 0; i < nrOfVertices; i++) {
        NODE *temp = graph->adjacencyLists[i];
        while (temp) {
            NODE *toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(graph->adjacencyLists);
    free(graph->visited);
    free(graph);
    
    return 0;
}