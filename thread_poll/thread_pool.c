/**
 * (C) 2007-2019 Alibaba Group Holding Limited
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Version: 1.0: thread_pool.c 08/03/2019 $
 *
 * Authors:
 *   qianyi.lh <qianyi.lh@alibaba-inc.com>
 */

#include "thread_pool.h"

#include <pthread.h>
#include <stdlib.h>

#include "queue.h"


typedef struct ThreadPool {
    Queue *queue;
    pthread_t *threads;//存储线程号的地址，create的时候就不用加&了
    pthread_mutex_t mutex;//互斥量
    pthread_cond_t cond;//条件变量
    size_t thread_count;//线程池中的线程数？
    int is_start;
} ThreadPool;//Threadpool类型的定义

typedef struct Task {
    void (*callback)(void *);//定义了一个返回值为void的函数指针，名叫callback,这个函数的参数为void *
    void *args;//一个不确定指向类型的函数指针
} Task;

void *threadStart(void *args) {
    ThreadPool *pool = (ThreadPool *)args;//将传递进来的参数强制类型转化为Threadpool类型的指针
    while (pool->is_start) {//说明线程池中已经有线程了
        pthread_mutex_lock(&pool->mutex);//加锁后，去判断任务队列中有没有任务
        while (QueueSize(pool->queue) < 1 && pool->is_start) {
            pthread_cond_wait(&pool->cond, &pool->mutex);
        }
        Task *task = (Task *)QueuePop(pool->queue);
        pthread_mutex_unlock(&pool->mutex);
        if (task && task->callback) {
            task->callback(task->args);//这步操作太骚了！！！！牛皮
            free(task);
        }
    }

    return NULL;
}

ThreadPool *ThreadPoolInit(size_t thread_count)//参数为线程池中线程的个数
{
    ThreadPool *pool = (ThreadPool *)malloc(sizeof(ThreadPool));//结构体指针初始化
    pool->queue = QueueInit();
    pool->threads = (pthread_t *)malloc(sizeof(pthread_t) * thread_count);//初始化一下这个指向pthrea_t类型的指针
    pool->thread_count = thread_count;//线程池中线程的数目
    pthread_mutex_init(&pool->mutex, NULL);//互斥量的动态初始化
    pthread_cond_init(&pool->cond, NULL);//条件变量的静态初始化
    pool->is_start = 0;
<<<<<<< HEAD
    return pool;//1111111111111111111111111
=======

    return pool;
>>>>>>> 9360e130839ceb44bf8ea9340981f2ec28f0006b
}

void ThreadPoolDestroy(ThreadPool *pool)
{
    ThreadPoolStop(pool);//is_start在上一步已经被变为0了啊，这一步有什么意义？
    pthread_cond_broadcast(&pool->cond);//唤醒所有正在等待任务队列中任务的线程
    //醒来吧，兄弟们
    int i;
    for (i = 0; i < pool->thread_count; ++i) {
        pthread_join(pool->threads[i], NULL);//将苏醒（从阻塞状态退出的）的线程
        //全部join
        //将线程池中的所有线程都给干掉了
    }
    QueueDestroy(pool->queue, free);
    pthread_mutex_destroy(&pool->mutex);//之所以先把所有的线程都干掉以后才销毁互斥量是因为保证了互斥量的安全销毁
    //即保证了后续没有任何线程企图锁定该互斥量
    pthread_cond_destroy(&pool->cond);//同前
}

void ThreadPoolStart(ThreadPool *pool)//给线程池中创建足够我想要的线程数，在这里是4
{
    if (pool->is_start) {
        return;//只有当pool->is_start为0时才不返回
    }
    pool->is_start = 1;
    int i;
    for (i = 0; i < pool->thread_count; ++i) {
        pthread_create(&(pool->threads[i]), NULL, threadStart, (void *)pool);
    }//给线程池中创建了4个线程
}

void ThreadPoolStop(ThreadPool *pool)
{
    pool->is_start = 0;
}

void ThreadPoolPushTask(ThreadPool *pool, void (*callback)(void *), void *args)
{
    Task *task = (Task *)malloc(sizeof(Task));//初始化一个指向Task类型的指针
    task->callback = callback;//用户传进来的函数名
    task->args = args;//用户传进来的参数
    pthread_mutex_lock(&pool->mutex);//上锁，保证对临界区的访问安全
    QueuePush(pool->queue, task);//第二个参数为用户传递进来想要执行的任务函数
    pthread_mutex_unlock(&pool->mutex);//将用户想要执行的任务成功放入了任
    //队列中，。。。。。。
    pthread_cond_signal(&pool->cond);//给等待处理任务们的线程发信号喽
}

size_t ThreadPoolTaskCount(ThreadPool *pool)
{
    pthread_mutex_lock(&pool->mutex);
    size_t size = QueueSize(pool->queue);
    pthread_mutex_unlock(&pool->mutex);

    return size;
}

