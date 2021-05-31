//BinTree
//Tue 25 May 2021 12:20:01 PM CST
//author: 1036-ce
//version: 1.0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct TNode* Tree;
typedef int ElementType;

typedef struct TNode
{
	ElementType data;
	struct TNode* left;
	struct TNode* right;
}TNode;

Tree CreateTree(ElementType x)
{
	Tree T=(Tree)malloc(sizeof(TNode));
	T->left=NULL;
	T->right=NULL;
	T->data=x;
	return T;
}

TNode* search(Tree T,ElementType x)
{
	if(T==NULL)
		return NULL;
	if(x>T->data)
		return search(T->right,x);
	else if(x<T->data)
		return search(T->left,x);
	else
		return T;
}
void insert(Tree T,ElementType x)
{
	if(x>T->data)
	{
		if(T->right)
			insert(T->right,x);
		else
		{	
			TNode *tmp=(TNode*)malloc(sizeof(TNode));
			tmp->left=NULL;
			tmp->right=NULL;
			tmp->data=x;
			T->right=tmp;
		}
	}
	else if(x<T->data)
	{
		if(T->left)
			insert(T->left,x);
		else
		{
			TNode *tmp=(TNode*)malloc(sizeof(TNode));
			tmp->data=x;
			tmp->left=NULL;
			tmp->right=NULL;
			T->left=tmp;
		}
		
	}
	else
		printf("The node is aleady in the tree\n");
}

int max(int a,int b)
{
	return a>b?a:b;
}
int height(Tree T)
{
	if(!T)
		return 0;
	return max(height(T->left),height(T->right))+1;
}

void PreorderTraver(Tree T)
{
	if(T)
		printf("%d ",T->data);
	else
		return;
	PreorderTraver(T->left);
	PreorderTraver(T->right);
}

void InorderTraver(Tree T)
{
	if(!T)
		return;
	InorderTraver(T->left);
	printf("%d ",T->data);
	InorderTraver(T->right);
}

void PostorderTraver(Tree T)
{
	if(!T)
		return;
	PostorderTraver(T->left);
	PostorderTraver(T->right);
	printf("%d ",T->data);
}

//create a queue for LevelOrderTraver
typedef TNode* Element;

typedef struct QNode
{
	Element *data;
	int front;
	int tail;
	int size;
}QNode;

typedef QNode* Queue;

Queue CreateQueue(int size)
{
	size++;
	Queue Q=(Queue)malloc(sizeof(Queue));
	Q->data=(Element*)malloc(sizeof(Element)*size);
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
void EnQueue(Queue Q,Element x)
{
	if(!full(Q))
		Q->data[++Q->tail % Q->size]=x;
}
Element DeQueue(Queue Q)
{
	if(!empty(Q))
		return Q->data[++Q->front % Q->size];
}

void LevelorderTraver(Tree T)
{
	Queue Q=CreateQueue(100);
	EnQueue(Q,T);
	while(!empty(Q))
	{
		TNode *tmp=DeQueue(Q);
		printf("%d ",tmp->data);
		if(tmp->left)
			EnQueue(Q,tmp->left);
		if(tmp->right)
			EnQueue(Q,tmp->right);
	}
}

void help(void)
{
	printf("command \"search\": find x in tree\n");
	printf("command \"insert\": insert x to tree\n");
	printf("command \"pre\": show the preordertraver of the tree\n");
	printf("command \"in\": show the inordertraver of the tree\n");
	printf("command \"post\": show the postordertraver of the tree\n");
	printf("command \"level\": show the levelordertraver of the tree\n");
	printf("command \"height\": show the height of tree\n");
	printf("------------------------------------------------------------\n\n");
}
void test(void)
{
	ElementType x;
	printf("Enter the root node of tree: ");
	scanf("%d",&x);
	Tree T=CreateTree(x);
	while(1)
	{
		char s[12];
		scanf("%s",s);
		if(strcmp(s,"quit")==0)
			break;
		else if(strcmp(s,"help")==0)
			help();
		else if(strcmp(s,"search")==0)
		{
			ElementType tmp;
			scanf("%d",&tmp);
			TNode *t=search(T,tmp);
			if(t)
			{
				printf("Search Success!\n");
			}
			else
				printf("There is no %d in tree\n",tmp);
		}
		else if(strcmp(s,"insert")==0)
		{
			ElementType tmp;
			scanf("%d",&x);
			insert(T,x);
		}
		else if(strcmp(s,"height")==0)
		{
			printf("%d\n",height(T));
		}
		else if(strcmp(s,"pre")==0)
		{
			PreorderTraver(T);
			printf("\n");
		}

		else if(strcmp(s,"in")==0)
		{
			InorderTraver(T);
			printf("\n");
		}
		else if(strcmp(s,"post")==0)
		{
			PostorderTraver(T);
			printf("\n");
		}
		else if(strcmp(s,"level")==0)
		{
			LevelorderTraver(T);
			printf("\n");
		}
		else
			printf("ERROR: Unknown the command ,please try again\n");
	}
}
int main(void)
{
	test();
	return 0;
}
