#ifndef FILA_H
#define FILA_H
#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dados[2];
    char letra;
    struct No *prox;
} No;

typedef struct {
    No *inicio;
    No *fim;
} Fila;

// Interface da fila
Fila *criarFila();
void enfileirar(Fila *fila, int dado1, int dado2, char letra);
int desenfileirar(Fila *fila, int *dado1, int *dado2, char *letra);
int filaVazia(Fila *fila);
void mostrarFila(Fila *fila, FILE *fp);
void liberarFila(Fila *fila);

#endif
