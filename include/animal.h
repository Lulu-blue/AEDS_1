#ifndef ANIMAL_H
#define ANIMAL_H
#include "fila.h"
#include "ManipulacaoArquivos.h"
#include "Fogo.h"
#include "utils.h"
#include "configuracao.h"


int interacaoAgua(char **mapa, Coordenada animal, int altura, int comprimento, Fila **fila, int interacao);
Coordenada andar(char **mapa, Coordenada animal, int altura, int comprimento, int *nVezesAgua, Fila **fila, int interacao);

#endif