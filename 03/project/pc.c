#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#include "eventbuf.h"

// Globals
struct eventbuf *eb;
sem_t *queue_mutex;
sem_t *items;
sem_t *spaces;
int event_count;
int outstanding_count;

sem_t *sem_open_temp(const char *name, int value) {
  sem_t *sem;

  // Create the semaphore
  if ((sem = sem_open(name, O_CREAT, 0600, value)) == SEM_FAILED)
    return SEM_FAILED;

  // Unlink it so it will go away after this process exits
  if (sem_unlink(name) == -1) {
    sem_close(sem);
    return SEM_FAILED;
  }

  return sem;
}

int producer_event_number(int producer_number, int event_number) {
  return producer_number * 100 + event_number;
}

void *produce(void *args) {
  int *id = args;
  for (int i = 0; i < event_count; i++) {
    int event_number = producer_event_number(*id, i);
    printf("P%d: adding event %d\n", *id, event_number);
    eventbuf_add(eb, event_number);
  }
  return NULL;
}

void *consume(void *args) {
  int *id = args;
  printf("C%d: got event \n", *id);
  return NULL;
}

int main(int argc, char *argv[]) {
  //Initialize Globals
  queue_mutex = sem_open_temp("pc-program mutex semaphore" , 1);
  items       = sem_open_temp("pc-program items semaphore" , 0);
  spaces      = sem_open_temp("pc-program spaces semaphore", 0);
  eb = eventbuf_create();

  // Parse the command line
  if (argc < 5) {
    printf("Usage: %s <producer_count> <consumer_count> <event_count> <outstanding_count>\n", argv[0]);
    return 1;
  }
  int producer_count    = atoi(argv[1]);
  int consumer_count    = atoi(argv[2]);
      event_count       = atoi(argv[3]);
      outstanding_count = atoi(argv[4]);

  // Start the correct number of producer threads
    // Each thread will be passed a pointer to an int, its ID number
  pthread_t producers[producer_count];
  int producer_ids[producer_count];
  for (int i = 0; i < producer_count; ++i) {
    producer_ids[i] = i;
    pthread_create(&producers[i], NULL, produce, &producer_ids[i]);
  }

  // Start the correct number of consumer threads
    // Each thread will be passed a pointer to an int, its ID number
  pthread_t consumers[consumer_count];
  int consumer_ids[consumer_count];
  for (int i = 0; i < consumer_count; i++) {
    consumer_ids[i] = i;
    pthread_create(&consumers[i], NULL, consume, &consumer_ids[i]);
  }

  // Wait for all producer threads to complete
  for (int i = 0; i < producer_count; i++) {
    pthread_join(producers[i], NULL);
  }

  // TODO
  // Notify all the consumer threads that they're done
    // This should cause them to exit

  // Wait for all consumer threads to complete
  for (int i = 0; i < consumer_count; i++) {
    pthread_join(consumers[i], NULL);
  }

  // TODO
  // Free the event buffer
}
