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

void bin(int num, int bit, int aux, int aux1)
{
    int x;
    if (bit == 1)
        x = 3;
    else
        x = 7;
    int bin[x];
    for (; aux >= 0; aux--)
    {
        if (num % 2 == 0)
            bin[aux] = 0;
        else
            bin[aux] = 1;
        num = num / 2;
    }
    for (aux = 0; aux < aux1; aux++)
        printf("%d", bin[aux]);
}

void main()
{
    struct linha vetor_linha[8];
    int bloco[32], mp[128];
    for (int i = 0; i < 128; i++)
        mp[i] = rand() % 500;
    // 4294967296;
    int endereco, n, op;
    do
    {
        printf("\n\tMEMORIA PRINCIPAL\n");
        for (int i = 0; i < 128; i++)
        {
            printf("\n\tCelula[");
            bin(i,0,6,7);
            printf("]: %d", mp[i]);
        }
        puts("\n\n----------------------------------------------------------");
        printf("\n\t\tMEMORIA CACHE\n");
        for (int i = 0; i < 8; i++)
        {
            printf("\nLinha[");
            bin(i, 1, 2, 3);
            printf("]:");
            for (int j = 0; j < 4; j++)
            {
                printf(" | %d ", vetor_linha[i].vet1[j]);
            }
        }
        puts("\n\n----------------------------------------------------------");
        puts("\n\t\tMENU\n");
        puts("(1) Para ler o conteudo de um endereco da memoria;");
        puts("(2) Para escrever em um determinado endereco da memoria;");
        puts("(3) Para apresentar as estatisticas de acertos e faltas;");
        puts("(0) Para sair.\n");
        printf("Digite o numero correspondente a opcao: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            printf("\nDigite o endereco desejado:\n");
            scanf("%d", &endereco);

            break;
        case 2:
            printf("\nDigite o endereco desejado:\n");
            scanf("%d", &endereco);

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