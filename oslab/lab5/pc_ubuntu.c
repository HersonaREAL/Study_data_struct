#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <semaphore.h>

#define num 500  /*打印字符个数*/
#define Cnum 20 /*消费者数量*/
#define buffsize 10 /*缓冲区大小*/

void Producer(int x);
void Consumer();
void P();
void C();
sem_t *empty,*full,*mutex;
int buffout=0;/*缓冲区输出位置*/
int buffin=0;/*缓冲区输入位置*/
int fbuff;/*文件名*/

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

    fbuff=open("fbuff",O_RDWR|O_CREAT,0666);
    lseek(fbuff,buffsize*sizeof(int),SEEK_SET);
    write(fbuff,(char*)&buffout,sizeof(int));/*out位置写入十一位方便消费者进程通信*/

    /*生产者*/
   if(!fork()){
        P();
        return 0;
        }

    /*消费者*/
    for(int i=0;i<Cnum;i++)
        if(!fork()){
        C();
        return 0;
        }

      wait(NULL);
      sem_unlink("empty");
      sem_unlink("full");
      sem_unlink("mutex");
      close(fbuff);
      sleep(1);
}

void P(){
    for(int i=0;i<num;i++)
        Producer(i);

}

void C(){
    for(int i=0;i<num/Cnum;i++)
        Consumer();
}



void Producer(int x){
    sem_wait(empty);
    sem_wait(mutex);

    /*文件缓冲区写入*/
    lseek(fbuff,buffin*sizeof(int),SEEK_SET);
    write(fbuff,(char*)&x,sizeof(int));
    buffin=(buffin+1)%buffsize;
    
    sem_post(mutex);
    sem_post(full);
}

void Consumer(){
       sem_wait(full);
       sem_wait(mutex);/*锁*/

    /*删除文件缓冲区内容并读出到标准输出*/

    /*获取buffout*/
    lseek(fbuff,buffsize*sizeof(int),SEEK_SET);
    read(fbuff,(char*)&buffout,sizeof(int));

    /*读取缓冲区内容*/
    int tmp;
    lseek(fbuff,buffout*sizeof(int),SEEK_SET);
    read(fbuff,(char*)&tmp,sizeof(int));

    /*buffout++并写入缓冲区*/
    buffout=(buffout+1)%buffsize;
    lseek(fbuff,buffsize*sizeof(int),SEEK_SET);
    write(fbuff,(char*)&buffout,sizeof(int));

    /*输出到终端*/
     printf("%d: %d\n",getpid(),tmp);
     fflush(stdout);

     sem_post(mutex);/*解锁*/
     sem_post(empty);
}
