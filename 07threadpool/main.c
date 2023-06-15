#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
/*
pthread_cond_wait();
pthread_cond_signal();
线程 互斥锁 条件变量 任务队列
*/

// 表示队列节点的结构体
typedef struct Task
{
    void (*function)(void *arg); // 函数指针
    void *arg;                   // 参数
    struct Task *next;           // next指针
} Task;

// 表示线程池
typedef struct ThreadPool
{
    // 任务队列
    Task *queueFront; // 队头指针
    Task *queueRear;  // 队尾指针

    // 线程数量
    int num;

    // 线程号
    pthread_t *threadID;

    // 互斥锁和条件变量
    pthread_mutex_t mutex; // 互斥锁
    pthread_cond_t cond;   // 条件变量

    // 关闭线程的标志位
    int shutdown;

} ThreadPool;

// 线程处理函数
void *worker(void *arg)
{
    ThreadPool *pool = (ThreadPool *)arg;

    while (1)
    {
        pthread_mutex_lock(&pool->mutex); // 加锁

        // 如果任务队列为空且线程池没有被关闭 线程睡眠
        while ((pool->queueFront == pool->queueRear) && (pool->shutdown == 0))
        {
            pthread_cond_wait(&pool->cond, &pool->mutex); // 线程睡眠
        }

        // 如果线程池被关闭
        if (pool->shutdown == 1)
        {
            pthread_mutex_unlock(&pool->mutex);

            printf("线程池被关闭 线程【%ld】退出...\n", pthread_self());
            pthread_exit((void *)0);
        }

        // 从任务队列获取任务并执行
        Task task;

        Task *t = pool->queueFront->next;
        task.function = t->function;
        task.arg = t->arg;
        task.next = NULL;
        pool->queueFront->next = t->next;
        free(t);

        if (pool->queueFront->next == NULL)
        {
            pool->queueRear = pool->queueFront;
        }

        // 释放互斥锁
        pthread_mutex_unlock(&pool->mutex);

        // 执行任务
        printf("线程【%ld】开始工作...\n", pthread_self());
        task.function(task.arg); // 通过函数指针调用函数
        printf("线程【%ld】结束工作...\n", pthread_self());
    }
}
ThreadPool *create_thread_pool(int num)
{
    // 申请线程池结构体
    ThreadPool *pool = malloc(sizeof(ThreadPool));
    if (NULL == pool)
    {
        fprintf(stderr, "malloc ThreadPool failure\n");
        return NULL;
    }

    // 初始化任务队列
    pool->queueFront = malloc(sizeof(Task));
    if (NULL == pool->queueFront)
    {
        fprintf(stderr, "malloc pool->queueFront failure\n");
        free(pool);
        return NULL;
    }
    pool->queueRear = pool->queueFront;
    pool->queueFront->next = NULL; // 下一个节点为NULL

    // 初始化线程池数量
    pool->num = num;

    // 初始化线程号
    pool->threadID = malloc(sizeof(pthread_t) * num);
    if (NULL == pool->threadID)
    {
        fprintf(stderr, "malloc pool->threadID failure\n");
        free(pool->queueFront);
        free(pool);
        return NULL;
    }

    // 初始化线程
    int i = 0;
    for (i = 0; i < num; i++)
    {
        if (pthread_create(&pool->threadID[i], NULL, worker, pool) != 0)
        {
            fprintf(stderr, "pthread_create failure\n");
            free(pool->queueFront);
            free(pool->threadID);
            free(pool);
            return NULL;
        }

        pthread_detach(pool->threadID[i]); // 线程运行结束后 自动释放资源
    }

    // 初始化互斥锁和条件变量
    pthread_mutex_init(&pool->mutex, NULL);
    pthread_cond_init(&pool->cond, NULL);

    // 初始化标志位
    pool->shutdown = 0;
}

// 任务函数
void taskfunction(void *arg)
{
    int num = *(int *)arg;
    printf("线程【%ld】正在工作 num = %d...\n", pthread_self(), num);
    sleep(1);
    free(arg);
}
void thread_pool_add(ThreadPool *pool, void(func)(void *), void *arg)
{
    pthread_mutex_lock(&pool->mutex);
    // 进队操作
    Task *t = malloc(sizeof(Task));
    if (NULL == t)
    {
        fprintf(stderr, "malloc t failure\n");
        return;
    }

    t->function = func;
    t->arg = arg;
    t->next = NULL;

    pool->queueRear->next = t;
    pool->queueRear = t;

    pthread_mutex_unlock(&pool->mutex);

    pthread_cond_signal(&pool->cond);
}
void thread_pool_destory(ThreadPool *pool)
{
    // 关闭线程池
    pool->shutdown = 1;

    // 唤醒所有线程
    int i = 0;
    for (i = 0; i < pool->num; i++)
    {
        pthread_cond_signal(&pool->cond);
    }

    // 释放线程号
    if (pool->threadID)
    {
        free(pool->threadID);
    }

    // 释放任务队列
    while (pool->queueFront->next != NULL)
    {
        Task *t = pool->queueFront->next;
        pool->queueFront->next = t->next;

        free(t);
    }

    free(pool->queueFront);

    // 销毁互斥量和条件变量
    pthread_mutex_destroy(&pool->mutex);
    pthread_cond_destroy(&pool->cond);

    // 释放线程池结构体
    free(pool);
}
int main(int argc, char *argv[])
{
    ThreadPool *pool = create_thread_pool(3);
    if (NULL == pool)
    {
        return -1;
    }

    printf("线程池创建完成\n");
    sleep(1);

    // 主线程往任务队列中添加任务 并且唤醒线程池中的线程
    int i;
    for (i = 0; i < 50; i++)
    {
        int *n = malloc(sizeof(int));

        *n = i;

        // 把任务添加到任务队列
        thread_pool_add(pool, taskfunction, n);
    }
    sleep(6);

    thread_pool_destory(pool);
    return 0;
}
