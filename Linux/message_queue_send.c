#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

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
    message.mtype = 1;

    while (1) {
        printf("Enter student ID (0 to exit): ");
        scanf("%d", &message.data.id);
        if (message.data.id == 0) break;

        printf("Enter name: ");
        scanf("%s", message.data.name);
        printf("Enter marks: ");
        scanf("%f", &message.data.marks);

        msgsnd(msgid, &message, sizeof(message.data), 0);
        printf("Data sent to queue.\n");
    }

    return 0;
}
