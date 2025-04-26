#ifndef MANIPULACAO_ARQUIVOS_H
#define MANIPULACAO_ARQUIVOS_H
#include "fila.h"
#include "utils.h"

char **lerArquivo(char *nomeArquivo,int *altura, int *comprimento, int *inicioIncendioX, int *inicioIncendioY, Fila *fila);
void salvarMapa(char **mapa, int altura, int comprimento, int interacao, Fila *movimentos, Coordenada animal);
void salvaCaminho(char **mapa, int altura, int comprimento, int passos, int morte);


#endif
