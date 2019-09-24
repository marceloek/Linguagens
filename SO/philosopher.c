// gcc -o test1 philosopher.c -lpthread
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define N 5 // numero de philosopher
#define thinking 0
#define hungry 1
#define eating 2
#define left (i + N - 1) % N //agarrar garfo da esquerda
#define right (i + 1) % N    //agarrar garfo da direita

void *mythread(void *data);
void take_forks(int);
void put_forks(int);
void test(int);

int nfilosofo[N] = {0, 1, 2, 3, 4};
int state[N] = {0, 0, 0, 0, 0}; // estados dos philosophers (comendo, pensando e com fome)
sem_t phil_sem[N];              // mutex de cada philosopher
sem_t mutex;

void *mythread(void *num)
{
    while (1)
    {
        int *id = num;
        sleep(1);
        take_forks(*id);
        sleep(1);
        put_forks(*id);
    }
}

void take_forks(int i)
{
    sem_wait(&mutex);
    state[i] = hungry;
    printf("Filosofo %d tem fome.\n", i);
    test(i);
    sem_post(&mutex);
    sem_wait(&phil_sem[i]); //down semaphore philosopher
    sleep(1);
}

void put_forks(int i)
{
    sem_wait(&mutex);
    state[i] = thinking;
    printf("Filosofo %d deixou os garfos %d e %d.\n", i, left, right);
    printf("Filosofo %d esta a pensar.\n", i);
    test(left);
    test(right);
    sem_post(&mutex);
}

void test(int i)
{
    if (state[i] == hungry && state[left] != eating && state[right] != eating)
    {
        state[2] = hungry;
        sleep(1);
        printf("Filosofo %d agarrou os garfos %d e %d.\n", i, left, right);
        printf("Filosofo %d esta a comer.\n", i);
        sem_post(&phil_sem[i]);
    }
}

int main(void)
{
    int i = 0;
    pthread_t philosopher[N];
    sem_init(&mutex, 0, 1); // inicializa o semáforo com valor 1
    for (i = 0; i < N; i++)
        sem_init(&phil_sem[i], 0, 0); // inicializa o semáforo com valor 1
    for (i = 0; i < N; i++)
    {
        int *j = malloc(sizeof(int));
        *j = i;
        pthread_create(&philosopher[i], NULL, mythread, &nfilosofo[i]);
        printf("Filosofo %d esta a pensar.\n", i);
    }
    for (i = 0; i < N; i++)
        pthread_join(philosopher[i], NULL);
    return (1);
}