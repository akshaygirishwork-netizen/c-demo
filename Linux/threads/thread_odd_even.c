#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <syscall.h>
#include <time.h>
#include <sched.h>

pthread_mutex_t lock;
pthread_cond_t cond;
struct timespec ts;

int num=1;

void set_realtime(int prio){
    struct sched_param param = {0};
    param.sched_priority=prio;

    if (pthread_setschedparam(pthread_self(), SCHED_FIFO, &param) != 0)
        perror("pthread_setschedparam");
}

int isprime(int num){

    if(num<=1){
        return 0;
    }
    for(int i=2;i*i<=num;i++){
        if(num%i == 0){
            return 0;
        }
    }
    return 1;
}

int isPowOfTo(int num){

    if((num&num-1)==0){
        return 1;
    }
    return 0;

}

void *even(void *p) {
    set_realtime(40);
    while(1){
        sleep(1);
        pthread_mutex_lock(&lock);

        while(((num%2 == 1) || isprime(num)) && num<=100)
            pthread_cond_wait(&cond,&lock);

        if(num>100){
            pthread_cond_broadcast(&cond);
            pthread_mutex_unlock(&lock);
            break;
        }
        printf("even:  [%d]\n", num++);

        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *odd(void *p) {
    set_realtime(60);
    while(1){
        sleep(1);
        pthread_mutex_lock(&lock);

        while(((num%2 == 0) || isprime(num)) && num<=100)
            pthread_cond_wait(&cond,&lock);

        if(num>100){
            pthread_cond_broadcast(&cond);
            pthread_mutex_unlock(&lock);
            break;
        }
        printf("odd:   [%d]\n", num++);

        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void* prime(void*p){
    set_realtime(80);

    while(1){
        sleep(1);
        pthread_mutex_lock(&lock);

        while(num <= 100 && !isprime(num))
            pthread_cond_wait(&cond,&lock);
        
        if(num>100){
            pthread_cond_broadcast(&cond);
            pthread_mutex_unlock(&lock);
            break;
        }

        printf("prime: [%d]\n",num++);
        
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&lock);

    }
    return NULL; 
}

void* powerOftwo(void*){

    while(1){
        sleep(1);
        pthread_mutex_lock(&lock);

        while(num<=100 && (num%2==1) || num%2 == 0 )
    }

}

int main() {
    pthread_t t1, t2 ,t3;

    pthread_mutex_init(&lock,NULL);
    pthread_cond_init(&cond,NULL);

    pthread_create(&t1, NULL, even, NULL);
    pthread_create(&t2, NULL, odd, NULL);
    pthread_create(&t3,NULL,prime,NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return 0;
}