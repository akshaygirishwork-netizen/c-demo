#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <string.h>

int main() {
    int id = semget(5, 2, IPC_CREAT | 0666); // 2 semaphores
    if (id < 0) { perror("semget"); return 1; }

    // Initialize semaphores (only first time)
    semctl(id, 0, SETVAL, 1); // Akshay starts first
    semctl(id, 1, SETVAL, 0); // Girish waits

    struct sembuf waitA = {0, -1, 0}; // wait on Akshay's turn
    struct sembuf signalG = {1, +1, 0}; // signal Girish

    int fd = open("data.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd < 0) { perror("open"); return 1; }

    char name[] = "Akshay";
    for (int i = 0; i < strlen(name); i++) {
        semop(id, &waitA, 1);     // wait for your turn
        write(fd, &name[i], 1);   // write one character
        printf("Akshay wrote: %c\n", name[i]);
        sleep(1);
        semop(id, &signalG, 1);   // signal Girish
    }

    close(fd);
    return 0;
}

