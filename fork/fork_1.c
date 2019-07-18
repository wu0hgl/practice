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