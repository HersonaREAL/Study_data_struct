/*�������������16��2λ��������10~99��
��ʵ�ֲ����������������м���̡�
ͳ�ƹؼ��ֵıȽϴ����ͼ�¼���ƶ�������*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void Quicksort(int A[], int len);
void Qsort(int A[], int left, int right);
int Media_3(int A[], int left, int right);//������ֵ�ָ����ѡ��Ŧ
void swap(int &A, int &B);

int main(void){
    srand((unsigned)time(NULL));
    int array_num;
    printf("Enter����\n");
    while(getchar()){
        printf("���ɼ�������");
        scanf("%d", &array_num);
        int *a = (int *)malloc(sizeof(int) * array_num);
        for (int i = 0; i < array_num; i++)
            a[i] = rand() % 90 + 10;
        printf("����ǰ:");
        for (int i = 0; i < array_num; i++)
            printf(" %d", a[i]);
        Quicksort(a, array_num);
        printf("\n�����:");
        for (int i = 0; i < array_num; i++)
            printf(" %d", a[i]);
        printf("\n\n");
        free(a);
    }
    system("pause");
}

int Media_3(int A[], int left, int right){
    //�����벻������ֵ��ֱ�ӷ��ص�һ��
    int center = (left + right) / 2;
    if(left+2>right){
        if(A[left]<A[right])
            swap(A[left], A[right ]);//����Ԫ��˳��������ֱ�Ӳ���Ŧ
        return A[right];
    }
    if(A[left]>A[center])
        swap(A[left], A[center]);
    if(A[left]>A[right])
        swap(A[left], A[right]);
    if(A[center]>A[right])
        swap(A[center], A[right]);
    //������A[left]<=A[center]<=A[left]
    swap(A[center], A[right - 1]);//����Ŧ
    return A[right - 1];
}
void swap(int &A, int &B){
    int C;
    C = A;
    A = B;
    B = C;
}
void Qsort(int A[], int left, int right){
    if(left==right)//ֻ��һ��Ԫ��ֱ�ӷ���
        return;
    int i, j;
    int pivot;//��Ŧ
    i = left;
    j = right - 1;
    pivot = Media_3(A, left, right);
    while(1){
        while(A[++i]<pivot){}//++i�����ƶ�i�ٱȽϣ���ΪMedia_3�����Ѿ��������ˣ���һ��Ԫ������Ƚ�
        while(A[--j]>pivot){}
        if(i<j)
            swap(A[i], A[j]);
        else
            break;
    }
    swap(A[i], A[right - 1]);//�ָ�����������Ŧ
    Qsort(A, left, i - 1);
    if(left+2>right)//���ֻ������Ԫ�صĵݹ�
        Qsort(A, i, right);
    else
        Qsort(A, i + 1, right);//�����ݹ�
}
void Quicksort(int A[], int len){
    Qsort(A, 0, len - 1);
}