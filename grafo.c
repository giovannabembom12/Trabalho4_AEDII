#include "grafo.h"

Grafo *grafo_criar(int n) {
    Grafo *g = malloc(sizeof(Grafo));
    g->n = n;
    g->m = 0;
    g->v = calloc(n, sizeof(Vertice));
    return g;
}

void grafo_destruir(Grafo *g) {
    for (int i = 0; i < g->n; i++) {
        NoAdj *p = g->v[i].lista;
        while (p) { NoAdj *tmp = p->prox; free(p); p = tmp; }
    }
    free(g->v);
    free(g);
}

void grafo_adicionar_aresta(Grafo *g, int u, int v) {
    // u -> v
    NoAdj *no = malloc(sizeof(NoAdj));
    no->destino = v;
    no->prox = g->v[u].lista;
    g->v[u].lista = no;
    g->v[u].grau++;

    // v -> u (não-direcionado)
    no = malloc(sizeof(NoAdj));
    no->destino = u;
    no->prox = g->v[v].lista;
    g->v[v].lista = no;
    g->v[v].grau++;
    g->m++;
}

int grafo_tem_aresta(Grafo *g, int u, int v) {
    for (NoAdj *p = g->v[u].lista; p; p = p->prox)
        if (p->destino == v) return 1;
    return 0;
}

static void embaralhar(int *a, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int t = a[i]; a[i] = a[j]; a[j] = t;
    }
}

Grafo *grafo_gerar_conexo(int n, double conectividade) {
    Grafo *g = grafo_criar(n);

    int *perm = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) perm[i] = i;
    embaralhar(perm, n);

    for (int i = 1; i < n; i++) {
        int u = perm[i];
        int v = perm[rand() % i];
        grafo_adicionar_aresta(g, u, v);
    }
    free(perm);

    int max_arestas = n * (n - 1) / 2;
    int alvo = (int)(conectividade * max_arestas);
    int tentativas = 0;
    while (g->m < alvo && tentativas < max_arestas * 10) {
        int u = rand() % n;
        int v = rand() % n;
        if (u != v && !grafo_tem_aresta(g, u, v))
            grafo_adicionar_aresta(g, u, v);
        tentativas++;
    }

    return g;
}

void grafo_imprimir_lista(Grafo *g) {
    printf("Lista de adjacência (%d vértices, %d arestas):\n", g->n, g->m);
    for (int i = 0; i < g->n; i++) {
        printf("  [%2d] ->", i);
        for (NoAdj *p = g->v[i].lista; p; p = p->prox)
            printf(" %d", p->destino);
        printf("\n");
    }
}

static int ciclo_rec(Grafo *g, int u, int pai_u, int *cor, int *prof) {
    cor[u] = 1;
    for (NoAdj *p = g->v[u].lista; p; p = p->prox) {
        int w = p->destino;
        if (w == pai_u) continue;          
        if (cor[w] == 1) {
            if (prof[u] - prof[w] + 1 >= 3) return 1;  // ciclo de tamanho >= 3
        }
        if (cor[w] == 0) {
            prof[w] = prof[u] + 1;
            if (ciclo_rec(g, w, u, cor, prof)) return 1;
        }
    }
    cor[u] = 2;
    return 0;
}

int grafo_tem_ciclo(Grafo *g) {
    int n = g->n;
    int *cor  = calloc(n, sizeof(int));
    int *prof = calloc(n, sizeof(int));

    int resultado = 0;
    for (int i = 0; i < n && !resultado; i++) {
        if (cor[i] == 0) {
            prof[i] = 0;
            resultado = ciclo_rec(g, i, -1, cor, prof);
        }
    }

    free(cor);
    free(prof);
    return resultado;
}
