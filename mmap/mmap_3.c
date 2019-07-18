// 有血缘关系匿名映射区通信
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
    // 创建匿名内存映射区
    int len = 4096;

    void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);      // MAP_SHARED可通信
    //void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);   // MAP_PRIVATE, 不可通信
    if (ptr == MAP_FAILED) {
        perror("error");
        exit(1);
    }

    //printf("%s", (char*)ptr);

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork error");
        exit(1);
    }
    if (pid > 0) {
        // 父进程写数据
        strcpy((char*)ptr, "haha");
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