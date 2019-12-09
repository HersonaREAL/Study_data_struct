/*
����ķ�㷨
*/
#include<stdio.h>
#include<stdlib.h>
#define MaxInt 2147483647 //64λϵͳint���ֵ
#define MVNum 15 //��󶥵���

//�ڽӾ���
struct AM_Graph{
    int vexs[MVNum];//�����
    int matrix[MVNum][MVNum];//�ڽӾ���
    int vexnum, arcnum;//ͼ�ĵ����ͱ���
};
bool CreateUDN(AM_Graph &G);
int LocateVex(AM_Graph G, int v);
void PrintUDN(AM_Graph G);

//prim�����ṹ
struct closedge{
    int adjvex;//��С����U�еĶ���
    int lowcast;//��С���ϵ�Ȩ
};
void MiniSpanTree_Prim(AM_Graph G, int u);

int main(void){
    AM_Graph G;
    int tmp;
    if(CreateUDN(G))
        PrintUDN(G);
    printf("���ĸ����㿪ʼ����?\n");
    scanf("%d", &tmp);
    MiniSpanTree_Prim(G, tmp);
    system("pause");
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

}

void MiniSpanTree_Prim(AM_Graph G, int u){
    int k;
    closedge c_edge[G.vexnum];
    k = LocateVex(G, u);
    //��ʼ��closedge����u������������Ϊmaxint
    for (int i = 0; i < G.vexnum;i++)
        if(i!=k){
            c_edge[i].adjvex = u;
            c_edge[i].lowcast = G.matrix[k][i];
        }
    c_edge[k].lowcast = 0;//��u����U��

    //��ʼ������С������
    for (int i = 1; i < G.vexnum;i++){
        //ѡ����T����һ�����
        int tmp_min = MaxInt; //����ѡ��СȨ�Ĺ��߱���
        //��c_edgeѡ����Сk
        for (int j = 0; j < G.vexnum;j++)
            if(c_edge[j].lowcast&&c_edge[j].lowcast<tmp_min){
                tmp_min = c_edge[j].lowcast;
                k = j; //kΪ��һ�����
            }

        printf("%d--%d\n", c_edge[k].adjvex, G.vexs[k]);//c_edge[k].adjvex��U�ڣ�G.vexs[k]��V-U��
        c_edge[k].lowcast = 0;//����u����U��

        //����c_edge�йش�ʱvexs[k]����СȨ�ı�
        for (int j = 0; j < G.vexnum;j++)
            //�ڽӾ����Ȩֵ��ԭ��lowcastС�ʹ�������Ȩֵ��С�ıߣ���ʱe_edge��U�ڶ��㲻��vexs[k]��
            if(G.matrix[k][j]<c_edge[j].lowcast){
                c_edge[j].adjvex = G.vexs[k];//����c_edge��U�Ķ���
                c_edge[j].lowcast = G.matrix[k][j];
            }
    }
}