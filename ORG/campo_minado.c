#include <stdio.h>

void mostra_campo(int campo[9][9], int user[9][9], int b, int a)
{
    puts("SITUACAO DO CAMPO MINADO");
    for (int i = 0; i < b; i++)
    {
        for (int j = 0; j < b; j++)
        {
            if (a == 1 && campo[i][j] == 9)
            {
                printf(" 9 ");
                continue;
            }
            if (user[i][j] == -1)
                printf("%d ", user[i][j]);
            else
                printf(" %d ", user[i][j]);
        }
        puts("");
    }
}

void calcula_bomba(int campo[9][9], int b)
{
    int i = 0;
    for (int x = 0; x < b; x++)
    {
        for (int y = 0; y < b; y++)
        {
            int i = 0;
            if (campo[x][y] == 9)
                continue;

            if (x - 1 != -1 && y - 1 != -1 && campo[x - 1][y - 1] == 9)
                i++;
            if (x - 1 != -1 && campo[x - 1][y] == 9)
                i++;
            if (x - 1 != -1 && y + 1 != b && campo[x - 1][y + 1] == 9)
                i++;
            if (y - 1 != -1 && campo[x][y - 1] == 9)
                i++;
            if (y + 1 != b && campo[x][y + 1] == 9)
                i++;
            if (x + 1 != b && y - 1 != -1 && campo[x + 1][y - 1] == 9)
                i++;
            if (x + 1 != b && campo[x + 1][y] == 9)
                i++;
            if (x + 1 != b && y + 1 != b && campo[x + 1][y + 1] == 9)
                i++;
            campo[x][y] = i;
        }
    }
}

int main()
{
    int campo[9][9] = {
        {0, 9, 9, 9, 0, 9, 0, 9, 0},
        {0, 0, 0, 0, 0, 0, 9, 9, 0},
        {0, 0, 9, 9, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 9, 0},
        {0, 9, 0, 9, 9, 0, 9, 0, 0},
        {0, 9, 0, 0, 0, 9, 9, 0, 9},
        {0, 0, 9, 0, 0, 0, 0, 0, 0},
        {0, 9, 9, 0, 9, 0, 9, 0, 0},
        {9, 0, 0, 9, 0, 9, 0, 0, 9}};
    int user[9][9] = {
        {-1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1}};
    int x, y, b;
    while (1)
    {
        puts("Digite a dificuldade do campo minado, exemplo: 5 = 5x5, 7 = 7x7 ou 9 = 9x9:");
        scanf("%d", &b);
        if (b == 5 || b == 7 || b == 9)
            break;
        printf("\nO valor digitado eh invalido! Tente novamente!\n");
    }
    //insere_bombas(campo, b);
    calcula_bomba(campo, b);

    for (int i = 0; i < 81; i++)
    {
        int a = 0;
        mostra_campo(campo, user, b, a);
        puts("\nDigite as coordenadas do campo minado (coluna)(linha): ");
        scanf("%d", &y);
        scanf("%d", &x);
        puts("");
        if (y > b || x > b)
            continue;
        x--;
        y--;
        user[x][y] = campo[x][y];
        if (campo[x][y] == 9)
        {
            a = 1;
            printf("\nA BOMBA EXPLODIU! VOCE PERDEU!\n");
            mostra_campo(campo, user, b, a);
            break;
        }
    }
}