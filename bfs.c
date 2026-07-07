#include <stdio.h>
#include <stdlib.h>
#include "bfs.h"
#include "fila.h"

ResultadoBFS *bfs_executar(Grafo *g, int origem) {
    int n = g->n;
    ResultadoBFS *r = malloc(sizeof(ResultadoBFS));
    r->origem = origem;
    r->n = n;
    r->pai   = malloc(n * sizeof(int));
    r->nivel = malloc(n * sizeof(int));
    r->ordem = malloc(n * sizeof(int));
    r->qtd_visitados = 0;

    int *visitado = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        r->pai[i]   = -1;
        r->nivel[i] = -1;
    }

    Fila *f = fila_criar(n);
    visitado[origem] = 1;
    r->nivel[origem] = 0;
    fila_inserir(f, origem);

    while (!fila_vazia(f)) {
        int u = fila_remover(f);
        r->ordem[r->qtd_visitados++] = u;
        for (NoAdj *p = g->v[u].lista; p; p = p->prox) {
            int w = p->destino;
            if (!visitado[w]) {
                visitado[w] = 1;
                r->pai[w]   = u;
                r->nivel[w] = r->nivel[u] + 1;
                fila_inserir(f, w);
            }
        }
    }

    fila_destruir(f);
    free(visitado);
    return r;
}

void bfs_destruir(ResultadoBFS *r) {
    free(r->pai);
    free(r->nivel);
    free(r->ordem);
    free(r);
}

void bfs_imprimir_ordem(ResultadoBFS *r) {
    printf("  Ordem de visitacao (origem = %d): ", r->origem);
    for (int i = 0; i < r->qtd_visitados; i++)
        printf("%d ", r->ordem[i]);
    printf("\n");
}

/* Imprime a arvore resultante da BFS, nivel a nivel, mostrando
 * o pai de cada vertice (formato pedido na questao 2). */
void bfs_imprimir_arvore(ResultadoBFS *r) {
    printf("  Arvore de busca em largura (raiz = %d):\n", r->origem);
    for (int nivel_atual = 0; nivel_atual <= r->n; nivel_atual++) {
        int achou = 0;
        for (int i = 0; i < r->qtd_visitados; i++) {
            int v = r->ordem[i];
            if (r->nivel[v] == nivel_atual) {
                if (!achou) { printf("    nivel %d: ", nivel_atual); achou = 1; }
                if (r->pai[v] == -1)
                    printf("%d(raiz) ", v);
                else
                    printf("%d(pai=%d) ", v, r->pai[v]);
            }
        }
        if (achou) printf("\n");
        else if (nivel_atual > 0) break;
    }
}
