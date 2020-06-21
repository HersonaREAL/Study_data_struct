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

void Producer(int x);
void P();

sem_t *empty,*full,*mutex;
int shm_out=0;/*缓冲区输出位置*/
int shm_in=0;/*缓冲区输入位置*/
int shmid;/*共享内存名*/
int *shm_a;

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
    shm_a[buffsize]=shm_out;

    /*生产者*/
    if(!fork()){
        P();
        return 0;
        }

      wait(NULL);
      sem_unlink("empty");
      sem_unlink("full");
      sem_unlink("mutex");
      shmctl(shmid,IPC_RMID,0);/*释放共享内存*/
}

void P(){
    for(int i=0;i<num;i++)
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
