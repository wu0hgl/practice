// setitimer使用
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>

int main(int argc, const char *argv[]) {
    // 设置定时器
    struct itimerval new_val;
    // 第一次触发的时间
    new_val.it_value.tv_sec = 2;
    new_val.it_value.tv_usec = 0;

    // 周期性定时
    new_val.it_interval.tv_sec = 1;
    new_val.it_interval.tv_usec = 0;

    // 倒计时2s
    setitimer(ITIMER_REAL, &new_val, NULL);
    while (1) {
        printf("haha\n");
    }

    return 0;
}