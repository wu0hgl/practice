// 查看内核中的未决信号集
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

int main(int argc, const char *argv[]) {
    // 每隔1s读一次内存中的未决信号集
    while (1) {
        sigset_t pendset;
        sigpending(&pendset);
        // 1-31信号判断
        int i = 0;
        for (i = 1; i < 32; ++i) {
            if (sigismember(&pendset, i)) {
                printf("1");
            }
            else {
                printf("0");
            }
        }
        printf("\n");
        sleep(1);
    }
    return 0;
}