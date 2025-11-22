#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <string.h>

int main() {
    int id = semget(5, 2, IPC_CREAT | 0666); // same semaphore set
    if (id < 0) { perror("semget"); return 1; }

    struct sembuf waitG = {1, -1, 0}; // wait on Girish's turn
    struct sembuf signalA = {0, +1, 0}; // signal Akshay

    int fd = open("data.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd < 0) { perror("open"); return 1; }

    char name[] = "Girish";
    for (int i = 0; i < strlen(name); i++) {
        semop(id, &waitG, 1);     // wait for your turn
        write(fd, &name[i], 1);   // write one character
        printf("Girish wrote: %c\n", name[i]);
        sleep(1);
        semop(id, &signalA, 1);   // signal Akshay
    }

    close(fd);
    return 0;
}

