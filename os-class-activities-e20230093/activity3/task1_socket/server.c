/* server.c — Simple TCP server */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9093  /* 8080 in the template; changed because the server is shared */
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *response = "Hello from server!";

    /* 1. Create socket */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    printf("Server: socket created (fd=%d)\n", server_fd);

    /* Allow port reuse (avoids "Address already in use" error) */
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    /* 2. Bind to address */
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;  /* Listen on all interfaces */
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Server: bound to port %d\n", PORT);

    /* 3. Listen for connections */
    if (listen(server_fd, 1) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Server: listening... waiting for a client to connect.\n");

    /* 4. Accept a connection */
    client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    if (client_fd < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Server: client connected!\n");

    /* 5. Receive message from client */
    int bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        printf("Server: received from client: \"%s\"\n", buffer);
    }

    /* 6. Send response to client */
    send(client_fd, response, strlen(response), 0);
    printf("Server: sent response: \"%s\"\n", response);

    /* 7. Close sockets */
    close(client_fd);
    close(server_fd);
    printf("Server: connection closed.\n");

    return 0;
}
