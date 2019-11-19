#include<stdio.h>
#include<stdlib.h>
typedef struct TreeNode *BinaryTree;
struct TreeNode{
    char data;
    TreeNode *Lchild;
    TreeNode *Rchild;
};

BinaryTree CreateTree(BinaryTree T, char *str);
void CopyStr(int &i,int &j,char *str,char *tmp_str);
void OutTree(BinaryTree T);
void Preorder_Traversal(BinaryTree T);
void Inorder_Traversal(BinaryTree T);
void Postorder_Traversal(BinaryTree T);
void Out_Node_LandR(BinaryTree T, char str);
int Out_High(BinaryTree T);
int Out_Degree(BinaryTree T);
int Out_Node_sum(BinaryTree T);
int Out_Leaf_sum(BinaryTree T);

int main(void){
    char str[100];
    char NODE;
    BinaryTree T;
    scanf("%s", str);
    getchar();
    T = CreateTree(T, str);
    printf("����:");
    Preorder_Traversal(T);
    printf("\n����:");
    Inorder_Traversal(T);
    printf("\n����:");
    Postorder_Traversal(T);
    printf("\n");
    OutTree(T);
    printf("�ڵ����:%d\n", Out_Node_sum(T));
    printf("Ҷ�ӽڵ����:%d\n", Out_Leaf_sum(T));
    printf("���ĸ߶�Ϊ:%d\n", Out_High(T));
    printf("�����Ķ�Ϊ:%d\n", Out_Degree(T));
    printf("������ĳ�ڵ�����������Ҷ���\n");
    scanf("%c", &NODE);
    getchar();
    Out_Node_LandR(T, NODE);
    getchar();
    getchar();
}



void CopyStr(int &i,int &j,char *str,char *tmp_str){
    int L_count = 0;//�����ż���
    int R_count = 0;//�����ż���
    while(L_count!=R_count||L_count==0){
        i++;
        if(str[i]=='(')
            L_count++;
        else if(str[i]==')')
            R_count++;
        tmp_str[j] = str[i];
        j++;
    }
}

BinaryTree CreateTree(BinaryTree T,char *str){
    T = (BinaryTree)malloc(sizeof(TreeNode));
    T->Lchild = T->Rchild = NULL;
    T->data = str[0];
    char L_Tmp_Str[100];//����ʱ��
    char R_Tmp_Str[100];//����ʱ��
    int i = 1;//str����
    int j = 0;//Tmp_str����

    //������
    if(str[i]=='\0')//����ĸֱ�ӷ���
        return T;
    if(str[i]=='('){
        if(str[i+1]==',') //������Ϊ��
            T->Lchild = NULL;
        else if(str[i+2]==','||str[i+2]==')'){
            //��Ҷ�ӽڵ�
            L_Tmp_Str[0] = str[i+1];
            L_Tmp_Str[1] = '\0';
            T->Lchild = CreateTree(T->Lchild, L_Tmp_Str);
            i++;
        }else{
            //����������
            CopyStr(i, j, str, L_Tmp_Str);
            L_Tmp_Str[j] = '\0';
            T->Lchild = CreateTree(T->Lchild, L_Tmp_Str);
        }
    }

    i++;
    j = 0;//��λ

    //������
    if(str[i]==')')
        T->Rchild = NULL;
    if(str[i]==','){
        if(str[i+2]==')'){
            R_Tmp_Str[0] = str[i + 1];
            R_Tmp_Str[1] = '\0';
            T->Rchild = CreateTree(T->Rchild, R_Tmp_Str);
        }else{
            CopyStr(i, j, str, R_Tmp_Str);
            R_Tmp_Str[j] = '\0';
            T->Rchild = CreateTree(T->Rchild, R_Tmp_Str);
        }
    }


    return T;
}

void OutTree(BinaryTree T){
    if(T){
        if(T->Lchild&&T->Rchild)
            printf("%c->%c,%c\n", T->data, T->Lchild->data, T->Rchild->data);
        if(T->Lchild&&!T->Rchild)
            printf("%c->%c,NULL\n", T->data, T->Lchild->data);
        if(!T->Lchild&&T->Rchild)
            printf("%c->NULL,%c\n", T->data, T->Rchild->data);
        OutTree(T->Lchild);
        OutTree(T->Rchild);
    }
}

void Preorder_Traversal(BinaryTree T){
    if(T){
        printf("%c", T->data);
        Preorder_Traversal(T->Lchild);
        Preorder_Traversal(T->Rchild);
    }
}
void Inorder_Traversal(BinaryTree T){
    if(T){
        Inorder_Traversal(T->Lchild);
        printf("%c", T->data);
        Inorder_Traversal(T->Rchild);
    }
}
void Postorder_Traversal(BinaryTree T){
    if(T){
        Postorder_Traversal(T->Lchild);
        Postorder_Traversal(T->Rchild);
        printf("%c", T->data);
    }
}

void Out_Node_LandR(BinaryTree T, char str){
    if(T){
        if(T->data==str){
            if(T->Lchild&&T->Rchild)
                printf("�����:%c,�Ҷ���:%c\n",T->Lchild->data,T->Rchild->data);
            if(T->Lchild&&!T->Rchild)
                printf("�����:%c,�Ҷ���:NULL",T->Lchild->data);
            if(!T->Lchild&&T->Rchild)    
                printf("�����:NULL,�Ҷ���:%c\n",T->Rchild->data);
            if(!T->Lchild&&!T->Rchild)  
                printf("�����:NULL,�Ҷ���:NULL\n");
            return;
        }
        Out_Node_LandR(T->Lchild,str);
        Out_Node_LandR(T->Rchild, str);
    }
}


int Out_Node_sum(BinaryTree T){
    int j = 0;//�ڵ�
    if(T){
        j++;
        j += Out_Node_sum(T->Lchild);
        j += Out_Node_sum(T->Rchild);
    }
    return j;
}

int Out_Leaf_sum(BinaryTree T){
    int i = 0;
    if(T){
        if(!T->Rchild&&!T->Lchild)
            i++;
        i += Out_Leaf_sum(T->Lchild);
        i += Out_Leaf_sum(T->Rchild);
    }
    return i;
}

int Out_High(BinaryTree T){
    int L = 1;
    int R = 1;
    if(T){
        L += Out_High(T->Lchild);
        R += Out_High(T->Rchild);
        if(L>=R)
            return L;
        else
            return R;
    }
    return 0;
}

int Out_Degree(BinaryTree T){
    if(T){
        if(!T->Lchild&&!T->Rchild)
            return 0;
        else if(T->Rchild&&T->Lchild)
            return 2;
        else if(!T->Lchild&&T->Rchild)
            return (Out_Degree(T->Rchild) > 1) ? 2 : 1;
        else if(T->Lchild&&!T->Rchild)
            return (Out_Degree(T->Lchild) > 1) ? 2 : 1;
    }
    return 0;
}