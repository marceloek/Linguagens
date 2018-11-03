#include <stdio.h>
#include <stdlib.h>

void sort(int vet[3][11])
{
    int temp, temp2;
    for (int i = 0; i < 10; i++)
    {
        if (vet[1][i] < vet[1][i + 1])
        {
            temp = vet[1][i + 1];
            temp2 = vet[0][i + 1];
            vet[1][i + 1] = vet[1][i];
            vet[0][i + 1] = vet[0][i];
            vet[1][i] = temp;
            vet[0][i] = temp2;
            i = -1;
        }
    }
}

void display(int vet[3][11])
{
    for (int j = 0; j < 3; j++)
    {
        if (j == 0)
            printf("Vertice: |");
        else if (j == 1)
            printf("Grau:    |");
        else if (j == 2)
            printf("Cor:     |");
        for (int i = 0; i < 11; i++)
        {
            if (vet[j][i] < 10)
                printf(" 0%d |", vet[j][i]);
            else
                printf(" %d |", vet[j][i]);
        }
        puts("");
    }
    puts("");
}

void welshpowell(int m[11][11], int vet[3][11])
{
    int i, j, k, p, aux, aux2, count = 0, count2 = 0, cor = 1;
    for (i = 0; i < 11; i++)
    {
        for (j = 0; j < 11; j++)
        {
            if (m[i][j] == 1)
            {
                count++;
                vet[1][i] = count;
            }
            if (count > count2)
                count2 = count;
        }
        count = 0;
    }
    sort(vet);
    display(vet);
    count = 0;
    count2 = 0;
    while (count2 != 11) //verifica se coloriu todos os vértices
    {
        for (k = 0; k < 11; k++) //laco para pintar ou nao os vértices
        {
            if (vet[2][k] == 0) //verifica se o vertice ja foi pintado
            {
                for (j = 0; j < 11; j++) //laco para achar os vertices conectados
                {
                    aux = vet[0][k] - 1; //posicao do vertice a ser colorido na matriz
                    if (m[aux][j] == 1)  //verifica coneccao com vertice
                    {
                        aux2 = j + 1;
                        for (p = 0; p < 11; p++) //laco para encontrar o vertice conectado no vetor
                        {
                            if (vet[0][p] == aux2) //caso encontre o vertice
                            {
                                if (vet[2][p] != cor)
                                {
                                    if (vet[2][p] != vet[2][k] || vet[2][p] == 0) //verifica se ambos tem a mesma cor
                                    {
                                        vet[2][k] = cor;
                                        count = 1;
                                    }
                                    else
                                    {
                                        vet[2][k] = 0;
                                        count = 0;
                                    }
                                }
                                else
                                    count = 0;
                            }
                        }
                        if (count == 0)
                            break;
                    }
                }
                if (count == 1) //caso o vertice foi pintado
                {
                    vet[2][k] = cor;
                    count2++;
                }
                else if (count == 0)
                {
                    vet[2][k] = 0;
                }
            }
            count = 0;
        }
        cor++;
    }
    display(vet);
}

int main(void)
{
    int m[11][11] = {{0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0},    //a
                     {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},    //b
                     {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},    //c
                     {0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1},    //d
                     {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},    //e
                     {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},    //f
                     {0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1},    //g
                     {1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1},    //h
                     {0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0},    //i
                     {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1},    //j
                     {0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0}};   //k
    int vet[3][11] = {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, //vertice
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},   //grau
                      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};  //cor
    welshpowell(m, vet);
}
/*
 
    int vet[3][11] = {{08, 11, 04, 07, 09, 10, 01, 02, 05, 06, 03}, //vertice
                      {05, 05, 04, 03, 03, 03, 02, 02, 02, 02, 01},   //grau
                      {01, 02, 01, 03, 02, 03, 02, 03, 01, 02, 02}};  //cor
 */
