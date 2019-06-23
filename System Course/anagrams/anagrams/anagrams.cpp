// anagrams.cpp : Defines the entry point for the console application.
//

// anagrams.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include"stdafx.h"
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct ll_node
{
	char word[50];
	struct ll_node *next;
}ll_node;

typedef struct node
{
	char word[50];
	struct node *left, *right;
	struct ll_node *head;
} Node;
char* sort_word(char arr[50])
{
	char temp;
	int n = strlen(arr);
	for (int i = 0; i<n; i++)
	{
		for (int j = 0; j<n - 1 - i; j++)
		{
			if (arr[j]>arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	return arr;
}
Node *newNode(char word[50])
{
	Node *temp = (Node *)malloc(sizeof(Node));
	strcpy(temp->word, word);
	temp->left = temp->right = NULL;
	temp->head = NULL;
	return temp;
}
Node* insert(Node* node, char word[50])
{
	if (node == NULL) return newNode(word);
	if (_stricmp(word, node->word)<0)
		node->left = insert(node->left, word);
	else if (_stricmp(word, node->word)>0)
		node->right = insert(node->right, word);
	return node;
}
Node* search(Node* root, char word[50])
{
	if (root == NULL || _stricmp(root->word, word) == 0)
		return root;
	if (_stricmp(root->word, word)<0)
		return search(root->right, word);
	return search(root->left, word);
}
ll_node *create_linked_list_node(char word[50])
{
	ll_node* new_node = (ll_node*)malloc(sizeof(ll_node));
	strcpy(new_node->word, word);
	new_node->next = NULL;
	return new_node;
}
ll_node *insert_into_list(Node *parent, ll_node* node, char word[50])
{
	ll_node* temp = parent->head;
	if (temp == NULL)
	{
		temp = create_linked_list_node(word);
		parent->head = temp;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = create_linked_list_node(word);
	}
	return parent->head;
}
void print_linked_list(ll_node* head)
{
	ll_node* temp = head;
	if (head == NULL)
	{
		printf("\nNO WORDS IN DICT");
		return;
	}
	printf("The anagrams are :");
	while (temp != NULL)
	{
		printf("%s \n", temp->word);
		temp = temp->next;
	}

}

int main()
{
	char input_word[50];
	printf("enter the input word\n");
	scanf("%s", input_word);
	FILE *fp;
	fp = fopen("words1.txt", "r");
	if (fp == NULL)
	{
		printf("file doesnt exists\n");
		return 0;
	}
	char *word = (char *)calloc(20, sizeof(char));
	char *copy_of_word = (char *)calloc(20, sizeof(char));
	Node* root = NULL;
	int flag = 0;
	while (!feof(fp))
	{
		Node *temp = NULL;
		fscanf(fp, "%s\n", word);
		strcpy(copy_of_word, word);
		if (root != NULL)
			temp = search(root, sort_word(copy_of_word));
		if (temp == NULL)
		{
			if (root == NULL)
			{
				temp = newNode(sort_word(copy_of_word));
				root = temp;
			}
			else
				temp = insert(root, sort_word(copy_of_word));
		}
	}//creates a bst
	rewind(fp);
	while (!feof(fp))
	{
		Node *temp = NULL;
		fscanf(fp, "%s\n", word);
		strcpy(copy_of_word, word);
		if (root != NULL)
			temp = search(root, sort_word(copy_of_word));
		if (temp != NULL)
		{
			ll_node* linked_list_node = create_linked_list_node(word);
			insert_into_list(temp, linked_list_node, word);
		}

	}
	Node* key;
	if (root != NULL)
		key = search(root, sort_word(input_word));
	if (key != NULL)
	{
		print_linked_list(key->head);
	}
	else printf("No key found\n");
	_getch();
	return 0;
}

