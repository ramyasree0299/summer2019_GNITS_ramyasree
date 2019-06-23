// linkadd.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
struct Node
{
	int data;
	struct Node *next;
};
typedef struct Node node;
node *reverse(node *head)
{
	node *temp = head;
	node *prev = NULL;
	node *next;
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
node *addlink(node * head1, node *head2)
{
	head1 = reverse(head1);
	head2 = reverse(head2);
	node *temp1 = head1;
	node *temp2 = head2;
	node *prev = NULL;
	node *head = NULL;
	int carry = 0;
	while (temp1 != NULL && temp2 != NULL)
	{
		node *temp = (node *)malloc(sizeof(node));
		temp->data = carry + temp1->data + temp2->data;
		temp->next = NULL;
		if (temp->data >= 10)
		{
			carry = 1;
			temp->data = temp->data % 10;
		}
		if (prev != NULL){
			prev->next = temp;
			prev = temp;
		}
		else {
			head = temp;
			prev = head;
		}
		temp1 = temp1->next;
		temp2 = temp2->next;
	}
	if (temp2 == NULL)
	{
		while (temp1 != NULL){
			node *temp = (node *)malloc(sizeof(node));
			temp->data = temp1->data + carry;
			temp->next = NULL;
			if (temp->data >= 10)
			{
				carry = 1;
				temp->data = temp->data % 10;
			}
			if (prev != NULL)
				prev->next = temp;
			prev = temp;
			temp1 = temp1->next;
		}

	}
	else if (temp1 == NULL)
	{
		while (temp2 != NULL){
			node *temp = (node *)malloc(sizeof(node));
			temp->data = temp1->data + carry;
			temp->next = NULL;
			if (temp->data >= 10)
			{
				carry = 1;
				temp->data = temp->data % 10;
			}
			if (prev != NULL)
				prev->next = temp;
			prev = temp;
			temp2 = temp2->next;
		}
	}

	head1 = reverse(head1);
	head2 = reverse(head2);
	temp1 = head1;
	temp2 = head2;
	while (temp1 != NULL)
	{
		printf("%d ", temp1->data);
		temp1 = temp1->next;
	}
	printf("+");
	while (temp2 != NULL)
	{
		printf("%d ", temp2->data);
		temp2 = temp2->next;
	}
	printf("=");
	return reverse(head);
}
int main()
{
	node *num11 = (node*)malloc(sizeof(node));
	node *num12 = (node*)malloc(sizeof(node));
	node *num13 = (node*)malloc(sizeof(node));
	node *num21 = (node*)malloc(sizeof(node));
	node *num22 = (node*)malloc(sizeof(node));
	num13->data = 9;
	num13->next = NULL;
	num12->data = 8;
	num12->next = num13;
	num11->data = 7;
	num11->next = num12;
	num22->data = 2;
	num22->next = NULL;
	num21->data = 1;
	num21->next = num22;
	node *head = addlink(num11, num21);
	node *temp = head;

	while (temp != NULL)
	{
		printf("%d ", temp->data);
		temp = temp->next;
	}
	_getch();
}
