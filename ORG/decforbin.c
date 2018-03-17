#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mantissa(double fracao, int rnum[52]){
	if(fracao - (int)fracao != 0){
		int i=0;
		fracao = fracao - (int)fracao;
		while (fracao != 0.0) {
			fracao *= 2;
			int resto = (int)fracao;
			fracao -= resto;
			rnum[i]=resto;
			i++;
		}
	}
}

void fexp(int aux, int exp1[11]){
    int i=10;
    while(aux>=2){
        exp1[i]=aux%2;
        aux /=2;
        i--;
    }
    exp1[i--]=aux;
}

int main(){
	int Bias = 1023, rnum[52], E=0, exp01, b, exp1[11];
	double tnum, aux;

	//colocando valores '0' para todas as posicoes da mantissa e exp
	for(int b=0;b<52;b++)
		rnum[b]=0;
	for(int b=0;b<11;b++)
		exp1[b]=0;

	printf("Digite um numero: "); //digitando o valor de entrada
	scanf("%lf", &tnum);

	aux = tnum;

	if(aux<0) //caso o valor seja negativo
		aux *=-1;

	//divisao sucessiva maior que 1 para encontrar o numero de bits
  if(aux>1){
      while(aux>1){
					E++;
        	aux /=2;
					if(aux/2<1)
						break;
	    }
	}

	//multiplicacao sucessiva menor que 1 para encontrar o numero de bits
	if(aux<1){
    	while(aux<1){
					E--;
        	aux *=2;
					if(aux*2>1)
						break;
	    }
	}

	mantissa(aux, rnum); //convertendo parte fracionaria

	exp01 = E + Bias; //somando bits da base 2 com os bits do double precision

	fexp(exp01, exp1); //calculando exp

	if(tnum<0) //printando S(1)	obs: (n)=bits utilizados
		printf("| 1 | ");
	else
		printf("| 0 | ");

    for(int n=0;n<11;n++)
        printf("%d", exp1[n]); //printando exp(11)
    printf(" |");

	for(b=0;b<51;b++){
		printf("%d", rnum[b]); //printando frac(51)
	}
	if(b==51)
			printf("%d |", rnum[b]); //printando frac(52)
	printf("\nS(1)	exp(11)				frac(52)\n");
	return 0;
}
