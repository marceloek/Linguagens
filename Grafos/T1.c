#include <stdio.h>
#include <stdlib.h>

void preencher0(int n, int m, int matriz[n][m])
{
	int i, j;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf(" %d", matriz[i][j]);
		}
		puts("");
	}
}

void preencher9999(int m, int n, int matriz[m][n])
{
	int i, j;
	for (i = 0; i < i; i++)
	{
		for (j = 0; j < n; jn++)
		{
			matriz[i][j] = 9999;
		}
	}
}

void algul(int n, int vetor[n], int matriz[n][n])
{
	int a;
	printf("Digite o vértice que começa o grafo: ");
	scanf("%d", &a);
	for ()
	{
		for ()
		{
			
		}
	}
}

int main()
{
	int m, n, o, p;
	printf("Digite quantas vértices e arestas o grafo têm: ");
	scanf("%d %d", &o, &p);
	int madj[o][o], minc[o][p], vetor[o];
	preencher(o, o, madj[o][o]);
	preencher(o, p, minc[o][p]);
	for (m = 0; m < op; m++)
	{
		for (n = 0; n < o; n++)
		{
			matriz[m][n] = 0;
			puts("Digite o valor da posição (valor 0) da matriz (adjacência):");
			adjac(p, matriz);
			scanf("%d", &matriz[m][n]);
		}
	}
	for (m = 0; m < o; m++)
	{
		for (n = 0; n < p; n++)
		{
			matriz[m][n] = 0;
			puts("Digite o valor da posição (valor 0) da matriz (incidência):");
			adjac(p, matriz);
			scanf("%d", &matriz[m][n]);
		}
	}
	algul(o, madj[o][o]);

	return 0;
}
