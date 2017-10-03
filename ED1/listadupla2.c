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

lista *push(lista *cabeca){
	nodo *new = (nodo*)malloc(sizeof(nodo));
	if(cabeca->nItens==0)
		cabeca->last=new;
	else{
		new->prev=cabeca->last;
		cabeca->last->next=new;
	}
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
		cabeca->first->prev= NULL;
		cabeca->first->next= NULL;
		cabeca->last->prev= NULL;
		cabeca->last->next= NULL;
	}
	else{
		cabeca->last=new;
		cabeca->last->next= NULL;
	}
	cabeca->nItens++;
	system("clear");
	return cabeca;
}

lista *pop(lista *cabeca){
	system("clear");
	if(cabeca->nItens==0){
		printf("A lista esta vazia!\n");
		return cabeca;
	}else{
		int n;
		printf("Digite o codigo do produto que deseja remover: ");
		scanf("%d", &n);
		nodo *ant;
		lista aux;
		if(cabeca->last->info.codigo==n&&cabeca->last->next==NULL && cabeca->last->prev==NULL){
			cabeca->last=cabeca->last->prev;
			cabeca->nItens = 0;
			printf("Produto com codigo [%d] foi removido com sucesso!\n", n);
			return cabeca;
		}else{
			aux = *cabeca;
			for(;cabeca->last!=NULL;cabeca->last=cabeca->last->prev){
				if(cabeca->last->info.codigo==n){
					if(cabeca->last->prev==NULL){
						cabeca->last=cabeca->last->next;
						cabeca->first=cabeca->last;
						cabeca->last->prev = NULL;
						while(cabeca->last->next!=NULL)
							cabeca->last=cabeca->last->next;
						cabeca->nItens--;
						printf("Produto com codigo [%d] foi removido com sucesso!\n", n);
						return cabeca;
					}
					else if(cabeca->last->next==NULL){
						cabeca->last=cabeca->last->prev;
						cabeca->last->next=NULL;
						cabeca->nItens--;
						printf("Produto com codigo [%d] foi removido com sucesso!\n", n);
						return cabeca;
				
					}
				else{
					ant=cabeca->last->prev;
					cabeca->last=cabeca->last->next;
					cabeca->last->prev=ant;
					while(cabeca->last->next!=NULL)
						cabeca->last=cabeca->last->next;
					cabeca->nItens--;
					printf("Produto com codigo [%d] foi removido com sucesso!\n", n);
					return cabeca;
				}
				}
				
			}
			puts("Codigo nao encontrado!");
				*cabeca = aux;
		}
		return cabeca;
	}
}

lista *display(lista *cabeca){
	system("clear");
	if(cabeca->nItens==0){
		printf("A lista esta vazia!\n");
		return cabeca;
	}
	else{
		lista aux = *cabeca;
		int a=cabeca->nItens;
		for(;cabeca->last!=NULL;cabeca->last=cabeca->last->prev){
			puts("----------------------------------------------------------");
			printf("Informacoes do Produto [%d]:\nCodigo: %d\n", a, (cabeca->last->info.codigo));
			printf("Nome: %s\nPreco: R$ %.2f\n", (cabeca->last->info.nome), (cabeca->last->info.preco));
			a--;
		}
		puts("----------------------------------------------------------");
		printf("%d", cabeca->nItens);
		puts("");
		*cabeca=aux;
		return cabeca;
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
				cabeca=display(cabeca);
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
