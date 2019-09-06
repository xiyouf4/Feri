#ifndef CLIENT_MENU_H
#define CLIENT_MENU_H

typedef enum cli_status {
    INIT = 1,
    LOGIN,
    REGISTER,
    EXIT,
} cli_status_t;

typedef enum cli_statusa {
    INITA = 1,
    PRAV_chat,            
    ALL_chat,               
    ADD_friend,            
    DEL_friend,                
    LIST_friend,
    BLACK_friend,
    FRI_chat_history,
    CREATE_group,
    ADD_group,
    BACK_group,
    FILEE,
    REFRESH,
    PULL_GROUP_LIST,
    PULL_GROUP_M,
    GROUP_GUAN,
    GROUP_TI,
    GROUP_RECORD,
    EXITA,
} cli_statusa_t;          

typedef enum messbox_status {
    INITB = 1,            
    FRIEND_APPLICATION = 2,               
    GROUP_APPLICATION = 3,            
    PRAV = 4,
    GROUP_ = 5,
    FILEN = 6,
    GROUP_TELL = 7,
    FRI_CHAT_HISTORY = 8,
    EXITB,                
} messbox_status_t;          


void cli_show_menu();

cli_status_t show_init_menu();
cli_status_t show_register_menu();
cli_status_t show_login_menu();


#endif
