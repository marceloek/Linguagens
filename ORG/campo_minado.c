#include <stdio.h>

void mostra_campo(int user[9][9], int b)
{
    for (int i = 0; i < b; i++)
    {
        for (int j = 0; j < b; j++)
        {
            printf("%d ", user[i][j]);
        }
        puts("");
    }
}

void calcula_bomba(int campo[9][9], int user[9][9], int b)
{
    int i = 0, x, y;
    puts("\nDigite as coordenadas do campo minado (coluna)(linha): ");
    scanf("%d", &y);
    scanf("%d", &x);
    puts("");
    x--;
    y--;
    if (x == 0)
    {
        if (campo[x + 1][y] == 9)
            i++;
        if (y == 0)
        {
            if (campo[x][y + 1] == 9)
                i++;
            if (campo[x + 1][y + 1] == 9)
                i++;
        }
        else if (y == b - 1)
        {
            if (campo[x][y - 1] == 9)
                i++;
            if (campo[x + 1][y - 1] == 9)
                i++;
        }
        else
        {
            if (campo[x + 1][y - 1] == 9)
                i++;
            if (campo[x + 1][y + 1] == 9)
                i++;
            if (campo[x][y + 1] == 9)
                i++;
            if (campo[x][y - 1] == 9)
                i++;
        }
    }
    else if (x == b - 1)
    {
        if (campo[x - 1][y] == 9)
            i++;
        if (y == 0)
        {
            if (campo[x][y + 1] == 9)
                i++;
            if (campo[x - 1][y + 1] == 9)
                i++;
        }
        else if (y == b - 1)
        {
            if (campo[x][y - 1] == 9)
                i++;
            if (campo[x - 1][y - 1] == 9)
                i++;
        }
        else
        {
            if (campo[x][y - 1] == 9)
                i++;
            if (campo[x][y + 1] == 9)
                i++;
            if (campo[x - 1][y - 1] == 9)
                i++;
            if (campo[x - 1][y + 1] == 9)
                i++;
        }
    }
    else
    {
        if (campo[x + 1][y] == 9)
            i++;
        if (campo[x - 1][y] == 9)
            i++;
        if (y == 0)
        {
            if (campo[x][y + 1] == 9)
                i++;
            if (campo[x - 1][y + 1] == 9)
                i++;
            if (campo[x + 1][y + 1] == 9)
                i++;
        }
        else if (y == b - 1)
        {
            if (campo[x - 1][y - 1] == 9)
                i++;
            if (campo[x + 1][y - 1] == 9)
                i++;
            if (campo[x][y - 1] == 9)
                i++;
        }
        else
        {
            if (campo[x][y - 1] == 9)
                i++;
            if (campo[x][y + 1] == 9)
                i++;
            if (campo[x - 1][y - 1] == 9)
                i++;
            if (campo[x - 1][y + 1] == 9)
                i++;
            if (campo[x + 1][y - 1] == 9)
                i++;
            if (campo[x + 1][y + 1] == 9)
                i++;
        }
    }
    user[x][y] = i;
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
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}};

    int b;
    puts("Digite a dificuldade do campo minado, exemplo: 5 = 5x5, 7 = 7x7 ou 9 = 9x9:");
    scanf("%d", &b);
    if (b == 5 || b == 7 || b == 9)
        printf("\n\nDificuldade escolhida foi: %d!\n", b);
    else
        printf("\nO valor digitado eh invalido!");

    for (int i = 0; i < 81; i++)
    {
        mostra_campo(user, b);
        if (campo[x][y] == 9)
        {
            printf("\nA BOMBA EXPLODIU! VOCE PERDEU!\n");
            calcula_bomba(campo, user, b);
            mostra_campo(user, b);
            puts("\nLOCALIZACAO DAS BOMBAS:\n");
            for (int i = 0; i < b; i++)
            {
                for (int j = 0; j < b; j++)
                {
                    printf("%d ", campo[i][j]);
                }
                puts("");
            }
            break;
        }
        else
        {
            calcula_bomba(campo, user, b);
        }
    }
}