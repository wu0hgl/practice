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
        printf("parent, pid: %d\n, ppid: %d\n", getpid(), getppid());
    }
    
    printf("haha\n");

    return  0;
}

/*
[zyb@server fork]$ ./a.out 
haha
parent, pid: 25654
, ppid: 22642
haha
[zyb@server fork]$ child, pid: 25655, ppid: 1
haha

[zyb@server fork]$ 
*/