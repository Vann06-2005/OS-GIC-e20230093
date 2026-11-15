/* client.c — Simple TCP client */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9093  /* must match server.c */
#define BUFFER_SIZE 1024

int main() {
    int sock_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE] = {0};
    const char *message = "Hello from client!";

    /* 1. Create socket */
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    printf("Client: socket created\n");

    /* 2. Set server address */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    /* Convert "127.0.0.1" (localhost) to binary form */
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("inet_pton");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    /* 3. Connect to server */
    printf("Client: connecting to server on port %d...\n", PORT);
    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }
    printf("Client: connected!\n");

    /* 4. Send message to server */
    send(sock_fd, message, strlen(message), 0);
    printf("Client: sent message: \"%s\"\n", message);

    /* 5. Receive response from server */
    int bytes_read = read(sock_fd, buffer, BUFFER_SIZE - 1);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        printf("Client: received from server: \"%s\"\n", buffer);
    }

    /* 6. Close socket */
    close(sock_fd);
    printf("Client: connection closed.\n");

    return 0;
}
