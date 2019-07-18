// 主线程先退出, 子线程正常执行
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>

void *myfunc(void *arg) {
    printf("child pthread id: %lu\n", pthread_self());
    printf("child thread .....\n");
    int i;
    for (i = 0; i < 3; i++)
        printf("child i = %d\n", i);

    //return NULL;
}

int main(void) {
    int i;
    pthread_t thid;
    int ret = pthread_create(&thid, NULL, myfunc, NULL);

    if (ret != 0) {
        printf("error number: %d\n", ret);
        printf("error information: %s\n", strerror(ret));
    }
    printf("parent pthread id: %lu\n", pthread_self());

    // 退出主线程, 子线程不受影响
    pthread_exit(NULL);

    printf("parent thread .....\n");
    for (i = 0; i < 3; i++)
        printf("i = %d\n", i);

    return 0;
}

/*
parent pthread id: 139948367210304
child pthread id: 139948358948608
child thread .....
child i = 0
child i = 1
child i = 2
*/