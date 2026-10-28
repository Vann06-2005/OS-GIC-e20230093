#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

int main() {
    char buffer[512];

    // 1. Open current directory
    DIR *dir = opendir(".");
    if (dir == NULL) {
        const char *err = "Error opening directory\n";
        write(2, err, strlen(err));
        return 1;
    }

    // 2. Print header line using write() to stdout (fd 1)
    const char *header = "Filename                       Size (bytes)\n------------------------------ ----------\n";
    write(1, header, strlen(header));

    struct dirent *entry;
    struct stat fileStat;

    // 3. Loop through entries
    while ((entry = readdir(dir)) != NULL) {
        if (stat(entry->d_name, &fileStat) == 0) {
            // 4. Format numbers into ASCII text in buffer, then write to stdout
            int len = snprintf(buffer, sizeof(buffer), "%-30s %10ld\n", entry->d_name, fileStat.st_size);
            if (len > 0) {
                write(1, buffer, len);
            }
        }
    }

    // 5. Close directory
    closedir(dir);
    return 0;
}
