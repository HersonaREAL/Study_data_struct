/*
顺序查找：使用数组或链表结构。
用随机函数生成16个不重复的字母（’a’~’z’），
键盘输入待查找的字母，返回查找成功与否，
若成功则返回该字母所在的位置（序号），并计算比较次数。
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int InOrderToFind(char a[],char key,int len);
void srandchar(char a[]);

int main(void){
    srand((unsigned)time(NULL));
    char a[16];
    char tmp;
    for (int i = 0; i < 16;i++)
        a[i] = rand() % 26+97;
    printf("随机得到16个字母\n");
    for (int i = 0; i < 16;i++)
        printf("%c", a[i]);
    printf("\n输入查找的字母\n");
    scanf("%c", &tmp);
    int order_num = InOrderToFind(a, tmp, 16);
    if(order_num==-1)
        printf("查不到\n");
    else
        printf("该字母序号为%d，比较了%d次", order_num, order_num+1);
    system("pause");
    return 0;
}

int InOrderToFind(char a[],char key,int len){
    for (int i = 0; i < len;i++)
        if(a[i]==key)
            return i;
    return -1;
}