/**
 * (C) 2007-2019 Alibaba Group Holding Limited
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Version: 1.0: queue.c 08/03/2019 $
 *
 * Authors:
 *   qianyi.lh <qianyi.lh@alibaba-inc.com>
 */

#include "queue.h"

#include <stdlib.h>


typedef struct Node {
    void *data;//一个指向类型不确定的指针
    struct Node *next;//指向自己结构体类型Node的指针next;
} Node;

typedef struct Queue {
    Node *head;//指向Node类型结构体的指针叫head
    Node *tail;//同上,它的作用好像是跟踪Node链表相当于一个临时指针一样的东西
    size_t size;
} Queue;

Queue *QueueInit(void)//初始化队列
{
    Queue *queue= (Queue *)malloc(sizeof(Queue));//Queue类型的指针queue，为啥要给指针分配大小啊？
    //如果将malloc部分注释掉接下来的一行会报错queue未初始化,为啥要初始化呀
    //我傻逼了，我知道了，给未初始化的指针解引用，我疯了，会导致内存泄漏的。
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    return queue;
}

void QueueDestroy(Queue *queue, void (*dataDestroy)(void *))//第二个参数其实就是free
    //之所以在这里不直接free而要选择参数传递的方式，是为了考虑代码的可移植性，
    //以及可以将其加入我自己的代码库，以后要用的时候我直接修改其API就OK啦
{
    Node *node = queue->head;
    while (node != NULL) {
        Node *tmp = node->next;
        if (dataDestroy) {
            dataDestroy(node->data);
        }
        free(node);
        node = tmp;
    }
    free(queue);
}

void QueuePush(Queue *queue, void *data)//第二个参数实际上是用户传递进来想要执行
    //的函数名以及传递给该函数的参数
{
    Node *node = (Node *)malloc(sizeof(Node));//初始化一个指向Node结构体类型的指针
    node->data = data;
    if (queue->tail) {//如果当前队列的尾指针不为NULL的话，还不是很确定
        queue->tail->next = node;//这一步还是相当于在操作Node,那么就将我这个新的数据node加入队列中 
        queue->tail = node;//tail和tail->next都是指向Node类型的指针，为什么要这样操作呢？
        //真正存储用户数据的还是Node链表
    } else {//如果queue->tail是NULL
        queue->head = queue->tail = node;
    }
    queue->size++;//任务队列中的任务数加1
}

void *QueuePop(Queue *queue)
{
    void *data = NULL;
    if (queue->size == 1) {
        data = queue->head->data;
        free(queue->head);
        queue->head = queue->tail = NULL;
        queue->size--;
    } else if (queue->size > 1) {
        data = queue->head->data;
        Node *tmp = queue->head;
        queue->head = queue->head->next;
        free(tmp);
        queue->size--;
    }

    return data;
}

size_t QueueSize(Queue *queue)
{
    return queue->size;
}

