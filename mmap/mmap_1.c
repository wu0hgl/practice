﻿// 利用内存映射区读文件
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(int argc, const char* argv[]) {
    // 打开一个文件
    int fd = open("english.txt", O_RDWR);
    int len = lseek(fd, 0, SEEK_END);
    // 创建内存映射区
    void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        perror("error");
        exit(1);
    }

    printf("%s", (char*)ptr);

    // 释放内存映射区
    munmap(ptr, len);
    close(fd);

    return 0;
}