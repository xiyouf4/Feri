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
    free(req);

    return resp;
}

response_status_t *user_login(client_t *client, const char *username, const char *password)
{
    request_login_t *req = create_request_login(username, password);                
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
    free(req);                                                                            
                                                                                          
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

cli_statusa_t show_login_menua()
{
    printf("-----------------------------\n");
    printf("\t1. 私聊 \n");
    printf("\t2. 群聊 \n");
    printf("\t3. 添加好友\n");
    printf("\t4. 删除好友\n");
    printf("\t5. 查看好友列表\n");
    printf("\t6. 好友聊天记录\n");
    printf("\t7. 屏蔽好友消息\n");
    printf("\t8. 创建群\n");
    printf("\t9. 解散群\n");
    printf("\t10. 申请加群\n");
    printf("\t11. 申请退群\n");
    printf("\t12. 群列表\n");
    printf("\t13. 查看群成员\n");
    printf("\t14. 群聊天记录\n");
    printf("\t15. 设置群管理员\n");
    printf("\t16. 群踢人\n");
    printf("\t17. 退出\n");
    printf("-----------------------------\n");
    printf("\t请选择：");
    int op;
    scanf("%d", &op);
    switch(op) {
    case 1:
        return PRAV_chat;
        break;
    case 2:
        return ALL_chat; 
        break;
    case 3:
        return ADD_friend; 
        break;
    case 4:
        return DEL_friend;
        break;
    case 5:
        return LIST_friend;
        break;
    case 17:
        return EXITA;
        break;
    default:                             
        printf("\n输入错误啊，兄弟\n\n");
        break;                           

    }

    return INITA;
}

void login_show_menu()
{
    cli_statusa_t statusa = INITA;                         
    while (statusa != EXITA) {                            
        switch (statusa) {                               
            case INITA:                                  
                statusa = show_login_menua();              
                break;                                  
            case PRAV_chat:                              
                //statusa = show_register_menu();          
                break;                                  
            case ALL_chat:
                break;
            case ADD_friend:                                 
                //statusa = show_login_menu();             
                break;                                  
            case DEL_friend:                
                //statusa = show_login_menu();
                break;                      
            case EXITA:                                  
                break;                                  
            default:                                    
                log_error("status unknown: %d", statusa);
                abort();                                
        }                                               
        clear_input_buffer();                           
    }                                                   









}

cli_status_t show_login_menu()                                       
{                                                                       
    char username[USERNAME_LEN];                                        
    char password[USERNAME_LEN];                                        
    printf("\tusername:");                                              
    scanf("%s", username);                                              
    printf("\n\tpassword:");                                            
    scanf("%s", password);                                              
    response_status_t *resp= user_login(&client, username, password);
    if (resp->status == 0) {                                            
        printf("登录成功");                                            
        printf("%s\n", resp->message);                                  
        login_show_menu();
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
