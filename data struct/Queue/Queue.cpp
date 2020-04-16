/*
队列的链式存储结构的实现
（1）用随机函数生成10个3位整数（100~999），把这些整数应用入队操作存于队列中；
（2）应用遍历操作输出队列的内容；
（3）把队列的内容翻转，应用出队操作输出队列的内容。
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
typedef struct Node *PtrNode;
typedef PtrNode Position;
typedef struct QNode *Queue;
struct Node
{
    int Data;
    PtrNode Next;
};

//指向队列头和尾的辅助结构
struct QNode {
    Position Front, Rear; // 队列的头、尾指针
};

Queue CreateQueue();
bool IsEmpty(Queue Q);
void EnQueue(int x,Queue Q);//入队
void DeQueue(Queue Q);//出队
void Reverse(Queue Q);//翻转
void OutPutQueue(Queue Q);

int main(void){
    srand((unsigned)time(NULL));
    printf("----------------------------------------\n");
    printf("0.随机十个数存入队列\n");
    printf("1.入队\n");
    printf("2.出队\n");
    printf("3.输出队列\n");
    printf("4.翻转并出队\n");
    printf("5.退出\n");
    printf("----------------------------------------\n");
    printf("请输入相应数字:");

    int judge;
    Queue Q = CreateQueue();
    while(1){
        scanf("%d", &judge);
        switch(judge){
            case 0:{
                for (int i = 0; i < 10;i++)
                    EnQueue((rand() % 900 + 100), Q);
                OutPutQueue(Q);
            }
            break;

            case 1:{
                int x;
                printf("输入入队元素:");
                scanf("%d", &x);
                EnQueue(x, Q);
            }
                break;

            case 2:
                DeQueue(Q);
                break;

            case 3 :
                OutPutQueue(Q);
                break;

            case 4:{
                Reverse(Q);
                while(!IsEmpty(Q)){
                    //全部出队
                    DeQueue(Q);
                }
            }
                break;

            case 5:
                return 0;
            default :
                printf("输入错误\n");
        }
        printf("\n请输入相应数字:");
    }
}



Queue CreateQueue(){
    Queue Q;
    Q = (Queue)malloc(sizeof(QNode));
    Q->Front = NULL;
    Q->Rear = NULL;
    return Q;
}

bool IsEmpty(Queue Q){
    return (Q->Front == NULL);
}

void EnQueue(int x,Queue Q){
    PtrNode TmpNode = (PtrNode)malloc(sizeof(Node));
    TmpNode->Data = x;
    TmpNode->Next = NULL;
    Q->Rear = TmpNode;
    if(IsEmpty(Q))
        Q->Front = TmpNode;//此时头和尾同时指向一个节点
    printf("入队元素:%d\n", x);
}

void DeQueue(Queue Q){
    if(IsEmpty(Q)){
        printf("队列空，无法出队\n");
        return;
    }

    PtrNode tmp = Q->Front;

    //队列只有一个元素
    if(Q->Rear==Q->Front)
        Q->Front = Q->Rear = NULL;
    else
        Q->Front = Q->Front->Next;

    printf("出队元素：%d\n", tmp->Data);
    free(tmp);
}

void OutPutQueue(Queue Q){
    if(IsEmpty(Q)){
        printf("队列空，无法输出\n");
        return;
    }

    PtrNode count=Q->Front;
    printf("输出队列为:");
    while(count!=NULL){
        printf("%d ", count->Data);
        count = count->Next;
    }
    printf("\n");
}

void Reverse(Queue Q){
    if(IsEmpty(Q)){
        printf("队列空，无法翻转\n");
        return;
    }
    PtrNode pre = Q->Front;   //排前面的辅助节点
    PtrNode cur = pre->Next;//当前节点
    PtrNode aft; //排后面的辅助节点
    Q->Front->Next = NULL;
    while(cur){
        aft = cur->Next; //排到当前节点后
        cur->Next = pre; //把前一节点地址存入当前节点Next
        pre = cur;  //把前一节点移动到当前节点
        cur = aft;  //当前节点也往后移动
    }
    
    //交换front和rear
    Q->Rear = Q->Front;
    Q->Front = pre;
}
