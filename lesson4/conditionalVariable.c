#include "pthread.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

#define THRESH_HOLD 2
#define TEMP 6

void waitToDo();
int count = 0;
int trigger = 0;

static void* handleThread1(void* argv);
static void* handleThread2(void* argv);
static void* handleThread3(void* argv);

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
pthread_cond_t condition2 = PTHREAD_COND_INITIALIZER;

int main(int argc, char* const argv[])
{
    int ret;
    pthread_t thread_id1, thread_id2, thread_id3;
    if (ret = pthread_create(&thread_id3, NULL, &handleThread3, NULL)) {
        printf("Error, cannot create Thread_3\n");
        return -1;
    }
    sleep(1);
    if (ret = pthread_create(&thread_id2, NULL, &handleThread2, NULL)) {
        printf("Error, cannot create Thread_2\n");
        return -1;
    }
    sleep(1);
    if (ret = pthread_create(&thread_id1, NULL, &handleThread1, NULL)) {
        printf("Error, cannot create Thread_1\n");
        return -1;
    }

    // pthread_mutex_lock(&lock);
    // waitToDo();
    // pthread_mutex_unlock(&lock);
    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    pthread_join(thread_id3, NULL);
    return 0;
}

static void* handleThread1(void* argv)
{
    printf("inside 1\n");
    pthread_mutex_lock(&lock);
    while (count < THRESH_HOLD) {
        count++;
        printf("[1] count's value = %d\n", count);
        sleep(1);
    }

    pthread_cond_signal(&condition2);
    // pthread_cond_signal(&condition2);
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

static void* handleThread2(void* argv)
{
    printf("inside 2\n");
    // pthread_mutex_lock(&lock);
    pthread_cond_wait(&condition2, &lock);

    for (int i = 1; i < 3; i++) {
        printf("[2] Thread 2 is running! with: %d times\n", i);
        trigger = 5;
        sleep(1);
    }
    pthread_cond_signal(&condition);
    sleep(1);
    // pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

static void* handleThread3(void* argv)
{
    printf("inside 3\n");
    pthread_mutex_lock(&lock);
    pthread_cond_wait(&condition, &lock);
    printf("...");
    while (1) {
        if (trigger == 5) {
            printf("[3] Thread 3 is running!\n");
            break;
        }
    }
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

void waitToDo()
{
    while (1) {
        pthread_cond_wait(&condition, &lock);
        if (count == THRESH_HOLD) {
            printf("Global variable count = %d ...\n", count);
            // pthread_cond_signal(&condition2);
            break;
        }
    }
}
