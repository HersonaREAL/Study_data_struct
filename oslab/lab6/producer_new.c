#define   __LIBRARY__
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

_syscall2(sem_t*,sem_open,const char *,name,unsigned int,value);
_syscall1(int,sem_wait,sem_t*,sem);
_syscall1(int,sem_post,sem_t*,sem);
_syscall1(int,sem_unlink,const char *,name);

_syscall3(void*,shmget,key_t,key, int,size, int,shmflg);
_syscall3(int,shmat,int,shmid, const void *,shmaddr, int,shmflg);

#define num 500  /*打印字符个数*/
#define Cnum 20 /*消费者数量*/
#define buffsize 10 /*缓冲区大小*/
#define shmkey 11

void Producer(int x);
void P();

sem_t *empty,*full,*mutex;
int shm_out=0;/*缓冲区输出位置*/
int shm_in=0;/*缓冲区输入位置*/
int shmid;/*共享内存名*/
int *shm_a;

int main(){
    void *shm;
    /*打开信号量*/
    if((empty=sem_open("empty",buffsize))==NULL){
        perror("sem_open error1\n");
        return -1;
    }  
      if((full=sem_open("full",0))==NULL){
        perror("sem_open error2\n");
        return -1;
    }   
     if((mutex=sem_open("mutex",1))==NULL){
        perror("sem_open error3\n");
        return -1;
    }

    shmid=shmget(shmkey,sizeof(int)*11,0);/*打开内存共享区*/
    if(shmid==-1){
        printf("shmget error\n");
        return -1;
    }
    shm=shmat(shmid,0,0);
    shm_a=(int *)shm;
    shm_a[buffsize]=shm_out;

    /*生产者*/
      P();
      sleep(1);
      sem_unlink("empty");
      sem_unlink("full");
      sem_unlink("mutex");
}

void P(){
    int i;
    for(i=0;i<num;i++)
        Producer(i);

}

void Producer(int x){
    sem_wait(empty);
    sem_wait(mutex);

    /*写入*/
    shm_a[shm_in]=x;
    shm_in=(shm_in+1)%buffsize;
    
    sem_post(mutex);
    sem_post(full);
}
