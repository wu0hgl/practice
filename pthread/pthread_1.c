// 输出顺序不确定
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>

void *myfunc(void * arg) {
    // 打印子线程ID
    printf("child thread id: %lud\n", pthread_self());
    return NULL;
}

int main(int argc, const char * argv[]) {
    // 创建一个子线程
    // 线程ID对应的变量
    pthread_t pthid;
    pthread_create(&pthid, NULL, myfunc, NULL);
    printf("parent thread id: %lud\n", pthread_self());

    for (int i = 0; i < 5; i++) {
        printf("i = %d\n", i);
    }

    sleep(2);

    return 0;
}