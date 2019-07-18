// 阻塞epoll, 服务端
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <unistd.h>

#define MAXLINE 10
#define SERV_PORT 9000

int main(void) {

    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN];

    int listenfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    listen(listenfd, 20);
    printf("Accepting connecting......\n");

    struct sockaddr_in cliaddr;
    socklen_t clilen = sizeof(cliaddr);
    int connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);
    printf("received from %s at port %d\n",
        inet_ntop(AF_INET, &cliaddr.sin_addr, str, sizeof(str)),
        ntohs(cliaddr.sin_port));

    int efd = epoll_create(10);

    struct epoll_event event;
    bzero(&event, sizeof(event));
    event.data.fd = connfd;
    event.events = EPOLLIN | EPOLLET;       // 边缘触发
    //event.events = EPOLLIN;                 // 水平触发
    epoll_ctl(efd, EPOLL_CTL_ADD, connfd, &event);

    struct epoll_event resevent[10];

    int res;
    while (1) {
        res = epoll_wait(efd, resevent, 10, -1);

        printf("res %d \n", res);
        if (resevent[0].data.fd == connfd) {
            int len = read(connfd, buf, MAXLINE / 2);
            write(STDOUT_FILENO, buf, len);
        }
    }


    return 0;
}

/*
[zyb@server block_epoll]$ ./server
Accepting connecting......
received from 127.0.0.1 at port 52464
epoll_wait begin
epoll_wait end
res 1
aaaa
epoll_wait begin
epoll_wait end
res 1
bbbb
epoll_wait begin
epoll_wait end
res 1
cccc
epoll_wait begin
^C
[zyb@server block_epoll]$
*/