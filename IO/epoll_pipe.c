// 基于管道, 边缘触发时父进程一次显示4个字符, 触发时一次显示全部字符
#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <errno.h>
#include <unistd.h>

#define MAXLINE 10

int main(int argc, const char *argv[]) {
    int i;
    char buf[MAXLINE], ch = 'a';

    int pfd[2];
    pipe(pfd);

    pid_t pid;
    pid = fork();

    if (pid == 0) {     // 子写
        close(pfd[0]);  // 关闭读管道
        while (1) {
            for (i = 0; i < MAXLINE / 2; i++)
                buf[i] = ch;
            buf[i - 1] = '\n';
            ch++;
            for (; i < MAXLINE; i++)
                buf[i] = ch;
            buf[i - 1] = '\n';
            ch++;
            write(pfd[1], buf, sizeof(buf));
            sleep(5);
        }
        close(pfd[1]);
    }
    else if (pid > 0) {     // 父读
        close(pfd[1]);
        int ret, len;

        int efd;
        efd = epoll_create(10);

        struct epoll_event event;
        // 一次只读4个字符
        event.events = EPOLLIN | EPOLLET;   // ET边沿触发
        // 一次读所有字符
        //event.events = EPOLLIN;             // 默认LT水平触发
        event.data.fd = pfd[0];
        epoll_ctl(efd, EPOLL_CTL_ADD, pfd[0], &event);

        struct epoll_event resevent[10];
        while (1) {
            ret = epoll_wait(efd, resevent, 10, -1);         // 阻塞
            printf("ret = %d\n", ret);
            if (resevent[0].data.fd == pfd[0]) {
                len = read(pfd[0], buf, MAXLINE / 2);
                write(STDOUT_FILENO, buf, len);
            }
        }
        close(pfd[0]);
        close(efd);
    }

    return 0;
}