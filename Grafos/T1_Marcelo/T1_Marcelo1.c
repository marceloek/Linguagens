#include <stdio.h>
#include <stdlib.h>

int algulinc(int h, int a, int vetor3[5], int vetor4[4], int matriz[5][8])
{
	int k = 999999, l, l1, l2;  //k é o comparador, l é a vértice, l1 salva valor de l
	for (int i = 0; i < 8; i++) //i=numero de colunas
	{
		if (matriz[a][i] > 0 && matriz[a][i] < k)
		{
			k = matriz[a][i]; //k=valor da aresta
			l = i;			  //aresta ou coluna
		}
	}
	l1 = l;
	l2 = l;
	for (int j = 0; j < 5; j++) //j= numero de linhas
	{
		if (matriz[j][l1] != matriz[a][l1]) //if adicional para nao pegar a mesma correspondência
		{
			if (k * -1 == matriz[j][l1] || k == matriz[j][l1]) //procurando vértice
			{
				l = j; //vértice ou linha
			}
		}
	}
	a = l;
	if (k == 999999)
	{
		a = 999;
		return 999;
	}
	else
	{
		vetor3[h] = l2;
		vetor4[h] = k;
	}
	return a;
}

int alguladj(int h, int a, int vetor1[5], int vetor2[4], int matriz[5][5])
{
	int k = 999999, l;			//k é o comparador, l é a vértice
	for (int i = 0; i < 5; i++) //i= numero de colunas
	{
		if (matriz[a][i] > 0 && matriz[a][i] < k)
		{
			k = matriz[a][i]; //k=valor da aresta
			l = i;			  //vértice ou linha
		}
	}
	a = l;
	if (k == 999999)
	{
		a = 999;
		return 999;
	}
	else
	{
		vetor2[h] = k;
		h++;
		vetor1[h] = a;
	}
	return a;
}

int main(void)
{
	int j, a = 1, h = 0, soma = 0, p; //a=valor do vertice inicial (linha), h=posicao do vetor, p=valor de a
	a--;
	p = a;

	//adjacencia
	int madj[5][5] = {{0, 30, -15, 0, 20},
					  {-30, 0, -10, 50, 0},
					  {15, 10, 0, 5, -10},
					  {0, 50, -5, 0, -30},
					  {-20, 0, 10, 30, 0}},
		vetor1[5] = {a, -2, -2, -2, -2}, //vetor para guardar as vértices, 'a' sempre fica na primeira posicao
		vetor2[4] = {0, 0, 0, 0};		 //vetor para guardar o valor das arestas (4 = vertices(5) - 1 )
	for (j = 0; j < 4; j++)
	{ //j<4 pois como tem 5 vértice o número de arestas = vertices - 1
		if (a != 999)
		{
			a = alguladj(h, a, vetor1, vetor2, madj); //atualizo valor de a e continuo a busca
			h++;
		}
		else
			break;
	}
	puts("------------------------------------------------------");
	printf("Caminho:");
	vetor1[0] = p;
	for (j = 0; j < 5; j++)
	{
		if (vetor1[j] >= 0)
			printf(" [%d] ->", vetor1[j] + 1); //imprimindo vetor1 que guarda os vértices
		else
			break;
	}
	for (j = 0; j < 4; j++) //calculando soma que faz o somatório da distância das arestas
	{
		soma += vetor2[j];
	}
	printf("\nDistância total (adjacência)(em unidades de medida): %d\n", soma);
	puts("------------------------------------------------------");
	puts("------------------------------------------------------");

	//incidência
	int minc[5][8] = {{30, 0, 0, 20, -15, 0, 0, 0},  //1
					  {-30, 50, 0, 0, 0, -10, 0, 0}, //2
					  {0, 0, 0, 0, 15, 10, -10, 5}, //3
					  {0, 50, -30, 0, 0, 0, 0, -5},  //4
					  {0, 0, 30, -20, 0, 0, 10, 0}}, //5
		vetor3[5] = {-2, -2, -2, -2, -2},			 //vetor para guardar as arestas (a,b,c,d,...),
		vetor4[4] = {0, 0, 0, 0};					 //vetor para guardar a distância das arestas (4 = vertices(5) - 1 )
	a = p, h = 0, soma = 0;
	for (j = 0; j < 4; j++)
	{ //j<4 pois como têm 5 vértices o número de arestas = vértices - 1
		if (a != 999)
		{
			a = algulinc(h, a, vetor3, vetor4, minc); //atualizo valor de a e continuo a busca
			h++;
		}
		else
			break;
	}
	printf("Caminho:");
	for (j = 0; j < 5; j++) //imprimindo vetor3 que guarda as arestas
	{
		if (vetor3[j] >= 0)
			printf(" [%d] ->", vetor3[j]);
		else
			break;
	}
	for (j = 0; j < 4; j++) //calculando soma que faz o somatório da distância das arestas
	{
		soma += vetor4[j];
	}
	printf("\nDistância total (incidência)(em unidades de medida): %d\n", soma); //imprimindo soma

	puts("------------------------------------------------------");
	printf("Legenda: {[0]=a,[1]=b,[2]=c,[3]=d,[4]=e,[5]=f,[6]=g,[7]=h,[8]=i,[9]=j,[10]=k,[11]=l,[12]=m, ...}\n");
	puts("------------------------------------------------------");
	return 0;
}