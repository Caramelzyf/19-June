#include <iostream>

//单链表
typedef struct LNode
{
    int data;
    struct LNode *next;
}LinkNode;

void CreatListF(LinkNode *&L,int a[],int n){       // 头插法
    LinkNode *s;
    L=(LinkNode*)malloc(sizeof(LinkNode));
    L->next=NULL;
    for(int i=0;i<n;i++){
        s=(LinkNode*)malloc(sizeof(LinkNode));
        s->data=a[i];
        s->next=L->next;
        L->next=s;
    }
}

void CreatListR(LinkNode *&L,int a[],int n){       //尾插法
    LinkNode *s,*r;
    L=(LinkNode*)malloc(sizeof(LinkNode));
    r=L;
    for(int i=0;i<n;i++){
        s=(LinkNode* )malloc(sizeof(LinkNode));
        s->data=a[i];
        r->next=s;
        r=s;
    }
    r->next=NULL;

}

void InitList(LinkNode *&L){                      //初始化
    L=(LinkNode*)malloc(sizeof(LinkNode));
    L->next=NULL;
}

void DestroyList(LinkNode *&L){                   //销毁单链表
    LinkNode *pre,*p;
    pre=L;
    p=L->next;
    while(p!=NULL){
        free(pre);
        pre=p;
        p=pre->next;
    }

    free(pre);
}

bool ListEmpty(LinkNode *&L){                      //链表是否为空
    return (L->next==NULL);
}

int Listlength(LinkNode *&L){                      //链表的长度
    LinkNode *p=L;
    int n=0;
    while(p->next!=NULL){
        n++;
        p=p->next;

    }
    return n;
}

void DisList (LinkNode*&L){                       //输出
    LinkNode *p=L->next;
    while(p!=NULL){
        printf("%d",p->data);
        p=p->next;
    }
    printf("\n");
}

bool GetElem(LinkNode *L,int i,int &e){            //查找第i个元素的值
    int j=0;
    LinkNode *p=L;
    if(i<0)
        return false;

    while(j<i&&p!=NULL){
       p= p->next;
       j++;
    }
    if(p==NULL)
        return false;
    else
        e=p->data;
    return true;
}

int LocateElem(LinkNode * L,int e){               //查找元素的逻辑序号
    int i=1;
    LinkNode *p=L->next;
    while (p!=NULL&&p->data!=e){
        i++;
        p=p->next;
    }
    if(p->data==e)
        return i;
    else
        return 0;
}
bool ListInsert(LinkNode *&L,int i,int e){       //插入数据元素
    LinkNode *p=L,*s;
    int j=0;
    if(i<=0)
        return false;

    while(j<i-1&&p!=NULL){
        j++;
        p=p->next;
    }
    if(p==NULL)
        return false;
    else
    {
        s=(LinkNode*)malloc(sizeof(LinkNode));
        s->data=e;
        s->next=p->next;
        p->next=s;
        return true;
    }
}

bool ListDelete(LinkNode *&L,int i,int e){          //销毁单链表
    LinkNode *p,*q;
    int j=0;
    p=L;
    if(i<=0)
        return false;
    while(j<i-1&&p!=NULL){
        j++;
        p=p->next;
    }
    if(p==NULL)
        return false;
    else
    {
        q=p->next;
        if(q==NULL)
            return false;
        else
        {
            p->next=q->next;
            e=q->data;
            free(q);
            return true;
        }
    }
}

//eg 1
void splid(LinkNode *&L,LinkNode *&L1,LinkNode *&L2){
    LinkNode *p=L->next,*q,*r;
    L1=L;
    r=L1;
    L2=(LinkNode*)malloc(sizeof(LinkNode));
    L2->next=NULL;

    while(p!=NULL){
        r->next=p;
        r=r->next;
        p=p->next;
        q=p->next;
        p->next=L2->next;
        L2->next=p;
        p=q;

    }
    r->next=NULL;


}

//双链表
typedef struct DNode
{
    int data;
    struct DNode *prior;
    struct DNode *next;
}DLinkNode;

//建立双链表
//头插法
void createlistF(DLinkNode *&L,int a[],int n){
    DLinkNode *s;
    L=(DLinkNode*)malloc(sizeof(DLinkNode));
    L->prior=L->next=NULL;
    for(int i=0;i<n;i++){
        s=(DLinkNode*)malloc(sizeof(DLinkNode));
        s->data=a[i];
        s->next=L->next;
        if(L->next!=NULL)           //将l后的第一个指针的prior域指向s
            L->next->prior=s;
        L->next=s;
        s->prior=L;
    }
}
//尾插法
void createlistR(DLinkNode *&L,int a[],int n){
    DLinkNode *s,*r;
    L=(DLinkNode*)malloc(sizeof(DLinkNode));
    r=L;
    for(int i=0;i<n;i++){
        s=(DLinkNode*)malloc(sizeof(DLinkNode));
        s->data=a[i];
        r->next=s;
        s->prior=r;
        r=s;
    }
    r->next=NULL;
}
//插入
bool insert(DLinkNode*&L,int i,int e){
    int j=0;
    DLinkNode *s,*p=L;
    if(i<=0)
        return false;
    while(j<i-1&&p!=NULL){
        p=p->next;
        j++;
    }
    if(p==NULL)
        return false;
    else
    {
        s=(DLinkNode*)malloc(sizeof(DLinkNode));
        s->data=e;
        s->next=p->next;
        if(p->next!=NULL)
            p->next->prior=s;
        s->prior=p;
        p->next=s;
        return true;
    }
}
//删除某结点元素
bool delete_elem(DLinkNode*&L,int i,int e){
    int j=0;
    DLinkNode *q,*p=L;
    if(i<=0)
        return false;
    while(j<i-1&&p!=NULL){
        p=p->next;
        j++;
    }
    if(p==NULL)
        return false;
    else
    {
        q=p->next;
        if(q==NULL)
            return false;
        e=q->data;
        p->next=q->next;
        if(p->next!=NULL)
            p->next->prior=p;
        free(q);
        return true;
    }
}
//有序表 插入
void insert_orderlist(LinkNode *&L,int e){
    LinkNode *pre=L,*p;
    p=(LinkNode*)malloc(sizeof(LinkNode));
    p->data=e;
    while(pre->next!=NULL&&pre->next->data<e){
        pre=pre->next;
    }
    p->next=pre->next;
    pre->next=p;
}
//二路归并
void unionlist(LinkNode *&LA,LinkNode *&LB,LinkNode*&LC){
    LinkNode *pa=LA->next,*pb=LB->next,*r,*s;
    LC=(LinkNode*)malloc(sizeof(LinkNode));
    r=LC;
    while(pa!=NULL&&pb!=NULL){
        if(pa->data<pb->data){
            s=(LinkNode*)malloc(sizeof(LinkNode));
            s->data=pa->data;
            r->next=s;
            r=s;
            pa=pa->next;
        }
        else {
            s=(LinkNode*)malloc(sizeof(LinkNode));
            s->data=pb->data;
            r->next=s;
            r=s;
            pb=pb->next;
        }
    }
    while(pa!=NULL){
        s=(LinkNode*)malloc(sizeof(LinkNode));
        s->data=pa->data;
        r->next=s;
        r=s;
        pa=pa->next;
    }
    while(pb!=NULL){
        s=(LinkNode*)malloc(sizeof(LinkNode));
        s->data=pb->data;
        r->next=s;
        r=s;
        pb=pb->next;
    }
    r->next=NULL;
}
int main() {

    return 0;
}