#include "server.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/epoll.h>

#include "log.h"
#include "socket.h"
#include "proto.h"

void signal_handle(int signal)
{
    (void)signal;
    log_warn("recv sigint, elegent exit now.......");
    server_stop(&server);
}

int server_init(server_t *server)
{
    server->stop = 0;
    server->l_fd = 0;
    server->acc_fd = 0;
    bzero(server->users, sizeof(server->users));
    server->ep_fd = epoll_create(5);
    if (server->ep_fd < 0) {
        log_error("server create_epoll failed, exit");
        abort();
    }

    return FERI_OK;
}

int server_start(server_t *server)
{
    server->l_fd = FERI_tcp_listen(LISTEN_ADDR, LISTEN_PORT, LISTEN_BACKLOG);
    if (server->l_fd < 0) {
        log_error("server start error, exit");
        abort();
    }    

    log_info("server started, listen on %s:%d", LISTEN_ADDR, LISTEN_PORT);

    struct epoll_event event;
    event.data.fd = server->l_fd;
    event.events = EPOLLIN;
    int ret = epoll_ctl(server->ep_fd, EPOLL_CTL_ADD, server->l_fd, &event);
    if (ret < 0) {
        log_error("server add listen fd to epoll failed, exit");
        abort();
    }    

    return FERI_OK;
}

int read_from_fd(int fd, char *buff, int len)
{
    int nread = read(fd, buff, len);
    if (nread == 0 || (nread == -1 && errno != EINTR && errno != EAGAIN)) {
        log_warn("client fd read error, close it, error: %s", strerror(errno));
        return -1;
    }
    if (nread != len) {
        // TODO
        log_warn("not read enough, give up...");
        return -1;
    }

    return nread;
}

int write_to_fd(int fd, const char *buff, int len)
{
    int nwritten = write(fd, buff, len);
    if (nwritten == 0 || (nwritten == -1 && errno != EINTR && errno != EAGAIN)) {
        close(fd);
    }
    if (nwritten != len) {
        log_warn("nwritten != nread, but...give up...");
        return -1;
    }

    return nwritten;
}

typedef proto_head_t *(*packet_process_ft)(proto_head_t *);//?????????????????????????????????????????????????????

proto_head_t *process_register(proto_head_t *req)
{
    request_register_t *request = (request_register_t *)req;
    fprintf(stderr, "want register, username: %s, password: %s\n", request->username, request->password);
    
    if (strcmp(request->username, "zhangxue") == 0) {
        fprintf(stderr, "不让 zhangxue 注册\n");
        return (proto_head_t *)create_response_status(1, "user exist!");
    }//检查此用户名是否已经注册
    // TODO
    // do data operator...
//如果此用户名没有被注册过，那么将其写入数据库并且返回注册成功
    return (proto_head_t *)create_response_status(0, "success");
}

proto_head_t *process_login(proto_head_t *req, server_t *server)
{
    request_login_t *request = (request_login_t *)req;                                             
    fprintf(stderr, "want login, username: %s, password: %s\n", request->username, request->password);    
    if(1) {
//核对成功
//遍历表中找request->username对应的主键自增号码i
        //int i;
        /*for(i = 0; i < MAX_USER_COUNT; i++) {
            if (strcmp(server->users[i].username, request->username) == 0) {

            }
        }*/
       /* server->users[i].is_login = 1;
        server->users[i].fd = server->acc_fd;
        strcpy(server->users[i].username, request->username);*/ 
        return (proto_head_t *)create_response_status(0, "success");
    } else if (2) {
//核对失败
        return (proto_head_t *)create_response_status(-1, "密码或账号不正确");
    }

}

proto_head_t *process_add_friend(proto_head_t *req, server_t *server)
{
    request_add_friend_t *request = (request_add_friend_t *)req;                                             
    fprintf(stderr, "want add %s to be friend\n", request->friendname);    
    int i;
    for (i = 0; i < MAX_USER_COUNT; i++) {
        if (1/*strcmp(server->users[i].username, request->friendname) == 0*/) {
//给消息盒子发消息,并且告诉客户端申请发送成功，请稍等；
//如果对方同意，将requst->username,reauest->friendname添加进好友表
        return (proto_head_t *)create_response_status(0, "好友申请发送成功");
        }
    }
    return NULL;
}

proto_head_t *process_del_friend(proto_head_t *req)
{
    request_add_friend_t *request = (request_add_friend_t *)req;                                             
    fprintf(stderr, "%s want delete this %s friend\n",request->username , request->friendname);    
    //在好友表中找到这两位的好友关系，删除之
    return (proto_head_t *)create_response_status(0, "成功删除");
}

proto_head_t *process_get_friend_list(proto_head_t *req)
{
    //char userlist[USERLIST_LEN];
    request_get_friend_list_t *request = (request_get_friend_list_t *)req;                                             
    fprintf(stderr, "%s want obtain himself friend list\n",request->username);    
    //在数据库的好友表中遍历与request->username有关系的用户，加到数组中，用*隔开
    char userlist[]="nihda*bgfdsc*JHGFDS*UYTRE*hgfds*YTREWQ*";
    return (proto_head_t *)create_response_friends_list(userlist);
}

proto_head_t *process_black_friend(proto_head_t *req)                                            
{                                                                                              
    request_add_friend_t *request = (request_add_friend_t *)req;                               
    fprintf(stderr, "%s want black this %s friend\n",request->username , request->friendname);
    //在好友表中找到这两位的好友关系，将black列变为1                                                   
    return (proto_head_t *)create_response_status(0, "拉黑成功");                              
}                                                                                              
    
proto_head_t *process_user_request(proto_head_t *req, server_t *server) {

    switch(req->type) {
    case 1000:
        return process_register(req);
        break;
    case 1001:
        return process_login(req, server);
        break;
    case 1002:
        return process_get_friend_list(req); 
        break;
    case 1003:
        return process_add_friend(req, server);
        break;
    case 1004:
        return process_del_friend(req);
        break;
    case 1006:
        return process_black_friend(req);
        break;
    }
        return NULL;
}

void close_user_fd(server_t *server, int user_fd)
{
    epoll_ctl(server->ep_fd, EPOLL_CTL_DEL, user_fd, NULL);
    close(user_fd);
}

static void process_user_send_data(int fd, server_t *server)
{
    char buffer[1024];
    int nread = read_from_fd(fd, buffer, sizeof(proto_head_t));
    if (nread < 0) {
        close_user_fd(server, fd);
        return;
    }
    proto_head_t *req = (proto_head_t *)buffer;
    if (req->magic != FERI_PROTO_HEAD) {
        log_warn("wrong proto head, close it");
        close_user_fd(server, fd);
        return;
    }
    int want_read_len = req->length - sizeof(proto_head_t);
    nread = read_from_fd(fd, buffer + sizeof(proto_head_t), want_read_len);//??????????????????????
    if (nread < 0) {
        close_user_fd(server, fd);
        return;
    }
    proto_head_t *resp = process_user_request(req, server);

    if (!resp) {
        log_warn("emmmm, check your code, close it");
        close_user_fd(server, fd);
        return;
    }
    write_to_fd(fd, (char *)resp, resp->length);
}

static void accept_new_connection(server_t *server)
{
    char addr[36];
    int port;

    int client_fd = FERI_tcp_accept(server->l_fd, addr, sizeof(addr), &port);
    if (client_fd < 0) {
        log_error("accept listen fd failed");
        abort();
    }
    log_info("new connection: %s:%d, fd: %d", addr, port, client_fd);

    struct epoll_event event;
    event.data.fd = client_fd;
    event.events = EPOLLIN;
    int ret = epoll_ctl(server->ep_fd, EPOLL_CTL_ADD, client_fd, &event);
    if (ret < 0) {
        log_error("epoll_ctl add client fd read event failed");
        abort();
    }
}

int server_run(server_t *server)
{
    struct epoll_event *events = (struct epoll_event *)malloc(MAX_USER_COUNT*sizeof(struct epoll_event));
    while (!server->stop) {
        int nevents = epoll_wait(server->ep_fd, events, MAX_USER_COUNT, -1);
        if (nevents < 0) {
            if (errno == EINTR || errno == EAGAIN) {
                continue;
            }
            log_errno_error("epoll_wait return failed");
            abort();
        }
        for (int i = 0; i < nevents; ++i) {
            int fd = events[i].data.fd;
            if (events[i].events == EPOLLIN) {
                if (fd == server->l_fd) {
                    accept_new_connection(server);    
                } else {
                    server->acc_fd = fd;
                    process_user_send_data(fd, server);
                }
            } 
        }
    }
    free(events);
    return FERI_OK;
}

void server_stop(server_t *server)
{
    server->stop = 1;
}

void server_destory(server_t *server)
{
    close(server->l_fd);
    close(server->ep_fd);
}
