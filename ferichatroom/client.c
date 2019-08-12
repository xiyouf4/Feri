#include <stdio.h>                                                                                          
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SUCCESS 0
#define FAILED -1
typedef struct agreement {
        int type;
        char username[20];
        char password[20];
        char answer[20];
        int success;
        int failed;
} Agreement;

void print()                        
{                                   
        printf("Lgoin(1)\n");       
        printf("register(0)\n");    
        printf("findpassword(2)\n");
}                                   

int client_init()
{
        struct sockaddr_in serv_addr;                                             
        int conn_fd;                                                              
        memset(&serv_addr, 0, sizeof(struct sockaddr_in));                        
        serv_addr.sin_family = AF_INET;                                           
        serv_addr.sin_port = htons(4510);                                         
        inet_aton("192.168.3.96", &serv_addr.sin_addr);                           
        conn_fd = socket(AF_INET, SOCK_STREAM, 0);                                
        connect(conn_fd , (struct sockaddr *)&serv_addr, sizeof(struct sockaddr));
        print();                                                                  
        return conn_fd;
}

int pack_out(Agreement *agreement, int conn_fd)
{
        int back;                                                                      
        int backa = -1;
        send(conn_fd, agreement, sizeof(struct agreement), 0);                             
        recv(conn_fd, &back, sizeof(int), 0);                                          
        if (back == SUCCESS) {                                                         
                backa = 0;
        } else if (back == FAILED) {
                backa = 1;                                                                                  
        }                                                    
        return backa;
}

int main()
{
        char comp[20];
        Agreement *agreement = (struct agreement *)malloc(sizeof(struct agreement));
        int conn_fd;
        conn_fd = client_init();
        scanf("%d",&agreement->type);
        switch(agreement->type) {
                case 0:
                        printf("\nplease enter your username:  ");                                         
                        scanf("%s", agreement->username);                                                  
                        do {                                                                               
                                printf("if you need input again because two inconsistencies in input!!!!");
                                printf("\nplease enter your password:  ");                                 
                                scanf("%s", agreement->password);                                          
                                printf("\nplease enter your password again:  ");                           
                                scanf("%s", comp);                                                         
                        } while(strcmp(comp, agreement->password) != 0);                                   
                        printf("scurity question||your real name:  ");                                   
                        scanf("%s", agreement->answer);
                        int a = pack_out(agreement, conn_fd);
                        if(a == 0) {
                                printf("register was successful\n");                                       
                        } else {
                                printf("register was failed\n");                                               
                        }
                        break;
                case 1:
                        printf("username:  ");
                        scanf("%s", agreement->username);
                        printf("password:  ");
                        scanf("%s", agreement->password);
                        int b = pack_out(agreement, conn_fd);
                        if (b == 0) {
                                printf("login was successful\n");                                       
                        } else {
                                printf("register was failed\n");                                               
                        }
                        break;
                case 2:
                        printf("username:   ");
                        scanf("%s", agreement->username);
                        printf("what's your real name:   ");
                        scanf("%s", agreement->answer);
                        send(conn_fd, agreement, sizeof(struct agreement), 0);                             
                        char *pass = (char *)malloc(25*sizeof(char));
                        recv(conn_fd, pass, sizeof(pass), 0);
                        if (pass != NULL) {
                            printf("your password is:  %s\n",pass);
                        } else {
                            printf("not found!!!\n");
                        }
                        break;
        }
        return 0;
}
