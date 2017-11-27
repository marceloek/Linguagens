#include <stdio.h>
#include <stdio_ext.h>
#include <string.h>
#include <stdlib.h>

typedef struct produto{
	int codigo;
	char nome[20];
	float preco;
}produto;

typedef struct nodo{
	produto info;
	struct nodo *next;
	struct nodo *prev;
}nodo;

typedef struct lista{
	int nItens;
	nodo *first;
	nodo *last;
}lista;

void push(lista *cabeca){
	nodo *new = (nodo*)malloc(sizeof(nodo));
	if(cabeca->nItens==0)
		cabeca->last=new;
	else{
		new->prev=cabeca->last;
		cabeca->last->next=new;
	}system("clear");
	getchar();
	printf("Codigo do produto: ");
	scanf("%d", &new->info.codigo);
	getchar();
	printf("Nome do produto: ");
	scanf("%[^\n]s", new->info.nome);
	getchar();
	printf("Preco do produto: R$ ");
	scanf("%f", &new->info.preco);
	if(cabeca->nItens==0){
		cabeca->first=new;
		cabeca->last=new;
		cabeca->first->prev= NULL;
		cabeca->first->next= NULL;
		cabeca->last->prev= NULL;
		cabeca->last->next= NULL;
	}else{
		cabeca->last=new;
		cabeca->last->next= NULL;
	}cabeca->nItens++;
	system("clear");
	return;
}

void pop(lista *cabeca){
	system("clear");
	if(cabeca->last==NULL){
		printf("A lista esta vazia!\n");
		return;
	}int n;
	printf("Digite o codigo do produto que deseja remover: ");
	scanf("%d", &n);
	nodo *ant;
	if(cabeca->last->info.codigo==n&&cabeca->last->next==NULL && cabeca->last->prev==NULL){
		cabeca->last=NULL;
		cabeca->nItens = 0;
		printf("Produto com codigo [%d] foi removido com sucesso!\n", n);
		return;
	}else{
		lista aux=*cabeca;
		for(;cabeca->last!=NULL;cabeca->last=cabeca->last->prev){
			if(cabeca->last->info.codigo==n){
				if(cabeca->last->prev==NULL){
					cabeca->last=cabeca->last->next;
					cabeca->first=cabeca->last;
					cabeca->last->prev = NULL;
					cabeca->nItens--;
					printf("Produto com codigo [%d] foi removido com sucesso!\n", n);
					return;
				}else if(cabeca->last->next==NULL){
					cabeca->last=cabeca->last->prev;
					cabeca->last->next=NULL;
					cabeca->nItens--;
					printf("Produto com codigo [%d] foi removido com sucesso!\n", n);
					return;
				}else{
					ant=cabeca->last;
					cabeca->last=cabeca->last->prev;
					cabeca->last->next=ant->next;
					cabeca->last=cabeca->last->next;
					cabeca->last->prev=ant->prev;
					cabeca->nItens--;
					printf("Produto com codigo [%d] foi removido com sucesso!\n", n);
					return;
				}
			}
		}*cabeca=aux;
	}puts("Codigo nao encontrado!");
}

void display(lista *cabeca){
	system("clear");
	if(cabeca->last==NULL){
		printf("A lista esta vazia!\n");
		return;
	}else{
		lista aux = *cabeca;
		int a=1;
		for(;cabeca->first!=NULL;cabeca->first=cabeca->first->next){
			puts("----------------------------------------------------------");
			printf("Informacoes do Produto [%d]:\nCodigo: %d\n", a, (cabeca->first->info.codigo));
			printf("Nome: %s\nPreco: R$ %.2f\n", (cabeca->first->info.nome), (cabeca->first->info.preco));
			a++;
		}puts("----------------------------------------------------------");
		printf("Numero de itens: %d\n", cabeca->nItens);
		puts("");
		*cabeca=aux;
	}
}

int main(){
	lista *cabeca = (lista*)malloc(sizeof(lista));
	cabeca->last = NULL;
	cabeca->first = NULL;
	cabeca->nItens = 0;
	int n;
	do{
		puts("\t\tMENU\n");
		puts("(1) Para inserir um produto na lista;");
		puts("(2) Para extrair um elemento da lista;");
		puts("(3) Para listar todos os campos dos elementos da lista;");
		puts("(0) Sair.\n");
		printf("Digite o numero correspondente a opcao: ");
		scanf("%d", &n);
		switch(n){
			case 1:
				push(cabeca);
				break;
			case 2:
				pop(cabeca);
				break;
			case 3:
				display(cabeca);
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
	free(cabeca);
	return 0;
}
