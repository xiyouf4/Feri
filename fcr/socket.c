#include "socket.h"

//#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>


#include "log.h"

static int FERI_tcp_reuse_addr(int fd) {
    int val = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) < 0) {
        log_errno_error("setsockopt failed!");
        return FERI_ERR;
    }

    return FERI_OK;
}

static int FERI_socket() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        log_errno_error("create socket failed");
        return FERI_ERR;
    }
    if (FERI_tcp_reuse_addr(sock) == FERI_ERR) {
        close(sock);
        return FERI_ERR;
    }
    return sock;
}

int FERI_tcp_listen(const char *addr, int port, int backlog)
{
    int sock = FERI_socket();
    if (sock == FERI_ERR) {
        return FERI_ERR;
    }

    struct sockaddr_in sa;
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    if (inet_pton(AF_INET, addr, &sa.sin_addr) < 0) {
        log_errno_error("inet_pton failed");
        return FERI_ERR;
    }

    if(bind(sock, (struct sockaddr *)&sa, sizeof(sa)) < 0) {
        log_errno_error("bind failed");
        return FERI_ERR;
    }

    if(listen(sock,backlog) < 0) {
        log_errno_error("listen failed");
        return FERI_ERR;
    }

    log_debug("listen on %s:%d, backlog is %d", addr, port, backlog);

    return sock;
}

int FERI_tcp_accept(int fd, char *client_ip, int client_ip_len, int *port)
{
    struct sockaddr_in sa;
    socklen_t len = sizeof(sa);
    int cfd = -1;

    while(1) {
        cfd = accept(fd, (struct sockaddr *)&sa, &len);
        if (cfd < 0) {
            if (errno == EINTR) {
                continue;
            }
            log_errno_error("accept failed");
            return FERI_ERR;
        }
        break;
    }
    if (curr_log_level == LOG_DEBUG) {
        char conn_ip[16] = {0};
        inet_ntop(AF_INET, &(sa.sin_addr), conn_ip, sizeof(conn_ip));
        log_debug("new connection, ip: %s, port: %d", conn_ip, ntohs(sa.sin_port));
    }

    if (client_ip) {
        inet_ntop(AF_INET,&(sa.sin_addr), client_ip, client_ip_len);
    }
    if (port) {
        *port = ntohs(sa.sin_port);
    }

    return cfd;
}

int FERI_tcp_connect(const char *addr, int port)
{
    int sock = FERI_socket();
    if (sock == FERI_ERR) {
        return FERI_ERR;
    }
    struct sockaddr_in sa;
    memset(&sa, 0 ,sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    if (inet_pton(AF_INET, addr, &sa.sin_addr) < 0) {
        log_errno_error("inet_pton failed");
        return FERI_ERR;
    }

    int ret = connect(sock, (struct sockaddr *)&sa, sizeof(sa));
    if (ret < 0) {
        log_errno_error("connect failed");
        return FERI_ERR;
    }

    log_debug("connect to %s:%d", addr, port);

    return sock;
}

int FERI_block_read(int fd, char *buf, int count)
{
    int nread = 0;
    while (nread != count) {
        int ret = read(fd, buf, count - nread);
        if (ret == -1) {
            if (errno == EINTR) {
                continue;
            }
            return ret;
        }
        if (ret == 0) {
            return nread;
        }
        nread += ret;
        buf += ret;
    }

    return nread;
}

int FERI_block_write(int fd, const char *buf, int count)
{
    int nwritten = 0;
    while (nwritten != count) {
        int ret = write(fd, buf, count - nwritten);
        if (ret == -1) {
            if (errno == EINTR) {
                continue;
            }
            return ret;
        }
        if (ret == 0) {
            return nwritten;
        }
        nwritten += ret;
        buf += ret;
    }

    return nwritten;
}






















