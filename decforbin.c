#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void fracaoParaBinario(double fracao, int rnum[52]){
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

int main(){
	int Bias = 1023, rnum[52], E=-1, exp, b;
	for(int b=0;b<52;b++)
		rnum[b]=0;
	char exp1[11];
	double tnum, aux;
	printf("Digite um numero: ");
	scanf("%lf", &tnum);
	aux = tnum;
	if(aux<0)
		aux *=-1;
	for(int a=0;aux>1;a++){
		aux /=2;
		E++;
	}
	aux*=2;
	printf("%lf", aux);
	fracaoParaBinario(aux, rnum);
	exp = E + Bias;
	itoa(exp, exp1, 2); //converte para base 2
	
	
	if(tnum<0)	//printando S
		printf("| 1 | ");
	else
		printf("| 0 | ");
	printf("%s | ", exp1); //printando exp
	
	for(b=0;b<51;b++){
		printf("%d", rnum[b]);
	}
	if(b==51)
			printf("%d |", rnum[b]);	
	return 0;
}
