#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    const char *fifo = "/tmp/myfifo";
    char buffer[100];

    // Create the FIFO if it doesn't exist
    mkfifo(fifo, 0666);

    while (1) {
        int fd = open(fifo, O_RDONLY);
        if (fd == -1) {
            perror("open failed");
            exit(1);
        }

        read(fd, buffer, sizeof(buffer));
        close(fd);

        printf("Received: %s\n", buffer);

        // Check for exit message
        if (strcmp(buffer, "exit") == 0) {
            printf("Exiting reader...\n");
            break;
        }
    }

    return 0;
}

