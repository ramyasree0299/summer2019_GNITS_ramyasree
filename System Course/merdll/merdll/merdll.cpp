#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
typedef struct node
{
	int data;
	node* prev;
	node* next;
}node;

node* create_node(int data)
{
	node* new_node = (node*)malloc(sizeof(node) * 1);
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->data = data;
	return new_node;
}

void insert_at_end(node** head, node* new_node)
{
	node* temp = *head;
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
	new_node->prev = temp;
}
node* create_double_linked_list(int* array, int len)
{
	node* head = NULL;
	node* new_node = NULL;
	int index;
	for (index = 0; index < len; index++)
	{
		new_node = create_node(array[index]);
		insert_at_end(&head, new_node);
	}
	return head;
}
void print_double_linked_list(node* head)
{
	node* ptr = head;
	while (ptr)
	{
		printf("%d ", ptr->data);
		ptr = ptr->next;
	}
}
node* split_list_mid_node(node* head)
{
	node* slow = head;
	node* fast = head;
	while (fast->next && fast->next->next)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	node* mid_node = slow->next;
	slow->next = NULL;
	return mid_node;
}
node* merge_two_sorted_list(node* list_1, node* list_2)
{
	if (!list_1)
	{
		return list_2;
	}
	if (!list_2)
	{
		return list_1;
	}
	if (list_1->data < list_2->data)
	{
		list_1->next = merge_two_sorted_list(list_1->next, list_2);
		list_1->next->prev = list_1;
		list_1->prev = NULL;
		return list_1;
	}
	else
	{
		list_2->next = merge_two_sorted_list(list_1, list_2->next);
		list_2->next->prev = list_2;
		list_2->prev = NULL;
		return list_2;
	}
}
node* mergeSort(node* head)
{
	if (!head || !head->next)
		return head;
	node *second = split_list_mid_node(head);
	head = mergeSort(head);
	second = mergeSort(second);
	return merge_two_sorted_list(head, second);
}

int main()
{
	int arr[5] = { 43,5,67,89,0};
	node* head = create_double_linked_list(arr, 5);
	head = mergeSort(head);
	printf("The sorted list\n");
	print_double_linked_list(head);
	printf("\n");
	_getch();
}