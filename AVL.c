//AVL_Tree.c
//2021年 05月 31日 星期一 13:54:22 CST
//author: 1036-ce
//version: 1.1
//operator: insert height InOrderTraver PreOrderTraver PostOrderTraver





#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ElementType;

typedef struct TNode
{
	ElementType data;
	struct TNode *left;
	struct TNode *right;
	int bf;
	int height;
}TNode;
typedef struct TNode* Tree;

typedef struct QNode
{
	TNode* data[3];
	TNode* PreNode;
	int size;
}QNode;
typedef QNode* Queue;

Queue CreateQueue(void)
{
	Queue Q=(Queue)malloc(sizeof(QNode));
	Q->size=0;
	Q->PreNode=NULL;
	return Q;
}

void EnQueue(Queue Q , TNode* N)
{
	if(Q->size==3)
	{
		Q->data[0]=Q->data[1];
		Q->data[1]=Q->data[2];
		Q->data[2]=N;
	}
	else
	{
		Q->data[Q->size++]=N;
	}
}
Tree CreateTree(ElementType x)
{
	Tree T=(Tree)malloc(sizeof(TNode));
	T->left=NULL;
	T->right=NULL;
	T->bf=0;
	T->height=1;
	T->data=x;
	return T;
}
TNode *CreateTNode(ElementType x)
{
	TNode *N=(TNode*)malloc(sizeof(TNode));
	N->left=NULL;
	N->right=NULL;
	N->height=1;
	N->bf=0;
	N->data=x;
	return N;
}
int max(int a,int b)
{
	return a>b?a:b;
}
void update(TNode *T)
{
	int h1,h2;
	if(T->left)
		h1=T->left->height;
	else
		h1=0;
	if(T->right)
		h2=T->right->height;
	else
		h2=0;
	T->height=max(h1,h2)+1;
	T->bf=h1-h2;
}
void LL_rot(Tree *T,Queue Q)
{
	TNode* N2=Q->data[1];
	TNode* N1=Q->data[2];
	
	N1->left=N2->right;
	N2->right=N1;
	if(*T==N1)
		*T=N2;
	else
	{
		TNode* N=Q->PreNode;
		N->left=N2;
		update(N);
	}
	update(N2);
	update(N1);
}
void RR_rot(Tree *T,Queue Q)
{
	TNode* N2=Q->data[1];
	TNode* N1=Q->data[2];
	
	N1->right=N2->left;
	N2->left=N1;

	if(*T==N1)
		*T=N2;
	else
	{
		TNode* N=Q->PreNode;
		N->right=N2;
		update(N);
	}
	update(N2);
	update(N1);
}

void LR_rot(Tree *T,Queue Q)
{
	TNode *N3=Q->data[0];
	TNode *N2=Q->data[1];
	TNode *N1=Q->data[2];

	N2->right=N3->left;
	N1->left=N3->right;
	N3->left=N2;
	N3->right=N1;

	if(*T==N1)
		*T=N3;
	else
	{
		TNode *N=Q->PreNode;
		N->left=N3;
		update(N);
	}
	update(N3);
	update(N2);
	update(N1);
}
void RL_rot(Tree *T,Queue Q)
{
	TNode *N3=Q->data[0];
	TNode *N2=Q->data[1];
	TNode *N1=Q->data[2];
	
	N1->right=N3->left;
	N2->left=N3->right;
	N3->left=N1;
	N3->right=N2;
	if(*T==N1)
		*T=N3;
	else
	{
		TNode* N=Q->PreNode;
		N->right=N3;
		update(N);
	}
	update(N3);
	update(N2);
	update(N1);
}
void rot(Tree *T,Queue Q)
{
	TNode *N3=Q->data[0];
	TNode *N2=Q->data[1];
	TNode *N1=Q->data[2];
	if(N1->left==N2 && N2->left==N3)
		LL_rot(T,Q);
	else if(N1->right==N2 && N2->right==N3)
		RR_rot(T,Q);
	else if(N1->left==N2 && N2->right==N3)
		LR_rot(T,Q);
	else if(N1->right==N2 && N2->left==N3)
		RL_rot(T,Q);
}
int flag=0;
void insert_opter(Queue Q,Tree T,ElementType x)
{
	if(x>T->data)
	{
		if(T->right)
		{
			insert_opter(Q,T->right,x);
			update(T);
			if(flag==1)
			{
				Q->PreNode=T;
				flag=2;
			}
			if(flag==0)
			{
				EnQueue(Q,T);
				if(T->bf==2 || T->bf==-2)
					flag=1;
			}
		
		}
		else
		{
			TNode *N=CreateTNode(x);
			T->right=N;
			update(T);
			EnQueue(Q,N);
			EnQueue(Q,T);
		}
	}
	else
	{
		if(T->left)
		{
			insert_opter(Q,T->left,x);
			update(T);	
			if(flag==1)
			{
				Q->PreNode=T;
				flag=2;
			}
			if(flag==0)
			{
				EnQueue(Q,T);
				if(T->bf==2 || T->bf==-2)
					flag=1;
			}	
		}
		else
		{
			TNode *N=CreateTNode(x);
			T->left=N;
			update(T);
			EnQueue(Q,N);
			EnQueue(Q,T);
		}
	}
}
Tree insert(Queue Q,Tree T,ElementType x)
{
	Q->size=0;
	insert_opter(Q,T,x);
	TNode *N=Q->data[2];
	if(Q->size==3  && (N->bf==2 || N->bf==-2))
		rot(&T,Q);
	return T;
}
void InOrderTraver(Tree T)
{
	if(T)
	{
		InOrderTraver(T->left);
		printf("%d ",T->data);
		InOrderTraver(T->right);
	}
}

void PreOrderTraver(Tree T)
{
	if(T)
	{
		printf("%d ",T->data);
		PreOrderTraver(T->left);
		PreOrderTraver(T->right);
	}
}

void PostOrderTraver(Tree T)
{
	if(T)
	{
		PostOrderTraver(T->left);
		PostOrderTraver(T->right);
		printf("%d ",T->data);
	}
}
int height(Tree T)
{
	if(!T)
		return 0;
	return max(height(T->left),height(T->right))+1;
}
void help(void)
{
	printf("\n");
	printf("command \"insert\": insert 'x' to the tree.\n");
	printf("command \"in\" : show the InOrderTraver of tree.\n");
	printf("command \"pre\": show the PreOrderTraver of tree.\n");
	printf("command \"post\": show the postOrderTraver of tree.\n");
	printf("command \"quit\": stop the process.\n");
	printf("-------------------------------------------------------\n");
}
void test(void)
{
	Queue Q=CreateQueue();
	printf("Enter the root of tree:");
	ElementType x;
	scanf("%d",&x);
	Tree T=CreateTree(x);
	printf("Success!\n");
	while(1)
	{
		char s[12];
		scanf("%s",s);
		if(strcmp(s,"insert")==0)
		{
			flag=0;
			ElementType x;
			scanf("%d",&x);
			T=insert(Q,T,x);
		}
		else if(strcmp(s,"in")==0)
		{
			InOrderTraver(T);
			printf("\n");
		}
		else if(strcmp(s,"pre")==0)
		{
			PreOrderTraver(T);
			printf("\n");
		}
		else if(strcmp(s,"post")==0)
		{
			PostOrderTraver(T);
			printf("\n");
		}
		else if(strcmp(s,"quit")==0)
		{
			printf("Over!\n");
			break;
		}
		else if(strcmp(s,"help")==0)
		{
			help();
		}
		else if(strcmp(s,"height")==0)
		{
			printf("%d\n",height(T));
		}
		else
		{
			printf("ERROR: Unknown the command,try again.\n");
		}
	}
}
int main(void)
{
	test();
	return 0;
}
