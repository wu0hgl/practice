// sigaction信号屏蔽
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

void myfunc(int nu) {
    printf("haha\n");
    sleep(3);
    printf("wake up\n");
}

int main(int argc, const char *argv[]) {
    struct sigaction act;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    // 添加临时屏蔽信号, 临时屏蔽
    sigaddset(&act.sa_mask, SIGQUIT);
    act.sa_handler = myfunc;
    sigaction(SIGINT, &act, NULL);

    while (1) {}

    return 0;
}

/*多次发送信号只捕捉一个
^Chaha
wake up
^C^C^C^C^C^C^C^C^Chaha
wake up
^\^\^\^\Quit (core dumped)
*/