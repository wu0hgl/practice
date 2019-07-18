#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>

#define MAX 100

// 全局变量
int number;

// 创建一把互斥锁
pthread_mutex_t mutex;

void *myfuncA(void *arg) {
    int i;
    for (i = 0; i < MAX; i++) {
        pthread_mutex_lock(&mutex);     // 加锁
        int cur = number;
        cur++;
        number = cur;
        printf("Thread_A, id = %ld, number = %d\n", pthread_self(), number);
        pthread_mutex_unlock(&mutex);   // 解锁
        usleep(10);                     // 为使线程A放弃cpu, 加sleep
    }

    return NULL;
}

void *myfuncB(void *arg) {
    int i;
    for (i = 0; i < MAX; i++) {
        pthread_mutex_lock(&mutex);     // 加锁
        int cur = number;
        cur++;
        number = cur;
        printf("Thread_B, id = %ld, number = %d\n", pthread_self(), number);
        pthread_mutex_unlock(&mutex);   // 解锁
        usleep(10);                     // 为使线程B放弃cpu, 加sleep
    }

    return NULL;
}

int main(void) {
    pthread_t p1, p2;

    // 初始化互斥锁
    pthread_mutex_init(&mutex, NULL);

    // 创建线程
    pthread_create(&p1, NULL, myfuncA, NULL);
    pthread_create(&p2, NULL, myfuncB, NULL);

    // 回收
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    // 销毁锁
    pthread_mutex_destroy(&mutex);
    return 0;
}