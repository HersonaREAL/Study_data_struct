/*�۰���ң�������ʵ�֣�����ǰԪ�������򡣼���Ƚϴ������ֱ��ò��ҳɹ������ɹ����в��ԡ�*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int cmpfunc(const void *a, const void *b);//��c����qsort�õıȽϺ���
void binary_search(char a[],char tmp, int len);


int main(void){
    srand((unsigned)time(NULL));
    char a[16];
    char tmp;
    for (int i = 0; i < 16;i++)
        a[i] = rand() % 26+97;
    printf("����õ�16����ĸ\n");
    for (int i = 0; i < 16;i++)
        printf("%c ", a[i]);
    qsort(a, 16,sizeof(char), cmpfunc);
    printf("\n�����\n");
    for (int i = 0; i < 16;i++)
        printf("%c ", a[i]);
    printf("\n������ҵ���ĸ\n");
    scanf("%c", &tmp);
    binary_search(a, tmp, 16);
    system("pause");
}


int cmpfunc(const void *a, const void *b)
{
    return ( *(char*)a - *(char*)b);       //����
}

void binary_search(char a[],char tmp, int len){
    int op = 0;
    int ed = len-1;
    int middle = (op + ed) / 2;
    int count = 0;

    //�жϲ���ȡ���ڣ�������������ҵ�һ���������һ��������
    while(op<=ed){
        count++;
        if(a[middle]==tmp){
            printf("�ҵ�����ĸ%c�����Ϊ%d,�Ƚ���%d��\n",a[middle], middle, count);
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
    printf("�Ҳ�������ĸ,886\n");
}