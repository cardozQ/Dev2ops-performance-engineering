#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

pthread_mutex_t lock;

void *worker(void *arg) {
  int id = *(int *)arg;

  while (1) {
    printf("Thread %d waiting for resource...\n", id);

    pthread_mutex_lock(&lock);

    printf("Thread %d got access!\n", id);

    // Simulate slow resource usage
    sleep(3);

    pthread_mutex_unlock(&lock);

    usleep(100000);
  }

  return NULL;
}

int main() {
  pthread_t threads[4];
  int ids[4];

  pthread_mutex_init(&lock, NULL);

  for (int i = 0; i < 4; i++) {
    ids[i] = i;
    pthread_create(&threads[i], NULL, worker, &ids[i]);
  }

  for (int i = 0; i < 4; i++) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}
