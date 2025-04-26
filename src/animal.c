#include <stdio.h>
#include <stdlib.h>
#include "animal.h"

int interacaoAgua(char **mapa, Coordenada animal, int altura, int comprimento, Fila **fila, int interacao)
{

    if (mapa[animal.x][animal.y] == '4')
    {
        Fila *historico = criarFila();
        int visinhaX[] = {1, 0, -1, 0};
        int visinhaY[] = {0, 1, 0, -1};

        for (int i = 0; i < 4; i++)
        {
            int nx = animal.x + visinhaX[i];
            int ny = animal.y + visinhaY[i];

            if (nx >= 0 && nx < altura && ny >= 0 && ny < comprimento)
            {
                if (mapa[nx][ny] == '2')
                {
                    mapa[nx][ny] = '3';
                    enfileirar(historico, nx, ny, '3');
                    *fila = buscarNaFila(*fila, nx, ny);
                }
            }
        }
        salvarMapa(mapa, altura, comprimento, interacao, historico, animal);
        liberarFila(historico);
        return 2; // tava na agua
    }

    return 0; // não estava na agua
}

Coordenada andar(char **mapa, Coordenada animal, int altura, int comprimento, int *nVezesAgua, Fila **fila, int interacao)
{

    if (*nVezesAgua == 2 && mapa[animal.x][animal.y] == '4')
    {
        (*nVezesAgua)++;
        return animal;
    }
    if (*nVezesAgua == 1 && mapa[animal.x][animal.y] == '4')
    {
        *nVezesAgua = interacaoAgua(mapa, animal, altura, comprimento, fila, interacao);
        return (animal);
    }

    Fila *opcao = criarFila();
    int visinhaX[] = {1, 0, -1, 0};
    int visinhaY[] = {0, 1, 0, -1};

    for (int i = 0; i < 4; i++)
    {
        int nx = animal.x + visinhaX[i];
        int ny = animal.y + visinhaY[i];

        if (nx >= 0 && nx < altura && ny >= 0 && ny < comprimento)
        {
            if (mapa[nx][ny] != '2')
            {
                char l = mapa[nx][ny];
                enfileirar(opcao, nx, ny, l);
            }
        }
    }
    if (filaVazia(opcao))
    {
        //morreu
        printf("aqui");
        Coordenada morte={-1,-1};
        return morte;
    }
    
    Coordenada passo = prioridade(opcao);
    // ver onde pode andar
    liberarFila(opcao);
    return passo;
}