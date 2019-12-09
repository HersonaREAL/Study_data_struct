/*
�ڽӾ���������ȱ���
*/
#include<stdio.h>
#include<stdlib.h>
#define MaxInt 2147483647 //64λϵͳint���ֵ
#define MVNum 15 //��󶥵���

//����
typedef struct Node *PtrNode;
typedef PtrNode Position;
typedef struct QNode *Queue;
struct Node
{
    int Data;
    PtrNode Next;
};

//ָ�����ͷ��β�ĸ����ṹ
struct QNode {
    Position Front, Rear; // ���е�ͷ��βָ��
};

Queue CreateQueue();
bool IsEmpty(Queue Q);
void EnQueue(int x,Queue Q);//���
int DeQueue(Queue Q);//����

//ͼ
struct AM_Graph{
    int vexs[MVNum];//�����
    int matrix[MVNum][MVNum];//�ڽӾ���
    int vexnum, arcnum;//ͼ�ĵ����ͱ���
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
    //������������
    Queue Q;
    Q = CreateQueue();
    EnQueue(v, Q);
    while(!IsEmpty(Q)){
        v = DeQueue(Q); //���Ӳ���vΪ���ӵĽ��
        for (int i = 0; i < G.vexnum;i++)
            if((!visited[i])&&(G.matrix[v][i]!=MaxInt)){
                printf("%d ", i);
                visited[i] = true;
                EnQueue(i, Q); //���������ڽӵ����
            }
    }
}


bool CreateUDN(AM_Graph &G){
    int v1_tmp, v2_tmp,w;
    printf("����ͼ�Ķ������������\n");
    scanf("%d%d", &G.vexnum, &G.arcnum);
    if(G.vexnum>15){
        printf("����ʧ��\n");
        return false;
    }
    
    //��ʼ�������
    printf("����%d�������Ϣ\n",G.vexnum);
    for (int i = 0; i < G.vexnum;i++)
        scanf("%d", &G.vexs[i]);

    //�����ʼ��
    for (int i = 0; i < MVNum; i++)
        for (int j = 0; j < MVNum; j++)
            G.matrix[i][j] = MaxInt;

    //��ʼ����
    printf("����ߵ�Ȩ�����ڵĵ�,������%d��\n", G.arcnum);
    for (int i = 0; i < G.arcnum;i++){
        scanf("%d%d%d", &w, &v1_tmp, &v2_tmp);
        if((LocateVex(G, v1_tmp)==-1)||(LocateVex(G, v2_tmp)==-1)){
            printf("����ĵ㲻���ڣ��ڽӱ���ʧ��\n");
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
        Q->Front = TmpNode;//��ʱͷ��βͬʱָ��һ���ڵ�
        Q->Rear = TmpNode;
    }else{
        PtrNode TmpNode = (PtrNode)malloc(sizeof(Node));
        TmpNode->Data = x;
        TmpNode->Next = NULL;
        Q->Rear->Next = TmpNode;//��ʱֻ��Ҫ�ƶ�β������
        Q->Rear = TmpNode;
    }
    //printf("���Ԫ��:%d\n", x);
}

int DeQueue(Queue Q){
    if(IsEmpty(Q)){
        printf("���пգ��޷�����\n");
        return MaxInt;
    }

    PtrNode tmp = Q->Front;

    //����ֻ��һ��Ԫ��
    if(Q->Rear==Q->Front)
        Q->Front = Q->Rear = NULL;
    else
        Q->Front = Q->Front->Next;

    //printf("����Ԫ�أ�%d\n", tmp->Data);
    int tmp_int = tmp->Data;
    free(tmp);
    return tmp_int;
}
