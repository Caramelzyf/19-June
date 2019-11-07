#include <iostream>


typedef struct NODE
{
    char data;
    struct NODE *leftC;
    struct NODE *rightC;
}BTNode;                          //二叉链
typedef struct Node
{
    char data[MAX];
    int num_son;
    struct Node *sons[MAXSON];
}TSonNode;        //孩子链存储结构


//中序遍历递归算法
void order(BTNode *b)
{
    if(b==NULL)
        return;
    order(b->leftC);
    printf("%c",b->data);
    order(b->rightC);
}

//括号表示法表示树
void display(BTNode*b)
{
    if(b!=NULL){
        printf("%c",b->data);
        if(b->leftC!=NULL||b->rightC!=NULL){
            printf("(");
            display(b->leftC);
            if(b->rightC!=NULL)
                printf(",");
            display(b->rightC);
            printf(")");
        }
    }
}





//哈夫曼树
typedef struct
{
    char data;    //节点值
    double weight;   //权值
    int parent;
    int lchild;
    int rchild;
}HTNode;
void CreateHT(HTNode ht[],int n0)  //n0为叶子节点的个数
{
    int k,i,lnode,rnode;
    double min1,min2;
    for(i=0;i<2*n0-1;i++)
        ht[i].parent=ht[i].lchild=ht[i].rchild=-1;
    for(i=n0;i<=2*n0-1;i++)
    {
        min1=min2=32767;
        lnode=rnode=-1;        //确定最小权重的两个节点位置
        for(k=0;k<=i-1;k++)
        {
            if(ht[k].parent==-1)
            {
                if(ht[k].weight<min1)
                {
                    min2=min1;
                    rnode=lnode;
                    min1=ht[k].weight;
                    lnode=k;
                }
                else if (ht[k].weight<min2)
                {
                    min2=ht[k].weight;
                    rnode=k;
                }
            }
        }
        ht[i].weight=ht[lnode].weight+ht[rnode].weight;
        ht[i].lchild=lnode;
        ht[i].rchild=rnode;
        ht[lnode].parent=i;
        ht[rnode].parent=i;
    }
}
///哈夫曼编码
#define N 10
typedef struct
{
    char cd[N];    //存放当前节点的哈夫曼编码
    int start;    //表示cd[start...n0]部分是哈夫曼编码
}HCode;
void CreateHCode (HTNode ht[],HCode hcd[],int n0)
{
    int i,f,c;
    HCode hc;
    for(i=0;i<n0;i++)
    {
        hc.start=n0;
        c=i;
        f=ht[i].parent;
        while(f!=-1)
        {
            if(ht[f].lchild==c)
                hc.cd[hc.start--]='0';
            else
                hc.cd[hc.start--]='1';
            c=f;
            f=ht[f].parent;
        }
        hc.start++;
        hcd[i]=hc;
    }
}
#define N 100010

struct node {
    int now;
    int period;
    int id;
} a[N];
int num=0;
void swap(struct node *x, struct node *y)
{
    struct node tmp=*x;
    *x=*y;
    *y=tmp;
}
bool cmp(struct node x, struct node y)
{
    if(x.now!=y.now)                 //x小，返回true；y小，返回false
    {
        return x.now<y.now;
    }
    return x.id<y.id;              //x，y的值相等，返回较小的id
}

void push(struct node a[], struct node val)     //将val放入堆中
{
    num++;                   //堆中元素个数加一
    a[num]=val;
    int p=num;
    while(p>1 && cmp(a[p],a[p/2]))      //保持小根堆的特性，根节点为a[1]，当 p不是根节点且a[p]<a[p/2]时
    {
        swap(&a[p/2],&a[p]);
        p/=2;
    }
}
struct node pop(struct node a[])
{
    struct node res =a[1];        //弹出根节点
    num--;
    a[1]=a[num];                   //将最末尾的结点放到根节点的位置，再调整堆
    int p=1,t;
    while(p*2<=num)
    {
        if(p*2+1>num||cmp(a[p*2],a[p*2+1]))
        {
            t=p*2;            //选出存在的子节点中较大的
        }else {
            t=p*2+1;
        }
        if(cmp(a[t],a[p])) {
            swap(&a[p],&a[t]);
            p=t;
        }else {
            break;       //调整结束
        }
    }
    return res;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}