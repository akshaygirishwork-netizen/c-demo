#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

int main() {
    struct sembuf lock = {0, -1, 0};   // P operation (lock)
    struct sembuf unlock = {0, 1, 0};  // V operation (unlock)
    int id;
    char name[] = "Girish\n";

    // Attach to the same semaphore
    id = semget(5, 1, IPC_CREAT | 0644);
    if (id < 0) {
        perror("semget");
        return 1;
    }

    int fd = open("data.txt", O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    printf("Process 2 waiting for lock...\n");
    semop(id, &lock, 1);   // Lock

    printf("Process 2 writing...\n");
    for (int i = 0; name[i]; i++) {
        write(fd, &name[i], 1);
        sleep(1);
    }

    semop(id, &unlock, 1); // Unlock
    printf("Process 2 done.\n");

    close(fd);
    return 0;
}
