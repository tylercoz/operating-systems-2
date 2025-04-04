#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

typedef struct {
  char *hello;
  char *goodbye;
} msgs;

void *run(void *arg) {
  msgs *messages = (msgs *)arg;

  printf("%s", messages->hello);
  printf("%s", messages->goodbye);

  return NULL;
}

int main(void) {
  pthread_t thread_id;

  printf("parent: hello\n");

  msgs messages;
  messages.hello = "child: hello\n";
  messages.goodbye = "child: goodbye\n";

  pthread_create(&thread_id, NULL, run, &messages);
  pthread_join(thread_id, NULL);

  printf("parent: goodbye\n");
}
