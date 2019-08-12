#include "threadpool.h"
#include "ready_socket_fd.h"

#include <stdio.h>
#include <mysql/mysql.h>
#include <unistd.h>
int main()
{
        Threadpool *pool; 
        int ready_fd;
        pool = Threadpoolinit(10);
        Threadpoolcreate(pool);
        while(1) {
               // pool = Threadpoolinit(10); //初始化线程池管理器
              //  Threadpoolcreate(pool); //创建线程池
                ready_fd = ready_socket_fd();
                printf("connect!!!\n");
                Threadpoolpushtask(pool, ready_fd); //参数是已就绪的套接字描述符
        }
        Threadpoolstop(pool);
        Threadpooldestory(pool);
        return 0;
}

