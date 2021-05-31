//Heap.c
//Tue 25 May 2021 08:28:36 PM CST
//author: 1036-ce
//version :1.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ER 0x3f3f3f3f

typedef int ElementType;
typedef struct Heap
{
	ElementType *data;
	int size;
	int flag;// if flag=0 then the heap is a minheap. else it is a maxheap;
}Heap;

void swap(ElementType *a,ElementType *b)
{
	ElementType tem=*a;
	*a=*b;
	*b=tem;
}

void MinHeapify(Heap *H)
{
	int n=(H->size-1)/2;	
	n=n-((2*n+1)==H->size);	//以上两式计算最后一个非叶子节点的下标
	
	while(n>=0)
	{
		ElementType *min=&H->data[2*n+1];
		int f=2*n+1;
		if(2*n+2<H->size && H->data[2*n+1]>H->data[2*n+2])
		{
			min=&H->data[2*n+2];
			f=2*n+2;
		}
		if(*min < H->data[n])
		{
			swap(min,&H->data[n]);
			while(2*f+1<H->size)
			{
				int f1=f;
				ElementType *min1=&H->data[2*f1+1];
				f=2*f1+1;
				if(2*f1+2<H->size && H->data[2*f1+1]>H->data[2*f1+2])
				{
					min1=&H->data[2*f1+2];
					f=2*f1+2;
				}
				if(*min1 < H->data[f1])
				{
					swap(min1,&H->data[f1]);
				}
			}
		}
		n--;
	}
}
void MaxHeapify(Heap *H)
{
	int n=(H->size-1)/2;
	n=n-((2*n+1)==H->size);

	while(n>=0)
	{
		ElementType *max=&H->data[2*n+1];
		int f=2*n+1;
		if(2*n+2 < H->size && H->data[2*n+1]<H->data[2*n+2])
		{
			max=&H->data[2*n+2];
			f=2*n+2;
		}
		if(*max> H->data[n])
		{
			swap(max , &H->data[n]);
			while(2*f+1<H->size)
			{
				int f1=f;
				ElementType *max1=&H->data[2*f1+1];
				f=2*f1+1;
				if(2*f1+2 < H->size && H->data[2*f1+1]< H->data[2*f1+2])
				{
					max1=&H->data[2*f1+2];
					f=2*f1+2;
				}
				if(*max1>H->data[f1])
				{
					swap(max1,&H->data[f1]);
				}
			}
		}
		n--;
	}

}
ElementType getMin(Heap* H)
{
	if(H->flag==1)
	{
		printf("The heap is a MaxHeap , can not execute this operator.\n");
		return ER;
	}
	else if(H->size==0)
	{
		printf("The Heap is empty\n");
		return ER;
	}
	else
	{
		H->size--;
		swap(&H->data[0],&H->data[H->size]);
		if(H->size > 0)
			MinHeapify(H);
		return H->data[H->size];
	}
}
ElementType getMax(Heap *H)
{
	if(H->flag==0)
	{
		printf("The heap is a MaxHeap , can not execute this operator.\n");
		return ER;
	}
	else if(H->size==0)
	{
		printf("The Heap is empty\n");
		return ER;
	}

	else
	{
		H->size--;
		swap(&H->data[0],&H->data[H->size]);
		if(H->size > 0)
			MaxHeapify(H);
		return H->data[H->size];
	}
}
Heap* CreateHeap(ElementType *data,int size,int flag)
{
	Heap* H=(Heap*)malloc(sizeof(Heap));
	H->data=(ElementType*)malloc(sizeof(ElementType)*size);
	H->size=size;
	H->flag=flag;
	for(int i=0;i<size;i++)
		H->data[i]=data[i];
	if(flag==0)
		MinHeapify(H);
	else
		MaxHeapify(H);
	return H;
}
void show(Heap *H)
{
	printf("flag=%d\n",H->flag);
	printf("size=%d\n",H->size);
	for(int i=0;i<H->size;i++)
		printf("%d ",H->data[i]);
	printf("\n");
}
void Free(Heap *H)
{
	ElementType *tmp=H->data;
	free(tmp);
	free(H);
}
void help(void)
{
	printf("command \"getmin\": get the min from the minheap and delete it from the minheap\n");
	printf("command \"getmax\": get the max from the maxheap and delete it from the maxheap\n");
	printf("command \"show\": show the status of heap\n");
	printf("-------------------------------------------------------------------------------\n\n");
}
void test(void)
{
	int size;
	printf("Enter the size of heap:");
	scanf("%d",&size);
	ElementType data[size];
	printf("Enter the %d element(s):",size);
	for(int i=0;i<size;i++)
		scanf("%d",&data[i]);
	int flag;
	printf("Enter the type of heap(0 means a minheap and 1 means a maxheap):");
	scanf("%d",&flag);
	Heap *H=CreateHeap(data,size,flag);
	printf("Create Heap Success!!\n");
	while(1)
	{
		char s[10];
		scanf("%s",s);
		if(strcmp(s,"getmin")==0)
		{
			ElementType tmp=getMin(H);
			if(tmp!=ER)
				printf("%d\n",tmp);
		}
		else if(strcmp(s,"getmax")==0)
		{
			ElementType tmp=getMax(H);
			if(tmp!=ER)
				printf("%d\n",tmp);
		}
		else if(strcmp(s,"show")==0)
		{
			show(H);
		}
		else if(strcmp(s,"quit")==0)
		{
			printf("Over\n");
			break;
		}
		else if(strcmp(s,"help")==0)
		{
			help();
		}
		else
		{
			printf("ERROR: Unknown the command, please try again\n");
		}
	}
}
int main(void)
{
	test();
	return 0;
}
