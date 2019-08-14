#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <pthread.h>

struct BAG {
        int type;
        int aona;
        char application[20];
        struct BAG *next;
};

struct BAGa {                 
        int type;            
        int aona;            
        char application[20];
};                           

void *allbag(void *fd)
{
        int conn_fd;
        conn_fd = *((int *)fd);
        struct BAG *temp, *start, *pnew;
        struct BAGa *pack;
        pack = (struct BAGa *)malloc(sizeof(struct BAGa));
        start = (struct BAG *)malloc(sizeof(struct BAG));
        pnew = (struct BAG *)malloc(sizeof(struct BAG));
        start->next = NULL;
        temp = start;

        while(1) {
                recv(conn_fd, pack, sizeof(struct BAG), 0);
                pnew->type = pack->type;                                            
                strcpy(pnew->application, pack->application);                         
                temp->next = pnew;                                        
                temp = pnew;                                              
                printf("**line is=%d       %d\n",__LINE__,pack->type);
                printf("**line is=%d       %s\n",__LINE__,pack->application);      
                sleep(100);
        }

}
