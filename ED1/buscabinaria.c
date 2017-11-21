#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int v[10]){
	int i, t1;
	for(i=0;i<9;i++){
		if(v[i]>v[i+1]){
			t1=v[i+1];
			v[i+1]=v[i];
			v[i]=t1;
			i=-1;
		}
	}
	system("clear");
}

void inserir(int v[10]){
	int n, i = 0;
	system("clear");
	for(;i<10;i++){
		printf("Digite o valor da posicao %d: ", i);
		scanf("%d", &n);
		v[i] = n;
	}
	bubbleSort(v);
}

void print(int v[10]){
	int i;
	for(i=0;i<10;i++){
		printf("Posicao %d: %d;\n", i, v[i]);
	}
}

int busca(int v[10], int min, int max, int n){
	int mid;
	mid=(min+max)/2;
	while(min<=max){
		if(n==v[mid]){
			printf("Valor encontrado na posicao: %d!\n", mid);
			return 0;
		}else if(n>v[mid]){
			return busca(v, mid+1, max, n);
		}else if(n<v[mid]){
			return busca(v, min, mid-1, n);
		}
	}
	puts("Valor nao encontrado!");
	return -1;
}

int main(){
	int v[10], p, n;
	do{
		puts("\t\tMENU\n");
		puts("(1) Para inserir os valores no vetor;");
		puts("(2) Para listar os valores dos elementos do vetor;");
		puts("(3) Para procurar determinado elemento;");
		puts("(0) Sair.\n");
		printf("Digite o numero correspondente a opcao: ");
		scanf("%d", &p);
		switch(p){
			case 1:
				system("clear");
				inserir(v);
				break;
			case 2:
				system("clear");
				print(v);
				break;
			case 3:
				system("clear");
				printf("Digite o valor do elemento que deseja encontrar: ");
				scanf("%d", &n);
				busca(v,0,9,n);
				break;
			case 0:
				system("clear");
				puts("Voce escolheu por sair! Ate nunca mais!");
				break;
			default:
				system("clear");
				puts("Opcao invalida!");
		}
	}while(p!=0);
	return 0;
}

