// kill用法
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

int main(int argc, const char *argv[]) {
    pid_t pid = fork();
    if (pid > 0) {
        while (1) {
            printf("parent process, %d\n", getpid());
            sleep(1);
        }
    }
    // child process
    // 杀死父进程
    else if (pid == 0) {
        sleep(2);
        kill(getppid(), SIGKILL);
    }

    return 0;
}