#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "pthread.h"

pthread_t thread_id1, thread_id2;

typedef struct{
    char name[30];
    char msg[30];
} thr_data_t;

static void *thrHandle1(void *args){
    pthread_t thr_id = pthread_self();
    thr_data_t *data = (thr_data_t *)args;

    if(pthread_equal(thr_id, thread_id1)){
        printf ("I'm thread 1!\n");
    }
    else{
        printf("I'm thread 2!\n");
        printf("Hello %s, welcome to join %s\n", data->name, data->msg);
    }
}

static void *thrHandle2(void *args){
    printf("======thrHandle2=======");
}

int main (int argc, char const *argv[]){
    int return_value;
    thr_data_t data = {0};

    strncpy(data.name, "DucLm", sizeof(data.name));
    strncpy(data.msg, "VNPT Technology", sizeof(data.msg));

    if(return_value = pthread_create(&thread_id1,NULL,&thrHandle1,NULL)){
        printf("Error, cannot create Thread_1\n");
        return -1;
    }
    sleep(2);
    

}