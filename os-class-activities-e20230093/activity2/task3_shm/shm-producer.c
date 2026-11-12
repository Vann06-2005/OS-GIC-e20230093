/* shm-producer.c — Writes to POSIX shared memory */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    /* Size of the shared memory region (in bytes) */
    const int SIZE = 4096;

    /* Name of the shared memory object (unique to me) */
    const char *name = "OS-sovannara";

    /* Messages to write */
    const char *message_0 = "Hello, ";
    const char *message_1 = "this is shared memory IPC!";

    int shm_fd;      /* Shared memory file descriptor */
    void *ptr;        /* Pointer to mapped memory */

    /* Create the shared memory object (or open if it already exists) */
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    /* Set the size of the shared memory region */
    if (ftruncate(shm_fd, SIZE) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    /* Map the shared memory into this process's address space */
    ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    /* Write messages to shared memory */
    sprintf(ptr, "%s", message_0);
    ptr += strlen(message_0);
    sprintf(ptr, "%s", message_1);
    ptr += strlen(message_1);

    printf("Producer: wrote to shared memory '%s'\n", name);
    printf("Producer: message = \"%s%s\"\n", message_0, message_1);

    return 0;
}
