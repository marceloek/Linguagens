#include <stdio.h>
#include <stdlib.h>
typedef struct _nodo{
    int chave, cor;         //cor: 0 = preto, 1 = vermelho
    struct _nodo *dir;
    struct _nodo *esq;
    struct _nodo *pai;
}TpNodo;
TpNodo *pRaiz; //guarda a raiz
void Init(){
    pRaiz = NULL;
}
void insere_sentinela(TpNodo *nodo){ //adiciona o sentinela
    TpNodo *senD = (TpNodo*)malloc(sizeof(TpNodo)), *senE = (TpNodo*)malloc(sizeof(TpNodo));
    senD->chave = 0;
    senD->cor = 0;
    senD->dir = NULL;
    senD->esq = NULL;
    senD->pai = nodo;
    senE->chave = 0;
    senE->cor = 0;
    senE->dir = NULL;
    senE->esq = NULL;
    senE->pai = nodo;
    nodo->dir = senD;
    nodo->esq = senE;
}
void rotacao_direita(TpNodo *aux){
    TpNodo *nodo = aux->esq; //guarda o filho a esquerda

    aux->esq = nodo->dir;
    if(aux->esq != NULL)
        aux->esq->pai = aux;

    if(aux->pai == NULL){ //caso seja a raiz
        nodo->pai = NULL;
        pRaiz = nodo;
    }
    else{
        nodo->pai = aux->pai;
        if(aux == nodo->pai->esq)
            nodo->pai->esq = nodo;
        else
            nodo->pai->dir = nodo;
    }

    nodo->dir = aux;
    aux->pai = nodo;
}
void rotacao_esquerda(TpNodo *aux){
    TpNodo *nodo = aux->dir; //guarda o filho a direita

    aux->dir = nodo->esq;
    if(aux->dir != NULL)
        aux->dir->pai = aux;

    if(aux->pai == NULL){ //caso seja a raiz
        nodo->pai = NULL;
        pRaiz = nodo;
    }
    else{
        nodo->pai = aux->pai;
        if(aux == nodo->pai->dir)
            nodo->pai->dir = nodo;
        else
            nodo->pai->esq = nodo;
    }

    nodo->esq = aux;
    aux->pai = nodo;
}
void balancear(TpNodo *nodo){
    TpNodo *aux;
    while(nodo->pai->cor){ //caso pai e vermelho
        if(nodo->pai == nodo->pai->pai->esq){ //arvore tende à esquerda
            aux = nodo->pai->pai->dir;
            if(aux->cor){ //primeiro caso: pai vermelho e tio vermelho
                nodo->pai->cor = 0;
                aux->cor = 0;
                nodo->pai->pai->cor = 1;
                nodo = nodo->pai->pai;
            }
            else{
                if(nodo == nodo->pai->dir){ //segundo caso: pai vermelho, tio preto e nodo no filho a direita
                    nodo = nodo->pai;
                    rotacao_esquerda(nodo);
                }
                //terceiro caso: pai vermelho, tio preto e nodo no filho a esquerda
                nodo->pai->cor = 0;
                nodo->pai->pai->cor = 1;
                rotacao_direita(nodo->pai->pai);
            }
        }
        else{ //arvore tende à direita
            aux = nodo->pai->pai->esq;

            if(aux->cor){ //primeiro caso: pai vermelho e tio vermelho
                nodo->pai->cor = 0;
                aux->cor = 0;
                nodo->pai->pai->cor = 1;
                nodo = nodo->pai->pai;
            }
            else{
                if(nodo == nodo->pai->esq){ //segundo caso: pai vermelho, tio preto e nodo e filho a esquerda
                    nodo = nodo->pai;
                    rotacao_direita(nodo);
                }
                //terceiro caso: pai vermelho, tio preto e nodo e filho a direita
                nodo->pai->cor = 0;
                nodo->pai->pai->cor = 1;
                rotacao_esquerda(nodo->pai->pai);
            }
        }
        if(nodo->pai == NULL) //caso nao tem pai
            return;
    }
}
int altura(TpNodo *nodo){ //determina a altura da arvore
    if(nodo->chave != 0){
        int altE = altura(nodo->esq);
        int altD = altura(nodo->dir);

        if(altE < altD)
            return altD + 1;
        else
            return altE + 1;
    }
    else
        return 0;
}
void inserir(int val){ //adiciona novo nodo
    TpNodo *aux = pRaiz, *pai = NULL, *new = (TpNodo*)malloc(sizeof(TpNodo)); //*aux - ponteiros de busca, *g_info - ponteiro para armazenar a informacao

    while(aux != NULL && aux->chave != 0){   //procura o local onde colocar o novo no
        pai = aux;                        //*g_pai guarda o pai do novo nodo

        if(val == aux->chave){ //caso o valor seja repetido
			printf("Esse valor ja esta inserido! Caso queira, tente novamente.\n");
			return;
        }
        else if(val < aux->chave)
            aux = aux->esq;
        else
            aux = aux->dir;
    }
    new->chave = val;     //guarda o valor no nodo
    new->cor = 1;        // adiciona a cor vermelha ao nodo
    if(pRaiz == NULL){       //caso seja a raiz do arvore, o primeiro numero inserido
        new->pai = NULL;
        pRaiz = new;
        insere_sentinela(new); //adiciona filhos sentinelas
    }
    else if(val < pai->chave){     //caso fique à esquerda do seu pai
        free(pai->esq);        //limpa sentinela à esquerda
        new->pai = pai;        //define o pai
        pai->esq = new;     //define que o pai tem um filho à esquerda
        insere_sentinela(new);   //adiciona filhos sentinalas
        balancear(new);          //balancea a arvore
    }
    else{                           //caso fique à direita do seu pai
        free(pai->dir);        //limpa sentinela à direita
        new->pai = pai;        //define o pai
        pai->dir = new;     //define que o pai tem um filho à direita
        insere_sentinela(new);   //adicina filhos sentinelas
        balancear(new);          //balancea a arvore
    }
    pRaiz->cor = 0; //raiz de cor preta
	printf("O valor foi inserido com sucesso!\n\n");
}
void exibirNivel(TpNodo *nodo, int i, int nivel){ //nivel: nivel desejado para imprimir; i: procura o nivel
    if(nodo->chave != 0){
        i++;
        exibirNivel(nodo->esq, i, nivel);
        exibirNivel(nodo->dir, i, nivel);
    }
    if(i == nivel && nodo->chave != 0){ //caso o i seja igual ao nivel, ele imprime nodo
        printf(" %d ", nodo->chave);
        if(nodo->pai == NULL)  //imprime raiz
            printf("(PRETO, NIL), ");
        else{ //cor do nodo
            if(nodo->cor)
                printf("(VERMELHO, ");
            else
                printf("(PRETO, ");

            printf("%d),", nodo->pai->chave);
        }
    }
    else if(i > nivel) //caso o "i" ja passou do nivel desejado
        return;
}
void exibir(){
	system("clear");
    if(pRaiz == NULL)
        printf("A arvore esta vazia.");

    else{
        int x, alt = altura(pRaiz);

        for(x = 0; x < alt; x++){ //envia qual nivel deve imprimir "x"
            printf("\nNivel %d:", x);
            exibirNivel(pRaiz, -1, x);
        }
    }
    printf("\n");
}
int main(){
    int n, key;
    Init();
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
				printf("\nSomente valores positivos sao permitidos!\n\n");
				break;
			}else{
				puts("");
				inserir(key);
				break;
			}
			case 2:
			exibir();
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
	free(pRaiz);
}
