#include <fcntl.h>
#include <unistd.h>
int main() {
    char buffer[1024];
    ssize_t bytesRead;
    // 1. Open source file for reading
    int src = open("result.txt", O_RDONLY);
    if (src < 0) {
        const char *err = "Error: cannot open result.txt\n";
        write(2, err, 30);  // 2 = stderr
        return 1;
    }
    // 2. Open/create destination file (0644 = rw-r--r--)
    int dst = open("copyresult.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dst < 0) {
        const char *err = "Error: cannot create copyresult.txt\n";
        write(2, err, 36);
        close(src);
        return 1;
    }
    // 3. Read from source and write to destination in chunks
    while ((bytesRead = read(src, buffer, sizeof(buffer))) > 0) {
        write(dst, buffer, bytesRead);
    }
    // 4. Close both file descriptors
    close(src);
    close(dst);
    const char *msg = "File copied successfully!\n";
    write(1, msg, 26);
    return 0;
}
