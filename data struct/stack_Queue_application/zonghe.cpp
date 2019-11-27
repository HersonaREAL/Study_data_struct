/*
�������������10��3λ������100~999��������Щ�������ڵ������У�Ȼ�����һ���������Ը�ֵΪ��׼�ѵ�����ָ�Ϊ�����֣�����С�ڸ�ֵ�Ľ�����ڴ��ڻ���ڸ�ֵ�Ľ��֮ǰ��
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
typedef struct Node *List;
typedef List Position;
//����ṹ
struct Node{
    int num;
    List Next;
};

List MakeEmpty();
List Insert(int num,List Head,int pos);//pos means position
List Delete(int num,List Head);
int Findnum(int num, List Head); //��ֵ����
Position Findth(int pos, List Head); //��λ����
void OutPutList(List Head);
List TASK(int x, List Head);//4(1)

int main(void){
    srand((unsigned)time(NULL));
    printf("--------------------------------------------------------------------------------\n");
    printf("1.��ʼ������,����ʮ����λ�������������������\n");
    printf("2.����һ���������Ը�ֵΪ��׼�ѵ�����ָ�Ϊ�����֣�����С�ڸ�ֵ�Ľ�����ڴ��ڻ���ڸ�ֵ�Ľ��֮ǰ\n");
    printf("3.�˳�\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("��������Ӧ����:");

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
                printf("����Ҫ�������:");
                int x;
                scanf("%d", &x);
                Head = TASK(x, Head);
                OutPutList(Head);
            }
            break;

            case 3:
                return 0;
            default :
                printf("�������\n");
        }
        printf("\n��������Ӧ����:");
    }
}


List TASK(int x, List Head){
    if(!Head){
        printf("����գ��޷����в���\n");
        return NULL;
    }

    List Head_low = (List)malloc(sizeof(Node));
    List Head_high = (List)malloc(sizeof(Node));//Ϊ������������ͷ�ڵ㣬�������
    List Tmp_low = Head_low;
    List Tmp_high = Head_high;
    List tmp = Head;

    //����ԭ�������ֳ���������
    while(tmp!=NULL){
        if(tmp->num<x){
            Tmp_low->Next = tmp;
            Tmp_low = Tmp_low->Next; //С�ڸ�ֵ�Ľڵ�������������ͬ
        }else{
            Tmp_high->Next = tmp;
            Tmp_high = Tmp_high->Next;
        }
        tmp=tmp->Next;
    }
    Tmp_high->Next = NULL;//β�ڵ���NULL��ֹ������ҧβ
    Tmp_low->Next = NULL;

    //�ϲ���������
    Tmp_low->Next = Head_high->Next;
    Tmp_low = Head_low->Next;
    
    free(Head_low);
    free(Head_high);

    return Tmp_low;//Tmp_lowΪͷ�ڵ�
}


List MakeEmpty(){ //�Ӹ��ж����޾�����
    List Head;
    Head = (List)malloc(sizeof(Node));
    Head->Next = (List)malloc(sizeof(Node));
    Head->num = rand()%900+100;
    Head->Next = NULL;
    return Head;
}


Position Findth(int pos, List Head){
    if(!Head)//�жϽڵ��Ƿ�Ϊ��
        return NULL;

    Position tmp = Head;
    int i = 1;

    //tmp�жϽڵ��Ƿ��ѿ�
    for (; i < pos&&tmp;i++){
        tmp = tmp->Next;
    }
    if(i!=pos)//i������posʱ˵�����ҵ�λ�ù���,ͷ�ڵ㲻�洢���ݣ�������
        return NULL;

    return tmp;
}


int Findnum(int num, List Head){
    if(Head==NULL){
        printf("����գ��޷�����\n");
        return -1;
    }
    List tmp = Head;
    int i = 1;

    //ע���жϵ��Ⱥ�˳�򣬻���Ӱ��
    while(tmp&&tmp->num!=num){
        tmp = tmp->Next;
        i++;
    }

    if(tmp!=NULL)
        return i;
    else
        return -1;//-1�������ʧ��
}


List Insert(int num,List Head,int pos){
    List tmp;

    //�ж��Ƿ����ͷ�ڵ�
    if(pos==1){
        tmp = (List)malloc(sizeof(Node));
        tmp->num = num;
        tmp->Next = Head;
        return tmp;
    }

    Position Po = Findth(pos-1, Head);//�ҳ�����λ�õĵ�ַ

    if(Po==NULL)//�ж�λ�ú�����
        return Head;

    tmp = (List)malloc(sizeof(Node));//������ʱ�ڵ�
    tmp->num = num;
    tmp->Next = Po->Next;
    Po->Next = tmp;
    return Head;
    
}


List Delete(int num,List Head){
    //�ж������Ƿ�Ϊ��
    if(!Head){
        printf("����գ�ɾ��ʧ��\n");
        return NULL;
    }

    int p = Findnum(num, Head);//p����ýڵ��������λ��
    List tmp ;

    //�Ҳ����õ�
    if(p==-1){
        printf("ɾ��ʧ�ܣ��Ҳ�����\n");
        return Head;
    }

    //�ж��Ƿ�Ϊͷ�ڵ�
    if(p==1){
        tmp = Head->Next;
        free(Head);
        return tmp;

    }

    Position pos = Findth(p, Head);//����ɾ���ڵ�ĵ�ַ
    Position pre = Findth(p - 1, Head);//����ǰһ���ڵ�

    //�ж��Ƿ�Ϊβ�ڵ�
    if(pos->Next==NULL){
        pre->Next = NULL;
        free(pos);
        return Head;
    }

    //�������β�ڵ�
    pre->Next = pos->Next;
    free(pos);
    return Head;
}


void OutPutList(List Head){
    if(!Head){
        printf("����գ��޷����\n");
        return;
    }
    printf("��������Ϊ:");
    List count = Head;
    while(count!=NULL){
        printf("%d ", count->num);
        count = count->Next;
    }
    printf("\n");
}