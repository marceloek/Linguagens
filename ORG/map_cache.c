#include <stdio.h>
#include <stdlib.h>

// 10) Map. Associativo por Conjuntos (2)
// escrita no retorno
// LRU (Mais Antigo é Substituido)
// Alunos: Kevin + Marcelo

typedef struct linha
{
    int vet1[4];
    int rotulo;
    int valido;
    int pol_sub;
} linha;

typedef struct bloco
{
    int vet2[4];
} bloco;

void bin(int num, int bits)
{
    int aux = bits-1, bin[bits];
    for (; aux >= 0; aux--)
    {
        if (num % 2 == 0)
            bin[aux] = 0;
        else
            bin[aux] = 1;
        num = num / 2;
    }
    for (aux = 0; aux < bits; aux++)
        printf("%d", bin[aux]);
}

void main()
{
    struct linha vetor_linha[8];
    int bloco[32], mp[128], ender[8];
    for (int i = 0; i < 128; i++)
        mp[i] = rand() % 1024;
    for (int i = 0; i < 8; i++){
        vetor_linha[i].pol_sub = 0;
        vetor_linha[i].rotulo = -1;
        for (int j = 0; j < 4; j++)
            vetor_linha[i].vet1[j]=-1;
	}
    int endereco, n, op;
    do
    {
        printf("\n\tMEMORIA PRINCIPAL\n");
        for (int i = 0; i < 128; i++)
        {
            printf("\n\tCelula[");
            bin(i, 7);
            printf("]: ");
            bin(mp[i], 10);
        }
        puts("\n\n---------------------------------------------------------------");
        printf("\n\t\t\tMEMORIA CACHE\n");
        puts("\n                    00           01           10           11\n");
        for (int i = 0; i < 8; i++)
        {
        	printf("\nRótulo[");
            if(vetor_linha[i].rotulo==-1)
                printf("------");
            else
                bin(vetor_linha[i].rotulo, 6);
            printf("] ");
            for (int j = 0; j < 4; j++)
            {
                printf("|");
                if(vetor_linha[i].vet1[j]==-1)
                	printf("----------");
                else
                	bin(vetor_linha[i].vet1[j], 10);
                printf("| ");
            }
            printf("[");
            bin(i, 3);
            printf("]");
        }
        puts("\n\n---------------------------------------------------------------");
        for (int j = 0; j < 4; j++)
        {
            if (vetor_linha[j].pol_sub == 0)
            {
                printf("Proxima localizacao: Linha [");
                bin(j, 3);
                printf("]");
                break;
            }
        }
        puts("\n---------------------------------------------------------------");
        puts("\n\t\t\tMENU\n");
        puts("(1) Para ler o conteudo de um endereco da memoria;");
        puts("(2) Para escrever em um determinado endereco da memoria;");
        puts("(3) Para apresentar as estatisticas de acertos e faltas;");
        puts("(0) Para sair.\n");
        printf("Digite o numero correspondente a opcao: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            printf("\nDigite o endereco desejado a ser lido:\n");
            scanf("%d", &endereco);
            sprintf(ender, "%d", endereco);
            printf("%s", ender);

            break;
        case 2:
            printf("\nDigite o endereco desejado a ser escrito:\n");
            scanf("%d", &endereco);
            sprintf(ender, "%d", endereco);
            printf("%s", ender);

            break;
        case 3:

            break;
        case 0:
            system("clear");
            puts("Voce escolheu por sair! Ate nunca mais!");
            break;
        default:
            system("clear");
            puts("Opcao invalida!");
        }
    } while (op != 0);
}