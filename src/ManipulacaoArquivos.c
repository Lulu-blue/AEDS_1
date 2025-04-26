#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ManipulacaoArquivos.h"

char **lerArquivo(char *nomeArquivo,int *altura, int *comprimento, int *inicioIncendioX, int *inicioIncendioY, Fila *fila)
{
    FILE *fp;
    fp = fopen(nomeArquivo, "r");
    if (!fp)
    {
        printf("Erro na abertura do arquivo.");
        exit(1);
    }

    char linha[1000];
    fgets(linha, sizeof(linha), fp);
    sscanf(linha, "%d %d %d %d", altura, comprimento, inicioIncendioX, inicioIncendioY);

    enfileirar(fila, *inicioIncendioX, *inicioIncendioY, '2');

    char **mapa = (char **)malloc(*altura * sizeof(char *));
    for (int i = 0; i < *altura; i++)
    {
        mapa[i] = (char *)malloc((*comprimento + 1) * sizeof(char));
    }

    for (int i = 0; i < *altura; i++)
    {
        fgets(linha, sizeof(linha), fp);
        int col = 0;
        for (int j = 0; linha[j] != '\0' && col < *comprimento; j++)
        {
            if (linha[j] != ' ' && linha[j] != '\n')
            {
                mapa[i][col] = linha[j];
                col++;
            }
        }
        mapa[i][col] = '\0';
    }

    mapa[*inicioIncendioX][*inicioIncendioY] = '2';

    fclose(fp);
    return mapa;
}

void salvarMapa(char **mapa, int altura, int comprimento, int interacao, Fila *movimentos, Coordenada animal)
{
    // Se for a primeira interação, substitui o conteúdo. Senão, adiciona.
    FILE *fp = fopen("output.dat", interacao == 1 ? "w" : "a");
    if (!fp)
    {
        printf("Erro ao abrir ou criar o arquivo output.dat\n");
        return;
    }

    fprintf(fp, "Interação %d: \n", interacao);
    mostrarFila(movimentos, fp); 

    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < comprimento; j++)
        {
            fprintf(fp, "%c", mapa[i][j]);
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "Posição do animal: ( %d, %d )\n", animal.x, animal.y);
    fclose(fp);
}

void salvaCaminho(char **mapa, int altura, int comprimento, int passos, int morte)
{
    FILE *fp = fopen("output.dat", "a");
    if (!fp)
    {
        printf("Erro ao abrir ou criar o arquivo output.dat\n");
        return;
    }

    fprintf(fp, "\nCaminho:\n");
    for (int i = 0; i < altura; i++)
    {
        for (int j = 0; j < comprimento; j++)
        {
            fprintf(fp, "%c", mapa[i][j]);
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "Nº de passos: %d\n", passos);
    if (morte == 0)
    {
        fprintf(fp, "O animal morreu x_x\n");
    }
    else
    {
        fprintf(fp, "O animal sobreviveu :)\n");
    }
    fclose(fp);
}
