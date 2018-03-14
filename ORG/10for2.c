#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

void fracaoParaBinario(double fracao, int rnum[63]){
	if(fracao - (int)fracao != 0){
		int i=11;
		fracao = fracao - (int)fracao;
		printf(".");
		while (fracao != 0.0) {
			fracao *= 2;
			int resto = (int)fracao;
			fracao -= resto;
			//printf("%d", resto);
			rnum[i]=resto;
			i++;
		}
		int a=i;
		for(i=11;i<a;i++)
			printf("%d", rnum[i]);
	}
}

int main(){
	int inum, Bias = 1023, fnum[63], E, exp;
	char exp1[11], exp2[11];
	double tnum;
	printf("Digite um numero: ");
	scanf("%lf", &tnum);
	inum = tnum;
	itoa(inum, exp1, 2); //converte para base 2
		
	E = strlen(exp1) -1;
	exp = E + Bias;
	itoa(exp, exp2, 2);
	if(tnum<0)				//printando S
		printf("| 1 | ");
	else
		printf("| 0 | ");
	printf("%s | ", exp2); //printando exp
	
	/*fracaoParaBinario(tnum, fnum);
	for(int i=0;i<11;i++)
		fnum[i]=exp1[i];
	for(int a=0;a<14;a++)
		printf("%d", fnum[a]);*/
	return 0;
}
