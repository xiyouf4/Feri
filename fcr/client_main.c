#include "client.h"

#include "log.h"
#include "client_menu.h"

int main()
{
    set_log_level(LOG_DEBUG);

    client_init(&client);
    client_start(&client);

    cli_show_menu();

    client_destroy(&client);

    return 0;
}
