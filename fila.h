#ifndef FILA_H
#define FILA_H

/* TAD Fila (FIFO) implementada com vetor circular.
 * Usada como estrutura auxiliar da busca em largura (BFS).
 * Capacidade fixa = numero de vertices do grafo, ja que na BFS
 * cada vertice entra na fila no maximo uma vez. */
typedef struct {
    int *dados;
    int capacidade;
    int inicio;
    int fim;
    int tamanho;
} Fila;

Fila *fila_criar(int capacidade);
void  fila_destruir(Fila *f);
int   fila_vazia(Fila *f);
void  fila_inserir(Fila *f, int valor);
int   fila_remover(Fila *f);

#endif
