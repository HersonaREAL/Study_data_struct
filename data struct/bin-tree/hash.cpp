#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//ͳ���ַ��õĽṹ
struct ch_num{
    char cha;
    int count=0;
}CH[128];

//�������ڵ�ṹ
typedef struct TreeNode *HuffTree;
struct TreeNode{
    char ch;
    int weight;
    int parent,lchild,rchild;
}HTNode,*HuffmanTree;

typedef char **HuffmanCode;//����������

//ȫ�ֱ�������
HuffmanCode HC;
char str[600];
int len;
ch_num *huffsum;


void CreatHuffTree(HuffTree &HT, ch_num *char_sum_array,int len);
void CreatHuffmanCode(HuffTree HT, HuffmanCode &HC, int len);
int sum_char(ch_num *charsum, char *str);
ch_num *creat_sum_array(ch_num *huff, int len);//huff�õĽṹ����
void PrintHuffmanTree(int len);
void PrintHuffmanCode(int len);


int main(void){
    gets(str);
    len = sum_char(CH, str);
    huffsum = creat_sum_array(huffsum, len);

    CreatHuffTree(HuffmanTree, huffsum, len);
    PrintHuffmanTree(len);
    CreatHuffmanCode(HuffmanTree, HC, len);
    PrintHuffmanCode(len);
    getchar();
}

int sum_char(ch_num *charsum,char *str){
    int j = 0;
    for (int i = 0; i < 128;i++)//��ȫ�ֽṹ���鸳ASCII
        charsum[i].cha = i;
    for (int i = 0; str[i] != '\0'; i++)//ͳ��
        charsum[str[i]].count++;
    for (int i = 0; i < 128;i++)//ͳ�Ƴ��ֲ�Ϊ����ַ�
        if(charsum[i].count!=0)
            j++;
    return j;
}

ch_num *creat_sum_array(ch_num *huff, int len){
    int j = 0;
    ch_num *huffsum = (ch_num *)malloc(sizeof(ch_num) * len);
    for (int i = 0; i < 128; i++)
        if(CH[i].count!=0){
            huffsum[j].cha = CH[i].cha;
            huffsum[j].count = CH[i].count;
            printf("%c:%d\n", huffsum[j].cha, huffsum[j].count);
            j++;
        }
    return huffsum;
}

void CreatHuffTree(HuffTree &HT, ch_num *char_sum_array,int len){
    if(len<=1)
        return;
    int m = 2 * len - 1;//�������ڵ���
    HT = (HuffTree)malloc(sizeof(TreeNode) * m);

    //�ְֺͶ�������0
    for (int i = 1; i <= m;i++)
        HT[i].parent = HT[i].lchild = HT[i].rchild = 0;

    printf("\n-------------------------��̬------------------------------\n�ڵ�     weight     parent     lchiled     rchild\n");
    //����Ȩֵ
    for (int i = 1; i <= len;i++){
        HT[i].ch = char_sum_array[i - 1].cha;
        HT[i].weight = char_sum_array[i - 1].count;
        printf("%-11d%-11d%-11d%-11d%-11d\n", i, HuffmanTree[i].weight, HuffmanTree[i].parent, HuffmanTree[i].lchild, HuffmanTree[i].rchild);
    }
    /*-------------��ʼ�����-----------------------*/
    int tmp, s1, s2;
    for (int i = len + 1; i <= m;i++){
        tmp = HT[i-1].weight;
        s1 = i-1;
        //ѡ����һ����Сֵ
        for (int j = 1; j <= i - 1;j++){
            if(HT[j].parent==0&&HT[j].weight<=tmp){
                tmp = HT[j].weight;
                s1 = j;
            }
        }
        //ѡ���ڶ����Ƚ�ֵ(parent��Ϊ0)
        for (int j = 1; j <=i - 1;j++){
            if(HT[j].parent==0&&j!=s1){
                tmp = HT[j].weight;
                break;
            }
        }
        //ѡ���ڶ�����Сֵ
            for (int j = 1; j <= i - 1;j++){
                if(HT[j].parent==0&&j!=s1&&HT[j].weight<=tmp){
                    tmp = HT[j].weight;
                    s2 = j;
                }
            }
            //�õ��½ڵ�i��ɾ��s1,s2����ĸ�ڵ㲻Ϊ0��
            HT[s1].parent = HT[s2].parent = i;
            HT[i].lchild = s1;
            HT[i].rchild = s2;
            //�õ��µĽڵ�
            HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
}

void CreatHuffmanCode(HuffTree HT, HuffmanCode &HC, int len){
    HC = (HuffmanCode)malloc(sizeof(char *) * (len + 1)); //����len���ַ����ռ�
    char cd[len];//��ʱ��ű���ռ�
    cd[len-1]='\0';
    int start;//��¼cd���λ��
    int c;//����±�
    int f;//��¼�ַ���˫�׽ڵ��±�i
    //���ַ������������
    for(int i=1;i<=len;i++){
        start = len - 1;//ָ����ֹ��
        c = i;
        f = HT[i].parent;

        //f==0����ص����ڵ�
        while(f!=0){
            start--;//����λ����ǰָ
            if(HT[f].lchild==c)//˫�׵�������Ƿ���ڵ�ǰ����±�
                cd[start] = '0';
            else
                cd[start] = '1';

            //���ϴ���
            c = f;
            f = HT[f].parent;
        }
        HC[i]=(char*)malloc(sizeof(char)*(len-start));//����һ������ı����С,��Ԥ��'\0'
        strcpy(HC[i], &cd[start]);

    }
}

void PrintHuffmanCode(int len){
     printf("\n���������룺\n");
     for (int i = 1; i <= len;i++){
        printf("%c : ", HuffmanTree[i].ch);
        for (int j = 0; HC[i][j] != '\0';j++)
            printf("%c", HC[i][j]);
        printf("\n\n");
    }
}

void PrintHuffmanTree(int len){
     printf("\n-------------------------��̬------------------------------\n�ڵ�     weight     parent     lchiled     rchild\n");
    for (int i = 1; i <= 2 * len - 1;i++)
        printf("%-11d%-11d%-11d%-11d%-11d\n", i, HuffmanTree[i].weight, HuffmanTree[i].parent, HuffmanTree[i].lchild, HuffmanTree[i].rchild);
}