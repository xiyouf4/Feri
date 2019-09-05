#ifndef PROTO_H
#define PROTO_H

#define FERI_PROTO_HEAD 1017

#include <stdint.h>

#define PROTO_TYPE_BASE 1000

typedef enum proto_type_t {
    REQ_REGISTER = 1000,
    REQ_LOGIN = 1001,
    REQ_GET_FRIEND_LIST = 1002,
    REQ_ADD_FRIEND = 1003,
    REQ_DEL_FRIEND = 1004,
    REQ_PRAVSEND_MESSAGE = 1005,
    REQ_BLACK_FRIEND = 1006,
    REQ_GROUPSEND_MESSAGE = 1007,
    REQ_PULL_FRI_APP = 1008,
    REQ_AGREE_ADD_EACH = 1009,
    REQ_PULL_PRAV_MESS = 1010,
    REQ_PULL_FRI_CHAT_HISTORY = 1011,
    REQ_CREATE_GROUP = 1012,
    REQ_ADD_GROUP = 1013,
    REQ_BACK_GROUP = 1014,
    REQ_PULL_GROUP = 1015,
    REQ_SEND_FEIL = 1016,
    REQ_REFRESH_PRAVMESS = 1017,
    REQ_PRAV_REFRESH = 1018,
    REQ_PULL_FILEN = 1019,
    REQ_PULL_GROUP_LIST = 1020,
    REQ_PULL_GROUP_M = 1021,
    REQ_GROUP_GUAN = 1022,
    REQ_GROUP_TI = 1023,

    RESP_STATUS = 2001,
    RESP_FRIEND_LIST = 2002,
    RESP_PRAVMESSAGE = 2003,
    RESP_GROUPMESSAGE = 2004,
    RESP_PULL_FRI_APP = 2005,
    RESP_PULL_PRAV_MESS = 2006,
    RESP_PULL_FRI_CHAT_HISTORY = 2007,
    RESP_SEND_FEIL = 2008,
    RESP_GROUP_LIST = 2009,
} proto_type_t;

#define USERNAME_LEN 32
#define PASSWORD_LEN 32
#define MAX_MESSAGE_LEN 800
#define MAX_MESSAGE_LENA 1600

typedef struct proto_head_t {
    uint32_t magic;
    uint32_t type;
    uint32_t length;
} proto_head_t __attribute__((aligned(1)));

typedef struct request_register_t {
    proto_head_t head;
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
} request_register_t __attribute__((aligned(1)));

typedef struct request_login_t {
    proto_head_t head;
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
} request_login_t __attribute__((aligned(1)));

typedef struct request_get_friend_list_t {
    proto_head_t head;
    char username[USERNAME_LEN];
} request_get_friend_list_t __attribute__((aligned(1)));

typedef struct request_add_friend_t {
    proto_head_t head;
    char username[USERNAME_LEN];
    char friendname[PASSWORD_LEN];
} request_add_friend_t __attribute__((aligned(1)));

typedef struct request_add_friend_back_t {              
    proto_head_t head;                             
    int answer;
    char username[USERNAME_LEN];                   
    char friendname[PASSWORD_LEN];                 
} request_add_friend_back_t __attribute__((aligned(1)));

typedef struct request_del_friend_t {
    proto_head_t head;
    char username[USERNAME_LEN];
    char friendname[PASSWORD_LEN];
} request_del_friend_t __attribute__((aligned(1)));

typedef struct request_black_friend_t {              
    proto_head_t head;                             
    char username[USERNAME_LEN];                   
    char friendname[PASSWORD_LEN];                 
} request_black_friend_t __attribute__((aligned(1)));

typedef struct request_pull_fri_app {
    proto_head_t head;                             
    int pull_type;
    char username[USERNAME_LEN];                   
    char friendname[PASSWORD_LEN];                 
} request_pull_fri_app_t __attribute__((aligned(1)));

typedef struct request_pravsend_message_t {
    proto_head_t head;
    char username[USERNAME_LEN];
    char target_name[USERNAME_LEN];
    char messgae[MAX_MESSAGE_LEN];
} request_pravsend_message_t __attribute__((aligned(1)));

typedef struct request_groupsend_message_t {              
    proto_head_t head;                               
    char username[USERNAME_LEN];                     
    char target_name[USERNAME_LEN];                  
    char messgae[MAX_MESSAGE_LEN];                                 
} request_groupsend_message_t __attribute__((aligned(1)));

typedef struct request_agree_add_each_t {              
    proto_head_t head;                           
    char username[USERNAME_LEN];                 
    char friendname[PASSWORD_LEN];                 
} request_agree_add_each_t __attribute__((aligned(1)));

typedef struct request_pull_pravmess_t {
    proto_head_t head;                           
    int pull_type;
    char username[USERNAME_LEN];
} request_pull_pravmess_t __attribute__((aligned(1)));

typedef struct request_refresh_pravmess {              
    proto_head_t head;                                
    int pull_type;                                    
    char username[USERNAME_LEN];                      
} request_refresh_pravmess_t __attribute__((aligned(1)));

typedef struct request_pull_fri_chat_history_t {
    proto_head_t head;                  
    int pull_type;                      
    char username[USERNAME_LEN*2];        
    char friendname[USERNAME_LEN*2];        
} request_pull_fri_chat_history_t __attribute__((aligned(1)));              

typedef struct request_create_group {
    proto_head_t head;
    char username[USERNAME_LEN];
    char groupname[USERNAME_LEN];
} request_create_group_t __attribute__((aligned(1)));

typedef struct request_add_group {                
    proto_head_t head;                               
    char username[USERNAME_LEN];                     
    char groupname[USERNAME_LEN];                    
} request_add_group_t __attribute__((aligned(1)));

typedef struct request_back_group {                
    proto_head_t head;                            
    char username[USERNAME_LEN];                  
    char groupname[USERNAME_LEN];                 
} request_back_group_t __attribute__((aligned(1)));

typedef struct request_pull_group_t {              
    proto_head_t head;                                
    int pull_type;                                    
    char username[USERNAME_LEN];                      
    char groupname[USERNAME_LEN];
} request_pull_group_t __attribute__((aligned(1)));

typedef struct request_send_file_t {              
    proto_head_t head;                             
    char username[USERNAME_LEN];                   
    char friendname[USERNAME_LEN];                  
    int num;
} request_send_file_t __attribute__((aligned(1)));

typedef struct request_pull_filen_t {              
    proto_head_t head;                            
    char username[USERNAME_LEN];                  
} request_pull_file_t __attribute__((aligned(1)));

typedef struct request_pull_group_list_t {             
    proto_head_t head;                            
    char username[USERNAME_LEN];                  
} request_pull_group_list_t __attribute__((aligned(1)));

typedef struct request_pull_group_m_t {              
    proto_head_t head;                                  
    char username[USERNAME_LEN];                        
    char groupname[USERNAME_LEN];                        
} request_pull_group_m_t __attribute__((aligned(1)));

typedef struct request_group_guan_t {              
    proto_head_t head;                               
    char username[USERNAME_LEN];                     
    char ua[USERNAME_LEN];                     
    char groupname[USERNAME_LEN];                    
} request_group_guan_t __attribute__((aligned(1)));

typedef struct request_group_ti_t {              
    proto_head_t head;                             
    char ua[USERNAME_LEN];                         
    char username[USERNAME_LEN];                   
    char groupname[USERNAME_LEN];                  
} request_group_ti_t __attribute__((aligned(1)));







//---------------------------------------------------------------------


#define MSG_LEN 300
typedef struct response_status_t {
    proto_head_t head;
    int status;
    char message[MSG_LEN];
} response_status_t __attribute__((aligned(1)));

#define USERLIST_LEN 1024
typedef struct response_friens_list_t {
    proto_head_t head;
    char userlist[USERLIST_LEN];
} response_friens_list_t __attribute__((aligned(1)));

typedef struct response_pravmessage_t {
    proto_head_t head;
    char username[USERNAME_LEN];
    char target_name[USERNAME_LEN];
    char message[MAX_MESSAGE_LEN];
} response_pravmessage_t __attribute__((aligned(1)));

typedef struct response_groupmessage_t {              
    proto_head_t head;                           
    char username[USERNAME_LEN];                 
    char target_name[USERNAME_LEN];              
    char message[MAX_MESSAGE_LEN];                          
} response_groupmessage_t __attribute__((aligned(1)));

typedef struct response_pull_fri_app {                
    proto_head_t head;                               
    int pull_type;                                   
    char username[USERNAME_LEN];                     
    char friendname[PASSWORD_LEN];                   
} response_pull_fri_app_t __attribute__((aligned(1)));

typedef struct response_pull_fri_chat_history {              
    proto_head_t head;                               
    char username[USERNAME_LEN];                     
    char target_name[USERNAME_LEN];                  
    char message[MAX_MESSAGE_LEN];                          
} response_pull_fri_chat_history_t __attribute__((aligned(1)));

typedef struct response_send_file_t {              
    proto_head_t head;                            
    char username[USERNAME_LEN];                  
    char friendname[USERNAME_LEN];                
    int num;                                      
} response_send_file_t __attribute__((aligned(1)));

typedef struct response_group_list_t {              
    proto_head_t head;                               
    char userlist[USERLIST_LEN];                     
} response_group_list_t __attribute__((aligned(1)));







//-----------------------------------------------------------------------------------------------------------------

request_register_t *create_request_register(const char *username, const char *password);

request_pull_file_t *create_request_pull_file(const char *username);

request_pull_group_list_t *create_request_pull_group_list(const char *username);

request_pull_group_m_t *create_request_pull_group_m(const char *username, char *groupname);

request_group_guan_t *create_request_group_guan(const char *ua, const char *username, char *groupname);

request_group_ti_t *create_request_group_ti(const char *ua, const char *username, char *groupname);

request_login_t *create_request_login(const char *username, const char *password);

request_get_friend_list_t *create_request_get_friend_list(const char *username);

request_add_friend_t *create_request_add_friend(const char *username,const char *friendname);

request_add_friend_back_t *create_request_add_back_friend(int anw, const char *username,const char *friendname);

request_del_friend_t *create_request_del_friend(const char *username,const char *friendname);

request_black_friend_t *create_request_black_friend(const char *username,const char *friendname);

request_pravsend_message_t *create_request_pravsend_message(const char *username, const char *target_name, const char *message);

request_groupsend_message_t *create_request_groupsend_message(const char *username, const char *groupname, const char *message);

request_pull_fri_app_t *create_request_pull_fri_app(int pull_type, const char *username, const char *friendname);

request_agree_add_each_t *create_request_agree_add_each(const char *username, const char *friendname);

request_pull_pravmess_t *create_request_pull_pravmess(int pull_type, const char *username);

request_refresh_pravmess_t *create_request_refresh_pravmess(int pull_type, const char *username);

request_refresh_pravmess_t *create_request_prav_refresh(int pull_type, const char *username);

request_pull_fri_chat_history_t *create_request_pull_fri_chat_history(int pull_type, const char *username, const char *friendname);

request_create_group_t *create_request_create_group(const char * username, const char *groupname);

request_add_group_t *create_request_add_group(const char * username, const char *groupname);

request_back_group_t *create_request_back_group(const char * username, const char *groupname);

request_pull_group_t *create_request_pull_group(int pull_type, const char *username, const char *groupname);

request_send_file_t *create_request_send_file(const char *username, const char *friendname, int num);

//--------------------------------------------------------------------------------------------------------------------------------------------------------
response_status_t *create_response_status(int status, const char *msg);

response_friens_list_t *create_response_friends_list(const char *userlist);

response_group_list_t *create_response_group_list(const char *userlist);

response_pravmessage_t *create_response_pravmessage(const char *username, const char *target_name, const char *message);

response_groupmessage_t *create_response_groupmessage(const char *username, const char *target_name, const char *message);

response_pull_fri_app_t *create_response_pull_fri_app(int pull_type, const char *username, const char *friendname);

response_pravmessage_t *create_response_pull_prav(const char *username, const char *target_name, const char *message);

response_pull_fri_chat_history_t *create_response_pull_fri_chat_history(const char *username, const char *target_name, const char *message);

response_send_file_t *create_response_send_file(const char *username, const char *friendname, int num);

#endif
