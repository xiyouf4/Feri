#include "clientallbag.h"

#include <stdio.h>                                                                                          
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
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
} Agreement;

typedef struct Waslogin {
        int type;
        char username[20];
        char selfname[20];
        int onlineyon;
} waslogin;

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
        size_t i;
        char sendbag[500];
        memset(sendbag, 0, 500);
        int back;                                                                      
        send(conn_fd, agreement, sizeof(struct agreement), 0);                             
        recv(conn_fd, sendbag, sizeof(sendbag), 0);
        recv(conn_fd, &back, sizeof(int), 0);                                          
        printf("back is %d,line is 49\n", back);
        for (i= 0; i < strlen(sendbag); i++) {
            if (sendbag[i] == '*') {
                printf("        ");
            }
            if (sendbag[i] != '*') {
                printf("%c", sendbag[i]);
            }
        }
        return back;
}

void WASLOGIN(int fd, char *username)
{
        int op;
        int opa;
        waslogin *waslogin = (struct Waslogin *)malloc(sizeof(struct Waslogin));
        printf("*set up(0)       query(1)\n"); 
        scanf("%d",&op);
        switch(op) {
        case 0:
                printf("Add friends(0)      delete friends(1)\n");
                scanf("%d", &opa);
                if (opa == 0) {
                        strcpy(waslogin->selfname, username);
                        printf("selfname = %s, line is%d\n", waslogin->selfname, __LINE__);
                        waslogin->type = 0;
                        printf("username:       ");
                        scanf("%s", waslogin->username);
                        send(fd, waslogin, sizeof(struct Waslogin), 0);
                        printf("friends application send success,please waiting for the other party's consent\n");

                } else if (opa == 1) {

                }
                break;
        case 1:
                printf("please enter your friends username:     ");
                scanf("%s", waslogin->username);
                waslogin->type = 2;
                send(fd, waslogin, sizeof(struct Waslogin), 0);
                recv(fd, waslogin, sizeof(struct Waslogin), 0);
                if(waslogin->onlineyon == 1) {
                        printf("%s      on-line\n", waslogin->username);
                } else if (waslogin->onlineyon == 0) {
                        printf("%s      off-line\n", waslogin->username);
                }
            break;
        }
}


int main()
{
        int back;
        size_t i;
        pthread_t pid;
        char comp[20];
        Agreement *agreement = (struct agreement *)malloc(sizeof(struct agreement));
        int conn_fd;
        char sendbag[500];
        memset(sendbag, 0, 500);
        conn_fd = client_init();
        scanf("%d",&agreement->type);
        int m = agreement->type;
        switch(m) {
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
                        int a = 0;
                        send(conn_fd, agreement, sizeof(struct agreement), 0);                             
                        recv(conn_fd, &a, sizeof(int), 0);                                          
                        printf("a=%d,line is 81\n", a);
                        if(a == SUCCESS) {
                                printf("register was successful\n");                                       
                        } else if (a == FAILED) {
                                printf("register was failed\n");                                               
                        }
                        break;
                case 1:
                        printf("username:  ");
                        scanf("%s", agreement->username);
                        printf("password:  ");
                        scanf("%s", agreement->password);
                        send(conn_fd, agreement, sizeof(struct agreement), 0);                             
                        recv(conn_fd, &back, sizeof(int), 0);                        
                        printf("%d is ok\n",__LINE__);
                        printf("******back is %d,line is 49\n", back);                     
                        if (back == SUCCESS) {
                                printf("login was success!\n");
                                recv(conn_fd, sendbag, sizeof(sendbag), 0);                  
                                for (i= 0; i < strlen(sendbag); i++) {   
                                        if (sendbag[i] == '*') {         
                                                printf("        ");      
                                        }                                
                                        if (sendbag[i] != '*') {         
                                                printf("%c", sendbag[i]);
                                        }                                
                                }                                        
                                pthread_create(&pid, NULL, allbag, (void *)&conn_fd);
                        } else if (back == FAILED) {
                                printf("login was failed!\n");
                        }
                        for (i= 0; i < strlen(sendbag); i++) {                       
                                if (sendbag[i] == '*') {                                 
                                        printf("        ");                                  
                                }                                                        
                                if (sendbag[i] != '*') {                                 
                                        printf("%c", sendbag[i]);                            
                                }                                                        
                        }                                                            
                        printf("\n");
                        //while (1) {
                                WASLOGIN(conn_fd, agreement->username);
                        //} 
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
