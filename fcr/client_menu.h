#ifndef CLIENT_MENU_H
#define CLIENT_MENU_H

typedef enum cli_status {
    INIT = 1,
    LOGIN,
    REGISTER,
    EXIT,
} cli_status_t;

void cli_show_menu();

cli_status_t show_init_menu();
cli_status_t show_register_menu();
cli_status_t show_login_menu();


#endif
