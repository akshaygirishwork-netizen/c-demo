#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock;
pthread_cond_t cond;

int num=1;

void *even(void *p) {

    while(1){
        pthread_mutex_lock(&lock);

        while(num%2 == 1 && num<=100)
            pthread_cond_wait(&cond,&lock);

        if(num>100){
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&lock);
            break;
        }

        printf("even:%d\n",num++);

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *odd(void *p) {
    while(1){
        pthread_mutex_lock(&lock);

        while(num%2 == 0 && num<=100)
            pthread_cond_wait(&cond,&lock);

        if(num>100){
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&lock);
            break;
        }

        printf(" odd:%d\n",num++);

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    char *p1, *p2;
    pthread_t t1, t2;

    pthread_mutex_init(&lock,NULL);
    pthread_cond_init(&cond,NULL);

    pthread_create(&t1, NULL, even, NULL);
    pthread_create(&t2, NULL, odd, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return 0;
}