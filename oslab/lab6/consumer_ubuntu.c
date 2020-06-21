#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define num 500  /*打印字符个数*/
#define Cnum 20 /*消费者数量*/
#define buffsize 10 /*缓冲区大小*/
#define shmkey 23

sem_t *empty,*full,*mutex;
int shm_out=0;/*缓冲区输出位置*/
int shm_in=0;/*缓冲区输入位置*/
int shmid;/*共享内存名*/
int *shm_a;

void Consumer();
void C();


int main(){
    /*打开信号量*/
    if((empty=sem_open("empty",O_CREAT,0666,buffsize))==SEM_FAILED){
        perror("sem_open error1\n");
        return -1;
    }  
      if((full=sem_open("full",O_CREAT,0666,0))==SEM_FAILED){
        perror("sem_open error2\n");
        return -1;
    }   
     if((mutex=sem_open("mutex",O_CREAT,0666,1))==SEM_FAILED){
        perror("sem_open error3\n");
        return -1;
    }

   shmid=shmget(shmkey,sizeof(int)*11,IPC_CREAT|0666);/*打开内存共享区*/
       if(shmid==-1){
        printf("shmget error\n");
        return -1;
    }
    void *shm=shmat(shmid,0,0);
    shm_a=(int *)shm;

    /*消费者*/
    for(int i=0;i<Cnum;i++)
        if(!fork()){
        C();
        return 0;
        }
        wait(NULL);
        sleep(1);
}


void C(){
    for(int i=0;i<num/Cnum;i++)
        Consumer();
}


void Consumer(){
       sem_wait(full);
       sem_wait(mutex);/*锁*/


    /*获取buffout*/
    shm_out=shm_a[buffsize];

    /*读取缓冲区内容*/
    int tmp;
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
