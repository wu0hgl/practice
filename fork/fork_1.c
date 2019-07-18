#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int counter = 200;

int main(int argc, const char* argv[])
{
    int i;
    pid_t pid;
    for(i=0; i<5; ++i) {    // 通过i可区分进程
        pid = fork();
        if(pid == 0)        // 子进程跳出for循环
            break;
    }

    if(i<5) {
        counter += 300;
        printf(" child process , pid = %d,  ppid = %d\n", getpid(), getppid());
        printf("counter = %d, &counter = %p\n\n", counter, &counter);

    }
    else if(i == 5) {
        counter += 100;
        printf(" parent process, pid = %d, ppid = %d, &counter = %p\n", getpid(), getppid(), &counter);
        printf("counter = %d, &counter = %p\n\n", counter, &counter);
        sleep(1);
    }

    return 0;
}

/*
 child process , pid = 25474,  ppid = 25473
counter = 500, &counter = 0x60104c

 parent process, pid = 25473, ppid = 22642, &counter = 0x60104c
counter = 300, &counter = 0x60104c

 child process , pid = 25475,  ppid = 25473
counter = 500, &counter = 0x60104c

 child process , pid = 25476,  ppid = 25473
counter = 500, &counter = 0x60104c

 child process , pid = 25477,  ppid = 25473
counter = 500, &counter = 0x60104c

 child process , pid = 25478,  ppid = 25473
counter = 500, &counter = 0x60104c

*/