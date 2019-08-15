#include "clientallbag.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <pthread.h>

struct BAG {
        int type;
        int aona;
        char messagefrom[20];
        char application[20];
        char message[1000];
        struct BAG *next;
};

struct BAGa {                 
        int type;            
        int aona;            
        char messagefrom[20];
        char application[20];
        char message[1000];
};                           

void *allbag(void *fd)
{
        printf("clientallbag.c %d is ok\n",__LINE__);
        int conn_fd;
        conn_fd = *((int *)fd);
        struct BAG *temp, *pnew;
        struct BAGa *pack;
        printf("clientallbag.c %d is ok\n",__LINE__);
        pack = (struct BAGa *)malloc(sizeof(struct BAGa));
        start = (struct BAG *)malloc(sizeof(struct BAG));
        pnew = (struct BAG *)malloc(sizeof(struct BAG));
        start->next = NULL;
        temp = start;
        printf("clientallbag.c %d is ok\n",__LINE__);
        while(1) {
                recv(conn_fd, pack, sizeof(struct BAG), 0);
                printf("%d is ok\n",__LINE__);
                pnew->type = pack->type;                                            
                strcpy(pnew->application, pack->application);                         
                strcpy(pnew->messagefrom, pack->messagefrom);                         
                strcpy(pnew->message, pack->message);                         
                temp->next = pnew;                                        
                temp = pnew;                                              
                printf("** clientallbag.c line is=%d       %d\n",__LINE__,pack->type);
                printf("**clientallbag.c line is=%d       %s\n",__LINE__,pack->application);      
                sleep(10);
        }
}
