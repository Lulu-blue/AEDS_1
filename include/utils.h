#ifndef UTILS_H
#define UTILS_H
#include "fila.h"
typedef struct {
    int x;
    int y;
} Coordenada;

Coordenada prioridade(Fila *Opcoes);
Fila *buscarNaFila(Fila *fila, int dado1, int dado2);
char **criarMatriz(int linhas, int colunas);

#endif