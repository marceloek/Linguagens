#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>

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
	if(cabeca->last->info.codigo==n&&cabeca->last->next==NULL && cabeca->last->prev==NULL){ //unico
		cabeca->last=NULL;
		cabeca->nItens = 0;
		printf("Produto com codigo [%d] foi removido com sucesso!\n", n);
		return;
	}else{
		lista aux=*cabeca;
		for(;cabeca->last!=NULL;cabeca->last=cabeca->last->prev){
			if(cabeca->last->info.codigo==n){
				if(cabeca->last->prev==NULL){ //primeiro
					cabeca->last=cabeca->last->next;
					cabeca->first=cabeca->last;
					cabeca->last->prev = NULL;
					cabeca->nItens--;
					printf("Produto com codigo [%d] foi removido com sucesso!\n", n);
					return;
				}else if(cabeca->last->next==NULL){ //ultimo
					cabeca->last=cabeca->last->prev;
					cabeca->last->next=NULL;
					cabeca->nItens--;
					printf("Produto com codigo [%d] foi removido com sucesso!\n", n);
					return;
				}else{ //meio
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

void insertionSort(lista *cabeca){
	system("clear");
	if(cabeca->nItens<=1){
		puts("A lista esta vazia ou ha somente um unico elemento!");
		return;
	}nodo *nx, *pv;
	for(nx=cabeca->first->next;nx!=NULL;nx=nx->next){
		for(pv=nx->prev;pv!=NULL;pv=pv->prev){
			if(pv->info.codigo > nx->info.codigo){
				if(cabeca->nItens==2){ //primeiro e ultimo
					pv->next=NULL;
					pv->prev=nx;
					nx->next=pv;
					nx->prev=NULL;
					cabeca->first=nx;
					cabeca->last=pv;
				}else if(pv->prev==NULL && nx->next!=NULL){ //primeiro e meio
					nx->next->prev=pv;
					pv->next=nx->next;
					pv->prev=nx;
					nx->next=pv;
					nx->prev=NULL;
					cabeca->first=nx;
				}else if(pv->prev!=NULL && nx->next==NULL){ //meio e ultimo
					pv->prev->next=nx;
					nx->prev=pv->prev;
					pv->next=NULL;
					pv->prev=nx;
					nx->next=pv;
					cabeca->last=pv;
				}else if(pv->prev!=NULL && nx->next!=NULL){ //meio e meio
					nx->next->prev=pv;
					pv->prev->next=nx;
					nx->prev=pv->prev;
					pv->next=nx->next;
					pv->prev=nx;
					nx->next=pv;
				}
			}
		}
	}puts("Voce ordenou por InsertionSort!");
}

void selectionSort(lista *cabeca){
	system("clear");
	if(cabeca->nItens<=1){
		puts("A lista esta vazia ou ha somente um unico elemento!");
		return;
	}nodo *nx, *px, *menor, *menorn, *menorp, *nextn, *nextp;
	for(nx=cabeca->first;nx!=NULL;nx=nx->next){
		menor = NULL;
		for(px=nx->next;px!=NULL;px=px->next){
			if(px->info.codigo < nx->info.codigo){
				menor = px;
				menorn = menor->next;
				menorp = menor->prev;
				nextn = nx->next;
				nextp = nx->prev;
			}
		}if(menor!=NULL){
			if(nx->prev==NULL && nx->next==menor && menor->next==NULL){ //primeiro e ultimo (juntos)
				nx->next=NULL;
				nx->prev=menor;
				menor->next=nx;
				menor->prev=NULL;
				cabeca->first=menor;
				cabeca->last=nx;
			}else if(nx->prev==NULL && nx->next==menor && menor->next!=NULL){ //primeiro e meio (juntos)
				menor->next->prev=nx;
				nx->next=menorn;
				nx->prev=menor;
				menor->next=nx;
				menor->prev=NULL;
				cabeca->first=menor;
			}else if(nx->prev!=NULL && nx->next==menor && menor->next==NULL){ //meio e ultimo (juntos)
				nx->prev->next=menor;
				menor->prev=nextp;
				nx->next=NULL;
				nx->prev=menor;
				menor->next=nx;
				cabeca->last=nx;
			}else if(nx->prev!=NULL && nx->next==menor && menor->next!=NULL){ //meio e meio (juntos)
				menorn->prev=nx;
				nextp->next=menor;
				menor->prev=nextp;
				nx->next=menorn;
				nx->prev=menor;
				menor->next=nx;
			}else if(nx->prev==NULL && nx->next!=menor && menor->next==NULL){ //primeiro e ultimo (separados)
				menor->prev=NULL;
				menor->next=nextn;
				nextn->prev=menor;
				nx->next=NULL;
				nx->prev=menorp;
				menorp->next=nx;
				cabeca->first=menor;
				cabeca->last=nx;	
			}else if(nx->prev==NULL && nx->next!=menor && menor->next!=NULL){ //primeiro e meio (separados)
				menorn->prev=nx;
				menorp->next=nx;
				nx->next=menorn;
				nx->prev=menorp;
				nextn->prev=menor;
				menor->next=nextn;
				menor->prev=NULL;
				cabeca->first=menor;
			}else if(nx->prev!=NULL && nx->next!=menor && menor->next==NULL){ //meio e ultimo (separados)
				nextp->next=menor;
				nextn->prev=menor;
				nx->next=NULL;
				nx->prev=menorp;
				menor->prev=nextp;
				menor->next=nextn;
				menorp->next=nx;
				cabeca->last=nx;
			}else if(nx->prev!=NULL && nx->next!=menor && menor->next!=NULL){ //meio e meio (separados) 
				menor->prev=nextp;
				menor->next=nextn;
				nx->next=menorn;
				nx->prev=menorp;
				menorn->prev=nx;
				menorp->next=nx;
				nextp->next=menor;
				nextn->prev=menor;
			}
		}px=NULL;
	}puts("Voce ordenou por SelectionSort!");
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
		puts("(4) Para ordenar a lista por InsertionSort;");
		puts("(5) Para ordenar a lista por SelectionSort;");
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
			case 4:
				insertionSort(cabeca);
				break;
			case 5:
				selectionSort(cabeca);
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
