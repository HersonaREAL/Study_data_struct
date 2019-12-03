/*
邻接矩阵表示图
无向图
图见文件夹附带文档
*/
#include<stdio.h>
#include<stdlib.h>
#define MaxInt 2147483647 //64位系统int最大值
#define MVNum 15 //最大顶点数

struct AM_Graph{
    int vexs[MVNum];//顶点表
    int matrix[MVNum][MVNum];//邻接矩阵
    int vexnum, arcnum;//图的点数和边数
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
                printf("%-3d\n", G.matrix[i][j]);
            else
                printf("%-3d ", G.matrix[i][j]);
        }

}