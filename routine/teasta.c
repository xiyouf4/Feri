#include <stdio.h>
#include <pthread.h>
static int glob = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
static void *threadfunc(void *arg)
{
        int loops = *((int *) arg);
        int j;
        pthread_mutex_lock(&mtx);
        for (j = 0; j < loops; j++){
                ++glob;
        }
        pthread_mutex_unlock(&mtx);
        return NULL;
}
int main()
{
        pthread_t t1,t2;
        int loops = 10000;
        pthread_create(&t1, NULL, threadfunc, &loops);
        pthread_create(&t2, NULL ,threadfunc, &loops);
        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
        printf("glob = %d\n", glob);
        return 0;
}

