#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdio_ext.h>
#define TAM 100

typedef struct produto{
	int codigo;
	char nome[TAM];
	float preco;
}tp_produto;

typedef struct nodo{
	tp_produto produto;
	struct nodo *prox;
}tp_nodo;

tp_nodo *push(tp_nodo *u){
	tp_nodo *v = (tp_nodo*)malloc(sizeof(tp_nodo));
	v->prox=u;
	system("clear");
	getchar();
	printf("Codigo do produto: ");
	scanf("%d", &v->produto.codigo);
	getchar();
	printf("Nome do produto: ");
	scanf("%[^\n]s", v->produto.nome);
	getchar();
	printf("Preco do produto: R$ ");
	scanf("%f", &v->produto.preco);
	system("clear");
	return v;
}

tp_nodo *pop(){
	
	return ;
}

void display(tp_nodo *u){
	system("clear");
	for(u=u;u!=NULL;u=u->prox){
		printf("Informacoes do produto:\nCodigo: %d\n", (u->produto.codigo));
		printf("Nome: %s\nPreco: R$ %.2f\n", (u->produto.nome), (u->produto.preco));
	}
}

int main(){
	int n;
	tp_nodo *u = NULL;
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
				u=push(u);
				break;
				system("clear");
			case 2:
				system("clear");
				u=pop(u);
				break;
			case 3:
				display(u);
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
	free(u);
	return 0;
}
