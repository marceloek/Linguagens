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

void case1(TpArvore *arvore, TpNodo *nodo){
	printf("case1");
	TpNodo *avo = nodo->pai->pai;
	avo->dir->cor = 1;
	avo->esq->cor = 1;
	avo->cor = 0;
	if(avo->pai == NULL) 
		avo->cor = 1;
}

void case3(TpArvore *arvore, TpNodo *nodo, int p){
	printf("case3");
	TpNodo *pai = nodo->pai;
	if(p==1){ //tio esq
		if(pai->cor == 0)
			pai->cor = 1;
		else
			pai->cor = 0;
		nodo->cor = 1;
		//nodo->alt++;
		if(pai->pai == NULL){
			nodo->pai = NULL;
			arvore->raiz = nodo;
		}else
			nodo->pai=pai->pai;
		pai->dir = nodo->esq;
		nodo->esq = pai;
		pai->pai = nodo;
		if(pai->esq != NULL)  //pega a folha a esquerda e atualiza o fb e a altura
			att_alt(pai->esq);
		else if(pai->dir != NULL)  //pega a folha a direita e atualiza o fb e a altura
			att_alt(pai->dir);
		else{  //nodo fica folha
			pai->alt = 0;
			att_alt(pai);
		}
		//pai->alt=pai->alt - 1;
	}
	else if(p==0){ //tio dir
		if(pai->cor == 0)
			pai->cor = 1;
		else
			pai->cor = 0;
		nodo->cor = 1;
		//nodo->alt++;
		if(pai->pai == NULL){
			nodo->pai = NULL;
			arvore->raiz = nodo;
		}else
			nodo->pai=pai->pai;
		pai->esq = nodo->dir;
		nodo->dir = pai;
		pai->pai = nodo;
		if(pai->dir != NULL) //pega a folha a direita e atualiza o Fb e a altura
			att_alt(pai->dir);
		else if(pai->esq != NULL)  //pega a folha a esquerda e atualiza o Fb e a altura
			att_alt(pai->esq);
		else{  //nodo fica folha
			pai->alt = 0;
			att_alt(pai);
		}
		//pai->alt=pai->alt - 1;
	}
}

void case2(TpArvore *arvore, TpNodo *nodo, int p){
	printf("case2");
	TpNodo *pai = nodo->pai, *avo = nodo->pai->pai;
	if(p==1){ //tio esq
		nodo->pai = avo;
		avo->dir = nodo;
		if(nodo->esq != NULL){
			pai->esq = nodo->dir;
			nodo->dir->pai = pai;
		}else
			pai->esq = NULL;
		nodo->dir = pai;
		pai->pai = nodo;
		case3(arvore,nodo, 1);
	}
	else if(p==0){ //tio dir
		nodo->pai = avo;
		avo->esq = nodo;
		if(nodo->esq != NULL){
			pai->dir = nodo->esq;
			nodo->esq->pai = pai;
		}else
			pai->dir = NULL;
		nodo->esq = pai;
		pai->pai = nodo;
		case3(arvore,nodo, 0);
	}
}

void balancear(TpArvore *arvore, TpNodo *nodo){
	if(nodo->pai->cor == 0){ //pai red
		if(nodo->pai->pai != NULL && nodo->pai->pai->esq != NULL && nodo->pai->pai->esq->cor == 0 && nodo->pai->pai->dir !=NULL && nodo->pai->pai->dir->cor == 0) //tio red e pai red
			case1(arvore,nodo);
		else if(nodo->pai->dir == nodo){ //x a direita
			if(nodo->pai->pai->esq == nodo->pai){
				if(nodo->pai->pai->dir == NULL || nodo->pai->pai->dir->cor == 1) //case 2 dir (tio dir)
					case2(arvore, nodo, 0);
			}
			else if(nodo->pai->pai->dir == nodo->pai){ 
				if(nodo->pai->pai->esq == NULL || nodo->pai->pai->esq->cor == 1){ //case 3 esq (tio esq)
					nodo = nodo->pai;
					case3(arvore, nodo, 1);
				}
			}
		}
		else if(nodo->pai->esq == nodo){ //x a esquerda
			if(nodo->pai->pai->dir == nodo->pai){
				if(nodo->pai->pai->esq == NULL || nodo->pai->pai->esq->cor == 1) //case 2 esq (tio esq)
					case2(arvore, nodo, 1);
			}
			else if(nodo->pai->pai->esq == nodo->pai){
				if(nodo->pai->pai->dir == NULL || nodo->pai->pai->dir->cor == 1){ //case 3 dir (tio dir)
					nodo = nodo->pai;
					case3(arvore, nodo, 0);
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
	if(new->pai != NULL && new->pai->pai != NULL)
		balancear(arvore, new);
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
        	printf("(%d) ", nodo->pai->chave);
        if(nodo->cor == 1)
        	printf(" BLACK, ");
        else
        	printf(" RED, ");
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
