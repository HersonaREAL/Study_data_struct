/*
用随机函数生成10个3位整数（100~999），把这些整数存于单链表中，然后读入一个整数，以该值为基准把单链表分割为两部分，所有小于该值的结点排在大于或等于该值的结点之前。
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
typedef struct Node *List;
typedef List Position;
//链表结构
struct Node{
    int num;
    List Next;
};

List MakeEmpty();
List Insert(int num,List Head,int pos);//pos means position
List Delete(int num,List Head);
int Findnum(int num, List Head); //按值查找
Position Findth(int pos, List Head); //按位查找
void OutPutList(List Head);
List TASK(int x, List Head);//4(1)

int main(void){
    srand((unsigned)time(NULL));
    printf("--------------------------------------------------------------------------------\n");
    printf("1.初始化链表,生成十个三位数随机整数并存入链表\n");
    printf("2.读入一个整数，以该值为基准把单链表分割为两部分，所有小于该值的结点排在大于或等于该值的结点之前\n");
    printf("3.退出\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("请输入相应数字:");

    List Head=NULL;
    int selection;
    while(1){
        scanf("%d", &selection);
        switch(selection){
            case 1:{
                Head=MakeEmpty();
                for (int i = 0; i < 9;i++)
                    Head = Insert((rand() % 900 + 100), Head, i + 1);
                OutPutList(Head);
            }
            break;

            case 2:{
                printf("输入要读入的数:");
                int x;
                scanf("%d", &x);
                Head = TASK(x, Head);
                OutPutList(Head);
            }
            break;

            case 3:
                return 0;
            default :
                printf("输入错误\n");
        }
        printf("\n请输入相应数字:");
    }
}


List TASK(int x, List Head){
    if(!Head){
        printf("链表空，无法进行操作\n");
        return NULL;
    }

    List Head_low = (List)malloc(sizeof(Node));
    List Head_high = (List)malloc(sizeof(Node));//为两个链表申请头节点，方便操作
    List Tmp_low = Head_low;
    List Tmp_high = Head_high;
    List tmp = Head;

    //遍历原链表，并分成两个链表
    while(tmp!=NULL){
        if(tmp->num<x){
            Tmp_low->Next = tmp;
            Tmp_low = Tmp_low->Next; //小于该值的节点相连，下面相同
        }else{
            Tmp_high->Next = tmp;
            Tmp_high = Tmp_high->Next;
        }
        tmp=tmp->Next;
    }
    Tmp_high->Next = NULL;//尾节点设NULL防止出现蛇咬尾
    Tmp_low->Next = NULL;

    //合并两个链表
    Tmp_low->Next = Head_high->Next;
    Tmp_low = Head_low->Next;
    
    free(Head_low);
    free(Head_high);

    return Tmp_low;//Tmp_low为头节点
}


List MakeEmpty(){ //加个判断有无旧链表
    List Head;
    Head = (List)malloc(sizeof(Node));
    Head->Next = (List)malloc(sizeof(Node));
    Head->num = rand()%900+100;
    Head->Next = NULL;
    return Head;
}


Position Findth(int pos, List Head){
    if(!Head)//判断节点是否为空
        return NULL;

    Position tmp = Head;
    int i = 1;

    //tmp判断节点是否已空
    for (; i < pos&&tmp;i++){
        tmp = tmp->Next;
    }
    if(i!=pos)//i不等于pos时说明查找的位置过大,头节点不存储数据，不返回
        return NULL;

    return tmp;
}


int Findnum(int num, List Head){
    if(Head==NULL){
        printf("链表空，无法查找\n");
        return -1;
    }
    List tmp = Head;
    int i = 1;

    //注意判断的先后顺序，会有影响
    while(tmp&&tmp->num!=num){
        tmp = tmp->Next;
        i++;
    }

    if(tmp!=NULL)
        return i;
    else
        return -1;//-1代表查找失败
}


List Insert(int num,List Head,int pos){
    List tmp;

    //判断是否插在头节点
    if(pos==1){
        tmp = (List)malloc(sizeof(Node));
        tmp->num = num;
        tmp->Next = Head;
        return tmp;
    }

    Position Po = Findth(pos-1, Head);//找出插入位置的地址

    if(Po==NULL)//判断位置合理性
        return Head;

    tmp = (List)malloc(sizeof(Node));//申请临时节点
    tmp->num = num;
    tmp->Next = Po->Next;
    Po->Next = tmp;
    return Head;
    
}


List Delete(int num,List Head){
    //判断链表是否为空
    if(!Head){
        printf("链表空，删除失败\n");
        return NULL;
    }

    int p = Findnum(num, Head);//p代表该节点在链表的位置
    List tmp ;

    //找不到该点
    if(p==-1){
        printf("删除失败，找不到点\n");
        return Head;
    }

    //判断是否为头节点
    if(p==1){
        tmp = Head->Next;
        free(Head);
        return tmp;

    }

    Position pos = Findth(p, Head);//查找删除节点的地址
    Position pre = Findth(p - 1, Head);//查找前一个节点

    //判断是否为尾节点
    if(pos->Next==NULL){
        pre->Next = NULL;
        free(pos);
        return Head;
    }

    //如果不是尾节点
    pre->Next = pos->Next;
    free(pos);
    return Head;
}


void OutPutList(List Head){
    if(!Head){
        printf("链表空，无法输出\n");
        return;
    }
    printf("链表内容为:");
    List count = Head;
    while(count!=NULL){
        printf("%d ", count->num);
        count = count->Next;
    }
    printf("\n");
}