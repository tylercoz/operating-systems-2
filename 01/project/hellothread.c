#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *run(void *arg) {
  int *thread_number = arg;
  printf("thread %d: 0\n", *thread_number);
  printf("thread %d: 1\n", *thread_number);
  // On my machine, it will print the first thread and then the second,
  // which qustions whether the threads are concurrent
  // the sleep shows that the threads are indeed concurrent.
  usleep(10000);
  printf("thread %d: 2\n", *thread_number);
  printf("thread %d: 3\n", *thread_number);
  printf("thread %d: 4\n", *thread_number);
  return NULL;
}

int main() {
  printf("launching threads\n");
  pthread_t t1;
  pthread_t t2;
  pthread_create(&t1, NULL, run, &(int){1});
  pthread_create(&t2, NULL, run, &(int){2});
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  printf("Threads complete!\n");
}
