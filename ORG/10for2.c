#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void fracaoParaBinario(double fracao){
	fracao = fracao - (int)fracao;
	while (fracao != 0.0) {
		fracao *= 2;
		int resto = (int)fracao;
		fracao -= resto;
		printf("%d", resto);
	}
}

int main(){
	int inum;
	char exp1[128];
	float tnum;
	scanf("%f", &tnum);
	inum = tnum;
	itoa(inum, exp1, 2); //converte para base 2
	printf("%s.", exp1);
	fracaoParaBinario(tnum);
	return 0;
}
