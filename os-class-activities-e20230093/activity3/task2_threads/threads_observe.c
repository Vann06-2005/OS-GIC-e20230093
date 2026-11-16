/* threads_observe.c — Threads with sleep for observation */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 4

void *worker(void *arg) {
    int id = *(int *)arg;
    printf("Thread %d (TID: %lu): sleeping 600 seconds...\n", id, (unsigned long)pthread_self());
    sleep(600);  /* 60 in the template; longer so there is time for the screenshots */
    printf("Thread %d: done.\n", id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];
    printf("PID: %d — observe threads now!\n\n", getpid());

    for (int i = 0; i < NUM_THREADS; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, worker, &ids[i]);
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}
