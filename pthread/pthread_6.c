// 使用pthread_cancel杀死分离的线程
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>

void* myfunc(void* arg)
{
    printf("child pthread id: %lu\n", pthread_self());

    while (1) {
        printf("haha\n");
        sleep(2);
    }

    return NULL;

}

int main(int argc, const char* argv[])
{
    pthread_t thid;
    // 初始化线程属性
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    // 返回错误号
    int ret = pthread_create(&thid, &attr, myfunc, NULL);
    if (ret != 0)
    {
        printf("error number: %d\n", ret);
        // 根据错误号打印错误信息
        printf("error information: %s\n", strerror(ret));
    }
    printf("parent pthread id: %lu\n", pthread_self());

    pthread_cancel(thid);
    sleep(1);

    pthread_attr_destroy(&attr);
    pthread_exit(NULL);
    //return 0;
}
/*
parent pthread id: 140625550829376
child pthread id: 140625542567680
haha
*/