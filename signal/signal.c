#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

void myfunc(int nu) {
    printf("catch signal: %d", nu);
}

int main(int argc, const char *argv[]) {
    // 捕捉Ctrl + c
    signal(SIGINT, myfunc);

    while (1) {
        printf("haha\n");
        sleep(1);
    }

    return 0;
}