// 测试一秒钟程序能数多少数字
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, const char *argv[]) {
    // 设置定时器
    alarm(1);
    int i = 0;
    while (1) {
        printf("%d\n", i++);
    }
    return 0;
}
/*
timer ./a.out 查看程序执行时间
real = 用户 + 内核 + 损耗
*/