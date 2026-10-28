#include <fcntl.h>    // open(), O_WRONLY, O_CREAT, O_TRUNC
#include <unistd.h>   // write(), close()
#include <string.h>   // strlen()
int main() {
    // 1. Open/create "output.txt" with 0644 permissions (rw-r--r--)
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        const char *err = "Error opening file\n";
        write(2, err, strlen(err)); // fd 2 = stderr
        return 1;
    }
    // 2. Write the message into the file
    const char *text = "Hello from Operating Systems class!\n";
    write(fd, text, strlen(text));
    // 3. Close the file
    close(fd);
    // 4. Print confirmation to the terminal screen (fd 1 = stdout)
    const char *msg = "File created successfully!\n";
    write(1, msg, strlen(msg));
    return 0;
}
