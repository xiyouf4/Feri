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
    EXITA,
} cli_statusa_t;          

typedef enum messbox_status {
    INITB = 1,            
    FRIEND_APPLICATION,               
    GROUP_APPLICATION,            
    PRAV,
    GROUP_,
    FILEN,
    GROUP_TELL,
    EXITB,                
} messbox_status_t;          






void cli_show_menu();

cli_status_t show_init_menu();
cli_status_t show_register_menu();
cli_status_t show_login_menu();


#endif
