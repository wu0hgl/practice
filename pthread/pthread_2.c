// 传值与传地址
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>

void *myfunc(void *arg) {
    //int num = *(int*)arg;
    int num = (int)arg;

    // 打印子线程ID
    printf("%dth child thread id: %lu\n", num, pthread_self());
}

int main(void) {
    pthread_t pthid[5];
    int i;

    for (i = 0; i < 5; i++) {
        //pthread_create(&pthid[i], NULL, myfunc, (void*)&i);
        // 由于int存储空间和指针的存储空间相同所以可以这么传 
        pthread_create(&pthid[i], NULL, myfunc, (void*)i);
    }
    printf("parent thread id: %lu", pthread_self());

    for (i = 0; i < 5; i++)         // 子线程不会执行接下来的for循环
        printf("i = %d\n", i);

    sleep(2);

    return 0;
}