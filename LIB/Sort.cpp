#include <iostream>
#define MAXD 10
typedef struct
{
    int key;   //关键字项
               //其他数据项
}RecType;      //排序元素类型

//直接插入排序
void InsertSort(RecType r[],int n)
{
    RecType tmp;
    int j;
    for(int i=1;i<n;i++)
    {
        if(r[i].key<r[i-1].key)  //当无序区第一个数小于有序区最后一个数时
        {
            tmp=r[i];
            j=i-1;
            do                  //找到tmp的插入位置
            {
                r[j+1]=r[j];
                j--;
            }while(j>=0&&r[j].key>tmp.key);
            r[j+1]=tmp;
        }
    }
}

//折半插入排序
void BinInsertSort(RecType r[],int n)
{
    int low,high,mid;
    RecType tmp;
    for(int i=0;i<n;i++)
    {
        if(r[i].key<r[i-1].key)
        {
            tmp=r[i];
            low=0;
            high=i-1;
            while (low<=high)
            {
                mid=(high+low)/2;
                if(tmp.key<r[mid].key)
                    high=mid-1;
                else
                    low=mid+1;

            }
            for(int j=i-1;j>=high+1;j--)
                r[j+1]=r[j];
            r[high+1]=tmp;
        }
    }
}

//希尔排序 分组插入排序
void ShellSort(RecType r[],int n)
{
    int d;
    int j;
    RecType tmp;
    d=n/2;
    while(d>0)
    {
        for(int i=d;i<d;i++)
        {
            tmp=r[i];
            j=i-d;
            while(j>=0&&tmp.key<r[j].key)
            {
                r[j+d]=r[j];
                j=j-d;
            }
            r[j+d]=tmp;
        }
        d=d/2;
    }
}

//冒泡排序
void BubbleSort(RecType r[],int n)
{
    RecType tmp;
    for(int i=0;i<n;i++)
        for(int j=n-1;j>i;j--)
            if(r[j].key<r[j-1].key)
            {
                tmp=r[j];
                r[j]=r[j-1];
                r[j-1]=tmp;
            }
}
//改进冒泡排序
void BubbleSort1(RecType r[],int n)
{
    RecType tmp;
    bool exchange;
    for(int i=0;i<n;i++)
    {
        exchange=false;
        for(int j=n-1;j>i;j--)
            if(r[j].key<r[j-1].key)
            {
                tmp=r[j];
                r[j]=r[j-1];
                r[j-1]=tmp;
                exchange= true;
            }
            if(!exchange)
                return;
    }
}

//快速排序
void QuickSort(RecType r[],int s,int t)
{
    int i,j;
    RecType tmp;
    if(s<t)
    {
        i=s;j=t;
        tmp=r[i];
        while(i<j)
        {
            while (j>i&&r[i].key>=tmp.key)
                j--;
            if(i<j)
                r[i++]=r[j];
            while (i<j&&r[i].key<=tmp.key)
                i++;
            if(i<j)
                r[j--]=r[i];
        }
        r[i]=tmp;
        QuickSort(r,s,i-1);
        QuickSort(r,i+1,t);
    }
}

//简单选择排序
void SelectSort(RecType r[],int n)
{   //选出无序区key最小的元素  与无序区的第一个元素交换位置
    int k;
    RecType tmp;
    for(int i=0;i<n;i++)
    {
        k=i;
        for(int j=i+1;j<n;j++)
        {
            if(r[j].key<r[k].key)
                k=j;               //寻找无序区i~n-1中key最小的r[k]
        }
        if(k!=i)
        {
            tmp=r[k];
            r[k]=r[i];
            r[i]=tmp;
        }
    }
}

//堆排序
void sift(RecType r[],int low,int high)     //筛选
{
    int i=low;
    int j=2*i;
    RecType tmp=r[i];
    while(j<=high)
    {
        if(j<high&&r[j].key<r[j+1].key)
            j++;         //j指向关键字较大的孩子
        if(tmp.key<r[j].key)
        {
            r[i]=r[j];
            i=j;
            j=2*i;
        }
        else
            break;            //根节点大于孩子节点，堆成立
    }
    r[j]=tmp;
}
void HeapSort(RecType r[],int n)
{
    int i;
    RecType tmp;
    for(i=n/2;i>=1;i--)
        sift(r,i,n);
    for(i=n;i>=2;i--)
    {
        tmp=r[1];
        r[1]=r[i];
        r[i]=tmp;
        sift(r,1,i-1);
    }
}


//二路归并
//对r[low]~r[high]进行归并
void Merge (RecType r[],int low,int mid,int high)
{
    RecType *r1;
    int i=low,j=mid+1,k=0;  //i为第一段序列的下标，j为第二段序列的下标，k为r1的下标
    r1=(RecType*)malloc((high-low+1)*sizeof(RecType));
    while(i<=mid&&j<=high)
    {
        if(r[i].key<=r[j].key)
        {
            r1[k]=r[i];
            i++;k++;
        }
        else
        {
            r1[k]=r[j];
            i++;k++;
        }
    }
    while(i<=mid)
    {
        r1[k]=r[i];
        i++;k++;
    }
    while(j<=high)
    {
        r1[k]=r[j];
        i++;k++;
    }
    for(k=0,i=low;i<=high;k++,i++)
        r[i]=r1[k];
    free(r1);
}
//对整个序列进行一趟归并
void MergePass(RecType r[],int length,int n)
{
    int i;
    for(i=0;i+2*length-1<n;i=i+2*length)
        Merge(r,i,i+length-1,1+2*length-1);
    if(i+length-1<n)
        Merge(r,i,i+length-1,n-1);
}
//二路归并
void MergeSort(RecType r[],int n)
{
    int length;
    for(length=1;length<n;length=2*length)
        MergePass(r,length,n);
}

typedef struct node
{
    char data[MAXD];   //MAXD为最大的关键字位数
    struct node *next;  //指向下一个节点
}NodeType;           //基数排序数据的节点类型

#define MAXE 20		//线性表中最多元素个数
#define MAXR 10		//基数的最大取值

//LSD基数排序算法
void RadixSort(NodeType *&p,int r,int d)//p为待排序序列的单链表指针，r为基数，d为关键字实际位数
{
    NodeType *head[MAXR],*tail[MAXR],*t;
    int i,j,k;
    for(i=0;i<=d-1;i++)
    {
        for(j=0;j<r;j++)
            head[j]=tail[j]=NULL;
        while(p!=NULL)
        {
            k=p->data[i]-'0';
            if(head[k]==NULL)
            {
                head[k]=p;
                tail[k]=p;
            }
            else   //链表非空，使用尾插法建立单链表
            {
                tail[k]->next=p;
                tail[k]=p;
            }
            p=p->next;
        }
        p=NULL;                 //重新用p收集所有节点
        for(j=0;j<r;j++)
        {
            if(head[j]!=NULL)
            {
                if(p==NULL)       //第一个非空链队
                {
                    p=head[j];
                    t=tail[j];
                }
                else {        //其余链队
                    t->next=head[j];
                    t=tail[j];
                }
            }
        }
        t->next=NULL;
    }
}
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}