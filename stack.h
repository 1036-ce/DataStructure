// stack.h
// Fri 28 May 2021 12:47:37 PM CST
// author : 1036-ce
// version: 1.0

typedef int ElementType;
typedef struct SNode
{
	ElementType *data;
	int top;
}SNode;
typedef SNode* Stack;

Stack CreateStack(int size)
{
	Stack S=(Stack)malloc(sizeof(ElementType)*size+sizeof(int));
	S->top=-1;
	return S;
}

int empty(Stack S)
{
	return S->top==-1;
}

int pop(Stack S)
{
	if(empty(S))
	{
		printf("ERROR: The Stack is empty\n");
		return -1;
	}
	else
		return S->data[S->top--];
}
void push(Stack S,ElementType x)
{
	S->data[++S->top]=x;
}
void show(Stack S)
{
	int tem=S->top;
	printf("The Stack : ");
	while(tem!=-1)
	{
		printf("%d ",S->data[tem--]);
	}
	printf("\n");
}
