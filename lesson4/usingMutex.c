#include "pthread.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

static void* handleThread2(void* argv);
static void* handleThread1(void* argv);

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
int count = 2;

int main(int argc, char const* argv[])
{
    int ret;
    pthread_t thread_id1, thread_id2;
    if (ret = pthread_create(&thread_id1, NULL, &handleThread1, NULL)) {
        printf("Error, cannot create Thread_1\n");
        return -1;
    }

    if (ret = pthread_create(&thread_id2, NULL, &handleThread2, NULL)) {
        printf("Error, cannot create Thread_2\n");
        return -1;
    }

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    return 0;
}

static void* handleThread1(void* argv)
{
    pthread_mutex_lock(&lock1);
    for (int i = 0; i < 5; i++) {
        printf("Thread 1: %d\n", count++);
        sleep(1);
    }
    pthread_mutex_unlock(&lock1);
    pthread_exit(NULL);
}

static void* handleThread2(void* argv)
{
    pthread_mutex_lock(&lock1);
    printf("Thread 2: %d\n", count++);
    sleep(2);
    pthread_mutex_unlock(&lock1);
    pthread_exit(NULL);
}