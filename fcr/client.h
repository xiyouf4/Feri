#ifndef CLIENT_H
#define CLIENT_H

#include "proto.h"

typedef struct client_t {
    char username[USERNAME_LEN];
    int conn_fd;
} client_t;

client_t client;

int client_init(client_t *client);
int client_start(client_t *client);
//void cli_menu();

//void client_stop(client_t *client);
void client_destroy(client_t *cient);

response_status_t *user_register(client_t *client, const char *username, const char *password);
response_status_t *user_login(client_t *client, const char *username, const char *password);
response_status_t *user_black_friend(client_t *client, const char *username, const char *friendname);
response_friens_list_t *user_get_friend_list(client_t *client, const char *username);
response_status_t *user_add_friend(client_t *client, const char *username, const char *friendname);
response_status_t *user_del_friend(client_t *client, const char *username, const char *friendname);
int user_send_message(client_t *client);

#endif
