/*
˳����ң�ʹ�����������ṹ��
�������������16�����ظ�����ĸ����a��~��z������
������������ҵ���ĸ�����ز��ҳɹ����
���ɹ��򷵻ظ���ĸ���ڵ�λ�ã���ţ���������Ƚϴ�����
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
    printf("����õ�16����ĸ\n");
    for (int i = 0; i < 16;i++)
        printf("%c", a[i]);
    printf("\n������ҵ���ĸ\n");
    scanf("%c", &tmp);
    int order_num = InOrderToFind(a, tmp, 16);
    if(order_num==-1)
        printf("�鲻��\n");
    else
        printf("����ĸ���Ϊ%d���Ƚ���%d��", order_num, order_num+1);
    system("pause");
    return 0;
}

int InOrderToFind(char a[],char key,int len){
    for (int i = 0; i < len;i++)
        if(a[i]==key)
            return i;
    return -1;
}