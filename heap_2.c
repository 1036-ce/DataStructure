//MinHeap.c 
//operator: insert, delelte ,find, getmin, heapify(min) 
//Wed 26 May 2021 12:29:22 PM CST
//author 1036-ce
//version :1.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 100
#define ER 0x3f3f3f3f

typedef int ElementType;

typedef struct HNode
{
	ElementType data[MAXSIZE];
	int size;
}HNode;
typedef HNode* Heap;

void swap(ElementType *a , ElementType *b)
{
	ElementType tem=*a;
	*a=*b;
	*b=tem;
}

void Heapify(Heap H, int pos)
{
	while(pos>=0)
	{
		ElementType *min=&H->data[2*pos+1];
		int f=2*pos+1;
		if(2*pos+2<H->size && H->data[2*pos+1]>H->data[2*pos+2])
		{
			min=&H->data[2*pos+2];
			f=2*pos+2;
		}
		if(*min<H->data[pos])
		{
			swap(min,&H->data[pos]);
			while(2*f+1<H->size)
			{
				int f1=f;
				ElementType *min1=&H->data[2*f1+1];
				f=2*f1+1;
				if(2*f1+2<H->size && H->data[2*f1+1]>H->data[2*f1+2])
				{
					min1=&H->data[2*f1+2];
				}
				if(*min1<H->data[f1])
				{
					swap(min1,&H->data[f1]);
				}
			}
		}
		pos--;
	}
}
void insert(Heap H,ElementType x)
{
	H->data[H->size++]=x;
	int pos=(H->size-1)/2;
	pos=pos-(2*pos+1==H->size);
	Heapify(H,pos);
}
int Find(Heap H,ElementType x)
{
	int pos=ER;
	for(int i=0;i<H->size;i++)
	{
		if(x==H->data[i])
		{
			pos=i;
			break;
		}
	}
	return pos;
}
void delete(Heap H,ElementType x)
{;
	int pos=Find(H,x);
	if(pos!=ER)
	{
		swap(&H->data[pos],&H->data[--H->size]);
		pos=(H->size-1)/2;
		pos=pos-(2*pos+1==H->size);
		Heapify(H,pos);
	}
	else
	{
		printf("There is not x in the heap.\n");
	}
}
ElementType getMin(Heap H)
{
	 if(H->size==0)
	{
		printf("The Heap is empty\n");
		return ER;
	}
	else
	{
		H->size--;
		swap(&H->data[0],&H->data[H->size]);
		if(H->size>0)
		{
			int pos=(H->size-1)/2;
			pos=pos-(2*pos+1==H->size);
			Heapify(H,pos);
		}
		return H->data[H->size];
	}
}
Heap CreateHeap(ElementType *data, int size)
{
	Heap H=(Heap)malloc(sizeof(HNode));
	H->size=size;
	for(int i=0;i<size;i++)
	{
		H->data[i]=data[i];
	}
	int pos=(size-1)/2;
	pos=pos-(2*pos+1==size);
	Heapify(H,pos);
	return H;
}
void show(Heap H)
{
	printf("size:%d\n",H->size);
	if(H->size==0)
		printf("The Heap is empty.\n");
	for(int i=0;i<H->size;i++)
	{
		printf("%d ",H->data[i]);
	}
	printf("\n");
}
void Free(Heap H)
{
	free(H);
}
void help(void)
{
	printf("command \"find\": find the pos of x that in heap.\n");
	printf("command \"getmin\": return the min in heap.\n");
	printf("command \"insert\": insert x to the heap.\n");
	printf("command \"delete\": delete x from the heap.\n");
	printf("command \"quit\": exit from the process.\n");
	printf("--------------------------------------------------\n");
}
void test(void)
{
	int size;
	printf("Enter the size of heap:");
	scanf("%d",&size);
	ElementType data[size];
	printf("Enter elements of heap:");
	for(int i=0;i<size;i++)
		scanf("%d",&data[i]);
	Heap H=CreateHeap(data,size);
	printf("Create Heap Success!!\n");
	while(1)
	{
		char s[12];
		scanf("%s",s);
		if(strcmp(s,"find")==0)
		{
			ElementType x;
			scanf("%d",&x);
			int pos=Find(H,x);
			if(pos!=ER)
				printf("%d\n",pos);
			else
				printf("%d is not in heap.\n",x);
		}
		else if(strcmp(s,"getmin")==0)
		{
			ElementType x=getMin(H);
			if(x!=ER)
				printf("%d\n",x);
		}
		else if(strcmp(s,"insert")==0)
		{
			ElementType x;
			scanf("%d",&x);
			insert(H,x);
		}
		else if(strcmp(s,"delete")==0)
		{
			ElementType x;
			scanf("%d",&x);
			delete(H,x);
		}
		else if(strcmp(s,"show")==0)
		{
			show(H);
		}
		else if(strcmp(s,"quit")==0)
		{
			printf("Over!\n");
			break;
		}
		else
		{
			printf("ERROR: Unknown the command , please try again.\n");
		}
	}
	Free(H);
}
int main(void)
{
	test();
	return 0;
}
