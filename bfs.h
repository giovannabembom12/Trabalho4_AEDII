#ifndef BFS_H
#define BFS_H

#include "grafo.h"

/* TAD que representa o resultado de uma busca em largura (BFS)
 * a partir de um vertice de origem. Guarda, para cada vertice:
 *   - pai[v]   : vertice do qual v foi descoberto na arvore de busca
 *                (-1 para a raiz ou vertices nao alcancados)
 *   - nivel[v] : profundidade de v na arvore (-1 se nao alcancado)
 *   - ordem[]  : sequencia em que os vertices foram visitados
 * Isso e suficiente para reconstruir/imprimir a arvore da BFS. */
typedef struct {
    int  origem;
    int  n;
    int *pai;
    int *nivel;
    int *ordem;
    int  qtd_visitados;
} ResultadoBFS;

ResultadoBFS *bfs_executar(Grafo *g, int origem);
void bfs_destruir(ResultadoBFS *r);
void bfs_imprimir_arvore(ResultadoBFS *r);
void bfs_imprimir_ordem(ResultadoBFS *r);

#endif
