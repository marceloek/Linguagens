#include <stdio.h>
#include <stdlib.h>

typedef struct linha
{
    int vet1[4];
    int dirty;
    int rotulo;
    int valido;
    int pol_sub;
} linha;

typedef struct conjunto
{
    struct linha vetor_linha[2];
} conjunto;

typedef struct bloco
{
    int vet2[4];
} bloco;

int dec(int bits, char num[bits])
{
    int cont = 0, cont2 = 1;
    for (int i = bits - 1; i >= 0; i--)
    {
        if (num[i] == '1')
            cont += cont2;
        cont2 *= 2;
    }
    return cont;
}

void bin(int num, int bits)
{
    int aux = bits - 1, bin[bits];
    for (; aux >= 0; aux--)
    {
        if (num % 2 == 0)
            bin[aux] = 0;
        else
            bin[aux] = 1;
        num /= 2;
    }
    for (aux = 0; aux < bits; aux++)
        printf("%d", bin[aux]);
}

void print_mem(struct bloco vetor_bloco[32], struct conjunto vetor_conjunto[4]){
    printf("\n\tMEMORIA PRINCIPAL\n");
    for (int i = 0; i < 32; i++)
    {
    	for (int j = 0;  j < 4; j++)
    	{
            printf("\n\tCelula[");
            bin(i*4+j, 7);
            printf("]: ");
            bin(vetor_bloco[i].vet2[j], 8);
		}
    }
    puts("\n\n------------------------------------------------------------------");
    printf("\n\t\t\tMEMORIA CACHE\n");
    puts("\n|P_S| |VALIDO| |DIRTY| |ROTULO | |   00   | |   01   | |   10   | |   11   | |LINHA| |CONJUNTOS|");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0;  j < 2; j++)
        {
            printf("|");
            bin(vetor_conjunto[i].vetor_linha[j].pol_sub,3);
            printf("| ");
            printf("|   %d  |", vetor_conjunto[i].vetor_linha[j].valido);
            printf(" |  %d  | |  ", vetor_conjunto[i].vetor_linha[j].dirty);
            if (vetor_conjunto[i].vetor_linha[j].valido == 0)
                printf("---");
            else
                bin(vetor_conjunto[i].vetor_linha[j].rotulo, 3);
            printf("  | ");

            for (int k = 0; k < 4; k++)
            {
                printf("|");
                if (vetor_conjunto[i].vetor_linha[j].valido == 0)
                    printf("--------");
                else
                    bin(vetor_conjunto[i].vetor_linha[j].vet1[k], 8);
                printf("| ");
            }
            printf("| ");
            bin(i*2+j, 3); //linha
            printf(" | |   ");
            bin(i, 2); //conjunto
            printf("    |");
            puts("");
        }
    }
    printf("\n\n------------------------------------------------------------------");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (vetor_conjunto[i].vetor_linha[j].pol_sub == 0)
            {
                printf("\nProxima localizacao: Linha [");
                bin(i*2 + j, 3);
                printf("] - ");
                printf("Conjunto [");
                bin(i, 2);
                printf("]");
                break;
            }
        }
    }
    puts("\n------------------------------------------------------------------");
}

void main(void)
{
    struct conjunto vetor_conjunto[4];
    struct bloco vetor_bloco[32]; 
    int int_conjunto, int_rotulo, acertos_leitura, acertos_escrita, faltas_leitura, faltas_escrita, op;
    char bits_endereco[7], bits_conjunto[2], bits_rotulo[3];
    for (int i = 0; i < 32; i++){
        for (int j = 0;  j < 4; j++)
        {
        	vetor_bloco[i].vet2[j] = rand() % 256;
    	}
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0;  j < 2; j++)
        {
            vetor_conjunto[i].vetor_linha[j].pol_sub = 0;
            vetor_conjunto[i].vetor_linha[j].valido = 0;
            vetor_conjunto[i].vetor_linha[j].dirty = 0;
        }
    }
   	print_mem(vetor_bloco, vetor_conjunto);

    do
    {
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
            scanf("%s", &bits_endereco);
            //0 0 0 0 1 0 1
            bits_conjunto[0] = bits_endereco[3];
            bits_conjunto[1] = bits_endereco[4];
            bits_rotulo[0] = bits_endereco[0];
            bits_rotulo[1] = bits_endereco[1];
            bits_rotulo[2] = bits_endereco[2];
            int_conjunto = dec(2, bits_conjunto);
            int_conjunto %= 2;
            int_rotulo = dec(3, bits_rotulo);
            // pega conjunto, num linha,
            for (int i = 0; i < 4; i++)
            {
                
            }

            break;
        case 2:
            printf("\nDigite o endereco do dado desejado a ser escrito:\n");
            scanf("%s", &bits_endereco);
            dec(7, bits_endereco);
            printf("\nDigite o conteudo do dado desejado a ser escrito:\n");

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