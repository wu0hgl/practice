﻿// MAP_PRIVATE与MAP_SHARED测试
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, const char* argv[]) {
    // 打开一个文件
    int fd = open("english.txt", O_RDWR);
    int len = lseek(fd, 0, SEEK_END);

    // 通信测试
    void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);    // MAP_PRIVATE, 父子进程不可通信
    //void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);   // MAP_SHARED, 父子进程可通信
    if (ptr == MAP_FAILED) {
        perror("error");
        exit(1);
    }
    close(fd);

    //printf("%s", (char*)ptr);

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork error");
        exit(1);
    }
    if (pid > 0) {
        // 父进程写数据
        strcpy((char*)ptr, "haha, hehe");
        // 回收
        wait(NULL);
    }
    else if (pid == 0) {
        // 读数据
        printf("%s\n", (char*)ptr);
    }

    // 释放内存映射区
    //ptr++;
    int ret = munmap(ptr, len);
    if (ret == -1) {
        perror("mmap error");
        exit(1);
    }

    return 0;
}
