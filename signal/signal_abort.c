// abort用法
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, const char *argv[]) {
    pid_t pid = fork();
    if (pid > 0) {
        // 父进程, 回收子进程资源
        int s;
        pid_t wpid = wait(&s);
        printf("child died pid = %d\n", wpid);
        if (WIFSIGNALED(s)) {
            printf("die by signal: %d \n", WTERMSIG(s));
        }
    }
    else if (pid == 0) {
        // 自己给自己发送信号
        //raise(SIGINT);
        while (1) {
            abort();
        }
    }

    return 0;
}

/*
child died pid = 12779
die by signal: 6
*/