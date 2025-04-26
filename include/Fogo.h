#ifndef FOGO_H
#define FOGO_H

#include "fila.h"
#include "utils.h"

void propagacaoFogo(char **mapa, Fila *filaDados, int altura, int comprimento, int interacao, Coordenada animal);
void propagacaoFogoVento(char **mapa, Fila *filaDados, int altura, int comprimento, int interacao, Coordenada *vento, Coordenada animal);

#endif
