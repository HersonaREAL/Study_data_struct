#define __LIBRARY__ 
#include <linux/sched.h>
#include <linux/kernel.h>  
#include <asm/segment.h>  
#include <asm/system.h>  
#include <unistd.h>

#define sem_num 32
sem_t semaphore[sem_num];

/*队列函数声明*/
void destoryQ(Queue Q);
struct task_struct* DeQueue(Queue Q);
Queue CreateQueue();
void EnQueue(struct task_struct *x,Queue Q);
int IsEmpty(Queue Q);


/*sem_open() 的功能是创建一个信号量，或打开一个已经存在的信号量。
sem_t 是信号量类型，根据实现的需要自定义。
name 是信号量的名字。不同的进程可以通过提供同样的 name 而共享同一个信号量。
如果该信号量不存在，就创建新的名为 name 的信号量；如果存在，就打开已经存在的名为 name 的信号量。
value 是信号量的初值，仅当新建信号量时，此参数才有效，其余情况下它被忽略。
当成功时，返回值是该信号量的唯一标识（比如，在内核的地址、ID 等），由另两个系统调用使用。如失败，返回值是 NULL。*/
sem_t *sys_sem_open(const char *name, unsigned int value){
    char tmp_name[20];
     int i;

        /*从用户复制字符串*/
    	for( i = 0; i<20; i++){
		char c = get_fs_byte(name+i);
		tmp_name[i] = c;
		if(c =='\0') break;
	}

    /*查找同名并且已经开启的*/
    for(i=0;i<sem_num;i++){
        if(strcmp(tmp_name,semaphore[i].name)==0&&semaphore[i].open)
        return &semaphore[i];
    }

    /*寻找空位创建*/
    for(i=0;i<sem_num;i++){
        if(!semaphore[i].open){
            strcpy(semaphore[i].name,tmp_name);
            semaphore[i].value=value;
            semaphore[i].open=1;
            semaphore[i].Wait_queue=CreateQueue();
            return &semaphore[i];
        }
    }
    printk("sem count max\n");
    return NULL;
}


/*sem_wait() 就是信号量的 P 原子操作。
如果继续运行的条件不满足，则令调用进程等待在信号量 sem 上。
返回 0 表示成功，返回 -1 表示失败。*/
int sys_sem_wait(sem_t *sem){
    cli();
    sem->value--;
    if(sem->value<0){
        current->state = TASK_UNINTERRUPTIBLE;
        EnQueue(current,sem->Wait_queue);
        schedule();
    }
    sti();
    return 0;
}


/*sem_post() 就是信号量的 V 原子操作。
如果有等待 sem 的进程，它会唤醒其中的一个。
返回 0 表示成功，返回 -1 表示失败。*/
int sys_sem_post(sem_t *sem){
    cli();
    sem->value++;
    if(sem->value<=0){
        struct task_struct *tmp=DeQueue(sem->Wait_queue);
        tmp->state=TASK_RUNNING;
    }
    sti();
    return 0;
}


/*sem_unlink() 的功能是删除名为 name 的信号量。
返回 0 表示成功，返回 -1 表示失败。*/
int sys_sem_unlink(const char *name){
    char tmp_name[20];
    int i;
    for(i=0;i<20;i++){
        char c=get_fs_byte(name+i);
        tmp_name[i]=c;
        if(c =='\0') 
            break;
    }
    
    for(i=0;i<sem_num;i++){
       int jud=strcmp(tmp_name,semaphore[i].name);
        if(jud==0&&semaphore[i].open)
            break;
        if(i==sem_num-1&&jud!=0)
            return -1;
    }

    semaphore[i].open=0;
    semaphore[i].value=0;
    destoryQ(semaphore[i].Wait_queue);
    return 0;
}

Queue CreateQueue(){
        Queue tmp;
        tmp=(Queue)malloc(sizeof(struct Qnode));
        tmp->front=tmp->rear=NULL;
        return tmp;
        
}
int IsEmpty(Queue Q){
    return (Q->front==NULL);
}

void EnQueue(struct task_struct *x,Queue Q){
    Ptrnode tmpnode=(Ptrnode)malloc(sizeof(struct node));
    tmpnode->data=x;
    tmpnode->next=NULL;
    if(IsEmpty(Q))
        Q->front=Q->rear=tmpnode;
    else
        Q->rear=Q->rear->next=tmpnode;
}

struct task_struct* DeQueue(Queue Q){
    if(IsEmpty(Q))
        return;
    Ptrnode tmp=Q->front;
    if(Q->rear==Q->front)
        Q->front = Q->rear = NULL;
    else
        Q->front = Q->front->next;

    struct task_struct *p=tmp->data;
    free(tmp);
    return p;

}

void destoryQ(Queue Q){
    if(IsEmpty(Q)){
        free(Q);
        return;
    }
    while(!IsEmpty(Q)){
        Ptrnode tmp=Q->front;
        Q->front=Q->front->next;
        free(tmp);
    }
    free(Q);
}