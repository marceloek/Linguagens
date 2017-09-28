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

lista *push(lista *cabeca){
	nodo *new = (nodo*)malloc(sizeof(nodo));
	new->prev=cabeca->last;
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
	if(cabeca->nItens==0){
		cabeca->first=new;
		cabeca->last=new;
	}
	else
		cabeca->last=new;
	cabeca->nItens++;
	system("clear");
	return cabeca;
}

lista *pop(lista *cabeca){
	system("clear");
	if(cabeca->nItens==0){
		printf("A lista esta vazia!\n");
		return NULL;
	}
	int n;
	printf("Digite o codigo do produto que deseja remover: ");
	scanf("%d", &n);
	lista *ant, *aux;
	for(aux=cabeca;aux->last!=NULL;aux->last=aux->last->next){
		if(aux->last->info.codigo==n)
			break;
		ant=aux;
	}
	if(aux->last==NULL){
		puts("Codigo do produto não encontrado!");
	}
	else if(aux->last==cabeca->last){
		cabeca->last=cabeca->last->next;
		printf("Produto com codigo [%d] foi removido com sucesso!\n", n);
	}else{
		ant->last->next = aux->last->next;
		aux->last->prev = ant->last;
		printf("Produto com codigo [%d] foi removido com sucesso!\n", n);
	}
	puts("");
	cabeca->nItens--;
	free(aux);
	return cabeca;
}

void display(lista *cabeca){
	system("clear");
	if(cabeca->nItens==0){
		printf("A lista esta vazia!\n");
	}
	else{
		int a=cabeca->nItens;
		lista *aux = (lista*)malloc(sizeof(lista));
		for(aux=cabeca;aux->last!=NULL;aux->last=aux->last->prev){
			puts("----------------------------------------------------------");
			printf("Informacoes do Produto [%d]:\nCodigo: %d\n", a, (aux->last->info.codigo));
			printf("Nome: %s\nPreco: R$ %.2f\n", (aux->last->info.nome), (aux->last->info.preco));
			a--;
		}
		puts("----------------------------------------------------------");
		printf("%d", cabeca->nItens);
	}
	puts("");
}

int main(){
	lista *cabeca = (lista*)malloc(sizeof(lista));
	cabeca->last = NULL;
	cabeca->first = NULL;
	cabeca->nItens = 0;
	int n;
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
				cabeca=push(cabeca);
				break;
				system("clear");
			case 2:
				cabeca=pop(cabeca);
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
