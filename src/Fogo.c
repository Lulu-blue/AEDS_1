#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Fogo.h"
#include "utils.h"
#include "ManipulacaoArquivos.h"

// interação é um contador que vai contar quantas vezes a função proṕagação foi usada

void propagacaoFogo(char **mapa, Fila *filaDados, int altura, int comprimento, int interacao, Coordenada animal) {
    Fila *historico = criarFila();
    int x, y;
    char n;

    if (filaVazia(filaDados)) return;

    desenfileirar(filaDados, &x, &y, &n);
    mapa[x][y] = '3';
    enfileirar(historico, x, y, '3');

    int visinhaX[] = {1, 0, -1, 0};
    int visinhaY[] = {0, 1, 0, -1};

    for (int i = 0; i < 4; i++) {
        int nx = x + visinhaX[i];
        int ny = y + visinhaY[i];

        if (nx >= 0 && nx < altura && ny >= 0 && ny < comprimento) {
            if (mapa[nx][ny] == '1') {
                mapa[nx][ny] = '2';
                enfileirar(filaDados, nx, ny, '2');
                enfileirar(historico, nx, ny, '2');
            }
        }
    }

    salvarMapa(mapa, altura, comprimento, interacao, historico, animal);
    liberarFila(historico);
}




void propagacaoFogoVento(char **mapa, Fila *filaDados, int altura, int comprimento, int interacao, Coordenada *vento, Coordenada animal)
{

    Fila *historico = criarFila();

    int x, y;
    char n;
    if (filaVazia(filaDados))
    {
        return;
    }

    desenfileirar(filaDados, &x, &y, &n);
    mapa[x][y] = '3';
    enfileirar(historico, x, y, '3');

    for (int i = 0; i < 4; i++)
    {
        int nx = x + vento[i].x;
        int ny = y + vento[i].y;
        if (!(nx == x && ny == y))
        {
            if (nx >= 0 && nx < altura && ny >= 0 && ny < comprimento)
            {
                if (mapa[nx][ny] == '1')
                {
                    mapa[nx][ny] = '2';
                    enfileirar(filaDados, nx, ny, '2');
                    enfileirar(historico, nx, ny, '2');
                }
            }
        }
    }
    salvarMapa(mapa, altura, comprimento, interacao, historico, animal);
    liberarFila(historico);
    return;
}