#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

Fila *fila_criar(int capacidade) {
    Fila *f = malloc(sizeof(Fila));
    f->dados = malloc(capacidade * sizeof(int));
    f->capacidade = capacidade;
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
    return f;
}

void fila_destruir(Fila *f) {
    free(f->dados);
    free(f);
}

int fila_vazia(Fila *f) {
    return f->tamanho == 0;
}

void fila_inserir(Fila *f, int valor) {
    if (f->tamanho == f->capacidade) {
        fprintf(stderr, "fila_inserir: fila cheia\n");
        return;
    }
    f->dados[f->fim] = valor;
    f->fim = (f->fim + 1) % f->capacidade;
    f->tamanho++;
}

int fila_remover(Fila *f) {
    if (fila_vazia(f)) {
        fprintf(stderr, "fila_remover: fila vazia\n");
        return -1;
    }
    int valor = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->tamanho--;
    return valor;
}
