/*************************************************************************
	> File Name: rw.c
	> Author: 
	> Mail: 
	> Created Time: 2018年01月28日 星期日 02时23分43秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

//1jiaoyichangsuo
int g_count = 0;
pthread_rwlock_t g_lock;

//two roles
void* Write(void* arg)
{
    size_t i = (size_t)arg;
    while(1)
    {
        pthread_rwlock_wrlock(&g_lock);
        ++g_count;
        printf("[%lu] write %d\n",i,g_count);
        pthread_rwlock_unlock(&g_lock);
        usleep(89123);
        printf("[%lu] write %d\n",i,g_count);
    }
    return NULL;
}

void* Read(void* arg)
{
    size_t i = (size_t)arg;
    while(1)
    {
        pthread_rwlock_rdlock(&g_lock);
        printf("[%lu] start read %d\n",i,g_count);
        pthread_rwlock_unlock(&g_lock);
        usleep(23456);
        printf("[%lu] finish read %d\n",i,g_count);
    }
    return NULL;
}

int main()
{
    pthread_rwlock_init(&g_lock,NULL);
    pthread_t tid[8];
    size_t i = 0;
    for(;i<2;++i)
    {
        pthread_create(&tid[i],NULL,Write,(void*)i);
    }
    for(i = 2;i<8;++i)
    {
        pthread_create(&tid[i],NULL,Read,(void*)i);
    }
    for(i = 0;i<8;++i)
    {
        pthread_join(tid[i],NULL);
    }
    pthread_rwlock_destroy(&g_lock);
    return 0;
}
