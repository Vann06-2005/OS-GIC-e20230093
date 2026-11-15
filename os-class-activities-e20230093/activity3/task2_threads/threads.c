/* threads.c — POSIX Threads demonstration */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 4

/* Shared counter (will demonstrate race condition) */
int shared_counter = 0;

/* Thread function — each thread increments the counter */
void *worker(void *arg) {
    int id = *(int *)arg;
    printf("Thread %d (TID: %lu): starting work...\n", id, (unsigned long)pthread_self());

    /* Simulate work */
    for (int i = 0; i < 100000; i++) {
        shared_counter++;  /* ⚠️ Race condition here! */
    }

    printf("Thread %d (TID: %lu): done.\n", id, (unsigned long)pthread_self());
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    printf("Main thread (TID: %lu): creating %d threads...\n",
           (unsigned long)pthread_self(), NUM_THREADS);
    printf("PID: %d — use this to observe threads with ps or htop\n\n", getpid());

    /* Create threads */
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, worker, &thread_ids[i]) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    /* Wait for all threads to finish */
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nAll threads completed.\n");
    printf("Expected counter value: %d\n", NUM_THREADS * 100000);
    printf("Actual counter value:   %d\n", shared_counter);

    if (shared_counter != NUM_THREADS * 100000) {
        printf("⚠️  Race condition detected! Counter is incorrect.\n");
        printf("This happens because multiple threads modify shared_counter simultaneously.\n");
    }

    return 0;
}
