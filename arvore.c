#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"

int comp = 0;
int rotacoes = 0;

struct TNodo
{
    char palavra[max_palavra];
    char traducao[max_palavra];
    int FB;
    struct TNodo *esq;
    struct TNodo *dir;
};
typedef struct TNodo nodo;

int contaNodos(nodo *a)
{
    if (a == NULL)
        return 0;
    int i = 1;
    i += contaNodos(a->dir);
    i += contaNodos(a->esq);
    return i;
}

int alturaArvore(nodo *a)
{
    // se a arvore estiver vazia retorna 0
    if (a == NULL)
        return 0;

    int esq, dir;

    // altura da subarvore da esquerda somada de 1
    esq = 1 + alturaArvore(a->esq);
    // altura da subarvore da direita somada de 1
    dir = 1 + alturaArvore(a->dir);

    // se a altura da arvore esquerda é maior ou igual que a da direita, retorna a altura da esquerda
    return esq >= dir ? esq : dir;
}

void imprimiArvoreAux(nodo *a, int key)
{
    if (a != NULL)
    {
        int i;
        for (i = 0; i < key; i++)
            printf("=");
        printf(" %s --> %s\n", a->palavra, a->traducao);
        imprimiArvoreAux(a->esq, key + 1);
        imprimiArvoreAux(a->dir, key + 1);
    }
}

void imprimiArvore(nodo *a)
{
    imprimiArvoreAux(a, 1);
}

nodo *consulta(nodo *a, char p[50])
{
    strlwr(p); // coloca a palavra para minusculo
    while (a != NULL)
    {
        // compara string 
        int compare = strcmp(p, a->palavra);
        comp++;
        if (compare == 0) // se for igual
        {
            comp++;
            return a;
        }
        else
        {
            comp++;
            // compara para determinar qual subárvore seguir
            a = compare < 0 ? a->esq : a->dir;
        }
    }
    return NULL;
}

// Imprime as estatísticas do programa no terminal
void printEstatisticas(char arv[3], float tempoArv, float tempoSaida, nodo *arvore)
{
    printf("\n\n======== ESTATÍSTICAS %s ========\n", arv);
    printf("Número de nodos: %d\n", contaNodos(arvore));
    printf("Altura: %d\n", alturaArvore(arvore));
    printf("Rotações: %d\n", rotacoes);
    printf("Comparações: %d\n", comp);
    printf("Tempo de Geração da Árvore: %.2f milisegundos\n", tempoArv);
    printf("Tempo de Processamento da Saída: %.2f milisegundos\n", tempoSaida);
    printf("\n\n\n");
}