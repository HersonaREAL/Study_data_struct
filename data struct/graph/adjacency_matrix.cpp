/*
�ڽӾ����ʾͼ
����ͼ
ͼ���ļ��и����ĵ�
*/
#include<stdio.h>
#include<stdlib.h>
#define MaxInt 2147483647 //64λϵͳint���ֵ
#define MVNum 15 //��󶥵���

struct AM_Graph{
    int vexs[MVNum];//�����
    int matrix[MVNum][MVNum];//�ڽӾ���
    int vexnum, arcnum;//ͼ�ĵ����ͱ���
};
bool CreateUDN(AM_Graph &G);
int LocateVex(AM_Graph G, int v);
void PrintUDN(AM_Graph G);

int main(void){
    AM_Graph G;
    if(CreateUDN(G))
        PrintUDN(G);
    system("pause");
    return 0;
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
                printf("%-3d\n", G.matrix[i][j]);
            else
                printf("%-3d ", G.matrix[i][j]);
        }

}