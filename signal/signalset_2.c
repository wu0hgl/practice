// 信号实时捕捉
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

int main(int argc, const char *argv[]) {
    // 手动屏蔽信号
    // 自定义信号集合
    sigset_t myset;
    // 清空集合
    sigemptyset(&myset);
    // 添加要阻塞的信号
    sigaddset(&myset, SIGINT);      // Ctrl + c
    sigaddset(&myset, SIGQUIT);     // Ctrl + 反斜杠
    sigaddset(&myset, SIGKILL);     // 实际没有被阻塞, 9号信号不能被阻塞

    // 把自定义信号集设置给内核
    sigprocmask(SIG_BLOCK, &myset, NULL);
    // 每隔1s读一次内存中的未决信号集
    while (1) {
        sigset_t pendset;
        sigpending(&pendset);
        // 1-31信号判断
        for (int i = 1; i < 32; ++i) {
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

/*可发送kill结束进程
0000000000000000000000000000000
^C0100000000000000000000000000000
0100000000000000000000000000000
^\0110000000000000000000000000000
0110000000000000000000000000000
[1]+  Killed                  ./a.out
Killed
*/