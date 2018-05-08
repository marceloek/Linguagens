#include <stdio.h>
#include <stdlib.h>

typedef struct _nodo{
	int chave, alt, cor;
	struct _nodo *esq;
	struct _nodo *dir;
	struct _nodo *pai;
}TpNodo;

typedef struct _arvore{
	TpNodo *raiz;
}TpArvore;

TpArvore *inicializa(){
	TpArvore *arvore = (TpArvore*)malloc(sizeof(TpArvore));
	arvore->raiz=NULL;
	return arvore;
}

void att_alt(TpNodo *nodo){
	TpNodo *aux = nodo->pai;
    while(aux != NULL){ //percore do no desejado até a raiz
        if(nodo->chave < aux->chave){ //à esquerda
            if(aux->dir == NULL){ //direita nulo
            	aux->alt = nodo->alt + 1;
			}else{ //direita nao nulo
                if(nodo->alt > aux->dir->alt) //maior
                	aux->alt = nodo->alt + 1;
                else //menor
                	aux->alt = aux->dir->alt + 1;
            }
        }
        else{ //à direita
            if(aux->esq == NULL){ //esquerda nulo
            	aux->alt = nodo->alt + 1;
            }else{ //esquerda nao nulo
                if(nodo->alt > aux->esq->alt) //maior
                	aux->alt = nodo->alt + 1;
                else //menor
                	aux->alt = aux->esq->alt + 1;
            }
        }
        nodo = aux;
        aux = aux->pai;
    }
}

void case1(TpNodo *nodo, int p){
	printf("<< CASE 1 >>\n");
	nodo->pai->pai->dir->cor = 1;
	nodo->pai->pai->esq->cor = 1;
	nodo->pai->pai->cor = 0;
	TpNodo *avo = nodo->pai->pai;
	if(avo->pai == NULL) 
		avo->cor = 1;
	else
		balancear(avo, p);
}

void case3(TpNodo *nodo, int p){
	printf("<< CASE 3 >>\n");
	TpNodo *pai = nodo->pai;
	if(p==1){ //tio esq
		nodo->pai->cor = 1;
		if(nodo->pai->pai->cor == 0)
			nodo->pai->pai->cor = 1;
		else
			nodo->pai->pai->cor = 0;
		nodo->pai = NULL;
		pai->dir = nodo->esq;
		nodo->esq = pai;
	}
	else if(p==0){ //tio dir
		nodo->pai->cor = 1;
		if(nodo->pai->pai->cor == 0)
			nodo->pai->pai->cor = 1;
		else
			nodo->pai->pai->cor = 0;
		nodo->pai = NULL;
		pai->esq = nodo->dir;
		nodo->dir = pai;
		
	}
}

void case2(TpNodo *nodo, int p){
	printf("<< CASE 2 >>\n");
	TpNodo *pai = nodo->pai, *avo = nodo->pai->pai;
	printf("p = %d", p);
	if(p==1){ //tio esq
		nodo->pai = avo;
		nodo->esq = nodo->esq;
		pai->esq = nodo->dir;
		nodo->dir = pai;
		pai->pai = nodo;
		pai->dir = pai->dir;
		case3(nodo, p);
	}
	else if(p==0){ //tio dir
		nodo->pai = avo;
		nodo->dir = nodo->dir;
		pai->dir = nodo->esq;
		nodo->esq = pai;
		pai->pai = nodo;
		pai->esq = pai->esq;
		case3(nodo, p);
	}
}

void balancear(TpNodo *nodo, int p){
	printf("TD OK\n");
	if(nodo->pai->cor == 0){ //pai red
		if(nodo->pai->pai->esq->cor == 0 && nodo->pai->pai->dir->cor == 0){ //tio red e pai red
			case1(nodo,p);
			printf("TD OK1\n");
		}

		else if(nodo->pai->dir == nodo){ //caso 2 ->> x a direita
			if(nodo->pai->pai->dir == nodo->pai){
				if(nodo->pai->pai->esq->cor == 1 || nodo->pai->pai->esq == NULL){ //tio esq
					p=1;
					printf("TD OK2\n");
					case2(nodo, p);
				}
			}
			else if(nodo->pai->pai->esq == nodo->pai){ 
				if(nodo->pai->pai->dir->cor == 1 || nodo->pai->pai->dir == NULL){ //tio dir
					p=0;
					printf("TD OK2\n");
					case2(nodo, p);
				}
			}
		}
		else if(nodo->pai->esq == nodo){ //caso 3 ->> x a esquerda
			if(nodo->pai->pai->dir == nodo->pai){
				if(nodo->pai->pai->esq->cor == 1 || nodo->pai->pai->esq == NULL){ //tio esq
					p=1;
					printf("TD OK3\n");
					case3(nodo, p);
				}
			}
			else if(nodo->pai->pai->esq == nodo->pai){
				if(nodo->pai->pai->dir->cor == 1 || nodo->pai->pai->dir == NULL){ //tio dir
					p=0;
					printf("TD OK3\n");
					case3(nodo, p);
				}
			}
		}
	}
}

void inserir(TpArvore *arvore, int key){
	TpNodo *aux = arvore->raiz, *pai, *new = (TpNodo*)malloc(sizeof(TpNodo));
	while(aux != NULL){ //percorre aonde inserir
		pai = aux;
		if(key == aux->chave){
			printf("Esse valor ja esta inserido! Caso queira, tente novamente.\n");
			return;
		}else if(key < aux->chave){
			aux = aux->esq;
		}else
		aux = aux->dir;
	}
	new->chave = key;
	new->dir=NULL;
	new->esq=NULL;
	new->alt=0;
	new->cor=0;

	if(arvore->raiz == NULL){ //raiz nula
		new->cor=1;
		new->pai = NULL;
		arvore->raiz = new;
	}
	else if(key < pai->chave){ //insere a esquerda
		new->pai = pai;
		pai->esq = new;
		att_alt(new);
	}
	else{ //insere a direita
		new->pai = pai;
		pai->dir = new;
		att_alt(new);
	}
	if(new->pai != NULL && new->pai->pai != NULL){
		int p=9;
		balancear(new, p);
	}
	printf("a\n");
	
	printf("O valor foi inserido com sucesso!\n\n");
}

void exibirNivel(TpNodo *nodo, int i, int nivel){
	if(nodo != NULL){
		i++;
		exibirNivel(nodo->esq, i, nivel);
		exibirNivel(nodo->dir, i, nivel);
	}
    if(nivel == i && nodo != NULL){ //caso o i seja igual ao nivel, ele printa nodo
    	printf(" %d ", nodo->chave);
        if(nodo->pai == NULL)  //printa raiz
        	printf("(NIL)");
        else
        	printf("(%d), ", nodo->pai->chave);
        if(nodo->cor == 1)
        	printf(" BLACK ");
        else
        	printf(" RED ");
    }
    else if(i > nivel)
    	return;
}

void exibir(TpArvore *arvore){
	system("clear");
	TpNodo *aux = arvore->raiz;
	if(aux == NULL)
		printf("A arvore esta vazia!");
	else{
		int x;
		for(x = 0; x <= aux->alt; x++){
			printf("\nNivel %d:", x);
			exibirNivel(aux, -1, x);
		}
	}
	printf("\n");
}

int main(){
	TpArvore *arvore = (TpArvore*)malloc(sizeof(TpArvore));
	arvore = inicializa();
	int n, key;
	do{
		puts("\t\tMENU\n");
		puts("(1) Para inserir um valor na arvore;");
		puts("(2) Para exibir os valores na arvore;");
		puts("(0) Para sair.\n");
		printf("Digite o numero correspondente a opcao: ");
		scanf("%d", &n);
		switch(n){
			case 1:
			system("clear");
			printf("Digite o valor do no da arvore: ");
			scanf("%d", &key);
			if(key <= 0){
				printf("\nSomente valores positivos sao permitidos!\n");
				break;
			}else{
				puts("");
				inserir(arvore, key);
				break;
			}
			case 2:
			exibir(arvore);
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
	free(arvore);
	return 0;
}
