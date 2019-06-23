#include"stdafx.h"
#include<stdio.h>
#include<stdlib.h>
typedef struct Node
{
	int data;
	struct Node* next;
}Node;
void  printList(Node* head)
{
	while (head != NULL)
	{
		printf("%d ", head->data);
		head = head->next;
	}
}
Node* newNode(int data)
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = data;
	temp->next = NULL;
	return temp;
}
Node* detect_cycle_start(Node* head)
{
	Node* slow = head->next;
	Node *fast = head->next->next;
	int flag = 0;
	while (slow && fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 1)
	{
		slow = head;
		while (slow->next != fast->next)
		{
			slow = slow->next;
			fast = fast->next;
		}
		return fast->next;
	}
	return NULL;
}
void insert(Node** head, char data)
{
	Node* new_node = newNode(data);
	Node* temp = *head;
	if (*head == NULL)
	{
		*head = new_node;
		return;
	}
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = new_node;
}

int main()
{
int arr[] = { 1,2,3,4,5,6,7,8,9 };
Node *head = NULL;
int i;
for (i = 0; i < 9; i++)
{
insert(&head, arr[i]);
}
printList(head);
Node* temp = head;
i = 0;
while (temp->next!= NULL)
{
temp = temp->next;
i++;
}
temp->next = head->next->next->next;
Node *t = detect_cycle_start(head);
printf("\n%u loop point and its data point %d\n", t,t->data);
system("pause");
}