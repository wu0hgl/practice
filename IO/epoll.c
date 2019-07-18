#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <errno.h>
#include <ctype.h>

#include "wrap.h"

#define MAXLINE     8192
#define SERV_PORT   8000
#define OPEN_MAX    5000

int main(int argc, const char *argv[]) {
    int i, ret;
    int n, num = 0;
    char buf[MAXLINE], str[OPEN_MAX];

    int connfd;

    struct sockaddr_in cliaddr;				// 客户端
    socklen_t clilen = sizeof(cliaddr);		// 客户端大小

    int listenfd;
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));   // 端口复用

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    Listen(listenfd, 20);

    ssize_t efd;
    efd = epoll_create(OPEN_MAX);
    if (efd == -1)
        perr_exit("epoll_create error");

    struct epoll_event tep;									// 创建epoll模型, efd指向红黑树根节点
    tep.events = EPOLLIN; tep.data.fd = listenfd;			// 将lfd的监听事件设置为读
    ret = epoll_ctl(efd, EPOLL_CTL_ADD, listenfd, &tep);	// 将lfd及对应的结构体设置到树上
    if (ret == -1)
        perr_exit("epoll_ctl");

    // 用于epoll_wait返回时的存储
    struct epoll_event ep[OPEN_MAX];
    ssize_t nready;
    int readfd;		// 存储返回事件集中的套接字描述符
    while (1) {
        nready = epoll_wait(efd, ep, OPEN_MAX, -1);     // 设置为阻塞监听
        if (nready == -1)
            perr_exit("epoll_wait error");

        for (i = 0; i < nready; i++) {
            if (!(ep[i].events & EPOLLIN))      // 不为读事件继续循环
                continue;

            if (ep[i].data.fd == listenfd) {    // 判断满足的事件是否为listenfd
                connfd = Accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);

                printf("received frome %s at port %d \n",
                    inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
                    ntohs(cliaddr.sin_port));
                printf("cfd %d----client %d\n", connfd, num++);

                tep.events = EPOLLIN; tep.data.fd = connfd;
                ret = epoll_ctl(efd, EPOLL_CTL_ADD, connfd, &tep);
                if (ret == -1)
                    perr_exit("epoll_ctl error");
            }
            else {
                readfd = ep[i].data.fd;
                n = read(readfd, buf, MAXLINE);

                if (n == 0) {
                    ret = epoll_ctl(efd, EPOLL_CTL_DEL, readfd, NULL);
                    if (ret == -1)
                        perr_exit("epoll_ctl error");
                    Close(readfd);
                    printf("client[%d] colsed connection\n", readfd);
                }
                else if (n < 0) {
                    perror("read n < 0 error: ");
                    ret = epoll_ctl(efd, EPOLL_CTL_DEL, readfd, NULL);
                    Close(readfd);
                }
                else {
                    for (i = 0; i < n; i++)
                        buf[i] = toupper(buf[i]);
                    Write(STDOUT_FILENO, buf, n);
                    Writen(readfd, buf, n);
                }
            }
        }
    }

    return 0;
}