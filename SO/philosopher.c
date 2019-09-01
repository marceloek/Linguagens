// gcc -o test1 philosopher.c -lpthread

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>

void *mythread(void *data);

#define N 5                     // numero de philosopher
#define thinking 0
#define hungry 1
#define eating 2

typedef int semaphore;
int state[N];                   // estados dos philosophers (comendo, pensando e com fome)

semaphore mutex = 1;
semaphore phil_sem[N];          // mutex de cada philosopher


int right(int i)
{
    int right_int = (i + 1) % N;
    printf("(philosopher right [%d])\n", right_int);
    return right_int;
}

int left(int i)
{
    int left_int = (i + N - 1) % N;
    printf("(philosopher left [%d])\n", right_int);
    return left_int;
}

void put_forks(int i)
{
    int left_int, right_int;
    sem_wait(&mutex);

    state[i] = thinking;

    right_int = right(i);
    left_int = left(i);
    test(left_int);
    test(right_int);

    sem_post(&mutex);
}

void test(int i)
{
    int right_int, left_int;
    right_int = right(i);
    left_int = left(i);
    if (state[i] == hungry && state[left_int] != eating && state[right_int] != eating)
    {
        state[i] = hungry;
        sem_wait(&phil_sem[i]);
    }
}


void take_forks(int i)
{
    printf("take forks 1, philo [%d]\n", i);
    sem_wait(&mutex);
    printf("take forks 2, philo [%d]\n", i);

    state[i] = hungry;
    test(i);

    sem_post(&mutex);
    printf("take forks 3, philo [%d]\n", i);

    sem_wait(&phil_sem[i]); //down semaphore philosopher
    printf("take forks 4, philo [%d]\n", i);
}

int main(void)
{
    int i = 0;

    for (i = 0; i < N; i++)
    {
        state[i] = 0;
        phil_sem[i] = 0;
    }

    pthread_t philosopher[N];

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
        sleep(2);

        take_forks(id);

        printf("filosofo [%d] esta comendo...\n\n", id);
        sleep(3);

        put_forks(id);
    }

    pthread_exit(NULL);
}