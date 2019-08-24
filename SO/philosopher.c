
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <semaphore.h>
#include <fcntl.h>

#define N 5
#define left ((i + N - 1) % N)
#define right ((i + 1) % N)
#define thinking 0
#define hungry 1
#define eating 2

void *mythread(void *data);

typedef int semaphore;
int state[N];

semaphore mutex = 1;
semaphore phil_sem[N];

sem_t s;

int main(void)
{
    for (int i = 0; i < N; i++)
    {
        state[i] = 0;
        phil_sem[i] = 0;
    }

    pthread_t philosopher[N];
    int i = 0;

    sem_init(&s, 0, 1); // inicializa o semáforo com valor 1

    for (i = 0; i < N; i++)
    {
        int *j = malloc(sizeof(int));
        *j = i;
        pthread_create(&philosopher[i], NULL, mythread, (void *)j);
    }
    /* We will now wait for each thread to<\n>
    * terminate */

    for (i = 0; i < N; i++)
    {
        pthread_join(philosopher[i], NULL);
        printf("Thread id %ld returned\n", philosopher[i]);
    }

    return (1);
}

void *mythread(void *data)
{
    int id;
    id = *((int *)data);
    free((int *)data);

    while (1)
    {
        printf("filosofo [%d] esta pensando...\n\n", id);
        sleep(3);

        take_forks(id);

        printf("filosofo [%d] esta comendo...\n\n", id);
        sleep(5);

        put_forks(id);
    }

    pthread_exit(NULL);
}

void take_forks(int i)
{
    sem_wait(&mutex);

    state[i] = hungry;
    test(i);

    sem_post(&mutex);

    sem_wait(&phil_sem[i]); //down semaphore philosopher
}

void put_forks(int i)
{
    sem_wait(&mutex);

    state[i] = thinking;

    test(left);
    test(right);

    sem_post(&mutex);
}

void test(int i)
{
    if (state[i] == hungry && state[left] != eating && state[right] != eating)
    {
        state[i] = hungry;
        sem_wait(&phil_sem[i]);
    }
}