#ifndef SERVER_H
#define SERVER_H

#include "proto.h"

#include "stdlib.h"

#define LISTEN_BACKLOG  1024
#define LISTEN_ADDR "0.0.0.0"

#define MAX_USER_COUNT 1000
#define MAX_HISTORY_MESSAGE 1000

int mess_nums_count;

/*typedef enum box_mess_type {
    FRIEND_APP = 1,
    GROUP_APP,
    PRVA,
    GROUP_,
    FILEN,
    GROUP_TELL,
} box_mess_type_t;*/

typedef struct user {
    int is_login;
    int fd;
    char username[USERNAME_LEN];
} user_t;

typedef struct box_content {
    int bit;                
    int type;               
    int doo;                
    char username[32];      
    char friendname[32];    
    char message[1000];     
    //struct BOX *next;     
} box_content_t;            

typedef struct BOX {                            
    char boxowner[USERNAME_LEN];                
    box_content_t contents[MAX_HISTORY_MESSAGE];
    struct BOX *next;                           
} box_t;                                        

typedef struct queue {
    box_t *head;      
    box_t *tail;      
} queue_t;            

typedef struct server {
    int stop;
    int l_fd;
    int acc_fd;
    int ep_fd;
    queue_t *queuee;
    char username[USERNAME_LEN];
    //user_t users[MAX_USER_COUNT];
} server_t;

user_t users[MAX_USER_COUNT];

server_t server;
void signal_handle(int signal);
int server_init(server_t *server);
int server_start(server_t *server);
int server_run(server_t *server);
void server_stop(server_t *server);
void server_destory(server_t *server);

#endif
