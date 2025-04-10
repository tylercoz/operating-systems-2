# Challenge: Fix the deadlock

Compile the attached program, called `deadlock.c`.

Run it several times. Does it ever freeze up?

Here's a bash oneliner that will attempt to run it 100 times in a row if
you want to make your life easier:

```
for i in $(seq 100); do echo "running"; ./deadlock; done
```

Why is it freezing?

Modify the code to prevent the deadlock.

```
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
        pthread_mutex_lock(&lock_b);
        pthread_mutex_lock(&lock_a);
        a[i]++;
        pthread_mutex_unlock(&lock_b);
        pthread_mutex_unlock(&lock_a);
    }

    return NULL;
}

int main(void)
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, run1, NULL);
    pthread_create(&t2, NULL, run2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}
```

## What to turn in

* A step-by-step description of which lines of code the two threads must
  execute in which order for deadlock to occur.

thread 1: locks a
thread 2: locks b
thread 1: waits for lock a to be released
thread 2: waits for lock b to be released

* A one line description of what you did to fix the deadlock.

change locks to always be acquired in the same order and release in the opposite order.
