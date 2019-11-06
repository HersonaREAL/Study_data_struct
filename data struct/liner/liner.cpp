#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
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
List Reverse(List Head);//��ת
int Findnum(int num, List Head); //��ֵ����
Position Findth(int pos, List Head); //��λ����
void OutPutList(List Head);

int main(void){
    srand((unsigned)time(NULL));
    printf("----------------------------------------\n");
    printf("1.��ʼ������,����ʮ����λ�������������������\n");
    printf("2.�����������\n");
    printf("3.��ֵ���ң������λ��\n");
    printf("4.����ֵɾ�������������\n");
    printf("5.��ת�������������\n");
    printf("6.��������\n");
    printf("7.�˳�\n");
    printf("----------------------------------------\n");
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
        }break;

        case 2:{
            OutPutList(Head);
        }break;

        case 3:{
            printf("������ҵ���:");
            int x;
            scanf("%d", &x);
            printf("���ҵ�����λ����:%d (��ʾ-1��ʾ����ʧ��)\n",Findnum(x, Head));
        }break;

        case 4:{
            printf("����ɾ������:");
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
            printf("��������ֵ��");
            scanf("%d", &x);
            printf("�������ڼ�λ:");
            scanf("%d", &pos);
            Head = Insert(x, Head, pos);
        }
        break;

        case 7:
            return 0;

        default:
            printf("�����!\n");
            break;
        }
        printf("\n��������Ӧ����:");
    }
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
    for (; i < pos&&tmp;i++){
        //tmp�жϽڵ��Ƿ��ѿ�
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
    while(tmp&&tmp->num!=num){
        //ע���жϵ��Ⱥ�˳�򣬻���Ӱ��
        tmp = tmp->Next;
        i++;
    }

    if(tmp!=NULL)
        return i;
    else
        return -1;//-1�������ʧ��
}


List Insert(int num,List Head,int pos){
    if(!Head)//�ж������Ƿ�Ϊ��
        return NULL;
    
    List tmp;
    if(pos==1){
    //�ж��Ƿ����ͷ�ڵ�
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


List Reverse(List Head){
    if(!Head){
        printf("����գ��޷���ת\n");
        return NULL;
    }
    List pre = Head;   //��ǰ��ĸ����ڵ�
    List cur = pre->Next;//��ǰ�ڵ�
    List aft; //�ź���ĸ����ڵ�
    Head->Next = NULL;
    while(cur){
        aft = cur->Next; //�ŵ���ǰ�ڵ��
        cur->Next = pre; //��ǰһ�ڵ��ַ���뵱ǰ�ڵ�Next
        pre = cur;  //��ǰһ�ڵ��ƶ�����ǰ�ڵ�
        cur = aft;  //��ǰ�ڵ�Ҳ�����ƶ�
    }
    return pre;//ѭ����β�ڵ�ʱ��pre��Ϊͷ�ڵ�
}