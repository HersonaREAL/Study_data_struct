/*
普利姆算法
*/
#include<stdio.h>
#include<stdlib.h>
#define MaxInt 2147483647 //64位系统int最大值
#define MVNum 15 //最大顶点数

//邻接矩阵
struct AM_Graph{
    int vexs[MVNum];//顶点表
    int matrix[MVNum][MVNum];//邻接矩阵
    int vexnum, arcnum;//图的点数和边数
};
bool CreateUDN(AM_Graph &G);
int LocateVex(AM_Graph G, int v);
void PrintUDN(AM_Graph G);

//prim辅助结构
struct closedge{
    int adjvex;//最小边在U中的顶点
    int lowcast;//最小边上的权
};
void MiniSpanTree_Prim(AM_Graph G, int u);

int main(void){
    AM_Graph G;
    int tmp;
    if(CreateUDN(G))
        PrintUDN(G);
    printf("从哪个顶点开始生成?\n");
    scanf("%d", &tmp);
    MiniSpanTree_Prim(G, tmp);
    system("pause");
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

}

void MiniSpanTree_Prim(AM_Graph G, int u){
    int k;
    closedge c_edge[G.vexnum];
    k = LocateVex(G, u);
    //初始化closedge，与u相连，不相连为maxint
    for (int i = 0; i < G.vexnum;i++)
        if(i!=k){
            c_edge[i].adjvex = u;
            c_edge[i].lowcast = G.matrix[k][i];
        }
    c_edge[k].lowcast = 0;//把u并入U集

    //开始生成最小生成树
    for (int i = 1; i < G.vexnum;i++){
        //选出树T的下一个结点
        int tmp_min = MaxInt; //用来选最小权的工具变量
        //在c_edge选出最小k
        for (int j = 0; j < G.vexnum;j++)
            if(c_edge[j].lowcast&&c_edge[j].lowcast<tmp_min){
                tmp_min = c_edge[j].lowcast;
                k = j; //k为下一个结点
            }

        printf("%d--%d\n", c_edge[k].adjvex, G.vexs[k]);//c_edge[k].adjvex在U内，G.vexs[k]在V-U内
        c_edge[k].lowcast = 0;//把新u并入U集

        //更新c_edge有关此时vexs[k]的最小权的边
        for (int j = 0; j < G.vexnum;j++)
            //邻接矩阵的权值比原来lowcast小就存在这条权值最小的边（此时e_edge的U内顶点不是vexs[k]）
            if(G.matrix[k][j]<c_edge[j].lowcast){
                c_edge[j].adjvex = G.vexs[k];//更新c_edge在U的顶点
                c_edge[j].lowcast = G.matrix[k][j];
            }
    }
}