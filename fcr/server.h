#ifndef SERVER_H
#define SERVER_H

#include "proto.h"

#define LISTEN_BACKLOG  1024
#define LISTEN_ADDR "0.0.0.0"

#define MAX_USER_COUNT 1000

typedef struct user {
    int is_login;
    char username[USERNAME_LEN];
} user_t;

typedef struct server {
    int stop;
    int l_fd;
    int ep_fd;
    user_t users[MAX_USER_COUNT];
} server_t;

server_t server;
void signal_handle(int signal);
int server_init(server_t *server);
int server_start(server_t *server);
int server_run(server_t *server);
void server_stop(server_t *server);
void server_destory(server_t *server);

#endif
