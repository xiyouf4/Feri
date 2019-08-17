#include "client.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "all.h"
#include "socket.h"
#include "proto.h"
#include "log.h"

#define DEFAULT_ADDR "127.0.0.1"

int client_init(client_t *client)
{
    client->conn_fd = 0;

    return FERI_OK;
}

int client_start(client_t *client)
{
    client->conn_fd = FERI_tcp_connect(DEFAULT_ADDR, LISTEN_PORT);
    if (client->conn_fd < 0) {
        log_warn("client conn %s:%d failed", DEFAULT_ADDR, LISTEN_PORT);
        abort();
    }

    return FERI_OK;
}

void client_destroy(client_t *client)
{
    log_warn("client conn %s:%d closed", DEFAULT_ADDR, LISTEN_PORT);
    close(client->conn_fd);
}

