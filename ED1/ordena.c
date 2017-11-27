#include <stdio.h>
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
	system("cls");
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
	system("cls");
	return cabeca;
}

void pop(lista *cabeca){
	system("cls");
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
					while(cabeca->last->next!=NULL)
						cabeca->last=cabeca->last->next;
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
					while(cabeca->last->next!=NULL)
						cabeca->last=cabeca->last->next;
					cabeca->nItens--;
					printf("Produto com codigo [%d] foi removido com sucesso!\n", n);
					free(ant);
					return;
				}
			}
		}*cabeca=aux;
	}puts("Codigo nao encontrado!");
}

void display(lista *cabeca){
	system("cls");
	if(cabeca->last==NULL){
		printf("A lista esta vazia!\n");
		return;
	}
	else{
		lista aux = *cabeca;
		int a=1;
		for(;cabeca->first!=NULL;cabeca->first=cabeca->first->next){
			puts("----------------------------------------------------------");
			printf("Informacoes do Produto [%d]:\nCodigo: %d\n", a, (cabeca->first->info.codigo));
			printf("Nome: %s\nPreco: R$ %.2f\n", (cabeca->first->info.nome), (cabeca->first->info.preco));
			a++;
		}
		puts("----------------------------------------------------------");
		printf("Numero de itens: %d\n", cabeca->nItens);
		puts("");
		*cabeca=aux;
	}
}

void insertionSort(lista *cabeca){
	system("cls");
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

/*void selectionSort(lista *cabeca){
	system("cls");
	if(cabeca->nItens<=1){
		puts("A lista esta vazia ou ha somente um unico elemento!");
		return;
	}else{
		int t2, cont1=0, p, k=1;
		nodo in11, in21, in31, in41;
		for(;cabeca->first->next!=NULL;cabeca->first=cabeca->first->next){
			cont1++;
			in11.prev=cabeca->first;
			in11.next=cabeca->first->next;
			in21.prev=cabeca->first;
			in11.next=cabeca->first->next;
			in31.prev=cabeca->first->prev;
			in41.prev=cabeca->first->prev;
			t2=cabeca->nItens+1;
			for(;cabeca->first!=NULL;cabeca->first=cabeca->first->next){
				if(k==1){
					p=cont1;
					k++;
				}else
					p++;
				if(cabeca->first->info.codigo < in11.prev->info.codigo){
					in11.prev=cabeca->first;
					t2=p;
				}
			}
			k=1;
			for(;cabeca->first!=NULL;cabeca->first=cabeca->first->prev){
				if(cabeca->first->info.codigo==in21.prev->info.codigo)
					break;
			}
			if(t2<=cabeca->nItens){
				for(;cabeca->first!=NULL;cabeca->first=cabeca->first->next){
					if(cabeca->first->info.codigo==in11.prev->info.codigo)
						break;
				}
				if(cabeca->first->next==NULL){
					cabeca->first=in21.prev;
					cabeca->first->prev->next=in21.prev;
					cabeca->first->next->prev=in21.prev;
					cabeca->last=in21.prev;
					cabeca->last->prev->next=in21.prev;
					cabeca->last->next->prev=in21.prev;
				}else{
					cabeca->first=in21.prev;
					cabeca->first->prev->next=in21.prev;
					cabeca->first->next->prev=in21.prev;
				}
				printf("Cont1 = %d \n", cont1);
				for(;cabeca->first!=NULL;cabeca->first=cabeca->first->prev){
					if(cabeca->first->info.codigo==in21.prev->info.codigo)
						break;
				}
				cabeca->first=in11.prev;
				cabeca->first->prev=in41.prev;
				cabeca->first->next=in21.next;
				printf("Cont1 = %d \n", cont1);
			}
		}
		puts("Voce ordenou por SelectionSort!");
	}
}*/

/*void mergeSort(lista *cabeca){


}*/

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
		//puts("(5) Para ordenar a lista por SelectionSort;");
		//puts("(6) Para ordenar a lista por MergeSort;");
		puts("(0) Sair.\n");
		printf("Digite o numero correspondente a opcao: ");
		scanf("%d", &n);
		switch(n){
			case 1:
				cabeca=push(cabeca);
				break;
				system("cls");
			case 2:
				pop(cabeca);
				break;
			case 3:
				display(cabeca);
				break;
			case 4:
				system("cls");
				insertionSort(cabeca);
				break;
			/*case 5:
				system("cls");
				selectionSort(cabeca);
				break;
			case 6:
				system("cls");
				mergeSort(cabeca);
				puts("Voce ordenou por MergeSort!");
				break;*/
			case 0:
				system("cls");
				puts("Voce escolheu por sair! Ate nunca mais!");
				break;
			default:
				system("cls");
				puts("Opcao invalida!");
		}
	}while(n!=0);
	free(cabeca);
	return 0;
}
