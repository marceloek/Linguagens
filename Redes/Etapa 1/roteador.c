#include <pthread.h>            // threads
#include <stdio.h>              // printf()
#include <string.h>             // exit()
#include <stdlib.h>             // atoi()
#include <arpa/inet.h>          // operacao de internet
#include <sys/socket.h>         // sockets
#include <sys/time.h>           // time do sistema
#include <unistd.h>             // constantes e tipos
#include "headers/structs.h"    // header com structs dos roteadores

struct roteador *roteadores;
struct sockaddr_in si_me, si_other;
int id_roteador;

void die(char *s)
{
    perror(s);
    exit(1);
}

void tempo_atual()
{
    struct timeval tv;
    struct timezone tz;
    struct tm *tm;
    gettimeofday(&tv, &tz);
    tm = localtime(&tv.tv_sec);
    printf("Horario atual: (%d:%02d:%02d:%d).\n", tm->tm_hour, tm->tm_min, tm->tm_sec, (int)tv.tv_usec);
}

void enviar()
{
}

void receber()
{
}

void menu()
{
}

void mapeia_rede()
{
    FILE *enlaces = fopen("configs/enlaces.config", "r");
    if (enlaces == NULL)
        die("Nao foi possivel abrir o arquivo 'enlaces.config'!");
    for (int i = 0;)
    {
    }
}

int main(int argc, char *argv[])
{
    id_roteador = malloc(sizeof(int));
    if (argc == 1) // Identificacao do roteador pelo programa
    {
        printf("Informe o ID do roteador: \n");
        scanf("%d", id_roteador);
    }
    else if (argc == 2) // Identificacao dada por linha de comando
    {
        *id_roteador = atoi(argv[1]);
        printf("Esse e o roteador ID: %d", id_roteador);
    }

    mapeia_rede();
    // pthread_create(&tids[0], NULL, router, (void *)&roteadores[0].porta);
    // pthread_create(&tids[1], NULL, terminal, NULL);
    // pthread_create(&tids[2], NULL, controlVec, NULL);
    // pthread_join(tids[0], NULL);
    // pthread_join(tids[1], NULL);
    // pthread_join(tids[2], NULL);

    close(socket) return (1);
}