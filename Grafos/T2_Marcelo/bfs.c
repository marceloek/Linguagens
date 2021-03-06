#include <stdio.h>
#include <stdlib.h>
#include "backtracking.h"

int bfs(int a, int matriz[21][21], int vetor1[21], int mp[4][21], int vet[21], int l, int vet2[1])
{   
	int aux, count=0, j=0, aa = a + 1;
	vetor1[a] = -1;
    vet[l-1]=-1;
	mp[3][a] = 1;
    for (int i = 0; i < 21; i++) //i= numero de colunas
    {
    	if (matriz[a][i] == 1 && vetor1[i] > -1)
    	{
    		aux = vet2[0];
    		for(j=0;j<aux;j++){
                if(mp[3][i]==-1)
                    count=0;
                else
                    count=1;
            }
            if(count == 0){
                vet2[0]++;
                vet[aux] = i;
            }
            if(mp[3][i]==-1)
                mp[3][i]=0;
            else if(mp[3][i]==0)
                mp[3][i]=1;

            if (mp[1][i] == 0 && vetor1[i] > -1)
            {
                mp[1][i] = matriz[a][i] + mp[1][a];
                mp[2][i] = aa;
            }
            else if (matriz[a][i] + mp[1][a] < mp[1][i])
            {
                mp[1][i] = matriz[a][i] + mp[1][a];
                mp[2][i] = aa;
            }
        }
    }
    printf("\n[%d] Interacao (V = %d):", l + 1, aa);
    for (int i = 0; i < 4; i++)
    {
        if(i==0)
            printf("\nvertices:  |");
        else if(i==1)
            printf("\ndistancia: |");
        else if(i==2)
            printf("\nVanterior: |");
        else if(i==3)
            printf("\ncor:       |");
        for (j = 0; j < 21; j++)
        {
            if (mp[i][j] < 10 && mp[i][j] > -1)
                printf("0");
            printf("%d | ", mp[i][j]);
        }
        puts("");
    }
    printf("\nVetor (F):");
    for(int i=0;i<21;i++){
        if(vet[i] > -1)
            printf(" %d", vet[i]+1);
    }
    puts("\n");
    return vet[l];
}

int main(void)
{
	int a = 1, vetor1[21] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21}, vet[21]={-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, l=0, vet2[2]={0,0};
	a--;
	int mp[4][21] = {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}};
	int m[21][21] =
    {{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, ///a01
    {1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  ///b02
    {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  ///c03
    {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},  ///d04
    {0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  ///e05
    {0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  ///f06
    {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  ///g07
    {0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  ///h08
    {0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},  ///i09
    {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},  ///j10
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},  ///k11
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},  ///l12
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},  ///m13
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},  ///n14
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0},  ///o15
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0},  ///p16
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0},  ///q17
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},  ///r18
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1},  ///s19
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},  ///t20
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0}}; ///z21
    while (l <= 20)
    {
        a = bfs(a, m, vetor1, mp, vet, l, vet2); ///atualizo valor de a e continuo a busca
        l++;
    }
    backtracking(21, mp);
}