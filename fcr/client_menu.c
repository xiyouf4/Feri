#include "client_menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

#include "all.h"
#include "socket.h"
#include "client.h"
#include "log.h"
#include "proto.h"

//int user_register();
void clear_input_buffer()
{
    while (getchar() != '\n')
        ;
}

response_status_t *user_register(client_t *client, const char *username, const char *password)
{
    request_register_t *req = create_request_register(username, password);
    uint32_t nwritten = FERI_block_write(client->conn_fd, (char *)req, req->head.length);
    if (nwritten != req->head.length) {
        log_error("send to server failed, exit");
        abort();
    }
    response_status_t *resp = (response_status_t *)malloc(sizeof(response_status_t));
    int nread = FERI_block_read(client->conn_fd, (char *)resp, sizeof(response_status_t));
    if (nread != sizeof(response_status_t)) {
        log_error("recv from server failed, exit");
        abort();
    }
    if (resp->head.type != RESP_STATUS) {
        log_error("recv from server data type != RESP_STATUS, exit");
        abort();
    }
    if (resp->head.magic != FERI_PROTO_HEAD) {
        log_error("recv from server data error, exit");
        abort();
    }
    //int status = resp->status;
    free(req);
    //free(resp);

    return resp;
}

cli_status_t show_register_menu()
{
    char username[USERNAME_LEN];
    char password[USERNAME_LEN];
    printf("\tusername:");
    scanf("%s", username);
    printf("\n\tpassword:");
    scanf("%s", password);
    response_status_t *resp= user_register(&client, username, password);
    if (resp->status == 0) {
        printf("注册成功!");
        printf("%s\n", resp->message);
    } else {
        printf("注册错误");
        printf("%s\n", resp->message);
    }

    free(resp);

    return INIT;
}

cli_status_t show_login_menu()                                       
{                                                                       
    char username[USERNAME_LEN];                                        
    char password[USERNAME_LEN];                                        
    printf("\tusername:");                                              
    scanf("%s", username);                                              
    printf("\n\tpassword:");                                            
    scanf("%s", password);                                              
    response_status_t *resp= user_register(&client, username, password);
    if (resp->status == 0) {                                            
        printf("登录成功");                                            
        printf("%s\n", resp->message);                                  
    } else {                                                            
        printf("登录失败");                                             
        printf("%s\n", resp->message);                                  
    }                                                                   
                                                                        
    free(resp);

    return INIT;                                                        
}                                                                       

cli_status_t show_init_menu()
{
    printf("-----------------------------\n");
    printf("\t1. 登录\n");
    printf("\t2. 注册\n");
    printf("\t3. 退出\n");
    printf("-----------------------------\n\n");
    printf("请选择: ");
    int choice = 0;
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            return LOGIN;
        case 2:
            return REGISTER;
        case 3:
            return EXIT;
        default:
            printf("\n输入错误啊，兄弟\n\n");
            break;
    }

    return INIT;
}

void cli_show_menu()
{
    cli_status_t status = INIT;
    while (status != EXIT) {
        switch (status) {
            case INIT:
                status = show_init_menu();
                break;
            case REGISTER:
                status = show_register_menu();
                break;
            case LOGIN:
                status = show_login_menu();
                break;
            case EXIT:
                break;
            default:
                log_error("status unknown: %d", status);
                abort();
        }
        clear_input_buffer();
    }
}
