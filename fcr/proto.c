#include "proto.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void init_packet_head(proto_head_t *head, proto_type_t type, int length)
{
    head->magic = FERI_PROTO_HEAD;
    head->type = type;
    head->length = length;
}

request_register_t *create_request_register(const char *username, const char *password)
{
    request_register_t *packet = (request_register_t *)malloc(sizeof(request_register_t));
    init_packet_head(&packet->head, REQ_REGISTER, sizeof(request_register_t));
    strncpy(packet->username, username, USERNAME_LEN);
    strncpy(packet->password, password, PASSWORD_LEN);
    return packet;
}

request_login_t *create_request_login(const char *username, const char *password)
{
    request_login_t *packet = (request_login_t *)malloc(sizeof(request_login_t));
    init_packet_head(&packet->head, REQ_LOGIN, sizeof(request_login_t));
    strncpy(packet->username, username, USERNAME_LEN);
    strncpy(packet->password, password, PASSWORD_LEN);
    return packet;
}

request_get_friend_list_t *create_request_get_friend_list(const char *username)
{
    request_get_friend_list_t *packet = (request_get_friend_list_t *)malloc(sizeof(request_get_friend_list_t));
    init_packet_head(&packet->head, REQ_GET_FRIEND_LIST, sizeof(request_get_friend_list_t));
    strncpy(packet->username, username, USERNAME_LEN);
    return packet;
}

request_add_friend_t *create_request_add_friend(const char *username, const char *friendname)
{
    request_add_friend_t *packet = (request_add_friend_t *)malloc(sizeof(request_add_friend_t));
    init_packet_head(&packet->head, REQ_ADD_FRIEND, sizeof(request_add_friend_t));
    strncpy(packet->username, username, USERNAME_LEN);
    strncpy(packet->friendname, friendname, USERNAME_LEN);
    return packet;
}

request_add_friend_back_t *create_request_add_back_friend(int anw, const char *username, const char *friendname)   
{                                                                                               
    request_add_friend_back_t *packet = (request_add_friend_back_t *)malloc(sizeof(request_add_friend_back_t));
    init_packet_head(&packet->head, REQ_ADD_FRIEND, sizeof(request_add_friend_t));              
    packet->answer = anw;
    strncpy(packet->username, username, USERNAME_LEN);                                          
    strncpy(packet->friendname, friendname, USERNAME_LEN);                                      
    return packet;                                                                              
}                                                                                               

request_del_friend_t *create_request_del_friend(const char *username, const char *friendname)
{
    request_del_friend_t *packet = (request_del_friend_t *)malloc(sizeof(request_del_friend_t));
    init_packet_head(&packet->head, REQ_DEL_FRIEND, sizeof(request_del_friend_t));
    strncpy(packet->username, username, USERNAME_LEN);
    strncpy(packet->friendname, friendname, USERNAME_LEN);
    return packet;
}

request_black_friend_t *create_request_black_friend(const char *username, const char *friendname)   
{
    request_black_friend_t *packet = (request_black_friend_t *)malloc(sizeof(request_black_friend_t));
    init_packet_head(&packet->head, REQ_BLACK_FRIEND, sizeof(request_black_friend_t));              
    strncpy(packet->username, username, USERNAME_LEN);                                          
    strncpy(packet->friendname, friendname, USERNAME_LEN);                                      
    return packet;                                                                              
}                                                                                               

request_pravsend_message_t *create_request_pravsend_message(const char *username, const char *target_name, const char * message)
{
    request_pravsend_message_t *packet = (request_pravsend_message_t *)malloc(sizeof(request_pravsend_message_t));
    init_packet_head(&packet->head, REQ_PRAVSEND_MESSAGE, sizeof(request_pravsend_message_t));
    strncpy(packet->username, username, USERNAME_LEN);                                          
    strncpy(packet->target_name, target_name, USERNAME_LEN);                                          
    strncpy(packet->messgae, message, USERNAME_LEN);                                          
    return packet;
}

request_groupsend_message_t *create_request_groupsend_message(const char *username, const char *target_name, const char * message)
{                                                                                                                                    
    request_groupsend_message_t *packet = (request_groupsend_message_t *)malloc(sizeof(request_groupsend_message_t));                                                       
    init_packet_head(&packet->head, REQ_GROUPSEND_MESSAGE, sizeof(request_groupsend_message_t));                                                                   
    strncpy(packet->username, username, USERNAME_LEN);      
    strncpy(packet->target_name, target_name, USERNAME_LEN);
    strncpy(packet->messgae, message, USERNAME_LEN);        
    return packet;                                                                                                                   
}                                                                                                                                    

request_pull_fri_app_t *create_request_pull_fri_app(int pull_type, const char *username, const char *friendname)
{
    request_pull_fri_app_t *packet = (request_pull_fri_app_t *)malloc(sizeof(request_pull_fri_app_t));
    init_packet_head(&packet->head, REQ_PULL_FRI_APP, sizeof(request_pull_fri_app_t));            
    packet->pull_type = pull_type;
    strncpy(packet->username, username, USERNAME_LEN);                                    
    strncpy(packet->friendname, friendname, PASSWORD_LEN);                                    
    return packet;                                                                        
}

request_agree_add_each_t *create_request_agree_add_each(const char *username, const char *friendname)
{
    request_agree_add_each_t *packet = (request_agree_add_each_t *)malloc(sizeof(request_agree_add_each_t));
    init_packet_head(&packet->head, REQ_AGREE_ADD_EACH, sizeof(request_agree_add_each_t));                  
    strncpy(packet->username, username, USERNAME_LEN);                                          
    strncpy(packet->friendname, friendname, USERNAME_LEN);                                      
    return packet;                                                                              
}

request_pull_pravmess_t *create_request_pull_pravmess(const char *username)
{                                                                                         
    request_pull_pravmess_t*packet = (request_pull_pravmess_t*)malloc(sizeof(request_pull_pravmess_t));
    init_packet_head(&packet->head, REQ_PULL_PRAV_MESS, sizeof(request_pull_pravmess_t));            
    strncpy(packet->username, username, USERNAME_LEN);                                    
    return packet;                                                                        
}                                                                                         

//----------------------------------------------------------------------------------------------------------------------------------------------
response_status_t *create_response_status(int status, const char *msg)
{
    response_status_t *packet = (response_status_t *)malloc(sizeof(response_status_t));
    init_packet_head(&packet->head, RESP_STATUS, sizeof(response_status_t));
    packet->status = status;
    strncpy(packet->message, msg, MSG_LEN);
    
    return packet;
}

response_friens_list_t *create_response_friends_list(const char *userlist)
{
    response_friens_list_t *packet = (response_friens_list_t *)malloc(sizeof(response_friens_list_t));
    init_packet_head(&packet->head, RESP_FRIEND_LIST, sizeof(response_friens_list_t));
    strncpy(packet->userlist, userlist, USERLIST_LEN);
    return packet;
}

response_pravmessage_t *create_response_pravmessage(const char *username, const char *target_name, const char * message)
{
    response_pravmessage_t *packet = (response_pravmessage_t *)malloc(sizeof(response_pravmessage_t));
    init_packet_head(&packet->head, RESP_PRAVMESSAGE, sizeof(response_pravmessage_t));
    strncpy(packet->username, username, USERNAME_LEN);      
    strncpy(packet->target_name, target_name, USERNAME_LEN);
    strncpy(packet->message, message, USERNAME_LEN);        
    return packet;
}

response_pull_fri_app_t *create_response_pull_fri_app(int pull_type, const char *username, const char *friendname)
{
    response_pull_fri_app_t *packet = (response_pull_fri_app_t *)malloc(sizeof(response_pull_fri_app_t));
    init_packet_head(&packet->head, RESP_PULL_FRI_APP, sizeof(response_pull_fri_app_t));                
    packet->pull_type = pull_type;                                                                    
    strncpy(packet->username, username, USERNAME_LEN);                                                
    strncpy(packet->friendname, friendname, PASSWORD_LEN);                                            
    return packet;                                                                                    
}

response_pravmessage_t *create_response_pull_prav(const char *username, const char *target_name, const char *message)
{
     response_pravmessage_t  *packet = (response_pravmessage_t *)malloc(sizeof(response_pravmessage_t));
     init_packet_head(&packet->head, RESP_PULL_PRAV_MESS, sizeof(request_pravsend_message_t));                      
     strncpy(packet->username, username, USERNAME_LEN);                                                            
     strncpy(packet->target_name, target_name, USERNAME_LEN);                                                      
     strncpy(packet->message, message, MAX_MESSAGE_LEN);                                                              
     return packet;                                                                                                
}
