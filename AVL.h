#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ABP.h"

nodo *rotacao_direita(nodo *p);
nodo *rotacao_esquerda(nodo *p);
nodo *rotacao_dupla_direita(nodo *p);
nodo *rotacao_dupla_esquerda(nodo *p);
nodo *Caso1(nodo *a, int *ok);
nodo *Caso2(nodo *a, int *ok);
nodo *InsereArvoreAVLAUX(nodo *a, char palavra[max_palavra], char traducao[max_palavra], int *ok);
nodo *InsereArvoreAVL(nodo *a, char palavra[max_palavra], char traducao[max_palavra]);