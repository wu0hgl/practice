﻿// alarm用法
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, const char *argv[]) {
    int ret = alarm(5);
    printf("ret = %d\n", ret);

    sleep(2);
    // 重新设置定时器
    ret = alarm(2);
    printf("ret = %d\n", ret);

    while (1) {
        printf("Hello World\n");
        sleep(1);
    }

    return 0;
}