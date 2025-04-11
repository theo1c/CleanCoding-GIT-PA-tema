/*Determinati daca exista sau nu drum direct intre doua restaurante
    dintr-o retea de tip graf*/
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node* next;
} NODE;

/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa

typedef struct g {
    int v;
    int* vis;
    NODE** alst;
} GPH;

typedef struct s {
    int t;
    int scap;
    int* arr;
} STK;

NODE* create_node(int v) {
    NODE* n = malloc(sizeof(NODE));
    n->data = v;
    n->next = NULL;
    return n;
}

void add_edge(GPH* g, int src, int dest) {
    NODE* nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;

    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

GPH* create_g(int v) {
    GPH* g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(v * sizeof(NODE*));
    g->vis = malloc(v * sizeof(int));

    for (int i = 0; i < v; i++) {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }
    return g;
}

STK* create_stack(int stack_cap) {
    STK* s = malloc(sizeof(STK));
    s->arr = malloc(stack_cap * sizeof(int));
    s->t = -1;
    s->scap = stack_cap;
    return s;
}

void push(int push, STK* s) {
    s->t += 1;
    s->arr[s->t] = push;
}
int pop(STK* s) {
    if (s->t == -1) {
        return -1;
    } else {
        int val = s->arr[s->t];
        s->t -= 1;
        return val;
    }
}

void DFS(GPH* g, STK* s, int v_nr) {
    push(v_nr, s);
    g->vis[v_nr] = 1;

    while (s->t != -1) {
        int current = pop(s);
        NODE* aux = g->alst[current];

        while (aux != NULL) {
            int con_ver = aux->data;
            if (g->vis[con_ver] == 0) {
                push(con_ver, s);
                g->vis[con_ver] = 1;
            }
            aux = aux->next;
        }
    }
}

void insert_edges(GPH* g, int edg_nr, int nrv) {
    int src, dest;
    printf("adauga %d munchii (de la 0 la %d)\n", edg_nr, nrv - 1);
    for (int i = 0; i < edg_nr; i++) {
        scanf("%d%d", &src, &dest);
        add_edge(g, src, dest);
    }
}

void wipe(GPH* g, int nrv) {
    for (int i = 0; i < nrv; i++) {
        g->vis[i] = 0;
    }
}

int is_direct_path(GPH* g, int start, int end) {
    STK* s = create_stack(g->v);
    DFS(g, s, start);

    if (g->vis[end] == 1) {
        free(s->arr);
        free(s);
        return 1;
    }

    free(s->arr);
    free(s);
    return 0;
}

int main() {
    int vertex_nr, edg_nr;
    int vertex_start, vertex_finish;

    printf("Introduceti nr de noduri ale grafului: ");
    scanf("%d", &vertex_nr);

    printf("Introduceti nr de muchii ale grafului: ");
    scanf("%d", &edg_nr);

    GPH* g = create_g(vertex_nr);
    insert_edges(g, edg_nr, vertex_nr);

    printf("Introduceti nr restaurantului sursa (nr intre 0 si %d): ",vertex_nr - 1);
    scanf("%d", &vertex_start);
    printf("Introduceti nr restaurantului destinatie: ");
    scanf("%d", &vertex_finish);

    if (is_direct_path(g, vertex_start, vertex_finish)) {
        printf("Exista drum intre %d si %d.\n", vertex_start, vertex_finish);
    } else {
        printf("Nu exista drum intre %d si %d.\n", vertex_start, vertex_finish);
    }

    return 0;
}
