#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "fila.h"



Coordenada prioridade(Fila *Opcoes)
{

    int x, y;
    char n;
    Coordenada passo;
    Fila *Intermediario = criarFila();
    Fila *Pior = criarFila();

    while (!filaVazia(Opcoes))
    {
        desenfileirar(Opcoes, &x, &y, &n);
        if (n == '4')
        {
            passo.x = x;
            passo.y = y;
            liberarFila(Intermediario);
            liberarFila(Pior);
            return passo;
        }
        if (n == '0' || n == '1')
        {
            enfileirar(Intermediario, x, y, n);
        }
        else
            enfileirar(Pior, x, y, n);
    }

    // Se tiverr vai retornar o primeiro passo intermediario encontrado
    if (!filaVazia(Intermediario))
    {
        desenfileirar(Intermediario, &x, &y, &n);
        passo = (Coordenada){x, y};
        liberarFila(Intermediario);
        liberarFila(Pior);
        return passo;
    }
    // vai retornar o primeiro caso ruim;
    else
    {
        desenfileirar(Pior, &x, &y, &n);
        passo = (Coordenada){x, y};
        liberarFila(Intermediario);
        liberarFila(Pior);
        return passo;
    }
}

Fila *buscarNaFila(Fila *fila, int dado1, int dado2) {
    // busca e remove da fila o nó com (dado1, dado2)
    Fila *filaAtualizada = criarFila();
    No *atual = fila->inicio;
    
    while (atual != NULL) {
        if (!(atual->dados[0] == dado1 && atual->dados[1] == dado2)) {
            enfileirar(filaAtualizada, atual->dados[0], atual->dados[1], atual->letra);
        }
        atual = atual->prox;
    }

    liberarFila(fila);
    return filaAtualizada;
}

char **criarMatriz(int linhas, int colunas){
    char **matriz = (char **)malloc(linhas * sizeof(char *));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (char *)malloc(colunas * sizeof(char));
        if (!matriz[i]) {
            printf("Erro ao alocar memória para a linha %d.\n", i);
            // libera o que já foi alocado antes de retornar
            for (int j = 0; j < i; j++) free(matriz[j]);
            free(matriz);
            return NULL;
        }
        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = '.';  // preenche com .
        }
    }

    return matriz;
}
