#include <stdio.h>
#include <stdlib.h>
#include "backtracking.h"

int dijkstra(int a, int matriz[7][7], int vetor1[7], int mp[3][7], int l)
{
    vetor1[a] = -1;
    int k = 999, aa = a + 1, j = 0, kk;
    for (int i = 0; i < 7; i++) //i= numero de colunas
    {
    	if (matriz[a][i] != 0 && vetor1[i] > -1)
    	{
    		if (mp[1][i] == 0)
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
    for (int i = 0; i < 3; i++)
    {
    	if(i==0)
    		printf("\nvertices:  |");
    	else if(i==1)
    		printf("\ndistancia: |");
    	else if(i==2)
    		printf("\nVanterior: |");
    	for (j = 0; j < 7; j++)
    	{
    		if (mp[i][j] < 10)
    			printf("0");
    		printf("%d | ", mp[i][j]);
    	}
    	puts("");
    }
    printf("\nVertices abertos: ");
    for(int i=0;i<7;i++){
        if(vetor1[i] > -1)
            printf("%d ", vetor1[i]);
    }
    puts("\n");
    for (int i = 0; i < 7; i++)
    {
    	if (mp[1][i] < k && vetor1[i] > -1 && mp[1][i] != 0)
    	{
    		k = mp[1][i];
    		kk = mp[0][i];
    	}
    }
    kk--;
    return kk;
}

int main(void)
{
	int a = 1, vet[7] = {1, 2, 3, 4, 5, 6, 7}, l = 0;
	a--;
    int m[7][7] = {{0, 7, 0, 5, 0, 0, 0},   //a
                   {7, 0, 8, 9, 7, 0, 0},   //b
                   {0, 8, 0, 0, 5, 0, 0},   //c
                   {5, 9, 0, 0, 15, 6, 0},  //d
                   {0, 7, 5, 15, 0, 8, 9},  //e
                   {0, 0, 0, 6, 8, 0, 11},  //f
                   {0, 0, 0, 0, 9, 11, 0}}; //g
    int mp[3][7] = {{1, 2, 3, 4, 5, 6, 7},
                   {0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 0, 0}};
    while(l<7)
    {
        a = dijkstra(a, m, vet, mp, l); ///atualizo valor de a e continuo a busca
        l++;
    }
    backtracking(7, mp);
}
