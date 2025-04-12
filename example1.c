#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct Graph {
    int vertices;
    NODE **adjList;
    int *visited;
} GPH;

NODE *create_node(int v) {
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    newNode->data = v;
    newNode->next = NULL;
    return newNode;
}

void add_edge(GPH *g, int src, int dest) {
    NODE *newNode = create_node(dest);
    newNode->next = g->adjList[src];
    g->adjList[src] = newNode;

    newNode = create_node(src);
    newNode->next = g->adjList[dest];
    g->adjList[dest] = newNode;
}

GPH *create_g(int v) {
    GPH *g = (GPH *)malloc(sizeof(GPH));
    g->vertices = v;
    g->adjList = (NODE **)malloc(v * sizeof(NODE *));
    g->visited = (int *)malloc(v * sizeof(int));
    for (int i = 0; i < v; i++) {
        g->adjList[i] = NULL;
        g->visited[i] = 0;
    }
    return g;
}

void DFS(GPH *g, int vertex) {
    g->visited[vertex] = 1;
    NODE *temp = g->adjList[vertex];
    while (temp) {
        int adjVertex = temp->data;
        if (!g->visited[adjVertex]) {
            DFS(g, adjVertex);
        }
        temp = temp->next;
    }
}

void reset_visited(GPH *g) {
    for (int i = 0; i < g->vertices; i++) {
        g->visited[i] = 0;
    }
}

int has_path(GPH *g, int src, int dest) {
    DFS(g, src);
    int result = g->visited[dest];
    reset_visited(g);
    return result;
}

void insert_edges(GPH *g, int edg_nr) {
    printf("Adauga %d muchii (indecsi de la 0 la %d):\n", edg_nr, g->vertices - 1);
    for (int i = 0; i < edg_nr; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);
        add_edge(g, src, dest);
    }
}

int main() {
    int nrv, edg_nr, src, dest;

    printf("Cate noduri are graful? ");
    scanf("%d", &nrv);
    printf("Cate muchii are graful? ");
    scanf("%d", &edg_nr);

    GPH *g = create_g(nrv);
    insert_edges(g, edg_nr);

    printf("Introduceti cele doua restaurante (indecsi): ");
    scanf("%d %d", &src, &dest);

    if (has_path(g, src, dest)) {
        printf("Exista drum intre %d si %d.\n", src, dest);
    } else {
        printf("NU exista drum intre %d si %d.\n", src, dest);
    }

    // Free memory (simplified example)
    for (int i = 0; i < nrv; i++) {
        NODE *temp = g->adjList[i];
        while (temp) {
            NODE *to_free = temp;
            temp = temp->next;
            free(to_free);
        }
    }
    free(g->adjList);
    free(g->visited);
    free(g);

    return 0;
}