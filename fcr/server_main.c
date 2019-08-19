#include "server.h"

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


int main()
{
    //queue_t *queuee = (queue_t *)malloc(sizeof(queue_t));

    signal(SIGINT, signal_handle);

    server_init(&server);

    server_start(&server);

    server_run(&server);

    server_destory(&server);
}
