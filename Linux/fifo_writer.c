#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    const char *fifo = "/tmp/myfifo";
    char msg[100];

    // Create named pipe (if it doesn't exist)
    mkfifo(fifo, 0666);

    while (1) {
        printf("Enter message to send to another process: ");
        scanf("%99s", msg);  // avoid overflow

        int fd = open(fifo, O_WRONLY);
        if (fd == -1) {
            perror("open failed");
            exit(1);
        }

        write(fd, msg, strlen(msg) + 1);
        close(fd);

        if (strcmp(msg, "exit") == 0) {
            printf("Exiting writer...\n");
            break;
        }
    }

    return 0;
}

