#include <iostream>

#define MAX 10
//尾进头出
typedef struct
{
    int data[MAX];
    int front,rear;      //队列为空：front=rear
}SqQueue;

void init(SqQueue *&q){
    q=(SqQueue*)malloc(sizeof(SqQueue));
    q->front=q->rear=-1;
}

bool enqueue(SqQueue *&q,int e){
    if(q->rear==MAX-1)
        return false;
    q->rear++;
    q->data[q->rear]=e;
    return true;
}
bool dequeue(SqQueue *&q,int &e){
    if(q->rear==q->front)
        return false;
    q->front++;
    e=q->data[q->front];
    return true;
}

//环形队列
//队列为空:front=rear
void init_c(SqQueue *&q){
    q=(SqQueue*)malloc(sizeof(SqQueue));
    q->front=q->rear=0;
}
bool enqueue_c(SqQueue *&q,int e){
    if((q->rear+1)%MAX==q->front)
        return false;
    q->rear=(q->rear+1)%MAX;
    q->data[q->rear]=e;
    return true;
}
bool dequeue_c(SqQueue *&q,int &e){
    if(q->rear==q->front)
        return false;
    q->front=(q->front+1)%MAX;
    e=q->data[q->front];
    return true;
}


typedef struct qnode
{
    int data;
    struct qnode *next;
}DataNode;
typedef struct
{
    DataNode *front;
    DataNode *rear;
}LinkQuNode;
void init_q(LinkQuNode*&q){
    q=(LinkQuNode*)malloc(sizeof(LinkQuNode));
    q->front=q->rear=NULL;
}
void destroy(LinkQuNode *&q){
    DataNode *pre,*p;
    pre=q->front;
    if(pre!=NULL)
    {
        p=pre->next;
        while(p!=NULL){
            free(pre);
            pre=p;
            p=p->next;
        }
        free(pre);
    }
    free(q);
}
void enqueue_l(LinkQuNode *& q,int e){
    DataNode *p;
    p=(DataNode*)malloc(sizeof(DataNode));
    p->data=e;
    p->next=NULL;
    if(q->rear==NULL)
        q->front=q->rear=p;
    else
    {
        q->rear->next=p;
        q->rear=p;
    }
}
bool dequeue_l(LinkQuNode *&q,int &e){
    DataNode *t;
    if(q->rear==NULL)
        return false;
    t=q->front;
    if(q->rear==q->front)
        q->rear=q->front=NULL;
    else
        q->front=q->front->next;
    e=t->data;
    free(t);
    return true;
}
    int main() {
        return 0;
    }
