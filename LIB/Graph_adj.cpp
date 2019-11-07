//图的存储结构：邻接表、邻接矩阵


#include <iostream>

#define MAXV 100  //最大顶点个数
#define INF 32767  //无穷，指不邻接的点
typedef struct
{
    int no;   //顶点的编号
              //顶点的其他信息
}VertexType;              //顶点的类型

typedef struct
{
    int edges[MAXV][MAXV];    //邻接矩阵数组
    int n,e;                  //顶点数、边数
    VertexType vexs[MAXV];    //存放顶点信息
}MatGraph;                                  //完整的邻接矩阵类型

typedef struct ANode
{
    int adjvex;            //该边的邻接点编号
    struct ANode *nextarc; //指向下一条边的指针
    int weight;            //该边的相关信息，例如权值
}ArcNode;                                  //边结点类型

typedef struct Vnode
{
      ArcNode *firstarc;  //指向第一个边结点
                          //顶点的其他信息
}VNode;                                   //邻接表的头结点类型
typedef struct
{
    VNode adjlist[MAXV];  //邻接表的头结点数组
    int n,e;              //图的顶点数和边数
}AdjGraph;                                //完整的图邻接表类型
typedef struct
{
    int data;          //顶点编号
    int parent;        //前一个顶点的位置
}QUEUE;
typedef struct
{
    int data[MAXV];
    int front,rear;
}SqQueue;




#define MAX 20010
struct node {
    int weight;
    int v;             //到v
    int next;        //指向兄弟结点，没有兄弟结点为-1
}e[MAX];
int p[MAX];           //存储父节点（边的开始结点）u
int eid;                //标记边的个数、序号
//int f[MAX];       //存储已经计算过的子节点个数
void init()
{
    memset(p,-1, sizeof p);
    //memset(f,-1, sizeof(f));
    eid=0;
}
void add (int u,int v,int w)     //存储一条边在e结构体数组中
{
    e[eid].v=v;
    e[eid].weight=w;
    e[eid].next=p[u];
    p[u]=eid;
    eid++;
}





//由邻接矩阵创建图的邻接表
void CreateAdj(AdjGraph *g,int a[MAXV][MAXV],int n,int e)
{
    ArcNode *p;
    g=(AdjGraph *)malloc(sizeof(AdjGraph));
    for(int i=0;i<n;i++)
        g->adjlist[i].firstarc=NULL;
    for(int i=0;i<n;i++)
    {
        for(int j=n-1;j>=0;j--)

            if(a[i][j]!=0&&a[i][j]!=INF)
            {
                p=(ArcNode*)malloc(sizeof(ArcNode));
                p->adjvex=j;
                p->weight=a[i][j];
                p->nextarc=g->adjlist[i].firstarc;
                g->adjlist[i].firstarc=p;
            }
    }
    g->n=n;
    g->e=e;
}

//输出邻接表
void DispAdj(AdjGraph *g)
{
    ArcNode *p;
    for(int i=0;i<g->n;i++){
        p=g->adjlist[i].firstarc;
        printf("%d:",i);
        while (p!=NULL){
            printf("%d[%d]->",p->adjvex,p->weight);
            p=p->nextarc;
        }
        printf("^\n");
    }
}

//销毁邻接表
void DestroyAdj(AdjGraph *g)
{
    ArcNode *pre,*p;
    for(int i=0;i<g->n;i++){
        pre=g->adjlist[i].firstarc;
        if(pre!=NULL)
        {
            p=pre->nextarc;
            while (p!=NULL)
            {
                free(pre);
                pre=p;
                p=p->nextarc;
            }
            free(pre);
        }
    }
    free(g);
}

//将邻接表转换为邻接矩阵
void ListToMat(AdjGraph *G,MatGraph &g)
{
    ArcNode *p;
    for(int i=0;i<G->n;i++){
        p=G->adjlist[i].firstarc;
        while (p!=NULL){
            g.edges[i][p->adjvex]=p->weight;
            p=p->nextarc;
        }
    }
    g.n=G->n;
    g.e=G->e;
}

//将邻接矩阵g转换成邻接表G
void MatToList(MatGraph g,AdjGraph *&G)
{
    int i,j;
    ArcNode *p;
    G=(AdjGraph *)malloc(sizeof(AdjGraph));
    for (i=0; i<g.n; i++)	 	//将邻接表中所有头结点的指针域置初值
        G->adjlist[i].firstarc=NULL;
    for (i=0;i<g.n;i++)		//检查邻接矩阵中每个元素
        for (j=g.n-1;j>=0;j--)
            if (g.edges[i][j]!=0 && g.edges[i][j]!=INF)	//存在一条边
            {
                p=(ArcNode *)malloc(sizeof(ArcNode));
                p->adjvex=j; p->weight= g.edges[i][j];
                p->nextarc=G->adjlist[i].firstarc;//采用头插法插入结点p
                G->adjlist[i].firstarc=p;
            }
            G->n=g.n;G->e=g.e;
}

int visited[MAXV];
//深度优先遍历
void DFS(AdjGraph *G,int v)
{
    ArcNode *p;
    visited[v]=1;
    printf("%d",v);
    p=G->adjlist[v].firstarc;
    while(p!=NULL)
    {
        if(visited[p->adjvex]==0)
            DFS(G,p->adjvex);
        p=p->nextarc;
    }
    printf("\n");
}

//广度优先遍历
void BFS(AdjGraph *G,int v)
{
    int w,i;
    ArcNode *p;
    SqQueue *qu;
    qu=(SqQueue*)malloc(sizeof(SqQueue));
    qu->front=qu->rear=-1;
    int visited[MAXV];
    for(i=0;i<G->n;i++)
        visited[i]=0;
    printf("%d",v);
    visited[v]=1;
    qu->rear++;
    qu->data[qu->rear]=v;
    while(qu->rear!=qu->front){
        qu->front++;
        w=qu->data[qu->front];
        p=G->adjlist[w].firstarc;
        while(p!=NULL){
            if(visited[p->adjvex]==0)
            {
                printf("%d",p->adjvex);
                visited[p->adjvex]=1;
                qu->rear++;
                qu->data[qu->rear]=p->adjvex;
            }
            p=p->nextarc;
        }
    }
    printf("\n");
}

//非连通图的遍历
void DisConnect(AdjGraph *g)
{
    for(int i=0;i<g->n;i++)
        if(visited[i]==0)
            BFS(g,i);
    for(int i=0;i<g->n;i++)
        if(visited[i]==0)
            DFS(g,i);
}

//判断图的连通性
bool Connect(AdjGraph*g)
{
    bool flag=true;
    for(int i=0;i<g->n;i++)
        visited[i]=0;
    DFS(g,0);
    for(int i=0;i<g->n;i++){
        if(visited[i]==0)
        {
            flag= false;
            break;
        }
    }
    return flag;
}

//判断图g中从顶点u到v是否存在简单路径
void ExistPath(AdjGraph*g,int u,int v,bool &has)
{
    //has表示u到v是否有路径，初始值为false
    int w;
    ArcNode *p;
    visited[u]=1;
    if(u==v)
    {
        has= true;
        return;
    }
    p=g->adjlist[u].firstarc;    //p指向u的第一个邻接点
    while(p!=NULL){
        w=p->adjvex;             //w是p的编号
        if(visited[w]==0)
            ExistPath(g,w,v,has);
        p=p->nextarc;
    }
}

//输出图g中从顶点u到v的所有简单路径
void FindAllPath(AdjGraph *g,int u,int v,int path[],int d)
{
    //d表示path中路径长度，初始值为-1
    int w;
    ArcNode *p;
    d++;              //将顶点加入到路径中
    path[d]=u;
    visited[u]=1;
    if(u==v&&d>=0)    //如果找到一条路径，输出   只需输出一条路径：u==v
    {
        for(int i=0;i<=d;i++){
            printf("%d",path[i]);
        }
        printf("\n");
    }
    p=g->adjlist[u].firstarc;    //p指向u的第一个邻接点
    while(p!=NULL){
        w=p->adjvex;             //w是p的编号
        if(visited[w]==0)
            FindAllPath(g,w,v,path,d);
        p=p->nextarc;
    }
    visited[u]=0;
}

//输出图g中从顶点u到v、长度为l的所有简单路径
void PathlenAll(AdjGraph *g,int u,int v,int l,int path[],int d)
{
    int w;
    ArcNode *p;
    d++;              //将顶点加入到路径中
    path[d]=u;
    visited[u]=1;
    if(u==v&&d==l)    //如果找到一条路径，输出
    {
        for(int i=0;i<=d;i++){
            printf("%d",path[i]);
        }
        printf("\n");
    }
    p=g->adjlist[u].firstarc;    //p指向u的第一个邻接点
    while(p!=NULL){
        w=p->adjvex;             //w是p的编号
        if(visited[w]==0)
            PathlenAll(g,w,v,l,path,d);
        p=p->nextarc;
    }
    visited[u]=0;
}

//输出图g中所有经过顶点k的所有简单回路
void path_r(AdjGraph *g,int k,int path[],int d)
{
    int w;
    ArcNode *p;
    visited[k]=1;
    d++;
    path[d]=k;
    p=g->adjlist[k].firstarc;//p为顶点k的第一个邻接点
    while(p!=NULL)
    {
        w=p->adjvex;
    }

}


//输出图g中从顶点u到v的最短路径
void ShortPath(AdjGraph *g,int u,int v)
{
    ArcNode *p;
    int w,j;
    QUEUE qu[MAXV];
    int visit[MAXV];
    int path[MAXV];
    int t=0;
    int front=-1,rear=-1;
    for(int i=0;i<MAXV;i++)
        visit[i]=0;
    rear++;
    qu[rear].data=u;           //u进队
    qu[rear].parent=-1;
    visit[u]=1;
    while(front!=rear)         //队不空时循环
    {
        front++;
        w=qu[front].data;
        if(w==v)
        {
            j=front;
            while (qu[j].parent!=-1)
            {
                path[t]=qu[j].data;
                t++;
                j=qu[j].parent;
            }
            for(int i=t;i>=0;i--)
                printf("%d",path[i]);
            printf("\n");
            return;
        }
        p=g->adjlist[w].firstarc;
        while (p!=NULL){
            if(visit[p->adjvex]==0){
                visit[p->adjvex]=1;
                rear++;
                qu[rear].data=p->adjvex;           //w邻接点进队
                qu[rear].parent=front;
            }
            p=p->nextarc;
        }
    }
}

//输出图g中距顶点v最远的一个顶点
int Maxdist(AdjGraph *g,int v){
    ArcNode *p;             //边结点p
    int qu[MAXV];//环形队列数组
    int k=0,j=0;
    int front=0,rear=0;      //头尾指针
    int visited[MAXV];
    for(int i=0;i<g->n;i++)
    {
        visited[i]=0;       //访问标记数组初始化为0
    }
    rear++;
    qu[rear]=v;         //顶点v进队
    visited[v]=1;      //已经访问顶点v
    while(rear!=front){          //将所有未访问过的邻接点进队
        front=(front+1)%MAXV;
        k=qu[front];
        p=g->adjlist[k].firstarc;//p指向k的第一个邻接点
        while (p!=NULL){
            j=p->adjvex;      //j指向p的下一个邻接点
            if(visited[j]==0)
            {
                visited[j]=1;
                rear=(rear+1)%MAXV;
                qu[rear]=j;
            }
            p=p->nextarc;
        }
    }
    return k;
}
//普利姆算法 求最小生成树
void Prim (MatGraph g,int v)    //以顶点v为起点，构建用邻接矩阵表示的图g的最小生成树
{
    int closest[MAXV];//
    int lowcost[MAXV];//
    int min;
    int k;            //记录最近顶点编号
    for(int i=0;i<g.n;i++)      //给两个数组置初值
    {
        lowcost[i]=g.edges[v][i];
        closest[i]=v;
    }
    for(int i=1;i<g.n;i++)
    {
        min=INF;             //初始化最小值
        for(int j=0;j<g.n;j++)
        {
            if(lowcost[j]!=0&&lowcost[j]<min)
            {
                min=lowcost[j];
                k=j;         //寻找下一个权值最小的边
            }
        }
        printf("边（%d,%d),权值：%d\n",closest[k],k,min);
        lowcost[k]=0;       //表示顶点k已经加入生成树中
        for(int j=0;j<g.n;j++)    //调整已加入生成树的顶点与其余顶点之间的候选边
        {
            if(lowcost[j]!=0&&g.edges[k][j]<lowcost[j])     //k为新加入的顶点，j为即将加入的顶点
            {
                lowcost[j]=g.edges[k][j];
                closest[j]=k;
            }
        }
    }
}


void Dijkstra(MatGraph g,int v)
{
    int dist[MAXV];
    int path[MAXV];
    int s[MAXV];     //s[i]=0,表示未访问
    int min,u=0;
    for(int i=0;i<g.n;i++) {
        dist[i]=g.edges[v][i];
        s[i]=0;
        if(g.edges[v][i]<INF)
            path[i]=v;
        else
            path[i]=-1;
    }
    s[v]=1;
    path[v]=0;
    for(int i=0;i<g.n-1;i++) {
        min=INF;
        for(int j=0;j<g.n;j++) {
            if(s[j]==0&&dist[j]<min) {
                u=j;
                min=dist[j];
            }
        }
        s[u]=1;
        for(int j=0;j<g.n;j++) {          //路径调整
            if(s[j]==0) {
                if(g.edges[u][j]<INF && dist[u]+g.edges[u][j]<dist[j]) {
                    dist[j]=dist[u]+g.edges[u][j];
                    path[j]=u;
                }
            }
        }
    }
}
































int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
