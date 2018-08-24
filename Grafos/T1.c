#include <stdio.h>
#include <stdlib.h>

int algulinc(int h,int a, int vetor3[7], int vetor4[6], int matriz[7][9])
{
	int k=999999, l, l1; //k é comparador, l é o valor da vértice, l1 salva valor de l
	for (int i = 0; i < 9; i++) //i= numero de colunas
	{
		if (matriz[a][i] > 0 && matriz[a][i] < k)
		{
			k = matriz[a][i]; //k=valor da aresta
			l = i; //qual aresta
		}
	}
	l1=l;
	vetor3[h]=l;
	for(int j=0;j<7;j++){ //procurando vértice
		if (k*-1==matriz[j][l1])
		{
			l = j; //vértice
		}
	}
	a=l;
	printf("k =%d, a=%d\n", k, a);
	if(k==999999){
		a=999;
		return 999;
	}else{
		vetor4[h]=k;
	}
	return a;
}

int alguladj(int h,int a, int vetor1[7], int vetor2[6], int matriz[7][7])
{
	int k=999999, l; //k é comparador, l=o valor da vértice
	for (int i = 0; i < 7; i++) //i= numero de colunas
	{
		if (matriz[a][i] > 0 && matriz[a][i] < k)
		{
			k = matriz[a][i]; //k=aresta
			l = i; //vértice
		}
	}
	a=l;
	if(k==999999){
		a=999;
		return 999;
	}else{
		vetor2[h]=k;
		h++;
		vetor1[h]=a;
	}
	return a;
}

int main(void)
{
	int j, a=1, h=0, soma=0, p; //a=valor do vertice inicial (linha), h=posicao do vetor, p=valor de a
	a--;
	p=a;

	//adjacencia		
	int madj[7][7] = {{0,2,0,6,12,0,0},
		{-2,0,1,0,0,5,0},
		{0,-1,0,0,0,0,40},
		{-6,0,0,0,0,-4,0},
		{-12,0,0,0,0,0,30},
		{0,-5,0,-4,0,0,8},
		{0,0,-40,0,-30,-8,0}},
	vetor1[7]={a,-2,-2,-2,-2,-2,-2}, //vetor para guardar as vértices, 'a' sempre fica na primeira posicao
	vetor2[6]={0,0,0,0,0,0}; //vetor para guardar o valor das arestas
	for(j=0;j<6;j++){ //j<4 pois como tem 5 vértice o número de arestas = vertices - 1
		if(a!=999){
			a=alguladj(h, a, vetor1, vetor2, madj);
			h++;
		}else
			break;
	}
	puts("------------------------------------------------------");
	printf("Caminho:");
	vetor1[0]=p;
	for(j=0;j<7;j++){
		if(vetor1[j]>=0)
			printf(" [%d] ->", vetor1[j]+1);
		else 
			break;
	}
	for(j=0;j<6;j++){
		soma += vetor2[j];
	}
	printf("\nDistância total (adjacência)(em unidades de medida): %d\n", soma);
	puts("------------------------------------------------------");

	//incidencia
	int minc[7][9] = {{2, 0, 0, 0, 12, 6, 0, 0, 0},  //1
					  {-2, 1, 0, 0, 0, 0, 0, 0, 5}, //2
					  {0, -1, 40, 0, 0, 0, 0, 0, 0},  //3
					  {0, 0, 0, 0, 0, -6, 4, 0, 0},  //4
					  {0, 0, 0, -30, -12, 0, 0, 0, 0}, //5
					  {0, 0, 0, 0, 0, 0, -4, 8, -5}, //6
					  {0, 0, -40, -30, 0, 0, 0, -8, 0}}, //7
	vetor3[7]={-2,-2,-2,-2,-2,-2,-2}, //vetor para guardar as vértices, 'a' sempre fica na primeira posicao
	vetor4[6]={0,0,0,0,0,0}; //vetor para guardar o valor das arestas
	a=p, h=0, soma=0; 
	for(j=0;j<6;j++){ //j<4 pois como tem 5 vértice o número de arestas = vertices - 1
		if(a!=999){
			a=algulinc(h, a, vetor3, vetor4, minc);
			h++;
		}else
			break;
	}
	printf("Caminho:");
	for(j=0;j<7;j++){
		if(vetor3[j]>=0)
			printf(" [%d] ->", vetor3[j]);
		else 
			break;
	}
	for(j=0;j<4;j++){
		soma += vetor4[j];
	}
	printf("\nDistância total (incidência)(em unidades de medida): %d\n", soma);
	
	puts("------------------------------------------------------");
	printf("Legenda: {[0]=a,[1]=b,[2]=c,[3]=d,[4]=e,[5]=f,[6]=g,[7]=h,[8]=i,[9]=j,[10]=k,[11]=l,[12]=m, ...}\n");
	return 0;
}
