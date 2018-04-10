#include <stdio.h>
#include <stdlib.h>

typedef struct _nodo{
	int chave, alt, fb;
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

void att_alt_fb(TpNodo *nodo){
	TpNodo *aux = nodo->pai;
    while(aux != NULL){ //percore do no desejado até a raiz
        if(nodo->chave < aux->chave){ //à esquerda
            if(aux->dir == NULL){ //direita nulo
            	aux->fb = -nodo->alt - 1;
            	aux->alt = nodo->alt + 1;
            }else{ //direita nao nulo
            	aux->fb = aux->dir->alt - nodo->alt;
                if(nodo->alt > aux->dir->alt) //maior
                	aux->alt = nodo->alt + 1;
                else //menor
                	aux->alt = aux->dir->alt + 1;
            }
        }
        else{ //à direita
            if(aux->esq == NULL){ //esquerda nulo
            	aux->fb = nodo->alt + 1;
            	aux->alt = nodo->alt + 1;
            }else{ //esquerda nao nulo
            	aux->fb = nodo->alt - aux->esq->alt;
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

void rotacao_simples_dir(TpArvore *arvore, TpNodo *avo){
	printf("\nRotacao Simples A Direita\n");
    TpNodo *aux = avo->dir;  //pega o filho
    avo->dir = aux->esq;
    if(avo->dir != NULL)  //caso o filho tenha um filho a esquerda
    	avo->dir->pai = avo;
    if(avo->pai == NULL){  //atualiza a raiz
    	aux->pai = NULL;
    	arvore->raiz = aux;
    }
    else{
    	aux->pai = avo->pai;
    	if(aux->pai->dir == avo)
    		aux->pai->dir = aux;
    	else
    		aux->pai->esq = aux;
    }
    aux->esq = avo;
    avo->pai = aux;
    if(avo->esq != NULL)  //pega a folha a esquerda e atualiza o fb e a altura
    	att_alt_fb(avo->esq);
    else if(avo->dir != NULL)  //pega a folha a direita e atualiza o fb e a altura
    	att_alt_fb(avo->dir);
    else{  //nodo fica folha
    	avo->alt = 0;
    	avo->fb = 0;
    	att_alt_fb(avo);
    }
}

void rotacao_simples_esq(TpArvore *arvore, TpNodo *avo){
	printf("\nRotacao Simples A Esquerda\n");
	TpNodo *aux = avo->esq;
	avo->esq = aux->dir;
    if(avo->esq != NULL)  //caso o filho tenha um filho a esquerda
    	avo->esq->pai = avo;

    if(avo->pai == NULL){  //atualiza a raiz
    	aux->pai = NULL;
    	arvore->raiz = aux;
    }
    else{
    	aux->pai = avo->pai;
    	if(aux->pai->esq == avo)
    		aux->pai->esq = aux;
    	else
    		aux->pai->dir = aux;
    }
    aux->dir = avo;
    avo->pai = aux;
    if(avo->dir != NULL) //pega a folha a direita e atualiza o Fb e a altura
    	att_alt_fb(avo->dir);
    else if(avo->esq != NULL)  //pega a folha a esquerda e atualiza o Fb e a altura
    	att_alt_fb(avo->esq);
    else{  //nodo fica folha
    	avo->alt = 0;
    	avo->fb = 0;
    	att_alt_fb(avo);
    }
}

void rotacao_dupla_dir(TpArvore *arvore, TpNodo *avo){
	TpNodo *aux = avo->dir, *aux2 = avo->dir->esq;
	printf("\nRotacao Dupla A Direita\n");
	int a=aux->fb;
	avo->dir=aux2;
	aux2->pai=avo;
	aux->fb=aux2->fb;
	aux->esq=aux2->dir;
	aux2->dir=aux;
	aux2->esq=aux2->esq;
	aux2->alt=+1;
	aux2->fb=a;
	aux->pai=aux2;
	aux->dir=aux->dir;
	aux->alt=-1;
	rotacao_simples_dir(arvore, avo);
}

void rotacao_dupla_esq(TpArvore *arvore, TpNodo *avo){
	TpNodo *aux = avo->esq, *aux2 = avo->esq->dir;
	printf("\nRotacao Dupla A Esquerda\n");
	int a=aux->fb;
	avo->esq=aux2;
	aux2->pai=avo;
	aux->fb=aux2->fb;
	aux->dir=aux2->esq;
	aux2->esq=aux;
	aux2->dir=aux2->dir;
	aux2->alt=+1;
	aux2->fb=a;
	aux->pai=aux2;
	aux->esq=aux->esq;
	aux->alt=-1;
	rotacao_simples_esq(arvore, avo);
}

void balancear_arvore(TpArvore *arvore, TpNodo *nodo){
    if(nodo->pai == NULL || nodo->pai->pai == NULL)  //compara somente se o no tiver avo
    	return;                                      
    TpNodo *aux = nodo->pai->pai;
    while(aux != NULL){
    	nodo = nodo->pai;
        if(aux->fb > 1){    //avo que esta a esquerda esta desbalanceado
            if(nodo->fb > 0)  //caso de RR
            	rotacao_simples_dir(arvore,aux);
            else  //caso de RL
            	rotacao_dupla_dir(arvore,aux);
        }
        else if(aux->fb < -1){   //avo que esta a direita esta desbalanceado
            if(nodo->fb < 0)  //caso de LL
            	rotacao_simples_esq(arvore,aux);
            else  //caso de LR
            	rotacao_dupla_esq(arvore,aux);
        }
        aux = aux->pai;
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
	new->fb=0;
	if(arvore->raiz == NULL){ //raiz nula
		new->pai = NULL;
		arvore->raiz = new;
	}
	else if(key < pai->chave){ //insere a esquerda
		new->pai = pai;
		pai->esq = new;
		att_alt_fb(new);
	}
	else{ //insere a direita
		new->pai = pai;
		pai->dir = new;	
		att_alt_fb(new);
	}
	balancear_arvore(arvore, new);
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
