#include "server.h"

#include <stdio.h>
#include <signal.h>


int main()
{
    signal(SIGINT, signal_handle);

    server_init(&server);

    server_start(&server);

    server_run(&server);

    server_destory(&server);
}
