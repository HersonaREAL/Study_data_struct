#include<stdio.h>
#include<stdlib.h>
//图
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

//Dijkstra
struct PATH {
    bool S[MVNum];//判断vexs[i]是否已经得到最短路径
    int Path[MVNum];//某点的前驱结点，可一直回溯源点
    int D[MVNum];//V0->Vi之间路径长
}About_Path;
void shortestpath(AM_Graph G, int v, PATH &About_PATH);
void PrintPath(AM_Graph G,PATH About_Path);

int main(void){
    AM_Graph G;
    int tmp;
    if(CreateUDN(G))
        PrintUDN(G);
    printf("选择一个点求到各点的最短路径\n");
    scanf("%d", &tmp);
    shortestpath(G, tmp,About_Path);
    PrintPath(G, About_Path);
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
                printf("%-10d\n", G.matrix[i][j]);
            else
                printf("%-10d ", G.matrix[i][j]);
        }

}

void shortestpath(AM_Graph G, int v,PATH &About_Path){
    //顶点初始化
    int v_i = LocateVex(G, v);
    for (int i = 0; i < G.vexnum;i++){
        About_Path.D[i] = G.matrix[v_i][i];
        if(About_Path.D[i]<MaxInt)
            About_Path.Path[i] = v;
        else
            About_Path.Path[i] = -1;
    }
    About_Path.S[v_i] = true;//把v并入S集
    About_Path.D[v_i] = 0;
    //初始化结束

    //开始寻路
    for (int n = 1; n < G.vexnum;n++){
        int tmp_min = MaxInt;

        //选择一条到V-S集的当前的最短路径
        for (int i = 0; i < G.vexnum;i++)
            if(!About_Path.S[i]&&About_Path.D[i]<tmp_min){
                v_i = i;
                tmp_min = About_Path.D[i];
            }
        About_Path.S[v_i] = true;//将此时的Vi加入S集合

        //更新vo出发到V-S点的最短路径
        for (int i = 0; i < G.vexnum;i++)
            //判断是否当前最短路径+权小于之前的路径,(About_Path.D[v_i]+G.matrix[v_i][i])>0防止溢出变负影响判断
            if(!About_Path.S[i]&&((About_Path.D[v_i]+G.matrix[v_i][i])<About_Path.D[i])&&(About_Path.D[v_i]+G.matrix[v_i][i])>0){
                About_Path.D[i] = About_Path.D[v_i] + G.matrix[v_i][i];
                About_Path.Path[i] = v_i;
            }

    }
}

void PrintPath(AM_Graph G,PATH About_Path){
    for (int i = 0; i < G.vexnum;i++){
        int k = i;
        printf("权为%d\n",About_Path.D[i]);
        printf("%d", G.vexs[k]);
        while(About_Path.Path[k]!=-1){
            printf("<-- %d", G.vexs[About_Path.Path[k]]);
            k = About_Path.Path[k];
        }
        printf("\n\n");
    }
}