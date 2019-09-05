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

request_groupsend_message_t *create_request_groupsend_message(const char *username, const char *groupname, const char * message)
{                                                                                                                                    
    request_groupsend_message_t *packet = (request_groupsend_message_t *)malloc(sizeof(request_groupsend_message_t));                                                       
    init_packet_head(&packet->head, REQ_GROUPSEND_MESSAGE, sizeof(request_groupsend_message_t));                                                                   
    strncpy(packet->username, username, USERNAME_LEN);      
    strncpy(packet->target_name, groupname, USERNAME_LEN);
    strncpy(packet->messgae, message, MAX_MESSAGE_LEN);        
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

request_pull_pravmess_t *create_request_pull_pravmess(int pull_type, const char *username)
{                                                                                         
    request_pull_pravmess_t *packet = (request_pull_pravmess_t *)malloc(sizeof(request_pull_pravmess_t));
    init_packet_head(&packet->head, REQ_PULL_PRAV_MESS, sizeof(request_pull_pravmess_t));            
    packet->pull_type = pull_type;
    strncpy(packet->username, username, USERNAME_LEN);                                    
    return packet;                                                                        
}                                                                                         

request_pull_fri_chat_history_t *create_request_pull_fri_chat_history(int pull_type, const char *username, const char *friendname)
{
     request_pull_fri_chat_history_t *packet = (request_pull_fri_chat_history_t *)malloc(sizeof(request_pull_fri_chat_history_t));   
     init_packet_head(&packet->head, REQ_PULL_FRI_CHAT_HISTORY, sizeof(request_pull_fri_chat_history_t));              
     packet->pull_type = pull_type;                                                                     
     strncpy(packet->username, username, USERNAME_LEN);                                                 
     strncpy(packet->friendname, friendname, USERNAME_LEN);                                                 
     return packet;                                                                                     
}

request_create_group_t *create_request_create_group(const char *username, const char *groupname)
{
    request_create_group_t *packet = (request_create_group_t *)malloc(sizeof(request_create_group_t));
    init_packet_head(&packet->head, REQ_CREATE_GROUP, sizeof(request_create_group_t));
    strncpy(packet->username, username, USERNAME_LEN);
    strncpy(packet->groupname, groupname, USERNAME_LEN);
    return packet;
}

request_add_group_t *create_request_add_group(const char *username, const char *groupname)      
{                                                                                                     
    request_add_group_t *packet = (request_add_group_t *)malloc(sizeof(request_add_group_t));
    init_packet_head(&packet->head, REQ_ADD_GROUP, sizeof(request_add_group_t));                
    strncpy(packet->username, username, USERNAME_LEN);                                                
    strncpy(packet->groupname, groupname, USERNAME_LEN);                                              
    return packet;                                                                                    
}                                                                                                     

request_back_group_t *create_request_back_group(const char *username, const char *groupname)   
{                                                                                            
    request_back_group_t *packet = (request_back_group_t *)malloc(sizeof(request_back_group_t));
    init_packet_head(&packet->head, REQ_BACK_GROUP, sizeof(request_back_group_t));             
    strncpy(packet->username, username, USERNAME_LEN);                                       
    strncpy(packet->groupname, groupname, USERNAME_LEN);                                     
    return packet;                                                                           
}                                                                                            

request_pull_group_t *create_request_pull_group(int pull_type, const char *username, const char *groupname)
{
    request_pull_group_t *packet = (request_pull_group_t *)malloc(sizeof(request_pull_group_t));
    init_packet_head(&packet->head, REQ_PULL_GROUP, sizeof(request_pull_group_t));                
    packet->pull_type = pull_type;                                                                       
    strncpy(packet->username, username, USERNAME_LEN);                                                   
    strncpy(packet->groupname, groupname, USERNAME_LEN);                                                   
    return packet;                                                                                       
}

request_send_file_t *create_request_send_file(const char *username, const char *friendname, int num)
{
     request_send_file_t *packet = (request_send_file_t *)malloc(sizeof(request_send_file_t));   
     init_packet_head(&packet->head, REQ_SEND_FEIL, sizeof(request_send_file_t));                     
     strncpy(packet->username, username, USERNAME_LEN);                                                               
     strncpy(packet->friendname, friendname, USERNAME_LEN);                                                           
     packet->num = num;
     return packet;                                                                                                   
}

request_refresh_pravmess_t *create_request_refresh_pravmess(int pull_type, const char *username)
{
    request_refresh_pravmess_t *packet = (request_refresh_pravmess_t *)malloc(sizeof(request_refresh_pravmess_t));
    init_packet_head(&packet->head, REQ_REFRESH_PRAVMESS, sizeof(request_refresh_pravmess_t));                
    packet->pull_type = pull_type;                                                                       
    strncpy(packet->username, username, USERNAME_LEN);                                                   
    return packet;                                                                                       
}

request_refresh_pravmess_t *create_request_prav_refresh(int pull_type, const char *username)
{
    request_refresh_pravmess_t *packet = (request_refresh_pravmess_t *)malloc(sizeof(request_refresh_pravmess_t));
    init_packet_head(&packet->head, REQ_PRAV_REFRESH, sizeof(request_refresh_pravmess_t));                    
    packet->pull_type = pull_type;                                                                                
    strncpy(packet->username, username, USERNAME_LEN);                                                            
    return packet;                                                                                                
}

request_pull_file_t *create_request_pull_file(const char *username)
{
    request_pull_file_t *packet = (request_pull_file_t *)malloc(sizeof(request_pull_file_t));
    init_packet_head(&packet->head, REQ_PULL_FILEN, sizeof(request_pull_file_t));                        
    strncpy(packet->username, username, USERNAME_LEN);                                                            
    return packet;                                                                                                
}

request_pull_group_list_t *create_request_pull_group_list(const char *username)
{
    request_pull_group_list_t *packet = (request_pull_group_list_t *)malloc(sizeof(request_pull_group_list_t));
    init_packet_head(&packet->head, REQ_PULL_GROUP_LIST, sizeof(request_pull_group_list_t));            
    strncpy(packet->username, username, USERNAME_LEN);                                       
    return packet;                                                                           
}

request_pull_group_m_t *create_request_pull_group_m(const char *username, char *groupname)
{
    request_pull_group_m_t *packet = (request_pull_group_m_t *)malloc(sizeof(request_pull_group_m_t));
    init_packet_head(&packet->head, REQ_PULL_GROUP_M, sizeof(request_pull_group_m_t));                   
    strncpy(packet->username, username, USERNAME_LEN);                                                         
    strncpy(packet->groupname, groupname, USERNAME_LEN);                                                         
    return packet;                                                                                             
}

request_group_guan_t *create_request_group_guan(const char *ua,const char *username, char *groupname)
{
    request_group_guan_t *packet = (request_group_guan_t *)malloc(sizeof(request_group_guan_t));
    init_packet_head(&packet->head, REQ_GROUP_GUAN, sizeof(request_group_guan_t));                
    strncpy(packet->username, username, USERNAME_LEN);                                                
    strncpy(packet->ua, ua, USERNAME_LEN);                                                
    strncpy(packet->groupname, groupname, USERNAME_LEN);                                              
    return packet;                                                                                             
}

request_group_ti_t *create_request_group_ti(const char *ua, const char *username, char *groupname)
{
    request_group_ti_t *packet = (request_group_ti_t *)malloc(sizeof(request_group_ti_t));
    init_packet_head(&packet->head, REQ_GROUP_TI, sizeof(request_group_ti_t));              
    strncpy(packet->username, username, USERNAME_LEN);                                          
    strncpy(packet->ua, ua, USERNAME_LEN);                                                      
    strncpy(packet->groupname, groupname, USERNAME_LEN);                                        
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

response_group_list_t *create_response_group_list(const char *userlist)
{
    response_group_list_t *packet = (response_group_list_t *)malloc(sizeof(response_group_list_t));
    init_packet_head(&packet->head, RESP_GROUP_LIST, sizeof(response_group_list_t));                
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

response_pull_fri_chat_history_t *create_response_pull_fri_chat_history(const char *username, const char *target_name, const char *message)
{
     response_pull_fri_chat_history_t  *packet = (response_pull_fri_chat_history_t *)malloc(sizeof(response_pull_fri_chat_history_t));
     init_packet_head(&packet->head, RESP_PULL_FRI_CHAT_HISTORY, sizeof(response_pull_fri_chat_history_t));          
     strncpy(packet->username, username, USERNAME_LEN);                                                 
     strncpy(packet->target_name, target_name, USERNAME_LEN);                                           
     strncpy(packet->message,  message, MAX_MESSAGE_LENA);                                                
     return packet;                                                                                     
}

response_groupmessage_t *create_response_groupmessage(const char *username, const char *target_name, const char *message)
{
    response_groupmessage_t *packet = (response_groupmessage_t *)malloc(sizeof(response_groupmessage_t));
    init_packet_head(&packet->head, RESP_GROUPMESSAGE, sizeof(response_groupmessage_t));                
    strncpy(packet->username, username, USERNAME_LEN);                                                
    strncpy(packet->target_name, target_name, USERNAME_LEN);                                          
    strncpy(packet->message, message, USERNAME_LEN);                                                  
    return packet;                                                                                    
}

response_send_file_t *create_response_send_file(const char *username, const char *friendname, int num)
{
     response_send_file_t *packet = (response_send_file_t *)malloc(sizeof(response_send_file_t));
     init_packet_head(&packet->head, RESP_SEND_FEIL, sizeof(response_send_file_t));             
     strncpy(packet->username, username, USERNAME_LEN);                                       
     strncpy(packet->friendname, friendname, USERNAME_LEN);                                   
     packet->num = num;                                                                       
     return packet;                                                                           
}


