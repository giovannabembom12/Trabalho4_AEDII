#include "grafo.h"
#include "locale.h"
#include "estatisticas.h"

#define num_buscas 10

static void titulo(const char *s) {
    printf("  %s\n", s);
}

static Grafo *arvore_criar(int n) {
    Grafo *g = grafo_criar(n);
    for (int i = 1; i < n; i++)
        grafo_adicionar_aresta(g, i, rand() % i);
    return g;
}

static void questao01(void){
    int vertices[] = {5,10,20,50,100};
    double porcentagens[] = {0.25, 0.50, 0.75, 1.00};



    printf("\n-- Questao 1: Criação de grafos com graus de conectividade variados --\n");

    for(int i=0; i<5; i++){         //num de grafos criados 
        int n = vertices[i];
        for(int j=0; j<4; j++){     // passagem pelas porcentagens
            double porcentagem = porcentagens[j]; 
            Grafo *grafo = grafo_gerar_conexo(n,porcentagem);
            printf("Grafo criado com %d vértices e conectividade de %.2f%%\n", n, porcentagem);
            grafo_imprimir_lista(grafo);
            grafo_destruir(grafo);
        }
        printf("\n");
    }

}
 
static void questao03(void){
    titulo("\nQUESTÃO 3 - Busca em profundidade (DFS)");
    
    int ns_ciclo[] = {5, 10, 20, 50, 100};
    double cs[] = {0.25, 0.50, 0.75, 1.00};

    for(int i = 0; i < 5; i++){
        int n = ns_ciclo[i];
        for(int j = 0; j < 4; j++){
            double c = cs[j];
            Grafo *g = grafo_gerar_conexo(n,c);

            printf("\n  Grafo criado com %d vértices e conectividade de %.2f%%\n\n", n, c*100);

            double tempos_busca[num_buscas];

            for(int k = 0; k < num_buscas;k++){
                int *visitado = calloc(n, sizeof(int));

                printf("        Vértices visitados na iteração %d: ", k+1);
                double inicio = tempoAtual();
                dfs_simples(g, 0, visitado);
                double fim = tempoAtual();
                printf("\n\n");

                tempos_busca[k] = fim - inicio;
                free(visitado);
            }

            double tempos_media = media(tempos_busca, num_buscas);
            printf("   A média de %d buscas nesse grafo foi: %.6f\n\n", num_buscas, tempos_media);

            grafo_destruir(g);
        }
    }

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
        dfs_caminhos(g, i, visitado, caminho, 0);
        printf("\n");
    }
 
    grafo_destruir(g);
}

static void questao5(void) {
    titulo("\nQUESTÃO 5 – Detecção de ciclos (DFS)");

    printf("\nGrafos COM ciclo (gerados aleatoriamente)\n");
    int ns_ciclo[] = {5, 10, 20, 50, 100};
    double cs[] = {0.25, 0.50, 0.75, 1.00};

    for (int k = 0; k < 5; k++) {
        int n = ns_ciclo[k];
        for (int j = 0; j < 4; j++) {
            double c = cs[j];
            Grafo *g = grafo_gerar_conexo(n, c);
            int tem = grafo_tem_ciclo(g);
            printf("  n = %3d, conectividade = %4.0f%%, arestas = %4d => %s\n",
                   n, c * 100, g->m,
                   tem ? "TEM CICLO" : "sem ciclo");
            grafo_destruir(g);
        }
        printf("\n");
    }

    printf("Grafos SEM ciclo (Árvores)\n");
    int ns_arvore[] = {5, 10, 20, 50, 100};
    for (int k = 0; k < 5; k++) {
        int n = ns_arvore[k];
        Grafo *g = arvore_criar(n);
        int tem = grafo_tem_ciclo(g);
        printf("  Árvore n = %3d, arestas = %3d => %s\n",
               n, g->m,
               tem ? "TEM CICLO (ERRO!)" : "sem ciclo (correto)");
        grafo_destruir(g);
    }

    printf("\nGrafo mínimo com ciclo (triângulo n = 3)\n");
    {
        Grafo *g = grafo_criar(3);
        grafo_adicionar_aresta(g, 0, 1);
        grafo_adicionar_aresta(g, 1, 2);
        grafo_adicionar_aresta(g, 2, 0);
        grafo_imprimir_lista(g);
        printf("  => %s\n", grafo_tem_ciclo(g) ? "TEM CICLO" : "sem ciclo");
        grafo_destruir(g);
    }
//o que ta acontecendo
    printf("\nGrafo caminho (n = 5, sem ciclo)\n");
    {
        Grafo *g = grafo_criar(5);
        grafo_adicionar_aresta(g, 0, 1);
        grafo_adicionar_aresta(g, 1, 2);
        grafo_adicionar_aresta(g, 2, 3);
        grafo_adicionar_aresta(g, 3, 4);
        grafo_imprimir_lista(g);
        printf("  => %s\n", grafo_tem_ciclo(g) ? "TEM CICLO (ERRO!)" : "sem ciclo (correto)");
        grafo_destruir(g);
    }
}

int main(void) {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    srand((unsigned)time(NULL));

    titulo("TRABALHO PRÁTICO 4 – AED2 – Questão 5: Detecção de Ciclos");

    questao01();
    questao03();
    questao4();
    questao5();

    return 0;
}
