#include <iostream>
//迷宫问题的各种解法

//一、数组
#define MAX 20
#define M 4
#define N 4
struct
{
    int i;
    int j;
    int di;
}st[MAX],path[MAX];

int top=-1;
int count=0;
int minlen=M*N;
int mg[M+2][N+2]={{1,1,1,1,1,1},{1,0,0,0,1,1},{1,0,1,0,0,1},{1,0,0,0,1,1},{1,1,0,0,0,1},{1,1,1,1,1,1}};

void display_path()     //输出路径
{
    printf("%2d：",++count);
    for(int k=0;k<=top;k++)
        printf("(%d,%d)",st[k].i,st[k].j);
    printf("\n");
    if(top+1<minlen){
        for(int k=0;k<=top;k++)
            path[k]=st[k];
        minlen=top+1;
    }
}
void dis_minpath()      //输出最短路径
{
    printf("最短路径：\n");
    for(int k=0;k<minlen;k++)
        printf("(%d,%d)",path[k].i,path[k].j);
    printf("\n");
    printf("最短路径长度：%d\n",minlen);
}
void mgpath(int xi,int yi,int xe,int ye)
{
    int i,j,di;
    int find=0;
    int i1=0,j1=0;
    top++;
    st[top].i=xi;
    st[top].j=yi;
    st[top].di=-1;
    mg[xi][yi]=-1;
    while(top>-1){
        i=st[top].i;
        j=st[top].j;
        di=st[top].di;
        if(i==xe && j==ye){
            display_path();
            mg[i][j]=0;
            top--;
            i=st[top].i;
            j=st[top].j;
            di=st[top].di;
            i1=0;j1=0;
        }
        find=0;
        while(di<4&&!find){
            di++;
            switch(di)
            {
                case 0:i1=i;j1=j-1;break;
                case 1:i1=i-1;j1=j;break;
                case 2:i1=i+1;j1=j;break;
                case 3:i1=i;j1=j+1;break;
            }
            if(mg[i1][j1]==0)
                find=1;
        }
        if(find){
            st[top].di=di;
            top++;
            st[top].i=i1;
            st[top].j=j1;
            st[top].di=-1;
            mg[i1][j1]=-1;
        }
        else
        {
            mg[i][j]=0;
            top--;
        }
    }
    if(count==0)
        printf("无可走路径");
    else
        dis_minpath();
}

//二、栈
#define MaxSize 20
typedef struct
{     int i;			//当前方块的行号
    int j;				//当前方块的列号
    int di;	//di是下一可走相邻方位的方位号（0，1，2，3）
    int pre;	//本路径中上一方块在队列中的下标
}   Box;				//定义方块类型
typedef struct
{    Box data[MaxSize];
    int top;			//栈顶指针
}  StType;			//定义顺序栈类型

bool st_mgpath(int xi,int yi,int xe,int ye)	//求解路径为:(xi,yi)->(xe,ye)
{    Box path[MaxSize], e;  int i,j,di,i1,j1,k;   bool find;
    StType *st;				            //定义栈st
    st=(StType*)malloc(sizeof(StType));
    st->top=-1;                         //初始化栈顶指针 InitStack(st);
    e.i=xi; e.j=yi; e.di=-1;			//设置e为入口
    st->top++;
    st->data[st->top]=e;                //方块e进栈
    mg[xi][yi]=-1;	//入口的迷宫值置为-1避免重复走到该方块
    while (st->top!=-1)		//栈不空时循环
    {
        e=st->data[st->top];     //取栈顶方块e
        i=e.i; j=e.j; di=e.di;
        if (i==xe && j==ye)		//找到了出口,输出该路径
        {
            printf("一条迷宫路径如下:\n");
            k=0;
            while (st->top!=-1)
            {
                e=st->data[st->top];
                st->top--;   	//出栈方块e
                path[k++]=e;	//将e添加到path数组中
            }
            while (k>=1)
            {     k--;
                printf("\t(%d,%d)",path[k].i,path[k].j);
                if ((k+2)%5==0)  //每输出每5个方块后换一行
                    printf("\n");
            }
            printf("\n");
            free(st);//销毁栈
            return true;	//输出一条迷宫路径后返回true
        }
        find=false;
        while (di<4 && !find)   //找相邻可走方块(i1,j1)
        {	di++;                     // di初始值为-1
            switch(di)
            {
                case 0:i1=i-1; j1=j;   break;
                case 1:i1=i;   j1=j+1; break;
                case 2:i1=i+1; j1=j;   break;
                case 3:i1=i;   j1=j-1; break;
            }
            if (mg[i1][j1]==0)  find=true;
            //找到一个相邻可走方块，设置find为真
        }
        if (find)  		//找到了一个相邻可走方块(i1,j1)
        {       st->data[st->top].di=di;	  //修改原栈顶元素的di值
            e.i=i1; e.j=j1; e.di=-1;
            st->top++;
            st->data[st->top]=e; 	  //相邻可走方块e进栈
            mg[i1][j1]=-1;
            //(i1,j1)迷宫值置为-1避免重复走到该方块
        }
        else			//没有路径可走,则退栈
        {	e=st->data[st->top];
            st->top--;  	   //将栈顶方块退栈
            mg[e.i][e.j]=0;    //让退栈方块的位置变为其他路径可走方块
        }
    }
    free(st);	//销毁栈
    return false;		//表示没有可走路径
}

//三、队列
typedef struct
{
    Box data[MaxSize];
    int front,rear;	//队头指针和队尾指针
}  QuType;		//定义顺序队类型

void print(QuType *qu,int front)
{
    int k=front;
    int ns=0;
    int j;
    printf("\n");
    do
    {
        j=k;
        k=qu->data[k].pre;
        qu->data[j].pre=-1;
    }while(k!=0);
    printf("一条迷宫路径如下:\n");
    k=0;
    while (k<MaxSize)
    {
        if(qu->data[k].pre==-1)
        {
            ns++;
            printf("\t(%d,%d)",path[k].i,path[k].j);
            if (ns%5==0)  //每输出每5个方块后换一行
                printf("\n");
        }
        k++;
    }
    printf("\n");
}
bool mgpath1(int xi,int yi,int xe,int ye)	//搜索路径为:(xi,yi)->(xe,ye)
{      Box e;
    int i, j, di, i1, j1;
    QuType *qu;		//定义顺序队指针qu
    qu=(QuType*)malloc(sizeof(QuType));
    qu->front=qu->rear=0;    //初始化队列qu,InitQueue(qu);
    e.i=xi;  e.j=yi;   e.pre=-1;
    qu->rear++;
    qu->data[qu->rear]=e;//(xi,yi)进队
    mg[xi][yi]=-1;		//将其赋值-1,以避免回过来重复搜索
    while (qu->front!=qu->rear)		//队不空循环
    {
        qu->front++;
        e=qu->data[qu->front];//出队方块e
        i=e.i;   j=e.j;
        if (i==xe && j==ye)		//找到了出口,输出路径
        {
            print(qu,qu->front);	//调用print函数输出路径
            free(qu);		//销毁队列
            return true;			//找到一条路径时返回真
        }
        for (di=0;di<4;di++)		//循环扫描每个方位
        {	switch(di)
            {
                case 0:i1=i-1; j1=j;   break;
                case 1:i1=i;   j1=j+1; break;
                case 2:i1=i+1; j1=j;   break;
                case 3:i1=i;   j1=j-1; break;
            }
            if (mg[i1][j1]==0)
            {     e.i=i1;  e.j=j1;
                e.pre=qu->front;
                qu->rear++;
                qu->data[qu->rear]=e;	//(i1，j1)方块进队
                mg[i1][j1]=-1;	//将其赋值-1
            }
        }
    }
    free(qu);		//销毁队列
    return false;
}

//四、递归
typedef struct
{     Box data[MaxSize];
    int length;			//路径长度
}  PathType;			//定义路径类型

void mgpath(int xi,int yi,int xe,int ye,PathType path)  //求解路径为:(xi，yi)    (xe，ye)
{
    int di,k,i,j;
    if  (xi==xe && yi==ye)
    {
        path.data[path.length].i = xi;
        path.data[path.length].j = yi;
        path.length++;
        printf("迷宫路径%d如下:\n",++count);
        for (k=0;k<path.length;k++)
        {
            printf("\t(%d，%d)",path.data[k].i, path.data[k].j);
            if ((k+1)%5==0)	//每输出每5个方块后换一行
                printf("\n");
        }
        printf("\n");
    }
    else				//(xi，yi)不是出口
    {
        if (mg[xi][yi]==0)	//(xi，yi)是一个可走方块
        {
            di=0;
            while (di<4)          	//对于(xi，yi)四周的每一个相邻方位di
            {
                path.data[path.length].i = xi;
                path.data[path.length].j = yi;
                path.length++;       //路径长度增1
                switch(di)       	//找方位di对应的方块(i，j)
                {
                    case 0:i=xi-1; j=yi;   break;
                    case 1:i=xi;   j=yi+1; break;
                    case 2:i=xi+1; j=yi;   break;
                    case 3:i=xi;   j=yi-1; break;
                }
                mg[xi][yi]=-1;        //避免来回重复找路径
                mgpath(i,j,xe,ye,path);
                path.length--;		//回退一个方块
                mg[xi][yi]=0;		//恢复(xi，yi)为可走
                di++;
            }
        }
    }
}

//五、图搜索






int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}