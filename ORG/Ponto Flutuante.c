#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main(){
	int inum; //parte inteira
	float tnum; //parte total
	float rnum; //parte resto
	char exp1[128];
	printf("Digite um numero: ");
	scanf("%f", &tnum);
	inum = tnum; //parte inteira
	rnum = tnum - inum; //resto
	
	itoa(inum, exp1, 2); //Converte para base 2
	
	if(tnum<0)
		printf("| 1 | "); //printa negativo
	else
		printf("| 0 | "); //printa positivo
	
	printf("%s |", exp1); //printa o exp
	return 0;
}

