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

tp_nodo *push(tp_nodo *atual){
	tp_nodo *new = (tp_nodo*)malloc(sizeof(tp_nodo));
	new->prox=atual;
	system("clear");
	getchar();
	printf("Codigo do produto: ");
	scanf("%d", &new->produto.codigo);
	getchar();
	printf("Nome do produto: ");
	scanf("%[^\n]s", new->produto.nome);
	getchar();
	printf("Preco do produto: R$ ");
	scanf("%f", &new->produto.preco);
	system("clear");
	return new;
}

tp_nodo *pop(tp_nodo *atual){
	system("clear");
	if(atual==NULL){
		printf("A lista esta vazia!\n");
		return NULL;
	}
	else{
	int n;
	printf("Digite o codigo do produto que deseja remover: ");
	scanf("%d", &n);
	tp_nodo *ant, *qlq;
	for(qlq=atual;qlq!=NULL;qlq=qlq->prox){
		if(qlq->produto.codigo==n)
			break;
		ant=qlq;
	}
	if(qlq==NULL){
		printf("Codigo do produto não encontrado!\n");
	}
	else if(qlq==atual){
		atual=atual->prox;
		printf("Produto com codigo [%d] foi removido com sucesso!\n", n);
	}
	else{
		ant->prox = qlq->prox;
		printf("Produto com codigo [%d] foi removido com sucesso!\n", n);
	}
	puts("");
	free(qlq);
	return atual;
	}
}

void display(tp_nodo *atual){
	system("clear");
	if(atual==NULL){
		printf("A lista esta vazia!\n");
	}
	else{
		for(atual=atual;atual!=NULL;atual=atual->prox){
			puts("----------------------------------------------------------");
			printf("Informacoes do Produto:\nCodigo: %d\n", (atual->produto.codigo));
			printf("Nome: %s\nPreco: R$ %.2f\n", (atual->produto.nome), (atual->produto.preco));
			puts("----------------------------------------------------------");
		}
	}
}

int main(){
	int n;
	tp_nodo *atual = NULL;
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
				atual=push(atual);
				break;
				system("clear");
			case 2:
				atual=pop(atual);
				break;
			case 3:
				display(atual);
				puts("");
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
	free(atual);
	return 0;
}
