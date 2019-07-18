// 查看管道缓冲区
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, const char* argv[]) {
    int fd[2];
    int ret = pipe(fd);
    if (ret == -1) {
        perror("pipe error");
        exit(1);
    }

    // 测试管道缓冲区大小
    long size = fpathconf(fd[0], _PC_PIPE_BUF);
    printf("size = %ld\n", size);

    printf("pipe[0] = %d \n", fd[0]);
    printf("pipe[1] = %d \n", fd[1]);

    close(fd[0]);
    close(fd[1]);

    return 0;
}
/*
size = 4096
pipe[0] = 3
pipe[1] = 4
*/