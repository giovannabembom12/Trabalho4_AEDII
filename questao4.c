#include "grafo.h"
#include <locale.h>
 
static void dfs(Grafo *g, int u, int *visitado, int *caminho, int profundidade) {
    caminho[profundidade] = u;
    visitado[u] = 1;
 
    for (int i = 0; i <= profundidade; i++)
        printf("%s%d", i ? " -> " : "  ", caminho[i]);
    printf("\n");
 
    for (NoAdj *p = g->v[u].lista; p; p = p->prox)
        if (!visitado[p->destino])
            dfs(g, p->destino, visitado, caminho, profundidade + 1);
 
    visitado[u] = 0;
}
 
static void questao4(void) {
    printf("-- Questao 4: Busca em Profundidade — todas as sequencias --\n\n");
 
    Grafo *g = grafo_gerar_conexo(6, 0.40); //está sendo usado valores fixos para facilitar a visualização do grafo
 
    grafo_imprimir_lista(g);
    printf("\n");
 
    int visitado[g->n];
    int caminho[g->n];
    memset(visitado, 0, sizeof(visitado));
 
    for (int i = 0; i < g->n; i++) {
        printf("Caminhos a partir do vertice %d:\n", i);
        dfs(g, i, visitado, caminho, 0);
        printf("\n");
    }
 
    grafo_destruir(g);
}
 
int main(void) {
    srand((unsigned)time(NULL));
    setlocale(LC_ALL, "pt_BR.UTF-8");
    questao4();
    return 0;
}
