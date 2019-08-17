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
    EXITA
} cli_statusa_t;          













void cli_show_menu();

cli_status_t show_init_menu();
cli_status_t show_register_menu();
cli_status_t show_login_menu();


#endif
