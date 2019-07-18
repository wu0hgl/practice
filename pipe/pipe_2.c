// 读写先后顺序
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(void) {
    int fd[2];
    char buf[10];
    char p[] = "haha";

    int ret = pipe(fd);
    if (ret == -1) {
        perror("pipe error");
        exit(1);
    }

    printf("pipe[0] = %d\n", fd[0]);
    printf("pipe[1] = %d\n", fd[1]);

    // 先读, 阻塞, 因为写端没有关闭, 不会返回0
    //ret = read(fd[0], buf, sizeof(buf));

    write(fd[1], p, sizeof(p));

    // 后写, 没有被阻塞
    ret = read(fd[0], buf, sizeof(buf));

    printf("ret = %d, %s, sizeof(buf)=%d\n", ret, buf, sizeof(buf));

    close(fd[0]);
    close(fd[1]);

    return 0;
}
/*
pipe[0] = 3
pipe[1] = 4
ret = 5, haha, sizeof(buf)=10
*/