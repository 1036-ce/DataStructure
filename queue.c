#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR 0x3f3f3f3f

typedef int ElementType;

typedef struct QNode
{
	ElementType *data;
	int front;
	int tail;
	int size;
}QNode;

typedef QNode* Queue;

Queue CreateQueue(int size)
{
	size++;
	Queue Q=(Queue)malloc(sizeof(Queue));
	Q->data=(ElementType*)malloc(sizeof(ElementType)*size);
	Q->front=0;
	Q->tail=0;
	Q->size=size;
	return Q;
}

int empty(Queue Q)
{
	return Q->front==Q->tail;
}
int full(Queue Q)
{
	return ((Q->tail+1) % Q->size)==Q->front;	
}
void EnQueue(Queue Q,ElementType x)
{
	if(!full(Q))
	{
		Q->tail=++Q->tail % Q->size;
		Q->data[Q->tail]=x;
		
	}
	else
		printf("ERROR : The Queue is full.\n");
}
int DeQueue(Queue Q)
{
	if(!empty(Q))
	{
		Q->front=++Q->front % Q->size;
		return Q->data[Q->front];
	}
	else
	{
		printf("ERROR : The Queue is empty\n");
		return ERROR;
	}
}

void show(Queue Q)
{
	if(!empty(Q))
	{
		printf("The Queue: ");
		int tem=Q->front;
		while(tem!=Q->tail)
		{
			tem++;
			tem= tem % Q->size;
			printf("%d ",Q->data[tem]);
		}
		printf("\n");
	}
}
void help(void)
{
	printf("commnd \"eq\": add a element to the queue\n");
	printf("commnd \"dq\": delete a element from the queue\n");
	printf("commit \"quit\": exit the process\n");
	printf("----------------------------------------------\n\n");
}
void test(void)
{
	printf("Enter the size of your Queue:\n");
	int size;
	scanf("%d",&size);
	Queue Q=CreateQueue(size);
	while(1)
	{
		char s[5];
		scanf("%s",s);
		if(strcmp(s,"eq")==0)
		{
			ElementType x;
			scanf("%d",&x);
			EnQueue(Q,x);
			show(Q);
		}
		else if(strcmp(s,"dq")==0)
		{
			int a=DeQueue(Q);
			show(Q);
			if(a!=ERROR)
				printf("The element of dequeue is : %d\n",a);
		}
		else if(strcmp(s,"quit")==0)
		{
			break;
		}
		else if(strcmp(s,"help")==0)
		{
			help();
		}
		else if(strcmp(s,"show")==0)
		{
			show(Q);
		}
		else
		{
			printf("ERROR : Unknown the command,please try again\n");
		}
	}
}

int main(void)
{
	test();
	return 0;
}
