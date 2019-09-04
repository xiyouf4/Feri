#include "server.h"

#include "mysql.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


int main()
{

    signal(SIGINT, signal_handle);

    myserver_init();

    server_init(&server);

    server_start(&server);

    server_run(&server);

    server_destory(&server);
}
