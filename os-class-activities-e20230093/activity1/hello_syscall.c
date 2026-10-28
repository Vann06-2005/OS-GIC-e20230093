#include <unistd.h>
int main() {
    const char *message = "Hello, System Call!\n";
    write(1, message, 19); // 1 = terminal screen, 19 = number of bytes
    return 0;
}
