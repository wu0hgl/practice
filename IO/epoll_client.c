// 客户端固定一次发送10个字符
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define MAXLINE     10
#define SERV_PORT   9000

int main(int argc, const char *argv[]) {
    int i;
    char buf[MAXLINE];
    char ch = 'a';

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
    servaddr.sin_port = htons(SERV_PORT);

    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    while (1) {
        for (i = 0; i < MAXLINE / 2; i++)
            buf[i] = ch;
        buf[i - 1] = '\n';
        ch++;
        for (; i < MAXLINE; i++)
            buf[i] = ch;
        buf[i - 1] = '\n';
        ch++;
        write(sockfd, buf, sizeof(buf));
        sleep(5);
    }
    close(sockfd);

    return 0;
}