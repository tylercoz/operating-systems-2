#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include "eventbuf.h"

// Globals
struct eventbuf *eb;


// sem_t *sem_open_temp(const char *name, int value) {
//   sem_t *sem;

//   // Create the semaphore
//   if ((sem = sem_open(name, O_CREAT, 0600, value)) == SEM_FAILED)
//     return SEM_FAILED;

//   // Unlink it so it will go away after this process exits
//   if (sem_unlink(name) == -1) {
//     sem_close(sem);
//     return SEM_FAILED;
//   }

//   return sem;
// }

void *produce(void *arg) {
  int *id = (int*)arg;
  printf("P:%d\n", *id);
  return NULL;
}

void *consume(void *id) {
  (void) id;
  return NULL;
}

int main(int argc, char *argv[]) {
  // Parse the command line
  if (argc < 5) {
    printf("Usage: %s <producer_count> <consumer_count> <event_count> <outstanding_count>\n", argv[0]);
    return 1;
  }
  int producer_count = atoi(argv[1]);
  int consumer_count = atoi(argv[2]);
  int event_count = atoi(argv[3]);
  int outstanding_count = atoi(argv[4]);
  (void) consumer_count;
  (void) event_count;
  (void) outstanding_count;
  // Create the event buffer
  eb = eventbuf_create();
  // Start the correct number of producer threads
    // Each thread will be passed a pointer to an int, its ID number
  pthread_t producers[producer_count];
  for (int i = 0; i < producer_count; i++) {
    pthread_create(&producers[i], NULL, produce, &i);
  }



  // Start the correct number of consumer threads
    // Each thread will be passed a pointer to an int, its ID number
  // Wait for all producer threads to complete
  // Notify all the consumer threads that they're done
    // This should cause them to exit
  // Wait for all consumer threads to complete
  // Free the event buffer
}
