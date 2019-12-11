/*�������������16��2λ��������10~99��
��ʵ�ֲ�鲢������������м���̡�
ͳ�ƹؼ��ֵıȽϴ����ͼ�¼���ƶ�������*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void Mergesort(int A[], int len);//��������
void Msort(int A[], int *TmpArray, int left, int right);
void Merge(int A[], int *TmpArray, int L, int R, int R_end);//�ϲ�����


int main(void){
    srand((unsigned)time(NULL));
    int array_num;
    printf("Enter����\n");
    while(getchar()){
        printf("���ɼ�������");
        scanf("%d", &array_num);
        int *a = (int *)malloc(sizeof(int) * array_num);
        //���������
        for (int i = 0; i < array_num; i++)
            a[i] = rand() % 90 + 10;
        printf("����ǰ:");
        for (int i = 0; i < array_num; i++)
            printf(" %d", a[i]);

        Mergesort(a, array_num);
        
        printf("\n�����:");
        for (int i = 0; i < array_num; i++)
            printf(" %d", a[i]);
        printf("\n\n");
        free(a);
    }
    system("pause");
}
void Mergesort(int A[], int len){
    int *TmpArray = (int *)malloc(sizeof(int) * len);
    if(TmpArray){
        Msort(A, TmpArray, 0, len - 1);
        free(TmpArray);
    }
    else
        printf("�޿ռ��������SB\n");
}

void Msort(int A[], int *TmpArray, int left, int right){
    int center=(left+right)/2;
    if(right>left){
        Msort(A, TmpArray, left, center);//�ݹ���
        Msort(A, TmpArray, center + 1, right);//�ݹ���
        Merge(A, TmpArray, left, center + 1, right);//�ϲ�����
    }
}

void Merge(int A[], int *TmpArray, int L, int R, int R_end){
    int L_end = R - 1;//�����н���λ��
    int Elements_Num = R_end - L + 1;//��Ҫ�ϲ���Ԫ�ظ���
    int Tmp_pos = L;//��ʱ�����Ӧԭ����λ��

    //�ϲ�
    while(L<=L_end&&R<=R_end){
        if(A[L]<=A[R]){
            TmpArray[Tmp_pos] = A[L];
            Tmp_pos++;
            L++;
        }
        else{
            TmpArray[Tmp_pos] = A[R];
            Tmp_pos++;
            R++;            
        }
    }

    //�ѱȽ�ʣ�µ�����ϲ���ȥ
    while(L<=L_end){
        TmpArray[Tmp_pos] = A[L];
        Tmp_pos++;
        L++;
    }
    while(R<=R_end){
        TmpArray[Tmp_pos] = A[R];
        Tmp_pos++;
        R++;        
    }

    //����ʱ����Ķ������ƻ�ȥ
    for (int i = 0; i < Elements_Num;i++){
        A[R_end] = TmpArray[R_end];//��ΪR_end����������û�ж������Կ��Ե��ŷŻ�ȥ
        R_end--;
    }
}