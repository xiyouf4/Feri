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
#include "client_menu.h"

void signal_handle(int signal)
{
    (void)signal;
    log_warn("recv sigint, elegent exit now.......");
    server_stop(&server);
}

int server_init(server_t *server)
{
    server->queuee = (queue_t *)malloc(sizeof(queue_t));
    server->queuee->head = NULL;
    server->queuee->tail = NULL;
    server->queue_g = (queue_group_t *)malloc(sizeof(queue_group_t));
    server->queue_g->first = NULL;
    server->queue_g->last = NULL;
    server->stop = 0;
    server->l_fd = 0;
    server->acc_fd = 0;
    bzero(users, sizeof(users));
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
    if (strcmp(request->username, "zxue") == 0) {
        fprintf(stderr, "不允许 zxue 注册\n");
        return (proto_head_t *)create_response_status(1, "user exist!");
    }//检查此用户名是否已经注册
    // TODO
    // do data operator...
//如果此用户名没有被注册过，那么将其写入数据库并且返回注册成功
   /* int i;
    for (i = 0; i < MAX_USER_COUNT; i++) {
        if(all_box[i].bit != 1) {
            all_box[i].bit = 1;
            strncpy(all_box[i].boxowner, request->username, USERNAME_LEN);
            break;
        } 
    }*/
    return (proto_head_t *)create_response_status(0, "success");
}

proto_head_t *process_login(proto_head_t *req, server_t *server)
{
    request_login_t *request = (request_login_t *)req;                                             
    fprintf(stderr, "want login, username: %s, password: %s\n", request->username, request->password);    
    if(1) {
//1,根据用户名和密码在数据库中核对，如果核对成功
//遍历表中找request->username对应的主键自增号码num
        /*for(i = 0; i < MAX_USER_COUNT; i++) {
            if (strcmp(server->users[i].username, request->username) == 0) {

            }
        }*/
        int num = 1;
        users[num].is_login = 1;//在在线链表中将好友变为上线状态
        users[num].fd = server->acc_fd;
        strcpy(users[num].username, request->username); 
        //为该用户在消息盒子队列中创建一个盒子
        box_t *box = (box_t *)malloc(sizeof(box_t));
        for (int i = 0; i < MAX_USER_COUNT; i++) {
            box->contents[i].bit = 0;
        }
        strncpy(box->boxowner, request->username, USERNAME_LEN);
        fprintf(stderr, "line is %d, server.c\n", __LINE__);
        if (server->queuee->tail != NULL) {
        fprintf(stderr, "line is %d, server.c\n", __LINE__);
            server->queuee->tail->next = box;
            server->queuee->tail = box;
        fprintf(stderr, "line is %d, server.c\n", __LINE__);
        } else {
            server->queuee->head = server->queuee->tail =box;
        }
        //fprintf(stderr, ",,,,,,,,,,,,,,,,,,,,,,,,,%s \n", server->queuee->head->next->boxowner);
        return (proto_head_t *)create_response_status(0, "登录成功");
    } else if (2) {
//如果核对失败
        return (proto_head_t *)create_response_status(-1, "密码或账号不正确");
    }

}

proto_head_t *process_add_friend(proto_head_t *req, server_t *server)
{
    request_add_friend_t *request = (request_add_friend_t *)req;                                             
    fprintf(stderr, "%s want add %s to be friend\n", request->username, request->friendname);    
    for (int i = 1; i < MAX_USER_COUNT; i++) {
        if (strcmp(request->friendname, users[i].username) == 0) {
            box_t *tmp = server->queuee->head;
            while(strcmp(tmp->boxowner, request->friendname) != 0) {
                tmp = tmp->next;
            }
            for (int j = 0; j < MAX_HISTORY_MESSAGE; j++){                                  
                if(tmp->contents[j].bit == 1) {                                         
                    continue;                                                           
                } else {                                                                
                    tmp->contents[j].bit = 1;                                           
                    tmp->contents[j].type = FRIEND_APPLICATION;                                 
                    tmp->contents[j].doo = 0;                                           
                    strncpy(tmp->contents[j].username, request->username, USERNAME_LEN);
                    //free(tmp);
                    break;                                                              
                }                                                                       
            }                                                                           
        fprintf(stderr, "line is %d, server.c\n", __LINE__);
            break;
        }
    }//已将将消息成功写入目标好友的消息盒子中

   /*for (i = 0; i < MAX_USER_COUNT; i++) {
        if (1strcmp(server->users[i].username, request->friendname) == 0) {
            
//如果对方同意，将requst->username,reauest->friendname添加进好友表
        return (proto_head_t *)create_response_status(0, "好友申请发送成功");
        } else {
        return (proto_head_t *)create_response_status(1, "对方不在线");
        }
    }*/
    return (proto_head_t *)create_response_status(0, "好友申请发送成功");
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
    
proto_head_t *process_pravsend_message(proto_head_t *req)
{
    request_pravsend_message_t *request = (request_pravsend_message_t *)req;                              
    fprintf(stderr, "%s want send pravite message to  %s \n",request->username, request->target_name);    
    box_t *tmp = server.queuee->head;                                                                                                  
    while (strcmp(tmp->boxowner, request->target_name) != 0) {                                                                         
        tmp = tmp->next;                                                                                                            
    }                                                                                                                               
    int i;                                                                                                                          
    for (i = 0; i < MAX_HISTORY_MESSAGE; i++) {                                                                                     
        if (tmp->contents[i].bit == 0) {
            tmp->contents[i].bit = 1;
            tmp->contents[i].type = PRAV;
            tmp->contents[i].doo = 0;
            strncpy(tmp->contents[i].username, request->username, USERNAME_LEN);
            strncpy(tmp->contents[i].friendname, request->target_name, USERNAME_LEN);
            strncpy(tmp->contents[i].message, request->messgae, USERNAME_LEN);
        }                                                                                                                           
        break;                                                                                                                      
    }                                                                                                                               
    printf("message is %s\n", tmp->contents[i].message);
    return (proto_head_t *)create_response_status(0, "消息发送成功");                             
}

proto_head_t *process_pull_fri_app(proto_head_t *req)
{
    request_pull_fri_app_t *request = (request_pull_fri_app_t *)req;                          
    fprintf(stderr, "%s want pull his friend application\n",request->username);
    box_t *tmp = server.queuee->head;
    while (strcmp(tmp->boxowner, request->username) != 0) {
        tmp = tmp->next;
    }
    int i;
    for (i = 0; i < MAX_HISTORY_MESSAGE; i++) {
        if (tmp->contents[i].type == FRIEND_APPLICATION && tmp->contents[i].doo == 0) {
            tmp->contents[i].doo = 1;
        }
        break;
    }
    return (proto_head_t *)create_response_pull_fri_app(FRIEND_APPLICATION, tmp->contents[i].username, tmp->contents[i].friendname);//                             
    if (i == MAX_HISTORY_MESSAGE) {
        return (proto_head_t *)create_response_pull_fri_app(FRIEND_APPLICATION, "您没有好友申请信息", "null");//                             
    }
    return NULL;
}

proto_head_t *process_add_each(proto_head_t *req)
{
    request_agree_add_each_t *request = (request_agree_add_each_t *)req;                          
    fprintf(stderr, "%s and %s will be friends\n",request->username, request->friendname);
    //在数据库的好友表中将这两人填入，并且默认互不拉黑
    return NULL;
}
    
proto_head_t *process_pull_pravmess(proto_head_t *req)
{
    request_pull_pravmess_t *request = (request_pull_pravmess_t *)req;                               
    fprintf(stderr, "%s want pull his pravite message\n",request->username);
//在消息盒子列表中找到request->username的消息盒子，并将其私聊类型且未处理的的消息发送过去，如果没有则发送暂时没有没有好友私聊您,回复response_pravmessage_t类型的包
    box_t *tmp = server.queuee->head;                                                                                                 
    while (strcmp(tmp->boxowner, request->username) != 0) {                                                                           
        tmp = tmp->next;                                                                                                              
    }                                                                                                                                 
    int i;                                                                                                                            
    for (i = 0; i < MAX_HISTORY_MESSAGE; i++) {                                                                                       
        if (tmp->contents[i].type == PRAV && tmp->contents[i].doo == 0) {                                                 
            tmp->contents[i].doo = 1;                                                                                                 
        }                                                                                                                             
        return (proto_head_t *)create_response_pull_prav(tmp->contents[i].username, tmp->contents[i].friendname, tmp->contents[i].message);//
        break;                                                                                                                        
    }                                                                                                                                 
    if (i == MAX_HISTORY_MESSAGE) {                                                                                                   
        return (proto_head_t *)create_response_pull_prav( "null", "null", "暂时没有好友私聊您");//                      
    }                                                                                                                                 

    return NULL;
}

proto_head_t *process_pull_fri_chat_history(proto_head_t *req)
{
    request_pull_fri_chat_history_t *request = (request_pull_fri_chat_history_t *)req;       
    response_pull_fri_chat_history_t *resp = (response_pull_fri_chat_history_t *)malloc(sizeof(response_pull_fri_chat_history_t));
    fprintf(stderr, "%s want pull the history message with %s\n",request->username, request->friendname);
    box_t *tmpa = server.queuee->head;                                                                     
    while (strcmp(tmpa->boxowner, request->friendname) != 0) {                                             
        tmpa = tmpa->next;                                                                                 
    }                                                                                                      
    int j;                                                                                                 
    for (j = 0; j < MAX_HISTORY_MESSAGE; j++) {                                                            
        if (tmpa->contents[j].type == PRAV && strcmp(tmpa->contents[j].username, request->username) == 0) {
            strcpy(resp->message, request->username);
            strcat(resp->message, ":\t");
            strcat(resp->message, tmpa->contents[j].message);//                                             
            strcat(resp->message, "\n");
        }                                                                                                  
        break;                                                                                             
    }                                                                                                      
    box_t *tmp = server.queuee->head;                                    
    while (strcmp(tmp->boxowner, request->username) != 0) {              
        tmp = tmp->next;                                                 
    }                                                                    
    int i;                                                               
    for (i = 0; i < MAX_HISTORY_MESSAGE; i++) {                          
        if (tmp->contents[i].type == PRAV && strcmp(tmp->contents[i].username, request->friendname) == 0) {
            strcat(resp->message, request->friendname);
            strcat(resp->message, ":\t");
            strcat(resp->message, tmp->contents[i].message);//
        }                                                                
        break;                                                           
    }                                                                    
                                           
    return (proto_head_t *)create_response_pull_fri_chat_history(request->username, request->friendname, resp->message);//
}

proto_head_t *process_create_group(proto_head_t *req)
{
    request_create_group_t *request = (request_create_group_t *)req;
    fprintf(stderr, "%s want to create a group named %s", request->username, request->groupname);
//假设已经创建好了该群
    group_box_t *group = (group_box_t *)malloc(sizeof(group_box_t)); 
        for (int i = 0; i < MAX_GROUP_MESSNUM; i++) {              
            group->group_messnum->flag = 0;
        }                                                       
        strncpy(group->groupname, request->groupname, USERNAME_LEN);
        strncpy(group->groupowner, request->username, USERNAME_LEN);
        fprintf(stderr, "line is %d, server.c\n", __LINE__);    
        if (server.queue_g->last != NULL) {                     
            fprintf(stderr, "line is %d, server.c\n", __LINE__);    
            server.queue_g->last->next = group;
            server.queue_g->last = group;
        fprintf(stderr, "line is %d, server.c\n", __LINE__);    
        } else {                                                
            server.queue_g->first = server.queue_g->last = group;
        }                                                       
        int i;
        for (i = 0; i < MAX_GROUP_MEMBER; i++) {
            group->member[i].here = 0;
        }
        strncpy(group->member[0].username, request->username, USERNAME_LEN);
        group->member[0].here = 1;
        int j;
        for (j = 0; j < MAX_GROUP_MESSNUM; j++) {
            group->group_messnum[j].flag = 0;
        }

    return (proto_head_t *)create_response_status(0, "成功创建");
}

proto_head_t *process_add_group(proto_head_t *req)
{
    request_add_group_t *request = (request_add_group_t *)req;                             
    fprintf(stderr, "%s want to add %s group", request->username, request->groupname);
    group_box_t *tmp = server.queue_g->first;
    while (strncmp(tmp->groupname, request->groupname, USERNAME_LEN) != 0) {
        tmp = tmp->next;
    }
    int i;
    for (i = 0; i < MAX_GROUP_MEMBER; i++) {
        if (tmp->member[i].here == 0) {
            tmp->member[i].here = 1;
            strncpy(tmp->member[i].username, request->username, USERNAME_LEN);
        }
    }

    return (proto_head_t *)create_response_status(0, "成功加入");
}

proto_head_t *process_back_group(proto_head_t *req)
{
    request_back_group_t *request = (request_back_group_t *)req;                           
    fprintf(stderr, "%s want to back %s group", request->username, request->groupname);
    group_box_t *tmp = server.queue_g->first;                                 
    fprintf(stderr, "@@@@@@@@@%s", tmp->member[0].username);
    fprintf(stderr, "@@@@@@@@@%s", tmp->member[1].username);
    while (strncmp(tmp->groupname, request->groupname, USERNAME_LEN) != 0) {  
        tmp = tmp->next;                                                      
    }                                                                         
    int i;                                                                    
    for (i = 0; i < MAX_GROUP_MEMBER; i++) {                                  
        if (strncmp(tmp->member[i].username, request->username, USERNAME_LEN) == 0) {
            tmp->member[i].here = 0;
            bzero(tmp->member[i].username, USERNAME_LEN);
        }
    }                                                                         
    return (proto_head_t *)create_response_status(0, "成功退出");
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
    case 1005:
        return process_pravsend_message(req);
        break;
    case 1006:
        return process_black_friend(req);
        break;
    case 1008:
        return process_pull_fri_app(req);
        break;
    case 1009:
        return process_add_each(req);
        break;
    case 1010:
        return process_pull_pravmess(req);
        break;
    case 1011:
        return process_pull_fri_chat_history(req);
        break;
    case 1012:
        return process_create_group(req);
        break;
    case 1013:                           
        return process_add_group(req);
        break;                           
    case 1014:
        return process_back_group(req);
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
                    //printf("!@#$!!!!\n");
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
