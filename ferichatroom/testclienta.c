#include <stdio.h>                                                                                          
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
        char recv_buf[500] = "feri is peri!!!";
        char send_buf[500] = "feri is peri!!!";
        char send_bufa[500] = "feri is feri *****8";
        struct sockaddr_in serv_addr;
        int conn_fd;
        memset(&serv_addr, 0, sizeof(struct sockaddr_in));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(4510);
        inet_aton("192.168.3.96", &serv_addr.sin_addr);
        conn_fd = socket(AF_INET, SOCK_STREAM, 0);
        connect(conn_fd , (struct sockaddr *)&serv_addr, sizeof(struct sockaddr));
        send(conn_fd, send_buf, sizeof(send_buf), 0);
        recv(conn_fd, recv_buf, sizeof(recv_buf), 0);
        send(conn_fd, send_bufa, sizeof(send_bufa), 0);
        printf("%s\n",recv_buf);
        return 0;
}
