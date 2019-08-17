#ifndef SOCKET_H
#define SOCKET_H

#include "all.h"

int FERI_tcp_listen(const char *addr, int port, int backlog);
int FERI_tcp_connect(const char *addr, int port);
int FERI_tcp_accept(int fd, char *client_ip, int client_ip_len, int *port );

int FERI_block_read(int fd, char *buf, int count);
int FERI_block_write(int fd, const char *buf, int count);

#endif
