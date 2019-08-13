#include "onlineclient.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mtu = PTHREAD_MUTEX_INITIALIZER;
struct Onlinequeue {
        int fd;
        char username[20];
        struct Onlinequeue *next;
};

struct Onlinequeue *temp;

onlinequeue *queueinit()
{
        struct Onlinequeue *temp, *start;
        start = (struct Onlinequeue *)malloc(sizeof(onlinequeue));
        start->next = NULL;
        temp = start;
        return temp;
}

void queueplus(int fd, char *username)
{
        //struct Onlinequeue *s = (struct Onlinequeue *)malloc(sizeof(struct Onlinequeue));
        int is_start = 0;
        pthread_mutex_lock(&mtu);
        if (is_start == 0) {
            temp = queueinit();
            is_start = 1;
        }
        struct Onlinequeue *pnew = (struct Onlinequeue *)malloc(sizeof(onlinequeue));
        pnew->fd = fd;
        strcpy(pnew->username, username);
        temp->next = pnew;
        temp = pnew;
        pthread_mutex_unlock(&mtu);
        printf("line is=%d       %s\n",__LINE__,pnew->username);
        printf("line is=%d       %d\n",__LINE__,pnew->fd);
}
