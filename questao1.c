#include "grafo.h"
#include <locale.h>

static void questao1(void){
    int vertices[] = {5,10,20,50,100};
    double porcentagens[] = {0.25, 0.50, 0.75, 1.00};



    printf("\n-- Questao 1: Criação de grafos com graus de conectividade variados --\n");

    for(int i=0; i<5; i++){         //num de grafos criados 
        int n = vertices[i];
        for(int j=0; j<4; j++){     // passagem pelas porcentagens
            double porcentagem = porcentagens[j]; 
            Grafo *grafo = grafo_gerar_conexo(n,porcentagem);
            printf("Grafo criado com %d vértices e conectividade de %.2f\n", n, porcentagem);
            grafo_imprimir_lista(grafo);
            grafo_destruir(grafo);
        }
        printf("\n");
    }

}

int main(void){
    srand((unsigned)time(NULL));       // quando for juntar os codigos TIRAR ESSA PARTE
    setlocale(LC_ALL, "pt_BR.UTF-8");  // set LC_ALL=pt_BR.UTF-8    -- colocar no terminal antes de compilar (windows)

    questao1();             
}