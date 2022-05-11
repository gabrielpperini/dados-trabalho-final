#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ABP.c"

#include "AVL.h"

nodo *rotacao_direita(nodo *p)
{
    nodo *u;
    u = p->esq;
    p->esq = u->dir;
    u->dir = p;
    p->FB = 0;
    p = u;
    return p;
}

nodo *rotacao_esquerda(nodo *p)
{
    nodo *z;
    z = p->dir;
    p->dir = z->esq;
    z->esq = p;
    p->FB = 0;
    p = z;
    return p;
}

nodo *rotacao_dupla_direita(nodo *p)
{
    nodo *u, *v;
    u = p->esq;
    v = u->dir;
    u->dir = v->esq;
    v->esq = u;
    p->esq = v->dir;
    v->dir = p;
    if (v->FB == 1)
        p->FB = -1;
    else
        p->FB = 0;
    if (v->FB == -1)
        u->FB = 1;
    else
        u->FB = 0;
    p = v;
    return p;
}

nodo *rotacao_dupla_esquerda(nodo *p)
{
    nodo *z, *y;
    z = p->dir;
    y = z->esq;
    z->esq = y->dir;
    y->dir = z;
    p->dir = y->esq;
    y->esq = p;
    if (y->FB == -1)
        p->FB = 1;
    else
        p->FB = 0;
    if (y->FB == 1)
        z->FB = -1;
    else
        z->FB = 0;
    p = y;
    return p;
}

nodo *Caso1(nodo *a, int *ok)
{
    rotacoes++;
    a = a->esq->FB == 1 ? rotacao_direita(a) : rotacao_dupla_direita(a);
    a->FB = 0;
    *ok = 0;
    return a;
}

nodo *Caso2(nodo *a, int *ok)
{
    rotacoes++;
    a = a->dir->FB == -1 ? rotacao_esquerda(a) : rotacao_dupla_esquerda(a);
    a->FB = 0;
    *ok = 0;
    return a;
}

nodo *InsereArvoreAVLAUX(nodo *a, char palavra[max_palavra], char traducao[max_palavra], int *ok)
{
    /* Insere nodo em uma árvore AVL, onde A representa a raiz da árvore,
        x, a chave a ser inserida e h a altura da árvore */
    if (a == NULL)
    {
        a = (nodo *)malloc(sizeof(nodo));
        strcpy(a->palavra, palavra);
        strcpy(a->traducao, traducao);
        a->esq = NULL;
        a->dir = NULL;
        a->FB = 0;
        *ok = 1;
    }
    else if (strcmp(palavra, a->palavra) < 0)
    {
        a->esq = InsereArvoreAVLAUX(a->esq, palavra, traducao, ok);
        if (*ok)
        {
            switch (a->FB)
            {
            case -1:
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                a->FB = 1;
                break;
            case 1:
                a = Caso1(a, ok);
                break;
            }
        }
    }
    else
    {
        a->dir = InsereArvoreAVLAUX(a->dir, palavra, traducao, ok);
        if (*ok)
        {
            switch (a->FB)
            {
            case 1:
                a->FB = 0;
                *ok = 0;
                break;
            case 0:
                a->FB = -1;
                break;
            case -1:
                a = Caso2(a, ok);
                break;
            }
        }
    }
    return a;
}

nodo *InsereArvoreAVL(nodo *a, char palavra[max_palavra], char traducao[max_palavra])
{
    int ok;
    strlwr(palavra);
    return InsereArvoreAVLAUX(a, palavra, traducao, &ok);
}