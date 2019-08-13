#include "threadpool.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <mysql/mysql.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERV_PORT 4510
#define BACKLOG 1000
#define MAXEVENTS 100


int main()
{
        Threadpool *pool = Threadpoolinit(10);
        Threadpoolcreate(pool);
        int epfd;
        int lfd,accfd;
        struct epoll_event ev;
        struct epoll_event *events = (struct epoll_event *)malloc(MAXEVENTS*sizeof(struct epoll_event));
        struct sockaddr_in serv_addr;
        lfd = socket(AF_INET, SOCK_STREAM, 0);
        printf("epoll1\n");
        if (lfd < 0) {
                printf("error:socket\n");
        }
        int optval = 1;
        setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, (void *)&optval, sizeof(int));
        setsockopt(lfd, SOL_SOCKET, SO_REUSEPORT,(void *)&optval,sizeof(int) );
        memset(&serv_addr, 0, sizeof(struct sockaddr_in));
        printf("epoll2\n");
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(SERV_PORT);
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        bind(lfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in));
        listen(lfd, BACKLOG);
        printf("epoll3\n");
        epfd = epoll_create(5);
        ev.data.fd = lfd;
        ev.events = EPOLLIN; 
        epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &ev);
        while (1) {
                int ready_num = 0;
                int i = 0;
                ready_num = epoll_wait(epfd, events, MAXEVENTS, -1);
                printf("epoll4\n");
                for (i = 0; i < ready_num; i++) {
                        if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || !(events[i].events & EPOLLIN)) {
                                printf("epoll error.1\n");
                                epoll_ctl(epfd,EPOLL_CTL_DEL,ev.data.fd,&ev);
                        } else if (lfd == events[i].data.fd) {
                                struct sockaddr cli_addr;
                                bzero(&cli_addr,sizeof(struct sockaddr));
                                socklen_t cli_len;
                                accfd = accept(lfd, (struct sockaddr *)&cli_addr, &cli_len); 
                                ev.data.fd = accfd;
                                ev.events = EPOLLIN;
                                epoll_ctl(epfd, EPOLL_CTL_ADD, accfd, &ev);
                                printf("epoll5\n");
                        } else if ( (events[i].events & EPOLLIN)){
                                Threadpoolpushtask(pool, events[i].data.fd, epfd, events[i]);
                                printf("epoll6\n");
                        }
                }
        }
        return 0;
}
