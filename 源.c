#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define true 2
#define false -2
#define maxsize 100
typedef int elemstyle;
typedef struct node
{
	elemstyle data;
	struct node* next;
}Node;
typedef struct hnode
{
	Node* pn;
	int n;
}HNode;
HNode* Init_HashTable(int n)
{
	Node* pn = (HNode*)malloc(sizeof(HNode) * n);
	for (int i = 0; i < n; i++)
	{
		pn[i].data = 0;
		pn[i].next = NULL;
	}
	HNode* pt = (HNode*)malloc(sizeof(HNode));
	pt->n = n;
	pt->pn = pn;
	return pt;
}
int freeHashTable(HNode* pt)
{
	if (pt == NULL)
	{
		return true;
	}
	else
	{
		for (int i = 0; i < pt->n; i++)
		{
			Node* curr = pt->pn[i].next;
			while (curr)
			{
				Node* next = curr->next;
				free(curr);
				curr = next;
			}
		}
		free(pt->pn);
		free(pt);
		return true;
	}
}
int insertHashTable(HNode* pt, elemstyle x)
{
	int d = x % pt->n;
	if (pt->pn[d].data == 0)
	{
		pt->pn[d].data = x;
		return true;
	}
	Node* prove = &(pt->pn[d]);
	Node* curr = pt->pn[d].next;
	while (curr && curr->data != x)
	{
		prove = curr;
		curr = curr->next;
	}
	if (curr)
	{
		return false;
	}
	Node* pmove = (Node*)malloc(sizeof(Node));
	pmove->data = x;
	pmove->next = NULL;
	prove->next = pmove;
	return true;
}
int findHashTable(HNode* pt, elemstyle val)
{
	int d = val % pt->n;
	if (pt->pn[d].data == 0)
	{
		return false;
	}
	if (pt->pn[d].data == val)
	{
		return true;
	}
	else
	{
		Node* prove = &(pt->pn[d]);
		Node* curr = pt->pn[d].next;
		while (curr && curr->data != val)
		{
			prove = curr;
			curr = curr->next;
		}
		if (curr)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
int deleteHashTable(HNode* pt, elemstyle val)
{

	int d = val % pt->n;
	if (pt->pn[d].data == 0)
	{
		return true;
	}
	else if (pt->pn[d].data == val)
	{
		if (pt->pn[d].next == NULL)
		{
			pt->pn[d].data = 0;
			return true;
		}
		else
		{
			Node* curr = pt->pn[d].next;
			pt->pn[d].data = curr->data;
			pt->pn[d].next = curr->next;
			free(curr);
			return true;
		}
	}
	else
	{
		Node* prove = &(pt->pn[d]);
		Node* curr = pt->pn[d].next;
		while (curr && curr->data != val)
		{
			prove = curr;
			curr = curr->next;
		}
		if (curr == NULL)
		{
			return false;
		}
		else
		{
			prove->next = curr->next;
			free(curr);
			return true;
		}
	}
}
void printHashTable(HNode* pt)
{
	if (pt == NULL)
	{
		printf("打印失败;");
	}
	else
	{
		for (int i = 0; i < pt->n; i++)
		{
			printf("%5d->:", i);
			if (pt->pn[i].data != 0)
			{
				printf("%5d", pt->pn[i].data);
			}
			Node* curr = pt->pn[i].next;
			while (curr)
			{
				printf("->%5d", curr->data);
				curr = curr->next;
			}
			putchar('\n');
		}
	}
}
int main(void)
{
	int n;
	int data;
	printf("输入散表的长度：\n");
	scanf_s("%d", &n);
	HNode* pt = Init_HashTable(n);
	int val[maxsize];
	printf("输入你关键码;\n");
	for (int i = 0; i < n; i++)
	{
		scanf_s("%d", &val[i]);
		insertHashTable(pt, val[i]);
	}
	scanf_s("%d", &data);
	int k = findHashTable(pt, data);
	if (k > 0)
	{
		printf("查找成功;\n");
	}
	else
	{
		printf("查找失败;\n");
	}
	printHashTable(pt);
	freeHashTable(pt);
}
