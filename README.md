# Trabalho Prático 4 – Algoritmos e Estruturas de Dados 2 (AED2)

Implementação de algoritmos de busca em grafos (BFS e DFS) e duas aplicações
derivadas da DFS: enumeração de todos os caminhos simples a partir de um
vértice e detecção de ciclos em grafos não-direcionados.

**Disciplina:** Algoritmos e Estruturas de Dados 2 — IComp/UFAM

## Autores

- André Malmsteen Oliveira Amorim
- Benjamim Isaac Ribeiro Lima
- Giovanna Bembom da Silva Bandeira
- Mariana Ramos André Simões

## Estrutura do repositório

```
.
├── grafo.h / grafo.c            # TAD Grafo (lista de adjacência) + geração de grafos conexos
├── fila.h / fila.c              # TAD Fila (vetor circular), auxiliar da BFS
├── bfs.h / bfs.c                # Busca em largura e impressão da árvore de busca
├── estatisticas.h / estatisticas.c  # Medição de tempo, média e desvio padrão
├── main.c                       # Ponto de entrada; uma função por questão (questao01..questao5)
└── README.md
```

## Como compilar

Requer um compilador C com suporte a C11 e à biblioteca `libm`.

```bash
gcc -std=gnu11 -Wall -Wextra -O2 -o programa main.c grafo.c bfs.c fila.c estatisticas.c -lm
```

> **Nota:** o programa usa `clock_gettime(CLOCK_MONOTONIC, ...)`, que depende de
> macros de recurso POSIX. Compile com `-std=gnu11` (ou defina
> `_POSIX_C_SOURCE 199309L` antes dos includes) — com `-std=c11` estrito a
> compilação falha em Linux.

No Windows (MinGW), o mesmo comando funciona normalmente:

```bash
gcc -std=gnu11 -Wall -Wextra -O2 -o programa.exe main.c grafo.c bfs.c fila.c estatisticas.c -lm
```

## Como executar

```bash
./programa
```

O programa não recebe argumentos. Ele executa sequencialmente as cinco
questões e imprime tudo na saída padrão. Para salvar a saída em arquivo:

```bash
./programa > saida.txt
```

Como a saída é longa (principalmente por causa da Questão 4, que lista todos
os caminhos simples de dois grafos), recomenda-se redirecionar para arquivo
em vez de ler direto no terminal.

## O que cada questão faz

1. **Questão 1 — Geração de grafos conexos:** cria grafos com 5, 10, 20, 50 e
   100 vértices, cada um em quatro graus de conectividade (25%, 50%, 75%,
   100%), e imprime a lista de adjacência de cada um.
2. **Questão 2 — Busca em largura (BFS):** para os mesmos 20 grafos, executa
   a BFS a partir do vértice 0, imprime a ordem de visitação e a árvore de
   busca (nível a nível, com pai de cada vértice) e mede o tempo de 10
   execuções, reportando a média.
3. **Questão 3 — Busca em profundidade (DFS):** mesma bateria de grafos;
   imprime a sequência de vértices visitados pela DFS recursiva a partir do
   vértice 0 e mede o tempo médio de 10 execuções.
4. **Questão 4 — Todos os caminhos via DFS:** usa dois grafos menores (6 e 8
   vértices) e, para cada vértice de origem, enumera por DFS todos os
   caminhos simples possíveis a partir dele.
5. **Questão 5 — Detecção de ciclos:** aplica DFS com coloração de vértices
   (branco/cinza/preto) para detectar ciclos de tamanho ≥ 3 em grafos
   aleatórios, em árvores puras (grupo de controle sem ciclo) e em dois casos
   manuais (triângulo e grafo caminho).
