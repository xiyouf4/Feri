#include "client_menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
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

response_status_t *user_add_friend(client_t *client, const char *username, const char *friendname)
{
    request_add_friend_t *req = create_request_add_friend(username, friendname);                      
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

response_status_t *user_del_friend(client_t *client, const char *username, const char *friendname)              
{                                                                                         
    request_del_friend_t *req = create_request_del_friend(username, friendname);                    
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

response_friens_list_t *user_get_friend_list(client_t *client, const char *username)
{
    request_get_friend_list_t  *req = create_request_get_friend_list(username);          
    uint32_t nwritten = FERI_block_write(client->conn_fd, (char *)req, req->head.length); 
    if (nwritten != req->head.length) {                                                   
        log_error("send to server failed, exit");                                         
        abort();                                                                          
    }                                                                                     
    response_friens_list_t *resp = (response_friens_list_t *)malloc(sizeof(response_friens_list_t));     
    int nread = FERI_block_read(client->conn_fd, (char *)resp, sizeof(response_friens_list_t));
    if (nread != sizeof(response_friens_list_t)) {                                             
        log_error("recv from server failed, exit");                                       
        abort();                                                                          
    }                                                                                     
    if (resp->head.type != RESP_FRIEND_LIST) {                                                 
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

response_status_t *user_black_friend(client_t *client, const char *username, const char *friendname)
{
    request_black_friend_t *req = create_request_black_friend(username, friendname);          
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

response_status_t *user_pravsend_message(client_t *client, const char *username, const char *target_name, const char *message)
{
    request_pravsend_message_t *req = create_request_pravsend_message(username, target_name, message);      
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

response_status_t *user_create_group(client_t *client, const char *groupname)
{
    request_create_group_t *req = create_request_create_group(client->username, groupname);
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

response_status_t *user_add_group(client_t *client, const char *groupname)
{
    request_add_group_t *req = create_request_add_group(client->username, groupname);
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

response_status_t *user_back_group(client_t *client, const char *groupname)                
{                                                                                         
    request_back_group_t *req = create_request_back_group(client->username, groupname);     
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

response_status_t *user_allchat_message(client_t *client, const char * username, const char *groupname, const char *group_mess)
{
    request_groupsend_message_t *req = create_request_groupsend_message(username, groupname, group_mess);
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

cli_statusa_t show_add_friend_menu(client_t client)
{
    char friendname[USERNAME_LEN];
    printf("\tfriendname:");
    scanf("%s", friendname);
    response_status_t *resp= user_add_friend(&client, client.username, friendname);
    if (resp->status == 0) {          
        printf("添加成功!");          
        printf("%s\n", resp->message);
    } else {                          
        printf("添加失败");           
        printf("%s\n", resp->message);
    }                                 
                                      
    free(resp);                       

    return INITA;
}

cli_statusa_t show_del_friend_menu(client_t client)                              
{                                                                 
    char friendname[USERNAME_LEN];                                
    printf("\tfriendname:");                                      
    scanf("%s", friendname);                                     
    response_status_t *resp= user_del_friend(&client, client.username, friendname);
    if (resp->status == 0) {                                      
        printf("删除成功!");                                      
        printf("%s\n", resp->message);                            
    } else {                                                      
        printf("删除失败");                                       
        printf("%s\n", resp->message);                            
    }                                                             
                                                                  
    free(resp);                                                   
                                                                  
    return INITA;                                                 
}                                                                 

cli_statusa_t show_list_friend_menu(client_t client)
{
    response_friens_list_t *resp= user_get_friend_list(&client, client.username);
    size_t i;
    for (i = 0; i < 100; i++) {
        if (resp->userlist[i] == '*') {
            printf("\n");
        } else {
            printf("%c", resp->userlist[i]);
        }
    }

    free(resp);                                                   

    return INITA;                                                 
}

cli_statusa_t show_black_friend_menu(client_t client)
{
    char friendname[USERNAME_LEN];                                                 
    printf("\tfriendname:");                                                       
    scanf("%s", friendname);                                                       
    response_status_t *resp= user_black_friend(&client, client.username, friendname);
    if (resp->status == 0) {          
        printf("拉黑成功!");          
        printf("%s\n", resp->message);
    } else {                          
        printf("拉黑失败");           
        printf("%s\n", resp->message);
    }                                 
                                      
    free(resp);                       
                                      
    return INITA;                     
}

void show_prav_refresh(client_t client)
{
    request_refresh_pravmess_t *req = create_request_prav_refresh(PRAV, client.username);
    uint32_t nwritten = FERI_block_write(client.conn_fd, (char *)req, req->head.length);     
    if (nwritten != req->head.length) {                                                      
        log_error("send to server failed, exit");                                            
        abort();                                                                             
    }                                                                                        
    response_pravmessage_t *resp = (response_pravmessage_t *)malloc(sizeof(response_pravmessage_t));//循环收        
    int nread = FERI_block_read(client.conn_fd, (char *)resp, sizeof(response_pravmessage_t));    
    if (nread != sizeof(response_pravmessage_t)) {                                                
        log_error("recv from server failed, exit");                                          
        abort();                                                                             
    }                                                                                        
    if (resp->head.type != RESP_PRAVMESSAGE) {                                                    
        log_error("recv from server data type != RESP_STATUS, exit");                        
        abort();                                                                             
    }                                                                                        
    if (resp->head.magic != FERI_PROTO_HEAD) {                                               
        log_error("recv from server data error, exit");                                      
        abort();                                                                             
    }                                                                                        
    if (strcmp(resp->username, "null") == 0) {
        printf("\t对方未回复\n");
    } else {
        printf("\t%s", resp->username);
        printf("%s:\n", resp->message);
    }
    while (strcmp(resp->target_name, "over") != 0) {
        int nread = FERI_block_read(client.conn_fd, (char *)resp, sizeof(response_pravmessage_t));
        if (nread != sizeof(response_pravmessage_t)) {                                            
            log_error("recv from server failed, exit");                                           
            abort();                                                                              
        }                                                                                         
        if (resp->head.type != RESP_PRAVMESSAGE) {                                                
            log_error("recv from server data type != RESP_STATUS, exit");                         
            abort();                                                                              
        }                                                                                         
        if (resp->head.magic != FERI_PROTO_HEAD) {                                                
            log_error("recv from server data error, exit");                                       
            abort();                                                                              
        }                                                                                         
        if (strcmp(resp->target_name, "over") == 0) {
            break;
        }
        printf("\t%s:", resp->username);                                                        
        printf("%s\n", resp->message);                                                         
    }
}

cli_statusa_t show_pravsend_message(client_t client)
{
    char target_name[USERNAME_LEN];                                                   
    char message[MAX_MESSAGE_LEN];
    printf("\ttarget_name:");                                                         
    scanf("%s", target_name);                                                         
    printf("\t请输入聊天内容:");
    scanf("%s", message);
    response_status_t *resp = user_pravsend_message(&client, client.username, target_name, message);
    if (resp->status == 0) {          
        printf("发送成功,");          
        printf("%s\n", resp->message);
    } else {                          
        printf("发送失败\n");           
        printf("%s\n", resp->message);
    }                                 
    free(resp);
    int loop = 0;
    printf("\t1.继续聊天\n");
    printf("\t2.退出\n");    
    printf("\t3.刷新\n");    
    printf("\t请选择：");
    scanf("%d", &loop);
    while (loop == 1 || loop == 3) {
        if (loop == 1) {
            printf("\t请输入聊天内容:");                                                                    
            scanf("%s", message);                                                                           
            response_status_t *resp = user_pravsend_message(&client, client.username, target_name, message);
            if (resp->status == 0) {                                                                        
                printf("\t发送成功,");                                                                        
                printf("%s\n", resp->message);                                                              
            } else {                                                                                        
                printf("\t发送失败\n");                                                                       
                printf("%s\n", resp->message);                                                              
            }                                                                                               
            free(resp);                                                                                     
            printf("\t1.继续聊天\n");                                                                       
            printf("\t2.退出\n");                                                                           
            printf("\t3.刷新\n");                                                                           
            printf("\t请选择\n");                                                                           
            scanf("%d", &loop);                                                                           
        } else if (loop == 3) {
            show_prav_refresh(client);
            printf("\t1.继续聊天\n");
            printf("\t2.退出\n");    
            printf("\t3.刷新\n");    
            printf("\t请选择\n");                                                                           
            scanf("%d", &loop);    
        }
    }
    return INITA;                     
}

cli_statusa_t show_pull_fri_chat_history_menu(client_t client)
{
    char friendname[USERNAME_LEN];
    printf("friendname: ");
    scanf("%s", friendname);
    request_pull_fri_chat_history_t *req = create_request_pull_fri_chat_history(FRI_CHAT_HISTORY, client.username, friendname);
    uint32_t nwritten = FERI_block_write(client.conn_fd, (char *)req, req->head.length);             
    if (nwritten != req->head.length) {                                                               
        log_error("send to server failed, exit");                                                     
        abort();                                                                                      
    }                                                                                                 
    response_pull_fri_chat_history_t *resp = (response_pull_fri_chat_history_t *)malloc(sizeof(response_pull_fri_chat_history_t));                 
    int nread = FERI_block_read(client.conn_fd, (char *)resp, sizeof(response_pull_fri_chat_history_t));            
    if (nread != sizeof(response_pull_fri_chat_history_t)) {                                                         
        log_error("recv from server failed, exit");                                                   
        abort();                                                                                      
    }                                                                                                 
    if (resp->head.type != RESP_PULL_FRI_CHAT_HISTORY) {                                                             
        log_error("recv from server data type != RESP_STATUS, exit");                                 
        abort();                                                                                      
    }                                                                                                 
    if (resp->head.magic != FERI_PROTO_HEAD) {                                                        
        log_error("recv from server data error, exit");                                               
        abort();                                                                                      
    }                                                                                                 
                                                                                                      
    printf("您与%s私聊记录为：\n", resp->target_name);
    printf("%s\n", resp->message);
    free(req);                                                                                        
    free(resp);
    return INITA;
}


cli_statusa_t show_allchat_menu(client_t client)
{
    char groupname[USERNAME_LEN];
    char group_mess[MAX_MESSAGE_LEN];
    printf("群名：");            
    scanf("%s", groupname);      
    printf("消息：");
    scanf("%s", group_mess);
    response_status_t *resp = user_allchat_message(&client, client.username, groupname, group_mess);
    if (resp->status == 0) {          
        printf("发送成功,");          
        printf("%s\n", resp->message);
    } else {                          
        printf("发送失败\n");         
        printf("%s\n", resp->message);
    }                                 
    free(resp);                       
    return INITA;                     
}

messbox_status_t show_pull_fri_app_menu(client_t client)
{
    request_pull_fri_app_t *req = create_request_pull_fri_app(FRIEND_APPLICATION, client.username, "null");      
    uint32_t nwritten = FERI_block_write(client.conn_fd, (char *)req, req->head.length);    
    if (nwritten != req->head.length) {                                                   
        log_error("send to server failed, exit");                                         
        abort();                                                                          
    }                                                                                     
    response_pull_fri_app_t *resp = (response_pull_fri_app_t *)malloc(sizeof(response_pull_fri_app_t));     
    int nread = FERI_block_read(client.conn_fd, (char *)resp, sizeof(response_pull_fri_app_t));
    if (nread != sizeof(response_pull_fri_app_t)) {                                             
        log_error("recv from server failed, exit");                                       
        abort();                                                                          
    }                                                                                     
    if (resp->head.type != RESP_PULL_FRI_APP) {                                                 
        log_error("recv from server data type != RESP_STATUS, exit");                     
        abort();                                                                          
    }                                                                                     
    if (resp->head.magic != FERI_PROTO_HEAD) {                                            
        log_error("recv from server data error, exit");                                   
        abort();                                                                          
    }                                                                                     

    if (strcmp(resp->username, "您没有好友申请信息") == 0) {
        free(req);
        free(resp);
        return INITB;
    }
                                                                                          
    printf("%s 想要添加您为好友\n", resp->username);
    printf("\t 请选择：\n");
    printf("\t1. 同意\n");
    printf("\t2. 拒绝\n");
    int op;
    scanf("%d", &op);
    if (op == 1) {
        request_agree_add_each_t *req = create_request_agree_add_each(resp->username, resp->friendname);
        uint32_t nwritten = FERI_block_write(client.conn_fd, (char *)req, req->head.length);
        if (nwritten != req->head.length) {                                                 
            log_error("send to server failed, exit");                                       
            abort();                                                                        
        }                                                                                   
        printf("您和%s已成为好友\n", resp->username);
    } else if (op ==2) {
        free(req);
        free(resp);
        return INITB;
    }

    free(req);                                                                            
    free(resp);
                                                                                          
    return INITB;                                                                          
}

messbox_status_t show_pull_fri_prav_menu(client_t client)
{
    request_pull_pravmess_t *req = create_request_pull_pravmess(PRAV, client.username);      
    uint32_t nwritten = FERI_block_write(client.conn_fd, (char *)req, req->head.length); 
    if (nwritten != req->head.length) {                                                   
        log_error("send to server failed, exit");                                         
        abort();                                                                          
    }                                                                                     
    response_pravmessage_t *resp = (response_pravmessage_t *)malloc(sizeof(response_pravmessage_t));     
    int nread = FERI_block_read(client.conn_fd, (char *)resp, sizeof(response_pravmessage_t));
    if (nread != sizeof(response_pravmessage_t)) {                                             
        log_error("recv from server failed, exit");                                       
        abort();                                                                          
    }                                                                                     
    if (resp->head.type != RESP_PULL_PRAV_MESS) {                                                 
        log_error("recv from server data type != RESP_STATUS, exit");                     
        abort();                                                                          
    }                                                                                     
    if (resp->head.magic != FERI_PROTO_HEAD) {                                            
        log_error("recv from server data error, exit");                                   
        abort();                                                                          
    }                                                                                     
    if (strcmp(resp->target_name, "over") == 0) {
        free(req);                                          
        free(resp);                                         
        return INITB;                                       
    }                                                       
    printf("%s ：", resp->username);
    printf("%s\n", resp->message);
    while (strcmp(resp->target_name, "over") != 0) {
        int nread = FERI_block_read(client.conn_fd, (char *)resp, sizeof(response_pravmessage_t));
        if (nread != sizeof(response_pravmessage_t)) {                                            
            log_error("recv from server failed, exit");                                           
            abort();                                                                              
        }                                                                                         
        if (resp->head.type != RESP_PULL_PRAV_MESS) {                                             
            log_error("recv from server data type != RESP_STATUS, exit");                         
            abort();                                                                              
        }                                                                                         
        if (resp->head.magic != FERI_PROTO_HEAD) {                                                
            log_error("recv from server data error, exit");                                       
            abort();                                                                              
        }                                                                                         
        if (strcmp(resp->target_name, "over") == 0) {
            break;
        }
        printf("%s ：", resp->username);                                                          
        printf("%s\n", resp->message);                                                            
    }

    printf("1.回复\n");
    printf("2.不回复\n");
    printf("3.刷新\n");
    printf("请选择:\n");
    int op;
    scanf("%d", &op);
    while (op == 1 || op == 3) {
        if (op == 1) {
            show_pravsend_message(client);
            printf("\t2. 退出\n");
            scanf("%d", &op);
        } else if (op == 3) {
            printf("..........................,,,,,,,,,,,,,,,,,,\n");
            show_prav_refresh(client);
            printf("1.回复\n");  
            printf("2.不回复\n");
            printf("3.刷新\n");  
            printf("请选择:\n"); 
            scanf("%d", &op);
        }
    }
    return INITB;
}

void user_pull_group(client_t *client, const char *username, const char *groupname)
{
    request_pull_group_t *req = create_request_pull_group(GROUP_, username, groupname);
    uint32_t nwritten = FERI_block_write(client->conn_fd, (char *)req, req->head.length);                
    if (nwritten != req->head.length) {                                                                  
        log_error("send to server failed, exit");                                                        
        abort();                                                                                         
    }                                                                                                    
    //循环收，直到发过来的群名项目为，完了
    response_groupmessage_t *resp = (response_groupmessage_t *)malloc(sizeof(response_groupmessage_t));                    
    int nread = FERI_block_read(client->conn_fd, (char *)resp, sizeof(response_groupmessage_t));               
    if (nread != sizeof(response_groupmessage_t)) {                                                            
        log_error("recv from server failed, exit");                                                      
        abort();                                                                                         
    }                                                                                                    
    if (resp->head.type != RESP_GROUPMESSAGE) {                                                                
        log_error("recv from server data type != RESP_STATUS, exit");                                    
        abort();                                                                                         
    }                                                                                                    
    if (resp->head.magic != FERI_PROTO_HEAD) {                                                           
        log_error("recv from server data error, exit");                                                  
        abort();                                                                                         
    }                                                                                                    
    printf("%s:\t", resp->username);   
    printf("%s\n", resp->message);  
    while (strcmp(resp->target_name, "完了") != 0) {
        nread = FERI_block_read(client->conn_fd, (char *)resp, sizeof(response_groupmessage_t));
        if (nread != sizeof(response_groupmessage_t)) {                                             
            log_error("recv from server failed, exit");                                             
            abort();                                                                                
        }                                                                                           
        if (resp->head.type != RESP_GROUPMESSAGE) {                                                 
            log_error("recv from server data type != RESP_STATUS, exit");                           
            abort();                                                                                
        }                                                                                           
        if (resp->head.magic != FERI_PROTO_HEAD) {                                                  
            log_error("recv from server data error, exit");                                         
            abort();                                                                                
        }                                                                                           
        printf("%s:\t", resp->username);                                                            
        printf("%s\n", resp->message);                                                              
   }
    printf("是否参与聊天？\n");
    printf("\t1. 是\n");
    printf("\t2. 否\n");
    int op;
    scanf("%d", &op);
    if (op == 1) {
        show_allchat_menu(*client);
        free(resp);
        free(req);                                                                                           
    } else {
        free(resp);
        free(req);                                                                                           
    }
}

messbox_status_t show_pull_group_menu(client_t client)
{
    char groupname[USERNAME_LEN];
    printf("群名：");            
    scanf("%s", groupname);      
    user_pull_group(&client, client.username, groupname);
    return INITB;
}

cli_statusa_t create_group_menu(client_t client)
{
    char groupname[USERNAME_LEN];
    printf("群名：");
    scanf("%s", groupname);
    response_status_t *resp = user_create_group(&client, groupname);
    if (resp->status == 0) {          
        printf("%s\n", resp->message);
    } else {                          
        printf("创建失败");           
    }                                 
    free(resp);                       
    return INITA;
}

cli_statusa_t add_group_menu(client_t client)
{
    char groupname[USERNAME_LEN];                                   
    printf("群名：");                                               
    scanf("%s", groupname);                                         
    response_status_t *resp = user_add_group(&client, groupname);
    if (resp->status == 0) {                                        
        printf("%s\n", resp->message);                              
    } else {                                                        
        printf("加群失败");                                         
    }                                                               
    free(resp);                                                     
    return INITA;
}

cli_statusa_t back_group_menu(client_t client)                    
{                                                                
    char groupname[USERNAME_LEN];                                
    printf("群名：");                                            
    scanf("%s", groupname);                                      
    response_status_t *resp = user_back_group(&client, groupname);
    if (resp->status == 0) {                                     
        printf("%s\n", resp->message);                           
    } else {                                                     
        printf("退群失败");                                      
    }                                                            
    free(resp);                                                  
    return INITA;                                                
}                                                                

response_status_t *user_refresh_pravmess(client_t client)
{
    request_refresh_pravmess_t *req = create_request_refresh_pravmess(PRAV, client.username);             
    uint32_t nwritten = FERI_block_write(client.conn_fd, (char *)req, req->head.length);            
    if (nwritten != req->head.length) {                                                             
        log_error("send to server failed, exit");                                                   
        abort();                                                                                    
    }                                                                                               
    response_status_t *resp = (response_status_t *)malloc(sizeof(response_status_t));
    int nread = FERI_block_read(client.conn_fd, (char *)resp, sizeof(response_status_t));      
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

cli_statusa_t show_refresh_pravmess(client_t client)
{
    response_status_t *resp = user_refresh_pravmess(client);
    printf("\t%s\n", resp->message);
    free(resp);
    return INITA;
}

cli_statusa_t send_file_menu(client_t client)
{
    char file[MAX_MESSAGE_LEN];
    char rfile[MAX_MESSAGE_LEN];
    printf("fcr聊天室将暂时为您发送默认文件\n");
    char friendname[USERNAME_LEN];
    printf("好友用户名：");
    scanf("%s", friendname);
    int fd;                                                  
    fd = open("send_file_text.txt", O_RDONLY);
    if (fd < 0) {
        perror("open err:");
    }
    int num = 0;                                  
    int ret = 0;
    while ((ret = read(fd, file, MAX_MESSAGE_LEN)) != 0) {
        if (ret == -1) {
            perror("file read err:");
            exit(0);
        }
        num += 1;                                 
    }                  
    request_send_file_t *req = create_request_send_file(client.username, friendname, num);
    uint32_t nwritten = FERI_block_write(client.conn_fd, (char *)req, req->head.length);
    if (nwritten != req->head.length) {                                                  
        log_error("send to server failed, exit");                                        
        abort();                                                                         
    }                                                                                    
    int fdd;                                   
    fdd = open("send_file_text.txt", O_RDONLY);
    while (read(fdd, rfile, MAX_MESSAGE_LEN) != 0) {   
        write(client.conn_fd, rfile, MAX_MESSAGE_LEN);
    }                                                
    response_status_t *resp = (response_status_t *)malloc(sizeof(response_status_t));     
    int nread = FERI_block_read(client.conn_fd, (char *)resp, sizeof(response_status_t));
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
    printf("%s\n", resp->message);
    free(resp);


    free(req);                                                                            
    return INITA;
}

messbox_status_t show_pull_file_menu(client_t client)
{                                        
    int fdfile;                                        
    fdfile = open("test.txt", O_RDWR|O_TRUNC|O_APPEND);
    char rfile[MAX_MESSAGE_LEN];                       

     request_pull_file_t *req = create_request_pull_file(client.username);
     uint32_t nwritten = FERI_block_write(client.conn_fd, (char *)req, req->head.length);     
    if (nwritten != req->head.length) {                                                      
        log_error("send to server failed, exit");                                            
        abort();                                                                             
    }                                                                                        
    response_send_file_t *resp = (response_send_file_t *)malloc(sizeof(response_send_file_t));        
    int nread = FERI_block_read(client.conn_fd, (char *)resp, sizeof(response_send_file_t));    
    if (nread != sizeof(response_send_file_t)) {                                                
        log_error("recv from server failed, exit");                                          
        abort();                                                                             
    }                                                                                        
    if (resp->head.type != RESP_SEND_FEIL) {                                                    
        log_error("recv from server data type != RESP_STATUS, exit");                        
        abort();                                                                             
    }                                                                                        
    if (resp->head.magic != FERI_PROTO_HEAD) {                                               
        log_error("recv from server data error, exit");                                      
        abort();                                                                             
    }                                                                                        
    printf("\t你将要接收 %s 发给您的文件\n", resp->friendname);
    int num = resp->num;
    while (num != 0) {
        read(client.conn_fd, rfile, MAX_MESSAGE_LEN);
        write(fdfile, rfile, MAX_MESSAGE_LEN);
        num--;
    }
    resp = (response_send_file_t *)malloc(sizeof(response_send_file_t));        
    nread = FERI_block_read(client.conn_fd, (char *)resp, sizeof(response_send_file_t));    
    if (resp->num == 0) {
        printf("\t接收成功\n");
    }
    free(req);                                                                               
    free(resp);
    return INITB;
}

messbox_status_t messbox_init_menu()                   
{                                               
    printf("-----------------------------\n");  
    printf("\t1. 好友申请\n");                      
    printf("\t3. 好友消息\n");                      
    printf("\t4. 群消息\n");                      
    printf("\t5. 文件消息\n");                      
    printf("\t7. 退出\n");                      
    printf("-----------------------------\n\n");
    printf("请选择: ");                         
    int choice = 0;                             
    scanf("%d", &choice);                       
    switch (choice) {                           
        case 1:                                 
            return FRIEND_APPLICATION;                       
            break;
        case 3:
            return PRAV;
            break;
        case 4:
            return GROUP_;
            break;
        case 5:           
            return FILEN;
            break;        
        case 7:                                 
            return EXITB;                        
            break;
        default:                                
            printf("\n输入错误啊，兄弟\n\n");   
            break;                              
    }                                           
    return INITB;                                
}                                               

cli_statusa_t messbox_show_menu(client_t client)                                    
{                                                       
    messbox_status_t statusb = INITB;                         
    while (statusb != EXITB) {                            
        switch (statusb) {                               
            case INITB:                                  
                statusb = messbox_init_menu();              
                break;                                  
            case FRIEND_APPLICATION:                              
                statusb = show_pull_fri_app_menu(client);          
                break;                                  
            case PRAV:                                 
                statusb = show_pull_fri_prav_menu(client);          
                break;                                  
            case GROUP_:
                statusb = show_pull_group_menu(client);          
                break;
            case FILEN:                               
                statusb = show_pull_file_menu(client);
                break;                                 
            case EXITB:                                  
                break;                                  
            default:                                    
                log_error("status unknown: %d", statusb);
                abort();                                
        }                                               
        clear_input_buffer();                           
    }                                                   

    return INITA;
}                                                       

cli_statusa_t show_login_menua(client_t client)
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
    printf("\t10. 加群\n");
    printf("\t11. 退群\n");
    printf("\t12. 群列表\n");
    printf("\t13. 查看群成员\n");
    printf("\t14. 群聊天记录\n");
    printf("\t15. 设置群管理员\n");
    printf("\t16. 群踢人\n");
    printf("\t17. 消息盒子\n");
    printf("\t18. 发文件\n");
    printf("\t19. 退出\n");
    printf("\t20. 刷新\n");
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
    case 6:
        return FRI_chat_history;
        break;
    case 7:
        return BLACK_friend;
        break;
    case 8:
        return CREATE_group; 
        break;
    case 10:
        return ADD_group;
        break;
    case 11:
        return BACK_group;
        break;
    case 17:
        return messbox_show_menu(client);
        break;
    case 18:
        return FILEE;
        break;
    case 19:
        return EXITA;
        break;
    case 20:         
        return REFRESH;
        break;       
    default:                             
        printf("\n输入错误啊，兄弟\n\n");
        break;                           

    }

    return INITA;
}

void login_show_menu(client_t client)
{
    cli_statusa_t statusa = INITA;                         
    while (statusa != EXITA) {                            
        switch (statusa) {                               
            case INITA:                                  
                statusa = show_login_menua(client);              
                break;                                  
            case PRAV_chat:                              
                statusa = show_pravsend_message(client);          
                break;                                  
            case ALL_chat:
                statusa = show_allchat_menu(client);          
                break;
            case ADD_friend:                                 
                statusa = show_add_friend_menu(client);             
                break;                                  
            case DEL_friend:                
                statusa = show_del_friend_menu(client);
                break;                      
            case LIST_friend:
                statusa = show_list_friend_menu(client);
                break;
            case BLACK_friend:
                statusa = show_black_friend_menu(client);
                break;
            case FRI_chat_history:
                statusa = show_pull_fri_chat_history_menu(client);
                break;
            case CREATE_group:
                statusa = create_group_menu(client);
                break;
            case ADD_group:
                statusa = add_group_menu(client);
                break;
            case BACK_group:
                statusa = back_group_menu(client);
                break;
            case FILEE:
                statusa = send_file_menu(client);
                break;
            case REFRESH://拉自己的私聊消息                         
                statusa = show_refresh_pravmess(client);
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
    //char username[USERNAME_LEN];                                        
    char password[USERNAME_LEN];                                        
    printf("\tusername:");                                              
    scanf("%s", client.username);                                              
    printf("\n\tpassword:");                                            
    scanf("%s", password);                                              
    response_status_t *resp= user_login(&client, client.username, password);
    if (resp->status == 0) {                                            
        printf("登录成功");                                            
        printf("%s\n", resp->message);                                  
        //消息盒子开始运行
        login_show_menu(client);
        return INIT;
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
