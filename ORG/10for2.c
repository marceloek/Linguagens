#include <stdio.h>
#include <conio.h>

void fracaoParaBinario(double fracao) {
    fracao = fracao - (int)fracao; // removendo a parte inteira: 12.25d --> 0.25d

    while (fracao != 0.0) {
        fracao *= 2;
        int resto = (int)fracao;
        fracao -= resto;

        printf("%d", resto);
    }
}

void decimalComFracaoParaBinario(double numero){
	char exp1[128];
    printf(".");
    fracaoParaBinario(numero);
    printf("\n");
}

int main() {
    double numero;
	exp1[128];
    numero = 12.25;
	itoa(numero, exp1, 2); //converte para base 2
    decimalComFracaoParaBinario(numero);

    numero = 62.62510;
    decimalComFracaoParaBinario(numero);

    return 0;
}
