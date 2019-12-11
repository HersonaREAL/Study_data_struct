/*用随机函数生成16个2位正整数（10~99）
，实现插归并排序，输出排序中间过程、
统计关键字的比较次数和记录的移动次数。*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void Mergesort(int A[], int len);//驱动程序
void Msort(int A[], int *TmpArray, int left, int right);
void Merge(int A[], int *TmpArray, int L, int R, int R_end);//合并程序


int main(void){
    srand((unsigned)time(NULL));
    int array_num;
    printf("Enter进入\n");
    while(getchar()){
        printf("生成几个数？");
        scanf("%d", &array_num);
        int *a = (int *)malloc(sizeof(int) * array_num);
        //随机数生成
        for (int i = 0; i < array_num; i++)
            a[i] = rand() % 90 + 10;
        printf("排序前:");
        for (int i = 0; i < array_num; i++)
            printf(" %d", a[i]);

        Mergesort(a, array_num);
        
        printf("\n排序后:");
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
        printf("无空间给你排序，SB\n");
}

void Msort(int A[], int *TmpArray, int left, int right){
    int center=(left+right)/2;
    if(right>left){
        Msort(A, TmpArray, left, center);//递归左
        Msort(A, TmpArray, center + 1, right);//递归右
        Merge(A, TmpArray, left, center + 1, right);//合并左右
    }
}

void Merge(int A[], int *TmpArray, int L, int R, int R_end){
    int L_end = R - 1;//左数列结束位置
    int Elements_Num = R_end - L + 1;//需要合并的元素个数
    int Tmp_pos = L;//临时数组对应原数组位置

    //合并
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

    //把比较剩下的数组合并进去
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

    //把临时数组的东西复制回去
    for (int i = 0; i < Elements_Num;i++){
        A[R_end] = TmpArray[R_end];//因为R_end在上述过程没有动，所以可以倒着放回去
        R_end--;
    }
}