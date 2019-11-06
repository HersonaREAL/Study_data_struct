#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
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
List Reverse(List Head);//翻转
int Findnum(int num, List Head); //按值查找
Position Findth(int pos, List Head); //按位查找
void OutPutList(List Head);

int main(void){
    srand((unsigned)time(NULL));
    printf("----------------------------------------\n");
    printf("1.初始化链表,生成十个三位数随机整数并存入链表\n");
    printf("2.输出链表内容\n");
    printf("3.数值查找，并输出位置\n");
    printf("4.按数值删除，并输出内容\n");
    printf("5.翻转链表，并输出内容\n");
    printf("6.插入链表\n");
    printf("7.退出\n");
    printf("----------------------------------------\n");
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
        }break;

        case 2:{
            OutPutList(Head);
        }break;

        case 3:{
            printf("输入查找的数:");
            int x;
            scanf("%d", &x);
            printf("查找的数的位置在:%d (显示-1表示查找失败)\n",Findnum(x, Head));
        }break;

        case 4:{
            printf("输入删除的数:");
            int x;
            scanf("%d", &x);
            Head = Delete(x, Head);
            OutPutList(Head);
        }break;

        case 5:{
            Head=Reverse(Head);
            OutPutList(Head);
        }break;
        case 6:{
            int x, pos;
            printf("输入插入的值：");
            scanf("%d", &x);
            printf("输入插入第几位:");
            scanf("%d", &pos);
            Head = Insert(x, Head, pos);
        }
        break;

        case 7:
            return 0;

        default:
            printf("输错啦!\n");
            break;
        }
        printf("\n请输入相应数字:");
    }
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
    for (; i < pos&&tmp;i++){
        //tmp判断节点是否已空
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
    while(tmp&&tmp->num!=num){
        //注意判断的先后顺序，会有影响
        tmp = tmp->Next;
        i++;
    }

    if(tmp!=NULL)
        return i;
    else
        return -1;//-1代表查找失败
}


List Insert(int num,List Head,int pos){
    if(!Head)//判断链表是否为空
        return NULL;
    
    List tmp;
    if(pos==1){
    //判断是否插在头节点
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


List Reverse(List Head){
    if(!Head){
        printf("链表空，无法翻转\n");
        return NULL;
    }
    List pre = Head;   //排前面的辅助节点
    List cur = pre->Next;//当前节点
    List aft; //排后面的辅助节点
    Head->Next = NULL;
    while(cur){
        aft = cur->Next; //排到当前节点后
        cur->Next = pre; //把前一节点地址存入当前节点Next
        pre = cur;  //把前一节点移动到当前节点
        cur = aft;  //当前节点也往后移动
    }
    return pre;//循环到尾节点时，pre作为头节点
}