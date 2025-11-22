#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread1(void *p) {
    int num=1;
    while(1){
        printf("%d\n",num);
        num=num+2;

        if(num>=100){
            pthread_exit("completed odd\n");
        }
    }
}

void *thread2(void *p) {
    int num=2;
    while(1){
        printf("%d\n",num);
        num=num+2;

        if(num>=100){
            pthread_exit("completed even\n");
        }
    }
}

int main() {
    char *p1, *p2;
    pthread_t t1, t2;

    pthread_create(&t1, NULL, thread1, "hello_t1");
    pthread_create(&t2, NULL, thread2, NULL);

    pthread_join(t1, (void**)&p1);
    pthread_join(t2, (void**)&p2);

    printf("After %s\n", p1);
    printf("After %s\n", p2);

    return 0;
}