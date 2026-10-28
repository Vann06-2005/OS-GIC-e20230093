#include <fcntl.h>
#include <unistd.h>

int main() {
    // 1. Open "output.txt" for reading
    int fd = open("output.txt", O_RDONLY);
    if (fd < 0) {
        write(2, "Error opening file\n", 19);
        return 1;
    }

    // 2. Read in chunks and write directly to stdout (fd 1)
    char buffer[256];
    ssize_t bytesRead;
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        write(1, buffer, bytesRead);
    }

    // 3. Close the file descriptor
    close(fd);
    return 0;
}
