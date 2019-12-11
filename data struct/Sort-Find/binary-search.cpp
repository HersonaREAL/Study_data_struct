/*折半查找：用数组实现，查找前元素先排序。计算比较次数。分别用查找成功、不成功进行测试。*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int cmpfunc(const void *a, const void *b);//给c语言qsort用的比较函数
void binary_search(char a[],char tmp, int len);


int main(void){
    srand((unsigned)time(NULL));
    char a[16];
    char tmp;
    for (int i = 0; i < 16;i++)
        a[i] = rand() % 26+97;
    printf("随机得到16个字母\n");
    for (int i = 0; i < 16;i++)
        printf("%c ", a[i]);
    qsort(a, 16,sizeof(char), cmpfunc);
    printf("\n排序后\n");
    for (int i = 0; i < 16;i++)
        printf("%c ", a[i]);
    printf("\n输入查找的字母\n");
    scanf("%c", &tmp);
    binary_search(a, tmp, 16);
    system("pause");
}


int cmpfunc(const void *a, const void *b)
{
    return ( *(char*)a - *(char*)b);       //升序
}

void binary_search(char a[],char tmp, int len){
    int op = 0;
    int ed = len-1;
    int middle = (op + ed) / 2;
    int count = 0;

    //判断不能取等于，特殊情况例如找第一个或者最后一个会跳出
    while(op<=ed){
        count++;
        if(a[middle]==tmp){
            printf("找到该字母%c，序号为%d,比较了%d次\n",a[middle], middle, count);
            return;
        }
        if(a[middle]>tmp){
            ed = middle-1;
            middle = (op + ed) / 2;
        }
        if(a[middle]<tmp){
            op = middle+1;
            middle = (op + ed) / 2;
        }
    }
    printf("找不到该字母,886\n");
}