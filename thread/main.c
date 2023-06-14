#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>

#include <pthread.h>

void printids(const char *s)
{
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();
    printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long)pid,
           (unsigned long)tid, (unsigned long)tid);
}

void *thr_fn(void *arg)
{
    int tmp = *(int *)arg;
    printf("tmp = %d\n",tmp);
    printf("----enter sub thread--------\n");
    printids("new thread: ");
    printf("----Change to C++ code!!------\n");
    printf("----exit from sub thread----\n");

    return ((void *)0);
}

int main(void)
{
    int err;
    int num = 123;

    pthread_t ntid;
    // 第四个参数为NULL，说明没有向线程函数传参数。
    err = pthread_create(&ntid, NULL, thr_fn, &num);
    if (err != 0)
    {
        perror("can't create thread");
    }
    printids("main thread:");
    sleep(1);
    exit(0);
}
