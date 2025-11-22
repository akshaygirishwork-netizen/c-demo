#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

// Union required for semctl()
union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main() {
    key_t key = ftok("semfile", 65);          // Unique key
    int semid = semget(key, 1, 0666 | IPC_CREAT); // Create semaphore

    union semun sem_union;
    sem_union.val = 1;                         // Initialize semaphore to 1
    semctl(semid, 0, SETVAL, sem_union);

    struct sembuf sb;

    printf("Process %d is trying to enter critical section...\n", getpid());

    // WAIT (P operation)
    sb.sem_num = 0;
    sb.sem_op = -1;   // decrement
    sb.sem_flg = 0;
    semop(semid, &sb, 1);  // wait until semaphore > 0

    // ---------- CRITICAL SECTION ----------
    printf("Process %d entered critical section\n", getpid());
    
    FILE *fp = fopen("shared.txt", "a");
    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }

    // Simple work: write numbers to the shared file
    for (int i = 1; i <= 5; i++) {
        fprintf(fp, "Process %d writing number %d\n", getpid(), i);
        fflush(fp);
        sleep(1); // simulate time-consuming work
    }

    fclose(fp);
    printf("Process %d leaving critical section\n", getpid());
    // --------------------------------------

    // SIGNAL (V operation)
    sb.sem_op = 1;    // increment semaphore (release)
    semop(semid, &sb, 1);

    return 0;
}
