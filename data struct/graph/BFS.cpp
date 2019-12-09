/*
邻接矩阵深度优先遍历
*/
#include<stdio.h>
#include<stdlib.h>
#define MaxInt 2147483647 //64位系统int最大值
#define MVNum 15 //最大顶点数

//队列
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
int DeQueue(Queue Q);//出队

//图
struct AM_Graph{
    int vexs[MVNum];//顶点表
    int matrix[MVNum][MVNum];//邻接矩阵
    int vexnum, arcnum;//图的点数和边数
};
bool CreateUDN(AM_Graph &G);
int LocateVex(AM_Graph G, int v);
void PrintUDN(AM_Graph G);
void BFS(AM_Graph G, int vex);

bool visited[MVNum];

int main(void){
    AM_Graph G;
    if(CreateUDN(G))
        PrintUDN(G);
    BFS(G, 0);
    system("pause");
}


void BFS(AM_Graph G, int v){
    printf("%d ", v);
    visited[v] = true;
    //创建辅助队列
    Queue Q;
    Q = CreateQueue();
    EnQueue(v, Q);
    while(!IsEmpty(Q)){
        v = DeQueue(Q); //出队并赋v为出队的结点
        for (int i = 0; i < G.vexnum;i++)
            if((!visited[i])&&(G.matrix[v][i]!=MaxInt)){
                printf("%d ", i);
                visited[i] = true;
                EnQueue(i, Q); //遍历到的邻接点入队
            }
    }
}


bool CreateUDN(AM_Graph &G){
    int v1_tmp, v2_tmp,w;
    printf("输入图的顶点个数，边数\n");
    scanf("%d%d", &G.vexnum, &G.arcnum);
    if(G.vexnum>15){
        printf("创建失败\n");
        return false;
    }
    
    //初始化顶点表
    printf("输入%d个点的信息\n",G.vexnum);
    for (int i = 0; i < G.vexnum;i++)
        scanf("%d", &G.vexs[i]);

    //矩阵初始化
    for (int i = 0; i < MVNum; i++)
        for (int j = 0; j < MVNum; j++)
            G.matrix[i][j] = MaxInt;

    //开始输入
    printf("输入边的权和相邻的点,共输入%d次\n", G.arcnum);
    for (int i = 0; i < G.arcnum;i++){
        scanf("%d%d%d", &w, &v1_tmp, &v2_tmp);
        if((LocateVex(G, v1_tmp)==-1)||(LocateVex(G, v2_tmp)==-1)){
            printf("输入的点不存在，邻接表创建失败\n");
            return false;
        }

        G.matrix[LocateVex(G, v1_tmp)][LocateVex(G, v2_tmp)] = w;
        G.matrix[LocateVex(G, v2_tmp)][LocateVex(G, v1_tmp)] = w;
    }
    return true;
}

int LocateVex(AM_Graph G, int v){
    for (int i = 0; i < G.vexnum;i++)
        if(v==G.vexs[i])
            return i;
    return -1;
}

void PrintUDN(AM_Graph G){
    for (int i = 0; i < G.vexnum;i++)
        for (int j = 0; j < G.vexnum;j++){
            if(j==G.vexnum-1)
                printf("%-10d\n", G.matrix[i][j]);
            else
                printf("%-10d ", G.matrix[i][j]);
        }
    printf("\n");
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
    if(IsEmpty(Q)){
        PtrNode TmpNode = (PtrNode)malloc(sizeof(Node));
        TmpNode->Data = x;
        TmpNode->Next = NULL;
        Q->Front = TmpNode;//此时头和尾同时指向一个节点
        Q->Rear = TmpNode;
    }else{
        PtrNode TmpNode = (PtrNode)malloc(sizeof(Node));
        TmpNode->Data = x;
        TmpNode->Next = NULL;
        Q->Rear->Next = TmpNode;//此时只需要移动尾部即可
        Q->Rear = TmpNode;
    }
    //printf("入队元素:%d\n", x);
}

int DeQueue(Queue Q){
    if(IsEmpty(Q)){
        printf("队列空，无法出队\n");
        return MaxInt;
    }

    PtrNode tmp = Q->Front;

    //队列只有一个元素
    if(Q->Rear==Q->Front)
        Q->Front = Q->Rear = NULL;
    else
        Q->Front = Q->Front->Next;

    //printf("出队元素：%d\n", tmp->Data);
    int tmp_int = tmp->Data;
    free(tmp);
    return tmp_int;
}
