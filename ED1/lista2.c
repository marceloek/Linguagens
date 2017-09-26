#include <stdio.h>
#include <stdio_ext.h>
#include <string.h>
#include <stdlib.h>

typedef struct produto{
	int codigo;
	char nome[20];
	float preco;
}tpProduto;

typedef struct nodo{
	tpProduto info;
	struct nodo *next;
	struct nodo *prev;
}nodo;

typedef struct lista{
	int nItens;
	nodo *first;
	nodo *last;
}lista;

nodo *push(nodo *atual, lista cabeca){
	nodo *new = (nodo*)malloc(sizeof(nodo));
	new->next=cabeca.last;
	cabeca.nItens++;
	system("clear");
	getchar();
	printf("Codigo do produto: ");
	scanf("%d", &new->info.codigo);
	getchar();
	printf("Nome do produto: ");
	scanf("%[^\n]s", new->info.nome);
	getchar();
	printf("Preco do produto: R$ ");
	scanf("%f", &new->info.preco);
	system("clear");
	return new;
}

nodo *pop(nodo *atual, lista cabeca){
	cabeca.nItens--;
	system("clear");
	if(atual==NULL){
		printf("A lista esta vazia!\n");
		return NULL;
	}
	else{
	int n;
	printf("Digite o codigo do produto que deseja remover: ");
	scanf("%d", &n);
	nodo *ant, *qlq;
	for(qlq=atual;qlq!=NULL;qlq=qlq->next){
		if(qlq->info.codigo==n)
			break;
		ant=qlq;
	}
	if(qlq==NULL){
		printf("Codigo do produto não encontrado!\n");
	}
	else if(qlq==atual){
		atual=atual->next;
		printf("Produto com codigo [%d] foi removido com sucesso!\n", n);
	}
	else{
		ant->next = qlq->next;
		printf("Produto com codigo [%d] foi removido com sucesso!\n", n);
	}
	puts("");
	free(qlq);
	return atual;
	}
}

void display(nodo *atual){
	system("clear");
	if(atual==NULL){
		printf("A lista esta vazia!\n");
	}
	else{
		for(atual=atual;atual!=NULL;atual=atual->next){
			puts("----------------------------------------------------------");
			printf("Informacoes do Produto:\nCodigo: %d\n", (atual->info.codigo));
			printf("Nome: %s\nPreco: R$ %.2f\n", (atual->info.nome), (atual->info.preco));
			puts("----------------------------------------------------------");
		}
	}
}

int main(){
	lista cabeca;
	int n;
	nodo *atual = NULL;
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
				atual=push(atual,cabeca);
				break;
				system("clear");
			case 2:
				atual=pop(atual,cabeca);
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
