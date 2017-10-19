#include<stdio.h>
#include<stdlib.h>

void bubbleSort(int v[6]){
	int i, temp;
	for(i=0;i<5;i++){
		if(v[i]>v[i+1]){
			temp=v[i+1];
			v[i+1]=v[i];
			v[i]=temp;
			i=-1;
		}
	}
	system("clear");
}

void selectionSort(int v[6]){
	int i, j, temp;
	for(i=0;i<5;i++){
		if(v[i]>v[j]){
			temp=v[j];
			v[j]=v[i];
			v[i]=temp;
		}
	}
	system("clear");	
}

void insertionSort(int v[6]){
	int i;
	for(i=0;i<6;i++){
		if(v[i]<v[i-1])
			
	}
	system("clear");
}

void print(int v[6]){
	int i;
	for(i=0;i<6;i++){
		printf("Posicao %d: %d;\n", i, v[i]);	
	}
}

int main(){
	int v[6]={4, 2, 7, 3, 9, 1}, n;
	do{
		puts("\t\tMENU\n");
		puts("(1) Para ordenar o vetor por BubbleSort;");
		puts("(2) Para ordenar o vetor por SelectionSort;");
		puts("(3) Para ordenar o vetor por InsertionSort;");
		puts("(4) Para listar os elementos do vetor;");
		puts("(0) Sair.\n");
		printf("Digite o numero correspondente a opcao: ");
		scanf("%d", &n);
		switch(n){
			case 1:
				system("clear");
				bubbleSort(v);
				puts("Voce ordenou por BubbleSort!");
				break;
			case 2:
				system("clear");
				selectionSort(v);
				puts("Voce ordenou por SelectionSort!");
				break;
			case 3:
				system("clear");
				insertionSort(v);
				puts("Voce ordenou por InsertionSort!");
				break;
			case 4:
				system("clear");
				print(v);
				break;
			case 0:
				system("clear");
				puts("Voce escolheu por sair! Ate nunca mais!");
				break;
			default:
				system("clear");
				puts("Opcao invalida!");
		}
	}while(n!=0);
	return 0;
}
