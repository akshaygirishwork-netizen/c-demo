#define _GNU_SOURCE

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h>

// void bind_to_cpu0()
// {
//     cpu_set_t set;
//     CPU_ZERO(&set);
//     CPU_SET(0, &set);   // force to CPU 0

//     if (pthread_setaffinity_np(pthread_self(), sizeof(set), &set) != 0)
//         perror("pthread_setaffinity_np");
// }

void set_realtime(int prio)
{
    struct sched_param param = {0};
    param.sched_priority = prio;

    if (pthread_setschedparam(pthread_self(), SCHED_FIFO, &param) != 0)
        perror("pthread_setschedparam");
}

/* LOW priority thread */
void *low_thread(void *p)
{
    // bind_to_cpu0(); 
    set_realtime(40);

    while (1)
    {
        printf("LOW  thread running\n");
        usleep(500000);   // 0.5 sec
    }
}

/* MEDIUM priority thread */
void *medium_thread(void *p)
{
    // bind_to_cpu0(); 
    set_realtime(60);

    while (1)
    {
        printf("MEDIUM thread running\n");
        usleep(100000);
    }
}

/* HIGH priority thread */
void *high_thread(void *p)
{
    // bind_to_cpu0(); 
    set_realtime(80);

    while (1)
    {
        printf("HIGH thread running\n");
        usleep(100000);
    }
}

int main()
{
    pthread_t t1, t2, t3;

    pthread_create(&t3, NULL, high_thread, NULL);
    pthread_create(&t2, NULL, medium_thread, NULL);
    pthread_create(&t1, NULL, low_thread, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    return 0;
}
