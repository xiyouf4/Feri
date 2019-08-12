#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <unistd.h>
#include <sys/socket.h>
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
        sprintf(a, "insert into account_manage values(0,\"%s\",\"%s\",\"%s\")", username, password, answer);
        printf("%s\n",a);
        if(mysql_query(&mysql, a) == 0)
        {
            return 0;
        } else {
                perror("mysql_query");
            return -1;
        }
}

int login(char *username, char *password, MYSQL mysql)
{
        char a[500];
        sprintf(a, "select *from account_manage where username=\"%s\" and password=\"%s\"", username, password);
        if (mysql_query(&mysql,a) == 0) {
                return 0;
        } else {
            perror("mysql_query");
            return -1;
        }
        return 0;
}

int findpassword(char *username, char *answer, MYSQL mysql)
{
        MYSQL_RES *result = NULL;
        MYSQL_ROW row;
        unsigned int num_fields = 0;
        unsigned int i;
        char a[500];
        //char password[25];
        sprintf(a, "select *from account_manage where username=\"%s\" and qa=\"%s\"", username, answer);
        if (mysql_query(&mysql,a) == 0) {
                result = mysql_store_result(&mysql);
                num_fields = mysql_num_fields(result);
                row = mysql_fetch_row(result);
                for (i = 0; i < num_fields; i++) {
                        printf("%-10s\n", row[i]);
                }
                return 0;                
        } else {                         
            perror("mysql_query");       
            return -1;                   
        }                                
        return 0;                        
}
int run_task(int fd)
{
        int recvback;
        int regiback;
        int logback;
        MYSQL mysql = init_mysql();
        agreement *agreement = (struct agreement *)malloc(sizeof(struct agreement));
        recvback = recv(fd, agreement, sizeof(struct agreement), 0);
        if(recvback == -1) {
                perror("recv");
        }
        switch(agreement->type) {
                case REGISTER:
                        regiback = registersql(agreement->username, agreement->password, agreement->answer, mysql);
                        send(fd, &regiback, sizeof(int), 0);
                        break;
                case LOGIN:
                        logback = login(agreement->username, agreement->password, mysql);
                        send(fd, &logback, sizeof(int), 0);
                        break;
                case FINDPASSWORDBACK:
                        findpassword(agreement->username, agreement->answer, mysql);
                        break;
        }
        close(fd);
        return 0;
}

