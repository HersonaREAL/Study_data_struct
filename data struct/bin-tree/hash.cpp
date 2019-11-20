#include<stdio.h>
#include<stdlib.h>

struct ch_num{
    char cha;
    int count=0;
}CH[128];

//哈夫曼节点结构
typedef struct TreeNode *HuffTree;
struct TreeNode{
    int weight;
    int parent,lchild,rchild;
}HTNode,*HuffmanTree;


void CreatHuffTree(HuffTree &HT, ch_num *char_sum_array,int len);
int sum_char(ch_num *charsum, char *str);
ch_num *creat_sum_array(ch_num *huff, int len);//huff用的结构数组




int main(void){
    char str[600];
    int len;
    gets(str);
    ch_num *huffsum;
    len = sum_char(CH, str);
    huffsum = creat_sum_array(huffsum, len);
    CreatHuffTree(HuffmanTree, huffsum, len);
    printf("\n-------------------------终态------------------------------\n节点     weight     parent     lchiled     rchild\n");
    for (int i = 1; i <= 2 * len - 1;i++)
        printf("%-11d%-11d%-11d%-11d%-11d\n", i, HuffmanTree[i].weight, HuffmanTree[i].parent, HuffmanTree[i].lchild, HuffmanTree[i].rchild);

      getchar();
}

int sum_char(ch_num *charsum,char *str){
    int j = 0;
    for (int i = 0; i < 128;i++)//给全局结构数组赋ASCII
        charsum[i].cha = i;
    for (int i = 0; str[i] != '\0'; i++)//统计
        charsum[str[i]].count++;
    for (int i = 0; i < 128;i++)//统计出现不为零的字符
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
    int m = 2 * len - 1;//哈夫曼节点数
    HT = (HuffTree)malloc(sizeof(TreeNode) * m);

    //爸爸和儿子们置0
    for (int i = 1; i <= m;i++)
        HT[i].parent = HT[i].lchild = HT[i].rchild = 0;

    printf("-------------------------初态------------------------------\n节点     weight     parent     lchiled     rchild\n");
    //输入权值
    for (int i = 1; i <= len;i++){
        HT[i].weight = char_sum_array[i - 1].count;
        printf("%-11d%-11d%-11d%-11d%-11d\n", i, HuffmanTree[i].weight, HuffmanTree[i].parent, HuffmanTree[i].lchild, HuffmanTree[i].rchild);
    }
    /*-------------初始化完成-----------------------*/
    int tmp, s1, s2;
    for (int i = len + 1; i <= m;i++){
        tmp = HT[i-1].weight;
        s1 = i-1;
        //选出第一个最小值
        for (int j = 1; j <= i - 1;j++){
            if(HT[j].parent==0&&HT[j].weight<=tmp){
                tmp = HT[j].weight;
                s1 = j;
            }
        }
        //选出第二个比较值(parent不为0)
        for (int j = 1; j < i - 1;j++){
            if(HT[j].parent==0&&j!=s1){
                tmp = HT[j].weight;
                break;
            }
        }
        //选出第二个最小值
            for (int j = 1; j <= i - 1;j++){
                if(HT[j].parent==0&&j!=s1&&HT[j].weight<=tmp){
                    tmp = HT[j].weight;
                    s2 = j;
                }
            }
            //得到新节点i，删除s1,s2（父母节点不为0）
            HT[s1].parent = HT[s2].parent = i;
            HT[i].lchild = s1;
            HT[i].rchild = s2;
            HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
}