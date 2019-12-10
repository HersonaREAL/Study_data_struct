#include<stdio.h>
#include<stdlib.h>
//ͼ
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

//Dijkstra
struct PATH {
    bool S[MVNum];//�ж�vexs[i]�Ƿ��Ѿ��õ����·��
    int Path[MVNum];//ĳ���ǰ����㣬��һֱ����Դ��
    int D[MVNum];//V0->Vi֮��·����
}About_Path;
void shortestpath(AM_Graph G, int v, PATH &About_PATH);
void PrintPath(AM_Graph G,PATH About_Path);

int main(void){
    AM_Graph G;
    int tmp;
    if(CreateUDN(G))
        PrintUDN(G);
    printf("ѡ��һ�����󵽸�������·��\n");
    scanf("%d", &tmp);
    shortestpath(G, tmp,About_Path);
    PrintPath(G, About_Path);
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
                printf("%-10d\n", G.matrix[i][j]);
            else
                printf("%-10d ", G.matrix[i][j]);
        }

}

void shortestpath(AM_Graph G, int v,PATH &About_Path){
    //�����ʼ��
    int v_i = LocateVex(G, v);
    for (int i = 0; i < G.vexnum;i++){
        About_Path.D[i] = G.matrix[v_i][i];
        if(About_Path.D[i]<MaxInt)
            About_Path.Path[i] = v;
        else
            About_Path.Path[i] = -1;
    }
    About_Path.S[v_i] = true;//��v����S��
    About_Path.D[v_i] = 0;
    //��ʼ������

    //��ʼѰ·
    for (int n = 1; n < G.vexnum;n++){
        int tmp_min = MaxInt;

        //ѡ��һ����V-S���ĵ�ǰ�����·��
        for (int i = 0; i < G.vexnum;i++)
            if(!About_Path.S[i]&&About_Path.D[i]<tmp_min){
                v_i = i;
                tmp_min = About_Path.D[i];
            }
        About_Path.S[v_i] = true;//����ʱ��Vi����S����

        //����vo������V-S������·��
        for (int i = 0; i < G.vexnum;i++)
            //�ж��Ƿ�ǰ���·��+ȨС��֮ǰ��·��,(About_Path.D[v_i]+G.matrix[v_i][i])>0��ֹ����为Ӱ���ж�
            if(!About_Path.S[i]&&((About_Path.D[v_i]+G.matrix[v_i][i])<About_Path.D[i])&&(About_Path.D[v_i]+G.matrix[v_i][i])>0){
                About_Path.D[i] = About_Path.D[v_i] + G.matrix[v_i][i];
                About_Path.Path[i] = v_i;
            }

    }
}

void PrintPath(AM_Graph G,PATH About_Path){
    for (int i = 0; i < G.vexnum;i++){
        int k = i;
        printf("ȨΪ%d\n",About_Path.D[i]);
        printf("%d", G.vexs[k]);
        while(About_Path.Path[k]!=-1){
            printf("<-- %d", G.vexs[About_Path.Path[k]]);
            k = About_Path.Path[k];
        }
        printf("\n\n");
    }
}