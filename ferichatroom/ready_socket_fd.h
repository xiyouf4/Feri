#include <sys/epoll.h>

#include <stdio.h>
#include <stdlib.h>

struct Ready {
    int ready_fd;
    int epfd;
    struct epoll_event ev;
};

struct Ready *readypointer;
struct Ready *ready_socket_fd();
