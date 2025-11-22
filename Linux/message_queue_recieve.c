#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct student {
    int id;
    char name[50];
    float marks;
};

struct msgbuf {
    long mtype;
    struct student data;
};

int main() {
    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    struct msgbuf message;

    while (1) {
        msgrcv(msgid, &message, sizeof(message.data), 1, 0);

        if (message.data.id == 0) {
            printf("Exit message received. Closing receiver.\n");
            break;
        }

        printf("\nReceived Student Details:\n");
        printf("ID: %d\n", message.data.id);
        printf("Name: %s\n", message.data.name);
        printf("Marks: %.2f\n", message.data.marks);
    }

    msgctl(msgid, IPC_RMID, NULL); // remove the queue
    return 0;
}

