#include<stdio.h>
#include<stdlib.h>

typedef struct{
	char nome[50];
	char endereco[100];
	int matricula;
} estudante;
	 
int main(){
	int i, n;
	printf("Digite o numero de alunos:\n");
	scanf("%d", &n);
	estudante *p = (estudante*)calloc(n, sizeof(estudante));
	
	if(!p)
		printf("Espaço insuficiente");
		
	for(i=0;i<n;i++){
		getchar();
		printf("Digite o nome do aluno %d:\n", i+1);
		fgets((p+i)->nome, 50, stdin);
		printf("Digite o endereco do aluno %d:\n", i+1);
		fgets((p+i)->endereco, 100, stdin);
		printf("Digite a matricula do aluno %d:\n", i+1);
		scanf("%d", &(p+i)->matricula);
		
	}
	system("clear");
	
	for(i=0;i<n;i++){
		printf("Nome do aluno %d: %s", i+1, (p+i)->nome);
		printf("Endereco do aluno %d: %s", i+1, (p+i)->endereco);
		printf("Matricula do aluno %d: %d\n", i+1, (p+i)->matricula);
		puts("");
	}
	free(p);	
	return 0;
}
