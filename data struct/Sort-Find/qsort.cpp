/*用随机函数生成16个2位正整数（10~99）
，实现插快速排序，输出排序中间过程、
统计关键字的比较次数和记录的移动次数。*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void Quicksort(int A[], int len);
void Qsort(int A[], int left, int right);
int Media_3(int A[], int left, int right);//三数中值分割，用来选枢纽
void swap(int &A, int &B);

int main(void){
    srand((unsigned)time(NULL));
    int array_num;
    printf("Enter进入\n");
    while(getchar()){
        printf("生成几个数？");
        scanf("%d", &array_num);
        int *a = (int *)malloc(sizeof(int) * array_num);
        for (int i = 0; i < array_num; i++)
            a[i] = rand() % 90 + 10;
        printf("排序前:");
        for (int i = 0; i < array_num; i++)
            printf(" %d", a[i]);
        Quicksort(a, array_num);
        printf("\n排序后:");
        for (int i = 0; i < array_num; i++)
            printf(" %d", a[i]);
        printf("\n\n");
        free(a);
    }
    system("pause");
}

int Media_3(int A[], int left, int right){
    //若传入不够三个值，直接返回第一个
    int center = (left + right) / 2;
    if(left+2>right){
        if(A[left]<A[right])
            swap(A[left], A[right ]);//两个元素顺序正常，直接藏枢纽
        return A[right];
    }
    if(A[left]>A[center])
        swap(A[left], A[center]);
    if(A[left]>A[right])
        swap(A[left], A[right]);
    if(A[center]>A[right])
        swap(A[center], A[right]);
    //交换后A[left]<=A[center]<=A[left]
    swap(A[center], A[right - 1]);//藏枢纽
    return A[right - 1];
}
void swap(int &A, int &B){
    int C;
    C = A;
    A = B;
    B = C;
}
void Qsort(int A[], int left, int right){
    if(left==right)//只有一个元素直接返回
        return;
    int i, j;
    int pivot;//枢纽
    i = left;
    j = right - 1;
    pivot = Media_3(A, left, right);
    while(1){
        while(A[++i]<pivot){}//++i是先移动i再比较，因为Media_3函数已经交换过了，第一个元素无需比较
        while(A[--j]>pivot){}
        if(i<j)
            swap(A[i], A[j]);
        else
            break;
    }
    swap(A[i], A[right - 1]);//恢复藏起来的枢纽
    Qsort(A, left, i - 1);
    if(left+2>right)//针对只有两个元素的递归
        Qsort(A, i, right);
    else
        Qsort(A, i + 1, right);//正常递归
}
void Quicksort(int A[], int len){
    Qsort(A, 0, len - 1);
}