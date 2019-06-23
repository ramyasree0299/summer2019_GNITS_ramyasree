#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

struct node
{
	int data;
	struct node *next;
};
int n, n1;
typedef struct node Node;
Node *reverse(Node *head)
{
	Node *temp = head;
	Node *prev = NULL;
	Node *next;
	while (temp != NULL)
	{
		next = temp->next;
		temp->next = prev;
		prev = temp;
		temp = next;
	}
	head = prev;
	return head;
}
Node *foo(Node *head, int k)
{
	Node *t1;
	Node *thead = NULL;
	Node *nhead;
	Node *tlist = head;
	Node *temp;
	Node *remain = NULL;
	int i = 0;
	if (n%k!=0)
	n1 = (n1%k)*k;
	printf("n1 : %d ", n1);
	temp = head;
	/*while (i<n1)
	{
	temp = temp->next;
	i++;
	}
	remain = temp;*/
	while (n1>0)
	{
		i = 0;
		temp = tlist;
		while (i<k - 1 && temp != NULL)
		{
			temp = temp->next;
			i++;
		}
		if (temp != NULL)
		{
			nhead = temp->next;
			temp->next = NULL;
			tlist = reverse(tlist);
			if (thead == NULL)
				thead = tlist;
			else
			{
				t1 = thead;
				while (t1->next != NULL)
					t1 = t1->next;
				t1->next = tlist;
			}
			tlist = nhead;
		}
		n1 /= k;
	}
	i = 0;
	if (n%k != 0)
	{
		temp = thead;
		while (temp->next != NULL)
			temp = temp->next;
	}
	temp->next = remain;
	head = thead;

	return head;
}

int main()
{
	n = 6;
	n1 = 6;
	int k = 3;
	int i;
	struct node *head = (struct node*)malloc(sizeof(struct node));
	struct node *temp1 = (struct node*)malloc(sizeof(struct node));
	struct node *temp2 = (struct node*)malloc(sizeof(struct node));
	struct node *temp3 = (struct node*)malloc(sizeof(struct node));
	struct node *temp4 = (struct node*)malloc(sizeof(struct node));
	struct node *temp5 = (struct node*)malloc(sizeof(struct node));
	struct node *temp6 = (struct node*)malloc(sizeof(struct node));
	struct node *temp7 = (struct node*)malloc(sizeof(struct node));
	temp7->data = 8;
	temp7->next = NULL;
	temp6->data = 7;
	temp6->next = temp7;
	temp5->data = 6;
	temp5->next = NULL;
	temp4->data = 5;
	temp4->next = temp5;
	temp3->data = 4;
	temp3->next = temp4;
	temp2->data = 3;
	temp2->next = temp3;
	temp1->data = 2;
	temp1->next = temp2;
	head->data = 1;
	head->next = temp1;
	Node *temp;
	head = foo(head, k);
	temp = head;
	printf("%d-->", head);
	printf("The swapped %d nodes\n", k);
	while (temp != NULL){
		printf("%d\t", temp->data);
		temp = temp->next;
	}
	_getch();
	return 0;
}