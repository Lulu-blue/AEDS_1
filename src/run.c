#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "fila.h"
#include "ManipulacaoArquivos.h"
#include "Fogo.h"
#include "utils.h"
#include "configuracao.h"
#include "animal.h"

void runSemVento() {
    int altura, comprimento, inicioX, inicioY;
    Coordenada passo;
    int interacao = 1, morte = 1, nPassos = 0;
    int nVezesNaAgua = 1;
    Fila *fila = criarFila();
    Coordenada animal = PosicaoAnimal();
    int limiteMax = interacoesMax();
    char **mapa = lerArquivo("input.dat", &altura, &comprimento, &inicioX, &inicioY, fila);
    char **caminho = criarMatriz(altura, comprimento);
    caminho[animal.x][animal.y] = '*';

    while (interacao <= limiteMax && !filaVazia(fila)) {
        propagacaoFogo(mapa, fila, altura, comprimento, interacao, animal);
        passo = andar(mapa, animal, altura, comprimento, &nVezesNaAgua, &fila, interacao);
    
        if (passo.x == -1 && passo.y == -1) {
            morte = 0;
            liberarFila(fila);
            break;
        }
    
        if (passo.x != animal.x || passo.y != animal.y) {
            nPassos++;
        }
    
        animal = passo;
        caminho[animal.x][animal.y] = '*';
        interacao++;
    }

    salvaCaminho(caminho, altura, comprimento, nPassos, morte);

    for (int i = 0; i < altura; i++) {
        free(mapa[i]);
        free(caminho[i]);
    }
    free(mapa);
    free(caminho);
    liberarFila(fila);
}

void runVento() {
    int altura, comprimento, inicioX, inicioY;
    Coordenada passo;
    int interacao = 1, morte = 1, nPassos = 0;
    int nVezesNaAgua = 1;
    Fila *fila = criarFila();
    Coordenada animal = PosicaoAnimal();
    int limiteMax = interacoesMax();
    Coordenada* vento=criarVento();
    char **mapa = lerArquivo("input.dat", &altura, &comprimento, &inicioX, &inicioY, fila);
    char **caminho = criarMatriz(altura, comprimento);
    caminho[animal.x][animal.y] = '*';

    while (interacao <= limiteMax && !filaVazia(fila)) {
        propagacaoFogoVento(mapa, fila, altura, comprimento, interacao, vento, animal);
        passo = andar(mapa, animal, altura, comprimento, &nVezesNaAgua, &fila, interacao);
    
        if (passo.x == -1 && passo.y == -1) {
            morte = 0;
            liberarFila(fila);
            break;
        }
    
        if (passo.x != animal.x || passo.y != animal.y) {
            nPassos++;
        }
    
        animal = passo;
        caminho[animal.x][animal.y] = '*';
        interacao++;
    }

    salvaCaminho(caminho, altura, comprimento, nPassos, morte);

    for (int i = 0; i < altura; i++) {
        free(mapa[i]);
        free(caminho[i]);
    }
    free(mapa);
    free(caminho);
    liberarFila(fila);
}
