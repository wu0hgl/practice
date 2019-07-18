// 3个线程不定时写同一全局资源, 5个线程不定时读同一全局资源
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>

int number = 0;

// 读写锁
pthread_rwlock_t lock;

void *write_func(void *arg) {
    while (1) {
        pthread_rwlock_wrlock(&lock);
        number++;
        printf("+++++write: %lu, %d\n", pthread_self(), number);
        pthread_rwlock_unlock(&lock);
        sleep(1);
    }
    return NULL;
}

void *read_func(void *arg) {
    while (1) {
        pthread_rwlock_rdlock(&lock);
        printf("======read: %lu, %d\n", pthread_self(), number);
        pthread_rwlock_unlock(&lock);
        sleep(1);
    }
    return NULL;
}

int main() {
    int i;
    pthread_t p[8];

    // 初始化读写锁
    pthread_rwlock_init(&lock, NULL);

    // 3个写线程
    for (i = 0; i < 3; i++) {
        pthread_create(&p[i], NULL, write_func, NULL);
    }

    // 5个读线程
    for (i = 3; i < 8; i++) {
        pthread_create(&p[i], NULL, read_func, NULL);
    }

    // 回收子线程
    for (i = 0; i < 8; i++) {
        pthread_join(p[i], NULL);
    }

    for (i = 0; i < 8; i++) {
        pthread_rwlock_destroy(&lock);
    }

    return 0;
}