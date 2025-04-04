#include <pthread.h>
#include <stdio.h>

void *run(void *arg) {
  printf("child: hello\n");
  printf("child: goodbye\n");
  return arg;
}

int main(void) {
  pthread_t thread_id;

  printf("parent: hello\n");
  pthread_create(&thread_id, NULL, run, NULL);
  pthread_join(thread_id, NULL);
  printf("parent: goodbye\n");
}
