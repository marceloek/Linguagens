#include<stdio.h>
#include<stdlib.h>
int main(){
	int n, i;
	printf("Digite o numero de posicoes:\n");
	scanf("%d", &n);
	int *p = (int *)calloc(n, sizeof(int));
	
	if(!p)
		printf("Espa�o insuficiente");
	system("clear");	
	
	for(i=0;i<n;i++){
		printf("Digite o conteudo das posicoes %d:\n", i);
		scanf("%d", p++);
	}
	p=p-n;
	for(i=0;i<n;i++){
		printf("Posi��es: %p 	Conte�do: %d\n", p, *p);
		p++;
	}
	free(p);
	return 0;
}