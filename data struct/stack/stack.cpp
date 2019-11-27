/*
ջ����ʽ�洢�ṹʵ��
��1���������������10��3λ������100~999��������Щ����Ӧ����ջ�������ڶ�ջ�У�����ջ�ӿڴ����öϵ�٣�����F5���������ԣ�����F10�����ִ�У�ֱ������ȫ����ջ��������ͣʱ�۲�ջ�����ݺ�ջ��λ�ã�
��2��Ӧ�ó�ջ���������ջ�����ݣ��ڳ�ջ�ӿڴ����öϵ�ڣ�����F5���������ԣ�����F10�����ִ�У�ֱ������������ȫ��ջ��������ͣʱ�۲�ջ�����ݺ�ջ��λ�õı仯�� 
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
    printf("0.�����ջʮ����\n");
    printf("1.��ջ\n");
    printf("2.��ջ\n");
    printf("3.ȫ����ջ��ջ\n");
    printf("4.�˳�\n");
    printf("----------------------------------------\n");
    printf("��������Ӧ����:");

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
            printf("������ջԪ��:");
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
            printf("�������\n");
        }
        printf("\n��������Ӧ����:");
  }
}


Stack CreateStack(){
    Stack S;
    S = (Stack)malloc(sizeof(Node));
    if (S == NULL){
        printf("ջ����ʧ��\n");
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
    printf("��ջԪ��:%d\n", x);
}

void Pop(Stack S){
    if (IsEmpty(S)){
     printf("ջ��");
     return;
    }
    int data_tmp = S->Next->Data;
    Stack p;
    p = S->Next;
    S->Next = S->Next->Next;
    free(p);
    printf("��ջԪ��%d\n", data_tmp);
}