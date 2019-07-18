#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(void) {
    pid_t pid;

    printf("haha\n");

    pid = fork();
    if (pid < 0) {
        perror("fork error");
        exit(1);
    }
    else if (pid == 0) {
            printf("child, pid: %d, ppid: %d\n", getpid(), getppid());
            sleep(1);
    }
    else {
        while (1) {
            printf("parent, pid: %d\n, ppid: %d\n", getpid(), getppid());
            sleep(5);
        }
    }
    
    printf("haha");

    return  0;
}

/*
[zyb@server ~]$ ps aux | grep "a.out"
zyb       27627  0.0  0.0   4212   344 pts/0    S+   22:50   0:00 ./a.out
zyb       27628  0.0  0.0      0     0 pts/0    Z+   22:50   0:00 [a.out] <defunct>
zyb       27630  0.0  0.0 112704   968 pts/1    S+   22:50   0:00 grep --color=auto a.out
*/