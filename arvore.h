#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_palavra 50

struct TNodo;
typedef struct TNodo nodo;

int contaNodos(nodo *a);
int alturaArvore(nodo *a);
void imprimiArvoreAux(nodo *a, int key);
void imprimiArvore(nodo *a);
nodo *consulta(nodo *a, char p[50]);
void printEstatisticas(char arv[3], float tempoArv, float tempoSaida, nodo *arvore);