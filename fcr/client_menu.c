#include "client_menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
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
    fprintf(stderr,"nread = %d, menu.c line is %d\n", nread, __LINE__);
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

cli_statusa_t show_pravsend_message(client_t client)
{
    char target_name[USERNAME_LEN];                                                   
    char message[MAX_MESSAGE_LEN];
    printf("\ttarget_name:");                                                         
    scanf("%s", target_name);                                                         
    printf("请输入聊天内容:");
    scanf("%s", message);
    response_status_t *resp = user_pravsend_message(&client, client.username, target_name, message);
    if (resp->status == 0) {          
        printf("发送成功,");          
        printf("%s\n", resp->message);
    } else {                          
        printf("发送失败\n");           
        printf("%s\n", resp->message);
    }                                 
                                      
//私聊没有写完
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
    request_pull_pravmess_t *req = create_request_pull_pravmess(client.username);      
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
    if (strcmp(resp->username, "您没有好友申请信息") == 0) {
        free(req);                                          
        free(resp);                                         
        return INITB;                                       
    }                                                       

    printf("%s ：", resp->username);
    printf("%s", resp->message);

    return INITB;
}





messbox_status_t messbox_init_menu()                   
{                                               
    printf("-----------------------------\n");  
    printf("\t1. 好友申请\n");                      
    printf("\t2. 加群申请\n");                      
    printf("\t3. 好友消息\n");                      
    printf("\t4. 群消息\n");                      
    printf("\t5. 文件消息\n");                      
    printf("\t6. 群通知\n");                      
    printf("\t7. 退出\n");                      
    printf("-----------------------------\n\n");
    printf("请选择: ");                         
    int choice = 0;                             
    scanf("%d", &choice);                       
    switch (choice) {                           
        case 1:                                 
            return FRIEND_APPLICATION;                       
        case 2:                                 
            return GROUP_APPLICATION;                    
        case 3:
            return PRAV;
            break;
        case 4:
            return GROUP_;
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
    printf("\t10. 申请加群\n");
    printf("\t11. 退群\n");
    printf("\t12. 群列表\n");
    printf("\t13. 查看群成员\n");
    printf("\t14. 群聊天记录\n");
    printf("\t15. 设置群管理员\n");
    printf("\t16. 群踢人\n");
    printf("\t17. 消息盒子\n");
    printf("\t18. 发文件\n");
    printf("\t19. 退出\n");
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
    case 7:
        return BLACK_friend;
        break;
    case 17:
        return messbox_show_menu(client);
        break;
    case 19:
        return EXITA;
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
