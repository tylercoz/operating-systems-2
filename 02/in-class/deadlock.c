#include <stdio.h>
#include <pthread.h>

#define ELEMENTS 50
#define THREADS 8

pthread_mutex_t lock_a = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock_b = PTHREAD_MUTEX_INITIALIZER;

int a[ELEMENTS] = {0};
int b[ELEMENTS] = {0};

void *run1(void *arg)
{
    (void)arg;

    for (int i = 0; i < ELEMENTS; i++) {
        pthread_mutex_lock(&lock_a);
        pthread_mutex_lock(&lock_b);
        a[i]++;
        pthread_mutex_unlock(&lock_b);
        pthread_mutex_unlock(&lock_a);
    }

    return NULL;
}

void *run2(void *arg)
{
    (void)arg;

    for (int i = 0; i < ELEMENTS; i++) {
        pthread_mutex_lock(&lock_a);
        pthread_mutex_lock(&lock_b);
        a[i]++;
        pthread_mutex_unlock(&lock_b);
        pthread_mutex_unlock(&lock_a);
    }

    return NULL;
}

int main(void)
{
    pthread_t t1;
    pthread_t t2;

    pthread_create(&t1, NULL, run1, NULL);
    pthread_create(&t2, NULL, run2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}
