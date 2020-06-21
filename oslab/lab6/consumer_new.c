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

sem_t *empty,*full,*mutex;
int shm_out=0;/*缓冲区输出位置*/
int shm_in=0;/*缓冲区输入位置*/
int shmid;/*共享内存名*/
int *shm_a;

void Consumer();
void C();


int main(){
    int i;
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



    /*消费者*/
    for(i=0;i<Cnum;i++)
        if(!fork()){
            shmid=shmget(shmkey,sizeof(int)*11,0);/*打开内存共享区*/
            if(shmid==-1){
                printf("shmget error\n");
                return -1;
            }
            shm=shmat(shmid,0,0);
            shm_a=(int *)shm;
            C();
            return 0;
        }
        wait(NULL);
        sleep(1);
}


void C(){
    int i;
    for(i=0;i<num/Cnum;i++)
        Consumer();
}


void Consumer(){
    int tmp;
    sem_wait(full);
    sem_wait(mutex);/*锁*/


    /*获取buffout*/
    shm_out=shm_a[buffsize];

    /*读取缓冲区内容*/
    tmp=shm_a[shm_out];

    /*buffout++并写入缓冲区*/
    shm_out=(shm_out+1)%buffsize;
    shm_a[buffsize]=shm_out;

    /*输出到终端*/
     printf("%d: %d\n",getpid(),tmp);
     fflush(stdout);

     sem_post(mutex);/*解锁*/
     sem_post(empty);
}
