/**
 * (C) 2007-2019 Alibaba Group Holding Limited
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Version: 1.0: thread_pool.h 08/03/2019 $
 *
 * Authors:
 *   qianyi.lh <qianyi.lh@alibaba-inc.com>
 */

#include <stddef.h>

typedef struct ThreadPool ThreadPool;//定义了一个结构体类型叫Threadpool;

ThreadPool *ThreadPoolInit(size_t thread_count);//应该是一个线程池创建函数，并且这个函数的返回值是
//struct Threadpool类型的。
void ThreadPoolDestroy(ThreadPool *pool);//不管是线程池销毁还是创建函数其参数均为Threadpool类型
void ThreadPoolStart(ThreadPool *pool);
void ThreadPoolStop(ThreadPool *pool);
void ThreadPoolPushTask(ThreadPool *pool, void (*callback)(void *), void *args);
size_t ThreadPoolTaskCount(ThreadPool *pool);

