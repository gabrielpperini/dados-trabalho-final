#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_palavra 50

struct TNodo;
typedef struct TNodo nodo;

int contaNodos(nodo *a);
void imprimiArvore(nodo *a);
void printEstatisticas(char arv[3], float tempoArv, float tempoSaida, nodo *arvore);