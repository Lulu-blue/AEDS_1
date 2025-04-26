#include <stdio.h>
#include <stdlib.h>
#include "configuracao.h"
#include "utils.h"

Coordenada* criarVento() {
    Coordenada* vento = malloc(4 * sizeof(Coordenada));
    vento[0] = (Coordenada){1, 0};
    vento[1] = (Coordenada){0, 1};
    vento[2] = (Coordenada){0, 0};
    vento[3] = (Coordenada){0, 0};
    return vento;
}

Coordenada PosicaoAnimal(){
    Coordenada animal={1,1};
    return animal;
}

int interacoesMax(){
    int interacoes=20;
    return interacoes;
}