//#include<stdlib.h>
//#include<string.h>
//#include "bst.h"
//typedef struct ll_node
//{
//	char word[50];
//	struct ll_node *next;
//}ll_node;
//
//typedef struct node
//{
//	char word[50];
//	struct node *left, *right;
//	struct ll_node *head;
//} Node;
//Node *newNode(char word[50])
//{
//	Node *temp = (Node *)malloc(sizeof(Node));
//	strcpy(temp->word, word);
//	temp->left = temp->right = NULL;
//	return temp;
//}
//Node* insert(Node* node, char word[50])
//{
//	if (node == NULL) return newNode(word);
//	if (stricmp(word, node->word)<0)
//		node->left = insert(node->left, word);
//	else if (stricmp(word, node->word)>0)
//		node->right = insert(node->right, word);
//	return node;
//}
//Node* search(Node* root, char word[50])
//{
//	if (root == NULL || stricmp(root->word,word)==0)
//		return root;
//	if (stricmp(root->word,word)<0)
//		return search(root->right, word);
//	return search(root->left, word);
//}