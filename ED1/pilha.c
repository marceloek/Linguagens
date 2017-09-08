#include<stdio.h>
#include<stdlib.h>
#define MAX 5

typedef struct _pilha{
	int info[MAX];
	int topo;
}tp_pilha;

int main(){
	int n, i;
	tp_pilha *pilha = (tp_pilha*)malloc(sizeof(tp_pilha));
	pilha->topo=-1;
	do{
		puts("\t\tMENU\n");
		puts("1- Inserir um elemento na pilha;");
		puts("2- Extrair um elemento da pilha;");
		puts("3- Mostra os valores da pilha;");
		puts("0- Sair.\n");
		printf("Digite o numero correspondente a opcao: ");
		scanf("%d", &n);
		switch(n){
			case 1:
				system("clear");
				if (pilha->topo < MAX-1){
					scanf("%d", (pilha->info+(++pilha->topo)));
				}
				else
					puts("A pilha esta cheia!!!");
				system("clear");
				break;
			case 2:
				system("clear");
				if (pilha->topo > -1){
					pilha->topo--;
				}
				else
					puts("A pilha esta vazia!!!");
				break;
			case 3:
				system("clear");
				for(i=MAX-1;i>=0;i--){
					printf("Posicao %d: %d\n", i, *(pilha->info+i));
				}
				puts("");
				break;
			case 0:
				system("clear");
				puts("Voce escolheu por sair! Ate nunca mais!!!");
				break;
			default:
				puts("Opcao invalida!");
		}
	}while(n!=0);
	free(pilha);
	return 0;
}
