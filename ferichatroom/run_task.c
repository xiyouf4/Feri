#include "run_task.h"
#include "onlinearry.h"
#include "clientallbag.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/types.h>

#define REGISTER 0
#define LOGIN 1
#define FINDPASSWORDBACK 2

typedef struct agreement {
        int type;
        char username[20];
        char password[20];
        char answer[20];
} agreement;

struct Waslogin {
        int type;
        char username[20];
        char selfname[20];
        int onlineyon;
} ;

struct BAGa {
        int type;
        int aona;
        char application[20];
};

MYSQL init_mysql(void)                                                                                              
{
        MYSQL mysql;
        mysql_init(&mysql);
        mysql_library_init(0, NULL, NULL);
        mysql_real_connect(&mysql, "127.0.0.1", "root", "1017129dameinv", "feri_chat_room", 0, NULL, 0);
        mysql_set_character_set(&mysql, "utf8");
        printf("Successful connection to MySQL database!!!\n");
        return mysql;
}

int close_mysql(MYSQL mysql)
{
       mysql_close(&mysql);
       mysql_library_end();
       printf("mysql exit!!\n");
       return 0;
}

int registersql(char *username, char *password, char *answer ,MYSQL mysql)
{
        char a[500];
        char b[500];
        sprintf(a, "insert into account_manage values(0,\"%s\",\"%s\",\"%s\")", username, password, answer);
        if (mysql_query(&mysql, a) == 0) {
                sprintf(b, "create table %s(username varchar(50),black varchar(50))", username);
                mysql_query(&mysql, b);
                return 0;
        } else {
            return -1;
        }
}

int login(char *username, char *password, MYSQL mysql, int fd)
{
        unsigned int i;
        MYSQL_RES *result = NULL;   
        MYSQL_ROW row, rowa;              
        MYSQL_FIELD *field;              
        unsigned int num_fields = 0;
        char a[400], sendbag[500], b[2]="*";
        int only_id, back;
        sprintf(a, "select *from account_manage where username=\"%s\" and password=\"%s\"", username, password);
        mysql_query(&mysql, a);
        result = mysql_store_result(&mysql);
        if (mysql_num_rows(result) > 0) {
                printf("^^^^^^^^\n");
                back = 0;
                send(fd, &back, sizeof(int), 0);
                rowa = mysql_fetch_row(result);
                only_id = *rowa[0]-48;
                mess[only_id].yon = 1;
                mess[only_id].fd = fd;
                strcpy(mess[only_id].username, username);
                printf("*****%s\n", mess[only_id].username);
                printf("*****%d\n", mess[only_id].yon);
                memset(a,0,400);
                sprintf(a, "select *from %s", username);
                mysql_query(&mysql, a);
                result = mysql_store_result(&mysql);
                num_fields = mysql_num_fields(result);
                while ((field = mysql_fetch_field(result))) {
                        strcat(sendbag,field->name);
                        strcat(sendbag, b);
                }
                while((row = mysql_fetch_row(result))) {
                        for (i = 0; i < num_fields; i++) {
                            strcat(sendbag,field->name);
                            strcat(sendbag, b);
                        }
                }
                send(fd, sendbag, sizeof(sendbag), 0);
                printf("%s\n",sendbag);
        } else {
                back = -1;
                send(fd, &back, sizeof(int), 0);
                printf("******@@@@@\n");
        }
        return 0;
}

char *findpassword(char *username, char *answer, MYSQL mysql)
{
        MYSQL_RES *result = NULL;
        MYSQL_ROW row;
        unsigned int num_fields = 0;
        char a[500];
        char *password = (char *)malloc(25*sizeof(char));
        sprintf(a, "select *from account_manage where username=\"%s\" and qa=\"%s\"", username, answer);
        if (mysql_query(&mysql,a) == 0) {
                result = mysql_store_result(&mysql);
                num_fields = mysql_num_fields(result);
                row = mysql_fetch_row(result);
                strncpy(password, row[2], 25);
                return password;                
        } else {                         
            perror("mysql_query");       
            return NULL;
        }                                
}

void WASLOGIN(int fd, MYSQL mysql)
{
        char a[300];
        char b[300];
        int op, i;
        int back, respond;
        struct Waslogin *waslogin = (struct Waslogin *)malloc(sizeof(struct Waslogin)); 
        struct BAGa *pack = (struct BAGa *)malloc(sizeof(struct BAGa));
        printf("%dis ok\n",__LINE__);
        recv(fd, waslogin, sizeof(struct Waslogin), 0);
        printf("%dis ok\n",__LINE__);
        op = waslogin->type;
        switch(op) {
        case 0:
                 printf("%dis ok\n",__LINE__);                                              
                 for (i = 0; i < 1000; i++) {                                
                     if (strcmp(mess[i].username, waslogin->username) == 0) {
                         pack->type = 0;
                         strcpy(pack->application, waslogin->selfname);
                         break;                                              
                     }                                                       
                 }
                 if (i != 1000) {
                        send(mess[i].fd, pack, sizeof(struct BAGa), 0);
                        back = 0;                                      
                        send(fd, &back, sizeof(int), 0);               
                        recv(fd, &respond, sizeof(int), 0);
                        if (respond == 0) {
                                sprintf(a, "insert into %s values(\"%s\",\"no\")",waslogin->selfname, waslogin->username);
                                sprintf(b, "insert into %s values(\"%s\",\"no\")",waslogin->username, waslogin->selfname);
                                printf("%s\n", a);
                                printf("%s\n", b);
                                mysql_query(&mysql,a);
                                mysql_query(&mysql,b);
                                printf("lalalala,haoyoutianjiachenggong\n");
                        }
                 printf("%dis ok\n",__LINE__);                               
            break;
        case 1:
            break;
        case 2:
                printf("%dis ok\n",__LINE__);
                for (i = 0; i < 1000; i++) {
                    if (strcmp(mess[i].username, waslogin->username) == 0) {
                        waslogin->onlineyon = 1;
                        break;
                    }
                }
                printf("%dis ok\n",__LINE__);
            if (i == 1000) {
                waslogin->onlineyon = 0;
            }
                printf("%dis ok\n",__LINE__);
            send(fd, waslogin, sizeof(struct Waslogin), 0);
                printf("%dis ok\n",__LINE__);
            break;
            }
        }
}

int run_task(int fd, int epfd, struct epoll_event ev)
{
        int recvback;
        int regiback;
        char *pass = (char *)malloc(25*sizeof(char));
        MYSQL mysql = init_mysql();
        agreement *agreement = (struct agreement *)malloc(sizeof(struct agreement));
        recvback = recv(fd, agreement, sizeof(struct agreement), 0);
        if(recvback == 0) //对端正常关闭会触发recv 收到0 同时会触发 epollin 和epollDHUP 
        {
            close(fd);
        }
        if(recvback == -1) {
                perror("recv");
                printf("line is %d\n", __LINE__);
        }
        switch(agreement->type) {
                case REGISTER:
                        regiback = registersql(agreement->username, agreement->password, agreement->answer, mysql);
                        printf("regiback = %d ,line is 136,run_task.c\n",regiback);
                        send(fd, &regiback, sizeof(int), 0);
                        break;
                case LOGIN:
                        login(agreement->username, agreement->password, mysql, fd);
                        WASLOGIN(fd, mysql);
                        break;
                case FINDPASSWORDBACK:
                        pass = findpassword(agreement->username, agreement->answer, mysql);
                        if (pass != NULL) {
                                send(fd, pass, sizeof(pass), 0);
                        }
                        free(pass);
                        break;
        }
        epoll_ctl(epfd, EPOLL_CTL_DEL, fd, &ev);
        close(fd);
        return 0;
}
