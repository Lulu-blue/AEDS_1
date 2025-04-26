#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

Fila *criarFila() {
    Fila *fila = (Fila *)malloc(sizeof(Fila));
    fila->inicio = NULL;
    fila->fim = NULL;
    return fila;
}

void enfileirar(Fila *fila, int dado1, int dado2, char letra) {
    No *novo = (No *)malloc(sizeof(No));
    novo->dados[0] = dado1;
    novo->dados[1] = dado2;
    novo->letra = letra;
    novo->prox = NULL;

    if (fila->fim != NULL) {
        fila->fim->prox = novo;
    } else {
        fila->inicio = novo;
    }

    fila->fim = novo;
}

int desenfileirar(Fila *fila, int *dado1, int *dado2, char *letra) {
    if (fila->inicio == NULL) {
        return 0; // Fila vazia
    }

    No *remover = fila->inicio;
    *dado1 = remover->dados[0];
    *dado2 = remover->dados[1];
    *letra = remover->letra;
    fila->inicio = remover->prox;

    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(remover);
    return 1;
}

int filaVazia(Fila *fila) {
    return (fila->inicio == NULL);
}

void mostrarFila(Fila *fila, FILE *fp) {
    No *atual = fila->inicio;
    if (!atual) {
        fprintf(fp, "Fila vazia.\n");
        return;
    }

    while (atual != NULL) {
        fprintf(fp, "(%d, %d) virou '%c'\n", atual->dados[0], atual->dados[1], atual->letra);
        atual = atual->prox;
    }
}

void liberarFila(Fila *fila) {
    int x, y;
    char c;
    while (desenfileirar(fila, &x, &y, &c));
    free(fila);
}

