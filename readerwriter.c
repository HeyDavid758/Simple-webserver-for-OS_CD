/****************
 * readerwriter.c
 *     used to learn readerwriter problem
 * 
 * 
 * compile by:
 * -gcc -std=gnu99 -o readerwriter readerwriter.c -lpthread
 ***************/
#include <stdio.h> 
#include <unistd.h> 
#include <pthread.h>
pthread_rwlock_t rwlock; //读写锁
int num=0;
//读线程函数
void * reader1(){
    for (int i = 0; i < 10; ++i)
    {
        pthread_rwlock_rdlock(&rwlock);
        printf("reader1 reads %d times num = %d\n", i,num);
        pthread_rwlock_unlock(&rwlock);
        sleep(1);
    }
}

void * reader2(){
    for (int i = 0; i < 10; ++i)
    {
        pthread_rwlock_rdlock(&rwlock);
        printf("reader2 reads %d times num = %d\n", i,num);
        pthread_rwlock_unlock(&rwlock);
        sleep(1);
    }
}

//写线程
void * writer1()
{
    for (int i = 0; i < 10; ++i)
    {
        pthread_rwlock_wrlock(&rwlock);
        num++;
        printf("writer1 writes %d times num=%d\n",i,num);
        pthread_rwlock_unlock(&rwlock);
        sleep(1);
    }
}

int main(int argc, char const *argv[])
{
    pthread_t thr1,thr2,thw1; //读线程、写线程
    pthread_rwlock_init(&rwlock,NULL); //初始化读写锁
    //rwlock=PTHREAD_RWLOCK_INITIALIZER; //使⽤宏来初始化读写锁
    //创建读写线程 多个读者，一个写者
    pthread_create(&thr1,NULL,reader1,NULL);
    pthread_create(&thr2,NULL,reader2,NULL);
    pthread_create(&thw1,NULL,writer1,NULL);
    //等待线程结束回收资源
    pthread_join(thr1,NULL);
    pthread_join(thr2,NULL);
    pthread_join(thw1,NULL);
    //销毁读写锁
    pthread_rwlock_destroy(&rwlock);
    return 0;
}