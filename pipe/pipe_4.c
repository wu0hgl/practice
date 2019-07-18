// 兄弟进程间通信, 父进程用于回收子进程
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, const char* argv[]) {
    int fd[2];
    int ret = pipe(fd);
    if (ret == -1) {
        perror("pipe error");
        exit(1);
    }

    int i = 0;
    for (i = 0; i < 2; i++) {
        pid_t pid = fork();
        if (pid == 0)
            break;
        if (pid == -1) {
            perror("fork error");
            exit(1);
        }
    }

    // 子进程1: ps -aux
    if (i == 0) {
        // 写管道操作, 关闭读端
        close(fd[0]);
        // 文件描述符重定向, STDOUT_FILENO, 
        dup2(fd[1], STDOUT_FILENO);
        // 执行ps aux
        execlp("ps", "ps", "aux", NULL);
        perror("excelp");
        exit(1);
    }
    // 子进程2: grep "bash"
    else if (i == 1) {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        execlp("grep", "grep", "bash", "--color=auto", NULL);
    }
    // 父进程回收子进程
    else if (i == 2) {
        close(fd[0]);
        close(fd[1]);
        wait(NULL);
        // 回收子进程
        pid_t wpid;
        while ((wpid = waitpid(-1, NULL, WNOHANG)) != -1) {
            if (wpid == 0)
                continue;
            printf("child die pid = %d\n", wpid);
        }
    }

    printf("pipe[0] = %d \n", fd[0]);
    printf("pipe[1] = %d \n", fd[1]);

    return 0;
}
/*
root      2208  0.0  0.0  22912  1048 ?        S    Jul14   0:00 /bin/bash /usr/bin/mysqld_safe
zyb       3549  0.0  0.0  24372  1024 pts/13   Ss   Jul14   0:00 bash
zyb       5961  0.0  0.1  24404  4836 pts/22   Ss   15:02   0:00 /bin/bash
zyb       5971  0.0  0.0  14372  2900 pts/22   S+   15:02   0:00 /bin/bash ./bler.sh
zyb       7837  0.0  0.1  24492  5480 pts/8    Ss   18:28   0:00 -bash
zyb       9777  0.0  0.0  15932   928 pts/8    S+   22:43   0:00 grep bash --color=auto
child die pid = 9777
pipe[0] = 3
pipe[1] = 4
*/