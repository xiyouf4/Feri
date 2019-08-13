#include "threadpool.h"
#include "ready_socket_fd.h"

#include <stdio.h>
#include <mysql/mysql.h>
#include <unistd.h>


int main()
{
        Threadpool *pool; 
        int ready_fd;
        int epfd;
        struct epoll_event ev;
        pool = Threadpoolinit(10);
        Threadpoolcreate(pool);
                printf("yes\n");
                ready_socket_fd();
                ready_fd = readypointer->ready_fd;
                printf("yes1\n");
                epfd = readypointer->epfd;
                printf("yes2\n");
                ev = readypointer->ev;
                printf("connect!!!\n");
                Threadpoolpushtask(pool, ready_fd, epfd, ev); //参数是已就绪的套接字描述符
        Threadpoolstop(pool);
        Threadpooldestory(pool);
        return 0;
}

