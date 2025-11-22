#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock;
pthread_cond_t cond;
int turn = 0; // 0 = number thread, 1 = letter thread

void* printNumbers(void* arg) {
    for (int i = 1; i <= 26; i++) {
        pthread_mutex_lock(&lock);

        // Wait until it's number thread's turn
        while (turn != 0)
            pthread_cond_wait(&cond, &lock);

        printf("%2d ", i);
        fflush(stdout);
        sleep(1);

        // Switch turn to letter thread
        turn = 1;
        pthread_cond_signal(&cond);

        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void* printLetters(void* arg) {
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        pthread_mutex_lock(&lock);

        // Wait until it's letter thread's turn
        while (turn != 1)
            pthread_cond_wait(&cond, &lock);

        printf("%c\n", ch);
        fflush(stdout);
        sleep(1);

        // Switch turn back to number thread
        turn = 0;
        pthread_cond_signal(&cond);

        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t tNum, tChar;

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&tNum, NULL, printNumbers, NULL);
    pthread_create(&tChar, NULL, printLetters, NULL);

    pthread_join(tNum, NULL);
    pthread_join(tChar, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return 0;
}
