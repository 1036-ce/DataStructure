//author :1036-ce
//Tue 25 May 2021 10:45:10 AM CST
//version :1.0
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
		Q->data[++Q->tail % Q->size]=x;
	else
		printf("ERROR : The Queue is full.\n");
}
int DeQueue(Queue Q)
{
	if(!empty(Q))
		return Q->data[++Q->front % Q->size];
	else
	{
		printf("ERROR : The Queue is empty\n");
		return ERROR;
	}
}

