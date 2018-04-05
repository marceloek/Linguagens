#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>

typedef struct _nodo{
	int chave, alt, altdir, altesq;
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

void rotacao_simples_dir(TpArvore *arvore, TpNodo *new){
	printf("\nRota\x87\xC6o Simples \x85 Direita\n");
	TpNodo *aux1=new, *aux2=new->pai, *aux3=new->pai->pai, *aux4=new->pai->pai->pai;
	if(new->pai->pai == arvore->raiz){ //avó é raiz
		arvore->raiz = aux2;
		arvore->raiz->dir=aux1;
		arvore->raiz->esq=aux3;
		aux1->pai=arvore->raiz;
		aux3->pai=arvore->raiz;
	}
	
	else{ //avó não é raiz
		aux4->dir=aux2;
		aux2->dir=aux1;
		aux2->esq=aux3;
		aux1->pai=aux2;
		aux3->pai=aux2;
	}
}

void rotacao_simples_esq(TpArvore *arvore, TpNodo *new){
	printf("\nRota\x87\xC6o Simples \x85 Esquerda\n");
	TpNodo *aux1=new, *aux2=new->pai, *aux3=new->pai->pai, *aux4=new->pai->pai->pai;
	if(new->pai->pai == arvore->raiz){ //avó é raiz
		arvore->raiz = aux2;
		arvore->raiz->dir=aux3;
		arvore->raiz->esq=aux1;
		aux1->pai=arvore->raiz;
		aux3->pai=arvore->raiz;
	}
	
	else{ //avó não é raiz
		aux4->esq=aux2;
		aux2->dir=aux3;
		aux2->esq=aux1;
		aux1->pai=aux2;
		aux3->pai=aux2;
	}
}

void rotacao_dir_esq(TpArvore *arvore, TpNodo *new){
	printf("\nRota\x87\xC6o Dupla \x85 Direita\n");
	TpNodo *aux1=new, *aux2=new->pai, *aux3=new->pai->pai;
	aux3->esq=aux1;
	aux1->pai=aux3;
	aux1->esq=aux2;
	aux2->pai=aux1;

	rotacao_simples_dir(arvore, new);
}

void rotacao_esq_dir(TpArvore *arvore, TpNodo *new){
	printf("\nRota\x87\xC6o Dupla \x85 Esquerda\n");
	TpNodo *aux1=new, *aux2=new->pai, *aux3=new->pai->pai;
	aux3->dir=aux1;
	aux1->pai=aux3;
	aux1->dir=aux2;
	aux2->pai=aux1;
	
	rotacao_simples_esq(arvore, new);
}

void balancear_arvore(){
	
}

void att_alt(TpNodo *nodo){
    TpNodo *aux = nodo->pai;
    while(aux != NULL){ //percore do no desejado atá a raiz
        if(nodo->chave < aux->chave){ //à esquerda
            if(aux->dir == NULL)
                aux->alt = nodo->alt + 1;
            else{
                if(nodo->alt > aux->dir->alt)
                    aux->alt = nodo->alt + 1;
                else
                    aux->alt = aux->dir->alt + 1;
            }
        }
        else{ //à direita
            if(aux->esq == NULL)
                aux->alt = nodo->alt + 1;
            else{
                if(nodo->alt > aux->esq->alt)
                    aux->alt = nodo->alt + 1;
                else
                    aux->alt = aux->esq->alt + 1;
            }
        }
        nodo = aux;
        aux = aux->pai;
    }
}

void inserir(TpArvore *arvore, int key){
	TpNodo *aux = arvore->raiz, *pai, *new = (TpNodo*)malloc(sizeof(TpNodo));
	while(aux != NULL){
		pai = aux;
		if(key == aux->chave){
			printf("Esse valor ja esta inserido! Caso queira, tente novamente.\n(Tecle para sair)\n");
			system("pause >nul");
			system("cls");
			return;
		}
		else if(key < aux->chave){
			aux = aux->esq;
		}else if(key > aux->chave){
			aux = aux->dir;
		}
	}
	new->chave = key;
	new->esq=NULL;
	new->dir=NULL;
	new->alt=0;

	if(arvore->raiz == NULL){
		new->pai = NULL;
		arvore->raiz = new;
	}
	else if(key < pai->chave){
		new->pai = pai;
		pai->esq = new;
		att_alt(new);
	}
	else if(key > pai->chave){
		new->pai = pai;
		pai->dir = new;	
		att_alt(new);
	}
	balancear_arvore();
	printf("O valor foi inserido com sucesso!\n(Tecle para sair)\n");
	system("pause >nul");
	system("cls");
}

void exibirNivel(TpNodo *nodo, int i, int nivel){
    if(nodo != NULL){
        i++;
        exibirNivel(nodo->esq, i, nivel);
        exibirNivel(nodo->dir, i, nivel);
    }
    if(nivel == i && nodo != NULL){ //caso o i seja igual ao nivel, ele imprime nodo
        printf(" %d ", nodo->chave);

        if(nodo->pai == NULL)  //imprime raiz
            printf("(NIL)");
        else
            printf("(%d), ", nodo->pai->chave);
    }
    else if(i > nivel)
        return;
}

void exibir(TpArvore *arvore){
    system("cls");
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
    system("pause >nul");
    system("cls");
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
			system("cls");
			printf("Digite o valor do no da arvore: ");
			scanf("%d", &key);
			puts("");
			inserir(arvore, key);
			break;
			case 2:
			exibir(arvore);
			break;
			case 0:
			system("cls");
			puts("Voce escolheu por sair! Ate nunca mais!");
			break;
			default:
			system("cls");
			puts("Opcao invalida!");
		}
	}while(n!=0);
	free(arvore);
	return 0;
}
