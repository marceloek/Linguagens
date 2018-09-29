#include <stdio.h>
#include <stdlib.h>
#include "backtracking.h"

int prim(int a, int matriz[8][8], int vetor1[8], int mp[3][8], int l)
{
	vetor1[a] = -1;
	int k = 999, j = 0, kk;
    for (int i = 0; i < 8; i++) //i= numero de colunas
    {
    	if (matriz[a][i] != 0 && vetor1[i] > -1)
    	{
    		if (mp[1][i] == 0)
    		{
    			mp[1][i] = matriz[a][i];
    			mp[2][i] = a;
    		}
    		else if (matriz[a][i] < mp[1][i])
    		{
    			mp[1][i] = matriz[a][i];
    			mp[2][i] = a;
    		}
    	}
    }
    printf("\n[%d] Interacao (V = %d):", l + 1, a);
    for (int i = 0; i < 3; i++)
    {
    	if(i==0)
    		printf("\nvertices:  |");
    	else if(i==1)
    		printf("\ndistancia: |");
    	else if(i==2)
    		printf("\nvanterior: |");
    	for (j = 0; j < 8; j++)
    	{
    		if (mp[i][j] < 10)
    			printf("0");
    		printf("%d | ", mp[i][j]);
    	}
    	puts("");
    }
    printf("\nVertices abertos: ");
    for(int i=0;i<8;i++){
    	if(vetor1[i] > -1)
    		printf("%d ", vetor1[i]);
    }
    puts("\n");
    for (int i = 0; i < 8; i++)
    {
    	if (mp[1][i] < k && vetor1[i] > -1 && mp[1][i] != 0)
    	{
    		k = mp[1][i];
    		kk = mp[0][i];
    	}
    }
    kk;
    return kk;
}

int main(void)
{
	int a = 0, vetor1[8] = {0, 1, 2, 3, 4, 5, 6, 7}, l = 0;
	int asave = a;
    int m[8][8] = {{0, 2, 0, 6, 5, 0, 0, 0},   //0
                   {2, 0, 7, 7, 0, 0, 0, 0},   //1
                   {0, 7, 0, 0, 6, 2, 0, 0},   //2
                   {6, 7, 0, 0, 0, 0, 0, 0},   //3
                   {5, 0, 6, 0, 0, 0, 4, 5},   //4
                   {0, 0, 2, 0, 0, 0, 4, 6},   //5
                   {0, 0, 0, 0, 4, 4, 0, 1},   //6
                   {0, 0, 0, 0, 5, 6, 1, 0}};  //7
    int mp[3][8] = {{0, 1, 2, 3, 4, 5, 6, 7},
                   {0, 0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 0, 0, 0}};
                   while(l<8)
                   {
        a = prim(a, m, vet, mp, l); ///atualizo valor de a e continuo a busca
        l++;
    }
    backtracking(asave, l-1, mp);
}
