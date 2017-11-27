#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio_ext.h>
#define TAM 50

typedef struct _produto{
	int cod;
	char nome[TAM];
	float preco;
}tp_produto;

typedef struct _pilha{
	tp_produto *info;
	int topo;
}tp_pilha;

int main(){
	int n, i, a;
	puts("Digite o numero de produtos:");
	scanf("%d", &a);
	tp_pilha *p = (tp_pilha*)malloc(sizeof(tp_pilha));
	p->topo=-1;
	p->info = (tp_produto*)malloc(sizeof(tp_produto)*a);
	do{
		puts("\t\tMENU\n");
		puts("(1) Para inserir um produto na pilha;");
		puts("(2) Para extrair um elemento da pilha;");
		puts("(3) Para listar todos os campos dos elementos da pilha;");
		puts("(0) Sair.\n");
		printf("Digite o numero correspondente a opcao: ");
		scanf("%d", &n);
		switch(n){
			case 1:
				system("clear");
				if (p->topo < a-1){
					p->topo++;
					__fpurge(stdin);
					printf("Codigo do produto [%d]: ", p->topo);
					scanf("%d", &((p->info+(p->topo))->cod));
					getchar();
					printf("Nome do produto [%d]: ", p->topo);
					scanf("%[^\n]s", ((p->info+(p->topo))->nome));
					getchar();
					printf("Preco do produto [%d]: R$ ", p->topo);
					scanf("%f", &((p->info+(p->topo))->preco));
				}else
					puts("A pilha esta cheia!!!");
				break;
				system("clear");
			case 2:
				system("clear");
				if (p->topo > -1){
					p->topo--;
					puts("Elemento extraido com sucesso!");
				}
				else
					puts("A pilha esta vazia!");
				break;
			case 3:
				system("clear");
				for(i=p->topo;i>=0;i--){
					printf("Informacoes do produto [%d]:\nCodigo: %d\n", i, (p->info->cod+i)),
					printf("Nome: %s\nPreco: R$ %.2f\n", (p->info->nome+i), (p->info->preco+i));
				}
				puts("");
				break;
			case 0:
				system("clear");
				puts("Voce escolheu por sair! Ate nunca mais!");
				break;
			default:
				puts("Opcao invalida!");
		}
	}while(n!=0);
	free(p);
	return 0;
}
