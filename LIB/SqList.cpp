#include <iostream>
#define MAX 10


typedef struct
{
    int data[MAX];
    int length;
}SqList;                  //顺序表类型

void createlist(SqList *&L,int a[],int n){     //创建顺序表
    L=(SqList*)malloc(sizeof(SqList));
    for(int i=0;i<n;i++)
        L->data[i]=a[i];
    L->length=n;
}
void dislist(SqList *L){                       //输出各元素值
    for(int i=0;i<L->length;i++){
        printf("%d",L->data[i]);
    }
    printf("\n");
}

bool get_elem(SqList *L,int i,int &e){          //e:顺序表中第i个值
    if(i<1||i>L->length)
        return false;
    e=L->data[i-1];
    return true;
}

int locate_elem(SqList *L,int e){               //按元素值查找，返回逻辑序号
    int i=0;
    while(i<L->length&&L->data[i]!=e)
        i++;
    if(i>=L->length)
        return 0;
    else
        return i+1;
}

bool insert(SqList*&L,int i,int e){             //插入e到第i个元素
    if(i<1||i>L->length)
        return false;
    i--;
    for(int j=L->length;j>i;j--)
        L->data[j]=L->data[j-1];
    L->data[i]=e;
    L->length++;
    return true;
}
bool delete_elem(SqList *&L,int i,int &e){          //删除第i个元素
    if(i<1||i>L->length)
        return false;
    i--;
    e=L->data[i];
    for(int j=i;j<L->length-1;j++)
        L->data[j]=L->data[j+1];
    L->length--;
    return true;
}
//有序表 插入算法
void orderinsert(SqList*&L,int e){
    int i=0;
    while(i<L->length&&L->data[i]<e)
        i++;
    for(int j=L->length;j>i;j--)
        L->data[j]=L->data[j-1];
    L->data[i]=e;
    L->length++;
}

//二路归并
void union_list(SqList* LA,SqList * LB,SqList *& LC){
    int i=0,j=0,k=0;
    LC=(SqList*)malloc(sizeof(SqList));
    while(i<LA->length&&j<LB->length){
        if(LA->data[i]<LB->data[j])
        {
            LC->data[k]=LA->data[i];
            i++;k++;
        }
        else
        {
            LC->data[k]=LB->data[j];
            j++;k++;
        }
    }
    while(i<LA->length){
        LC->data[k]=LA->data[i];
        i++;k++;
    }
    while(j<LB->length){
        LC->data[k]=LB->data[j];
        j++;k++;
    }
    LC->length=k;
}
int main() {

    return 0;
}