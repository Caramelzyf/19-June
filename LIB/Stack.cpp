#include <iostream>
#define MAX 10
typedef struct {
    int data[MAX];
    int top;
}SqStack;

void init(SqStack *&s){
    s=(SqStack*)malloc(sizeof(SqStack));
    s->top=-1;
}

typedef struct LinkNode
{
    int data;
    struct LinkNode *next;
}LinkStNode;

void init_l(LinkStNode *&s){
    s=(LinkStNode*)malloc(sizeof(LinkStNode));    //创建头结点
    s->next=NULL;                                 //栈为空
}
void destroy(LinkStNode *&s){
    LinkStNode *pre=s,*p=s->next;
    while(p!=NULL){
        free(pre);
        pre=p;
        p=p->next;
    }
    free(pre);
}
void push(LinkStNode *&s,int e){
    LinkStNode *p;
    p=(LinkStNode*)malloc(sizeof(LinkStNode));
    p->data=e;
    p->next=s->next;
    s->next=p;
}
bool pop(LinkStNode *&s,int &e){
    LinkStNode *p;
    if(s->next==NULL)
        return false;
    p=s->next;
    e=p->data;
    s->next=p->next;
    free(p);
    return true;
}
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}