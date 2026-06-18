#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//já dizia taylor swift
typedef struct NoAdj {
    int destino;
    struct NoAdj *prox;
} NoAdj;

typedef struct {
    NoAdj *lista;
    int grau;
} Vertice;

typedef struct {
    int n;
    int m;
    Vertice *v;
} Grafo;

Grafo *grafo_criar(int n);
void   grafo_destruir(Grafo *g);
void   grafo_adicionar_aresta(Grafo *g, int u, int v);
int    grafo_tem_aresta(Grafo *g, int u, int v);
Grafo *grafo_gerar_conexo(int n, double conectividade);
void   grafo_imprimir_lista(Grafo *g);
int    grafo_tem_ciclo(Grafo *g);

#endif