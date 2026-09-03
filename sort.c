#include "sort.h"

//判断数组是否有序
bool isSorted(int* arr,int start,int end)
{
    for(int i=start;i<end;i++)
    {
        if(arr[i]>arr[i+1])
        {
            return false;
        }
    }
    return true;
}

//归并函数
void merge(int *arr,int *temparr,int left,int mid,int right)
{
    int i=left,j=mid+1;
    int k=left;
    while(i<=mid&&j<=right)
    {
        if(arr[i]<=arr[j])
        {
            temparr[k++]=arr[i++];
        }
        else
        {
            temparr[k++]=arr[j++];
        }
    }
    while(i<=mid)
    {
        temparr[k++]=arr[i++];
    }
    while(j<=right)
    {
        temparr[k++]=arr[j++];
    }
    for(int p=left;p<=right;p++)
    {
        arr[p]=temparr[p];
    }
}

void iterativeMergeSort(int* arr,int n,int* temparr,int left,int right)
{
    if(n<=1) return;
    int mid=(left+right)/2;
    if(!isSorted(arr,left,mid))
    {
        iterativeMergeSort(arr,mid-left+1,temparr,left,mid);
    }
    if(!isSorted(arr,mid+1,right))
    {
        iterativeMergeSort(arr,right-mid,temparr,mid+1,right);
    }
    merge(arr,temparr,left,mid,right);
}
//归并排序(递归)
void Iterative_MergeSort(int* arr,int n)
{
    int* temparr=(int*)malloc(sizeof(int)*n);
    iterativeMergeSort(arr,n,temparr,0,n-1);
    free(temparr);
}



//归并排序(非递归)
void Non_Iterative_MergeSort(int* arr,int n)
{
    int* temparr=(int*)malloc(sizeof(int)*n);
    for(int i=1;i<n;i*=2)//i表示归并数组中元素个数
    {
        int left=0,mid=left+i-1,right=left+i*2-1;//left,mid,right用来划分数组
        while(mid<n-1)//保证至少mid的右侧有一个元素
        {
            if(right>=n)
            {
                right=n-1;
            }
            merge(arr,temparr,left,mid,right);
            left+=i*2;
            mid+=i*2;
            right+=i*2;
        }
    }
    free(temparr);
}

//交换函数
void swap(int* a,int* b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}

//递归判断是否是堆并进行调整
void Heap(int* arr,int n,int node)//形参解释：node是待判断和调整的堆结点
{
    if(2*node>n) return;//不存在子节点
    if((2*node<=n)&&(2*node+1)>n)//仅仅存在左孩子结点
    {
        if(arr[node]<arr[2*node])//小于左孩子
        {
            swap(&arr[node],&arr[2*node]);
            //说明:如果这个结点仅仅存在左孩子，说明这个结点左孩子没有孩子，此时不需要递归了
        }
        return;
    }
    else//左右孩子结点都存在
    {
        if(arr[node]>=arr[2*node]&&arr[node]>=arr[2*node+1])//大于左右孩子结点
        {
            return;
        }
        else if(arr[node]<arr[2*node]&&arr[node]>=arr[2*node+1])//小于左孩子
        {
            swap(&arr[node],&arr[2*node]);
            Heap(arr,n,2*node);
        }
        else if(arr[node]>=arr[2*node]&&arr[node]<arr[2*node+1])
        {
            swap(&arr[node],&arr[2*node+1]);
            Heap(arr,n,2*node+1);
        }
        else//小于左右两个孩子
        {
            int index=arr[2*node]>=arr[2*node+1]?(2*node):(2*node+1);
            swap(&arr[node],&arr[index]);
            Heap(arr,n,index);
        }
    }
}

//建立堆函数
void CreateHeap(int* arr,int n)
{
    for(int i=n;i>=2;i--)
    {
        if(arr[i]>arr[i/2])
        {
            swap(&arr[i],&arr[i/2]);
            Heap(arr,n,i);//每次交换，堆可能发生变化，需要调用函数进行调整
        }
    }
}


/*
堆排序算法：
注意传入的数组是从下标1开始的，数组下标0不存储数据，
也就是说传入的参数数组大小n实际上只有索引为1到n的元素是有效的，0索引无效
另一方面，数组arr的实际大小为n+1
*/
void Heap_Sort(int *arr,int n)
{
    if(n<=1) return;
    CreateHeap(arr,n);//将数组转化为堆
    for(int i=n;i>=2;i--)
    {
        swap(&arr[i],&arr[1]);
        Heap(arr,i-1,1);
        //解释：
        //1.第二个参数为何是i-1:最大的数已经到了数组中最后一个位置，无需调整
        //2.第三个参数为何是1:将一个不确定大小的数调整到1的位置，需要重新判断和调整保证还是堆的形式。
    }
}



//快速排序
void QuickSort(int *arr,int start,int end)
{
    if(start>=end) return;//待排序的数组中只有一个元素或没有元素
    int pivot=arr[start];//选取pivot值，pivot是随机的，因此这里默认是start指向的元素
    int left=start,right=end;
    bool empty=true;//empty表示空位，赋值true左边有空位，false右边有空位
    while(left!=right)
    {
        if(empty)
        {
            if(arr[right]<pivot)
            {
                arr[left]=arr[right];
                empty=false,left++;
            }
            else
            {
                right--;
            }
        }
        else
        {
            if(arr[left]>pivot)
            {
                arr[right]=arr[left];
                empty=true,right--;
            }
            else
            {
                left++;
            }
        }
    }
    arr[left]=pivot;
    //递归调用，第三个形参将其中的参数由left改成right也可以
    if(left-1>=start)
    {
        QuickSort(arr,start,left-1);
    }
    if(left+1<=end)
    {
        QuickSort(arr,left+1,end);
    }
}
void Quick_Sort(int* arr,int n)
{
    if(n<=1) return;
    QuickSort(arr,0,n-1);
}



//希尔排序
void Hill_Sort(int* arr,int n)//arr需要排序的数组，n数组中元素的个数
{
    int d=D;
    if(n<=1) return;
    while(d>0)
    {
        for(int i=d;i<n;i+=d)
        {
            int temp=arr[i];
            for(int j=i-d;j>=0;j-=d)
            {
                if(temp>=arr[j])
                {
                    arr[j+d]=temp;
                    break;
                }
                else
                {
                    arr[j+d]=arr[j];
                    if(j==0) arr[j]=temp;
                }
            } 
        }
        d/=2;
    }
}


//折半插入排序
void Mid_Insert_Sort(int* arr,int n)//arr为需要排序的数组，n为数组中元素的数量
{
    if(n<=1) return;
    for(int i=1;i<n;i++)
    {
        if(arr[i]>=arr[i-1]) continue;//有序的时候直接跳过，保证数组本身有序的时候时间复杂度为O(n)
        int temp=arr[i];
        int left=0,right=i-1;
        while(left<=right)
        {
            int mid=(left+right)/2;
            if(temp<arr[mid])
            {
                right=mid-1;
            }
            else
            {
                left=mid+1;
            }
        }
        for(int j=i-1;j>=left;j--)
        {
            arr[j+1]=arr[j];
        }
        arr[left]=temp;
    }
}



//直接插入排序算法
void Direct_Insert_Sort(int* arr,int n)
{
    if(n<=1) return;//数组中只有一个元素，不需要进行排序
    for(int i=1;i<n;i++)
    {
        int temp=arr[i];
        for(int j=i-1;j>=0;j--)
        {
            if(temp>=arr[j])
            {
                arr[j+1]=temp;
                break;
            }
            else
            {
                arr[j+1]=arr[j];
                if(j==0)
                {
                    arr[j]=temp;
                }
            }
        }
    }
}