#include "box.h"

#include "stdlib.h"

typedef struct BOX {
    int type;
    char username[32];
    char friendname[32];
    struct BOX *next;
} box_t;

void *box(void *fd)
{
        int conn_fd;
        conn_fd = *((int *)fd);
        box_t *temp, *pnew, *start;
        start = (box_t *)malloc(sizeof(box_t));
        start->next = NULL;
        temp = start;
        pnew = (box_t*)malloc(sizeof(box_t));
        while(1) {
                recv(conn_fd, pack, sizeof(struct BAG), 0);
                pnew->type = pack->type;
                strcpy(pnew->application, pack->application);
                strcpy(pnew->messagefrom, pack->messagefrom);
                strcpy(pnew->message, pack->message);
                temp->next = pnew;
                temp = pnew;
                pnew = (box_t*)malloc(sizeof(box_t));
        }
}
