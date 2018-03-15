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
	char exp1[11];
	double tnum, aux;
	
	//colocando valores '0' para todas as posicoes da parte fracionaria
	for(int b=0;b<52;b++) 
		rnum[b]=0;
		
	printf("Digite um numero: "); //digitar o valor de entrada
	scanf("%lf", &tnum);
	
	aux = tnum;
	
	if(aux<0) //caso o valor seja negativo
		aux *=-1;
		
	//divisao sucessiva maior que 1 para encontrar o numero de bits
	for(int a=0;aux>1;a++){ 
		aux /=2;
		E++;
	}
	aux*=2;
	
	fracaoParaBinario(aux, rnum); //convertendo parte fracionaria
	
	exp = E + Bias; //somando bits da base 2 com os bits do double precision
	
	itoa(exp, exp1, 2); //conversao para base 2
	
	if(tnum<0)	//printando S(1)	obs: (n)=bits utilizados
		printf("\n| 1 | ");
	else
		printf("| 0 | ");
	printf("%s | ", exp1); //printando exp(11)
	
	for(b=0;b<51;b++){
		printf("%d", rnum[b]); //printando frac(51)
	}
	if(b==51)
			printf("%d |", rnum[b]); //printando frac(52)
	printf("\nS(1)	exp(11)				frac(52)");
	return 0;
}
