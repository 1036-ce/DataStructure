// stack.c
// Fri 28 May 2021 12:48:29 PM CST
// author: 1036-ce
// version: 1.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void test(void)
{
	int size;
	printf("Enter the size of Stack :");
	scanf("%d",&size);
	printf("\n");
	Stack S=CreateStack(size);
	while(1)
	{
		int a;
		ElementType x;
		char s[5];
		scanf("%s",s);
		if(strcmp(s,"q")==0)
		{
			printf("Over\n");
			break;
		}
		else
			a=strcmp(s,"pop")==0;
		switch(a)
		{
			case 1:
				pop(S);
				show(S);
				break;
			case 0:
				scanf("%d",&x);
				push(S,x);
				show(S);
				break;
			default:
				break;
		}
	}
}
int main(void)
{
	test();
	return 0;
}
