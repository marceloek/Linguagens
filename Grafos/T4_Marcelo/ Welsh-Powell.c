#include <stdio.h>
#include <stdlib.h>

void sort(int vet[3][11])
{
    int temp1, temp2, i;
    for (i = 0; i < 10; i++)
    {
        if (vet[1][i] < vet[1][i + 1])
        {
            temp1 = vet[1][i + 1];
            temp2 = vet[0][i + 1];
            vet[1][i + 1] = vet[1][i];
            vet[0][i + 1] = vet[0][i];
            vet[1][i] = temp1;
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
            printf("Vertices: |");
        else if (j == 1)
            printf("Graus:    |");
        else if (j == 2)
            printf("Cores:    |");
        for (int i = 0; i < 11; i++)
        {
            if (vet[j][i] < 10)
                printf(" 0%d |", vet[j][i]);
            else
                printf(" %d |", vet[j][i]);
        }
        puts("");
    }
}

void welshpowell(int m[11][11], int vet[3][11])
{
    int i, j, k, aux1, aux2, count1 = 0, count2 = 0, cor = 1;
    for (i = 0; i < 11; i++) //linha da matriz (vertice)
    {
        for (j = 0; j < 11; j++) //coluna da matriz (procura os vertices conectados)
        {
            if (m[i][j] == 1) //encontra o vertice conectado
            {
                count1++;           //aumenta contador de grau pela coneccao
                vet[1][i] = count1; //aplica grau
            }
        }
        count1 = 0; //reseta contador apos mudar de vertice
    }
    sort(vet);           //aplica a ordenacao do grau dos vertices
    while (count2 != 11) //verifica se coloriu todos os vertices
    {
        for (k = 0; k < 11; k++) //laco para pintar ou nao os vertices
        {
            if (vet[2][k] == 0) //verifica se o vertice ja foi pintado
            {
                for (j = 0; j < 11; j++) //laco para achar os vertices conectados
                {
                    aux1 = vet[0][k] - 1; //posicao do vertice a ser colorido na matriz
                    if (m[aux1][j] == 1)  //verifica a coneccao com o vertice
                    {
                        aux2 = j + 1;            //aumenta mais um por conta do valor real do vertice e nao sua posicao
                        for (i = 0; i < 11; i++) //laco para encontrar no vetor o vertice conectado
                        {
                            if (vet[0][i] == aux2) //caso encontre o vertice
                            {
                                if (vet[2][i] != cor) //caso a cor do vertice for diferente da cor a ser aplicada
                                    count1 = 1; //variavel para mudar a cor
                                else            //caso a cor do vertice for igual a cor a ser aplicada
                                    count1 = 0; //variavel para nao mudar a cor
                                break; //break para nao continuar a busca, pois ja achou o vertice e ele eh unico
                            }
                        }
                        if (count1 == 0) //caso encontre ao menos um vertice irregular, o laco é interrompido, ja que nao eh mais necessario continuar e para nao mudar o count1
                            break;
                    }
                }
                if (count1 == 1) //caso o vertice sera pintado
                {
                    vet[2][k] = cor; //aplica cor
                    count2++;        //aumenta o contador dos vertices pintados
                }
            }
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
    welshpowell(m, vet);                                   //aplico o algoritmo
}
