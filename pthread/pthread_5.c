// 当线程A数的数字还没有写入内存中时, 就已经失去cpu
// 当线程B数的数字同步到内存中时, 会导致共享的数据混乱 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>

#define MAX 1000
// 全局变量
int number;

// 线程处理函数
void* funcA_num(void* arg)
{
    for (int i = 0; i<MAX; ++i)
    {
        int cur = number;
        cur++;
        number = cur;
        printf("Thread A, id = %lu, number = %d\n", pthread_self(), number);
        usleep(10);
    }

    return NULL;
}

void* funcB_num(void* arg)
{
    for (int i = 0; i<MAX; ++i)
    {
        int cur = number;
        cur++;
        number = cur;
        printf("Thread B, id = %lu, number = %d\n", pthread_self(), number);
        usleep(10);
    }

    return NULL;
}

int main(int argc, const char* argv[])
{
    pthread_t p1, p2;

    // 创建两个子线程
    pthread_create(&p1, NULL, funcA_num, NULL);
    pthread_create(&p2, NULL, funcB_num, NULL);

    // 阻塞，资源回收
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    return 0;
}
/*
number可能数的数字不足
*/