#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
static void *threadfuc(void *arg)
{
    char *s=(char *)arg;
    printf("%s",s);//这个地方的s不应该是个指针吗？要输出hello world不应该是*s吗,要解引用的啊！！！？
    return (void *)strlen(s);
}
int main()
{
    pthread_t t1;
    void *res;
    int s;
    s=pthread_create(&t1, NULL, threadfuc, "hello world\n");//第三个参数为void *(*start)(void *)的意义为
    //这是一个函数指针它的名字叫做start,它指向的函数的参数为一个不确定类型的指针，并且pthread_create()的
    //第三个参数也是不确定指向类型的指针
    if (s != 0)
        printf("errno:pthread_create\n");
    s=pthread_join(t1,&res);//第二个参数为void**arg,是说这是个不确定指向类型的二级指针？？
    if (s != 0)
        printf("errno:pthread_join\n");
    printf("thread return %ld\n",(long)res);//因为线程终止时的返回不为空，那么这个地方的res应该是线程
//返回的值的拷贝，因为线程返回值为void*那么res的值应该是一个指针啊，要正确的输出12不应该是*res吗？

    exit(EXIT_SUCCESS);
}
