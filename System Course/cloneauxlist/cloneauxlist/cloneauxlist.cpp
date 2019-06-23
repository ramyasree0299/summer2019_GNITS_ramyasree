// cloneauxlist.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
struct node
{
	int data;
	struct node *next;
	struct node *random;
};
typedef struct node Node;
Node* clone(Node *head)
{
	printf("The Nodes in the order\n");
	Node *temp = head;
	while (temp != NULL)
	{
		Node *t1 = (Node *)malloc(sizeof(Node));
		t1->data = temp->data;
		t1->next = temp->next;
		temp->next = t1;
		temp = temp->next->next;
		printf("%d->", t1->data);
	}
	temp = head;
	while (temp != NULL)
	{
		if (temp->random != NULL)
			temp->next->random = temp->random;
		else {
			temp->random = NULL;
			temp->next->random = NULL;
		}
		temp = temp->next->next;
	}
	head = head->next;
	temp = head;
	while (temp != NULL && temp->next != NULL)
	{
		temp->next = temp->next->next;
		temp = temp->next;
	}
	if (head == NULL)printf("NULL");
	return head;
}
int main()
{
	int k = 3;
	int i;
	struct node *head = (struct node*)malloc(sizeof(struct node));
	struct node *temp1 = (struct node*)malloc(sizeof(struct node));
	struct node *temp2 = (struct node*)malloc(sizeof(struct node));
	struct node *temp3 = (struct node*)malloc(sizeof(struct node));
	struct node *temp4 = (struct node*)malloc(sizeof(struct node));
	struct node *temp5 = (struct node*)malloc(sizeof(struct node));
	temp5->data = 6;
	temp5->next = NULL;
	temp5->random = NULL;
	temp4->data = 5;
	temp4->next = temp5;
	temp4->random = NULL;
	temp3->data = 4;
	temp3->next = temp4;
	temp3->random = NULL;
	temp2->data = 3;
	temp2->next = temp3;
	temp2->random = NULL;
	temp1->data = 2;
	temp1->next = temp2;
	temp1->random = NULL;
	head->data = 1;
	head->next = temp1;
	head->random = NULL;
	head->random = temp2;
	temp2->random = temp5;
	temp5->random = temp4;
	temp3->random = temp5;
	head = clone(head);
	Node *temp = head;
	printf("\n");
	printf("Clonned Nodes with corresponding random data in the linked list\n");
	while (temp != NULL)
	{
		if (temp->random != NULL)
			printf("%d-->%d\n", temp->data, temp->random->data);
		temp = temp->next;
	}
	_getch();
	return 0;
}