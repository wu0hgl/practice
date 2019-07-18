#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        printf("./a.out, fifoname\n");
        exit(1);
    }

    int ret = access(argv[1], F_OK);    // 判断文件是否存在
    if (ret == -1) {
        int r = mkfifo(argv[1], 0664);  // 创建fifo
        if (r == -1) {
            perror("mkfifo error");
            exit(1);
        }
        printf("有名管道%s创建成功\n", argv[1]);
    }

    int fd = open(argv[1], O_WRONLY);
    if (fd == -1) {
        perror("open error");
        exit(1);
    }

    char *p = "haha";
    while (1) {
        //int len = write(fd, p, sizeof(p));    // 好像和编码方式有关
        int len = write(fd, p, strlen(p) + 1);
        printf("write: %s\nlen = %d\n", p, len);
        sleep(1);
    }

    close(fd);

    return 0;
}