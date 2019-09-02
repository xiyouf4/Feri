#ifndef SERVER_H
#define SERVER_H

#include "proto.h"

#include "stdlib.h"

#define LISTEN_BACKLOG  1024
#define LISTEN_ADDR "0.0.0.0"

#define MAX_USER_COUNT 1000
#define MAX_HISTORY_MESSAGE 1000
#define MAX_GROUP_MEMBER 100
#define MAX_GROUP_MESSNUM 300

int mess_nums_count;

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

typedef  struct group_member {
    int here;
    char username[USERNAME_LEN];
} group_member_t;

typedef struct group_box_message {   
    int flag;                        
    char username[USERNAME_LEN];     
    char group_mess[MAX_MESSAGE_LEN];
    struct group_box_message *next;
} group_box_message_t;               

typedef struct queue_message {
    group_box_message_t *a;   
    group_box_message_t *z;   
} queue_message_t;            

typedef struct GROUP_BOX {
    char groupowner[USERNAME_LEN];
    char groupname[USERNAME_LEN];
    queue_message_t *poin;
    group_member_t member[MAX_GROUP_MEMBER];
    group_box_message_t group_messnum[MAX_GROUP_MESSNUM];
    struct GROUP_BOX *next;
} group_box_t;

typedef struct queue_group {
    group_box_t *first;
    group_box_t *last;
} queue_group_t;

typedef struct file_content {
    int bit;
    char file[MAX_MESSAGE_LEN];
} file_content_t;

typedef struct file {
    char username[USERNAME_LEN];
    char friendname[USERNAME_LEN];
    file_content_t fileall[500];
} file_t;

typedef struct server {
    int stop;
    int l_fd;
    int acc_fd;
    int ep_fd;
    file_t allfile;
    queue_group_t *queue_g;
    queue_t *queuee;
    queue_message_t *emm;
    char username[USERNAME_LEN];
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
