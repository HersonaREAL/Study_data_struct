/*
栈的链式存储结构实现
（1）用随机函数生成10个3位整数（100~999），把这些整数应用入栈操作存于堆栈中，在入栈接口处设置断点①，按“F5”启动调试，按“F10”逐句执行，直到数据全部入栈。程序暂停时观察栈顶数据和栈顶位置；
（2）应用出栈操作输出堆栈的内容，在出栈接口处设置断点②，按“F5”启动调试，按“F10”逐句执行，直到所有数据完全出栈，程序暂停时观察栈顶数据和栈顶位置的变化； 
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
typedef struct Node* PtrNode;
typedef PtrNode Stack;
struct Node {
    int Data;
    PtrNode Next;
};

bool IsEmpty(Stack S);
Stack CreateStack();
void Push(int x, Stack S);
void Pop(Stack S);

int main(void){
    srand((unsigned)time(NULL));
    printf("----------------------------------------\n");
    printf("0.随机入栈十个数\n");
    printf("1.入栈\n");
    printf("2.出栈\n");
    printf("3.全部出栈入栈\n");
    printf("4.退出\n");
    printf("----------------------------------------\n");
    printf("请输入相应数字:");

    int judge;
    Stack S = CreateStack();
    while (1)
    {
        scanf("%d", &judge);
        switch (judge)
        {
        case 0:{
            for (int i = 0; i < 10;i++)
                Push((rand() % 900 + 100), S);
        }
        break;

        case 1:{
            printf("输入入栈元素:");
            int x;
            scanf("%d", &x);
            Push(x, S);
            }
        break;

        case 2:Pop(S);break;

        case 3:{
            while(!IsEmpty(S))
                Pop(S);
        }
        break;
        
        case 4:
            return 0;
            
        default:
            printf("输入错误\n");
        }
        printf("\n请输入相应数字:");
  }
}


Stack CreateStack(){
    Stack S;
    S = (Stack)malloc(sizeof(Node));
    if (S == NULL){
        printf("栈创建失败\n");
        return NULL;
    }
    S->Next = NULL;
    return S;
}

bool IsEmpty(Stack S){
    return S->Next == NULL;
}

void Push(int x, Stack S){
    Stack tmp = (Stack)malloc(sizeof(Node));
    tmp->Data = x;
    tmp->Next = S->Next;
    S->Next = tmp;
    printf("入栈元素:%d\n", x);
}

void Pop(Stack S){
    if (IsEmpty(S)){
     printf("栈空");
     return;
    }
    int data_tmp = S->Next->Data;
    Stack p;
    p = S->Next;
    S->Next = S->Next->Next;
    free(p);
    printf("出栈元素%d\n", data_tmp);
}