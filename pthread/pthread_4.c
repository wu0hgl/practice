#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>

/*
    join与pthread_exit
    没有return返回和return NULL结果一样都是core dumped
    使用return &number和pthread_exit(&number)时, 主线程的pthread_join(thid, (void**)&ptr);都可以收到number的值
*/

int number = 100;

void *myfunc(void *arg) {
    printf("child pthread id: %lu\n", pthread_self());
    printf("child thread .....\n");
    number++;
    int i;
    for (i = 0; i < 3; i++)
        printf("child i = %d\n", i);

    // return NULL;     // Segmentation fault (core dumped)
    //return &number;
    pthread_exit(&number);
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

    int *ptr;
    // 阻塞等待子线程的结束, 并回收pcb
    pthread_join(thid, (void**)&ptr);
    printf("++++++ number = %d\n", *ptr);

    printf("parent thread .....\n");
    for (i = 0; i < 3; i++)
        printf("i = %d\n", i);

    return 0;
}

/*
parent pthread id: 139819023099712
child pthread id: 139819014838016
child thread .....
child i = 0
child i = 1
child i = 2
++++++ number = 101
parent thread .....
i = 0
i = 1
i = 2

*/