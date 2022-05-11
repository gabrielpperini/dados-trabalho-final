#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#include "AVL.c"

nodo *CriarArvoreDicionario(nodo *arvore, FILE *arq, int arvType)
{
    char *palavra, *traducao, linha[100]; // linhas a serem lidas do arquivo

    // percorre todo o arquivo lendo linha por linha
    while (fgets(linha, 1000, arq))
    {
        if (linha != NULL)
        {
            // define palavras
            palavra = strtok(linha, "\t");
            traducao = strtok(NULL, "\t\n");
            // insere palavras na arvore dependendo seu modelo: ABP =1 e AVL != 1
            if (arvType == 1)
            {
                arvore = InsereArvoreABP(arvore, palavra, traducao);
            }
            else
            {
                arvore = InsereArvoreAVL(arvore, palavra, traducao);
            }
        }
    }
    return arvore;
}

void parafraseaTexto(nodo *arvore, FILE *entrada, FILE *saida)
{
    char *palavra, linha[1000]; // linhas a serem lidas do arquivo
    char separador[] = {" ,.&*%%\\?!;/'@\"$#=><()][}{:\n\t"};

    // percorre todo o arquivo lendo linha por linha
    while (fgets(linha, 1000, entrada))
    {
        char *copy = strdup(linha);
        palavra = strtok(linha, separador); // considera qualquer caractere não alfabético como separador
        while (palavra != NULL)
        {
            // busca na aravore a correspondencia da palavra
            nodo *result = consulta(arvore, strdup(palavra));

            // define a palavra a ser escrita na saida
            char *palavraToPrint = strdup(result == NULL ? palavra : result->traducao);

            // processo para definir o divisor das duas palavra
            int from = palavra - linha + strlen(palavra);
            palavra = strtok(NULL, separador);
            int to = palavra != NULL ? palavra - linha : strlen(copy);

            // escreve na saida a palavra e seu delimitador
            fprintf(saida, "%s%.*s", palavraToPrint, to - from, copy + from);
        }
    }
}

int mainAux(int argc, char const *argv[], int arvType)
{
    setlocale(LC_ALL, ""); // para imprimir corretamente na tela os caracteres acentuados

    FILE *dicionario;
    FILE *entrada;
    FILE *saida;

    // Variaveis de tempo para contagem
    clock_t startArv, endArv, startSaida, endSaida;
    float tempoArv, tempoSaida;

    // O numero de parametros esperado é 4: nome do programa (argv[0]), nome do arq do dicionario(argv[2]),
    // nome do arq de entrada(argv[2]), nome do arq de saida(argv[3])
    if (argc != 4)
    {
        printf("Número incorreto de parâmetros.\nPara chamar o programa digite: exemplo <arq_dicionário> <arq_entrada> <arq_saida>\n");
        return 1;
    }

    dicionario = fopen(argv[1], "r"); // abre o arquivo de dicionario para leitura
    if (dicionario == NULL)           // se não conseguiu abrir o arquivo
    {
        printf("Erro ao abrir o arquivo %s", argv[1]);
        return 1;
    }

    entrada = fopen(argv[2], "r"); // abre o arquivo de entrada para leitura
    if (entrada == NULL)           // se não conseguiu abrir o arquivo
    {
        printf("Erro ao abrir o arquivo %s", argv[2]);
        return 1;
    }

    saida = fopen(argv[3], "w"); // abre o arquivo para saida

    // Grava o tempo de começo de construção da arvore
    startArv = clock();

    // Cria arvore do arquivo de dicionario
    nodo *arvore = NULL;
    arvore = CriarArvoreDicionario(arvore, dicionario, arvType);

    // Grava o tempo final de construção da arvore
    endArv = clock();

    // imprimiArvore(arvore);

    // Grava o tempo de começo do processo de parafrasear o texto
    startSaida = clock();

    // Parafrasea o texto e imprime na saida
    parafraseaTexto(arvore, entrada, saida);

    // Grava o tempo final do processo de parafrasear o texto
    endSaida = clock();

    // define os tempos decorridos
    tempoArv = (float)(endArv - startArv) / CLOCKS_PER_SEC * 1000;       // geração da arvore
    tempoSaida = (float)(endSaida - startSaida) / CLOCKS_PER_SEC * 1000; // processo de parafrasear o texto

    printEstatisticas(arvType == 1 ? "ABP" : "AVL", tempoArv, tempoSaida, arvore);

    // fecha os arquivos
    fclose(dicionario);
    fclose(entrada);
    fclose(saida);
    return 0;
}
