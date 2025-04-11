//cod reparat
#include <stdlib.h>
#include <stdio.h>

//implementarea unei structuri de tip nod
typedef struct Node {
    int data;
    struct Node *next;
} NODE;

//implementarea unei structuri de tip graf care utilizeaza struct nod
typedef struct Graph {
    int vertex;
    int *visited;
    struct Node **adjacency_lists;
} GPH;

//functie pt initializarea nodurilor
NODE *create_node(int v) {
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

//functie pt initializarea grafului
GPH *create_graph(int vertex_nr) {
    GPH *graph = malloc(sizeof(GPH));
    graph->vertex = vertex_nr;
    graph->adjacency_lists = malloc(vertex_nr * sizeof(NODE *));
    graph->visited = malloc(sizeof(int) * vertex_nr);
    for (int i = 0; i < vertex_nr; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

//adaugarea muchiilor in graf
void add_edge(GPH *graph, int src, int dest) {
    NODE *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

//inserarea muchiilor de la tastatura
void insert_edge(int vertex_nr, int edge_nr, GPH *graph) {
    int src, dest;
    printf("Introduceti %d muchii (de la 0 la %d):\n", edge_nr, vertex_nr - 1);
    for (int i = 0; i < edge_nr; i++) {
        scanf("%d%d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

int is_empty(NODE *queue) {
    return queue == NULL;
}

void enqueue(NODE **queue, int data) {
    NODE *new_node = create_node(data);
    if (is_empty(*queue)) {
        *queue = new_node;
    } else {
        NODE *temp = *queue;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

int dequeue(NODE **queue) {
    int data = (*queue)->data;
    NODE *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return data;
}

void print_graph(GPH *graph) {
    for (int i = 0; i < graph->vertex; i++) {
        NODE *temp = graph->adjacency_lists[i];
        printf("%d: ", i);
        while (temp) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

void print_queue(NODE *queue) {
    while (queue != NULL) {
        printf("%d ", queue->data);
        queue = queue->next;
    }
    printf("\n");
}

void wipe_visited_list(GPH *graph, int vertex_nr) {
    for (int i = 0; i < vertex_nr; i++) {
        graph->visited[i] = 0;
    }
}

void DFS(GPH *graph, int vertex_nr) {
    NODE *adj_list = graph->adjacency_lists[vertex_nr];
    NODE *temp = adj_list;

    graph->visited[vertex_nr] = 1;
    printf("%d ", vertex_nr);

    while (temp != NULL) {
        int connected_vertex = temp->data;
        if (graph->visited[connected_vertex] == 0) {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

void BFS(GPH *graph, int start) {
    NODE *queue = NULL;

    graph->visited[start] = 1;
    enqueue(&queue, start);

    while (!is_empty(queue)) {
        int current = dequeue(&queue);
        printf("%d ", current);

        NODE *temp = graph->adjacency_lists[current];
        while (temp) {
            int adj_vertex = temp->data;
            if (graph->visited[adj_vertex] == 0) {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}
void free_graph(GPH *graph) {
    for (int i = 0; i < graph->vertex; i++) {
        NODE *temp = graph->adjacency_lists[i];
        while (temp != NULL) {
            NODE *next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph->adjacency_lists);
    free(graph->visited);
    free(graph);
}

int main() {
    int vertex_nr, edge_nr, starting_vertex;

    printf("Introduceti nr de noduri al grafului: ");
    scanf("%d", &vertex_nr);

    printf("Introduceti nr de muchii ale grafului: ");
    scanf("%d", &edge_nr);

    GPH *graph = create_graph(vertex_nr);
    insert_edge(vertex_nr, edge_nr, graph);

    printf("Introduceti nodul de start pentru parcurgerea DFS: ");
    scanf("%d", &starting_vertex);
    printf("Parcurgere cu DFS: ");
    DFS(graph, starting_vertex);

    wipe_visited_list(graph, vertex_nr);
    printf("\n");

    printf("Introduceti nodul de start pentru parcurgerea BFS: ");
    scanf("%d", &starting_vertex);
    printf("Parcurgere cu BFS: ");
    BFS(graph, starting_vertex);
    printf("\n");
    free_graph(graph);

    return 0;
}
