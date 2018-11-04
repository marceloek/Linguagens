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
            if (m[i][j] == 1) //aplica grau
            {
                count++;
                vet[1][i] = count;
            }
            if (count > count2) //encontra maior grau do vetor
                count2 = count;
        }
        count = 0; //reseta contador
    }
    sort(vet);
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
                    if (m[aux][j] == 1)  //verifica a coneccao com o vertice
                    {
                        aux2 = j + 1;
                        for (p = 0; p < 11; p++) //laco para encontrar no vetor o vertice conectado
                        {
                            if (vet[0][p] == aux2) //caso encontre o vertice
                            {
                                if (vet[2][p] != cor) //caso a cor do vertice for diferente da cor a ser aplicada
                                {
                                    if (vet[2][p] != vet[2][k] || vet[2][p] == 0) //verifica se ambos nao tem a mesma cor ou se o vertice conectado esta sem cor
                                        count = 1;                                //variavel para atribuir a cor depois
                                    else
                                        count = 0; //variavel para reseta a cor depois
                                }
                                else //caso a cor do vertice nao for diferente da cor a ser aplicada, a cor do vertice eh resetada
                                    count = 0;
                            }
                        }
                        if (count == 0) //caso encontre ao menos um vertice irregular
                            break;
                    }
                }
                if (count == 1) //caso o vertice sera pintado
                {
                    vet[2][k] = cor; //aplica cor
                    count2++;        //aumenta o contador dos vertices pintados
                }
                else if (count == 0) //caso o vertice nao sera pintado
                    vet[2][k] = 0;   //reseta cor
            }
            count = 0; //reseta contador da cor
        }
        cor++; //aumenta a cor a ser aplicada
    }
    display(vet); //printa vetor
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