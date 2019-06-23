#include "stdafx.h"
#include<iostream>
#include<map>
#include<conio.h>
using namespace std;
struct node{
	int data;
	struct node *next, *random;
};

struct node* create_node(char data){
	struct node *new_node = (struct node*)malloc(sizeof(struct node));
	new_node->data = data;
	new_node->next = NULL;
	new_node->random = NULL;
	return new_node;
}
struct node* clone_hash_impl1(struct node* head){
	struct node* temp1 = head, *temp2 = create_node('0');
	struct node *result_head = temp2;
	map<struct node*, struct node*> corresponding;
	while (temp1 != NULL){
		temp2->next = create_node(temp1->data);
		corresponding.insert(make_pair(temp1, temp2->next));
		temp1 = temp1->next;
		temp2 = temp2->next;
	}
	temp2 = result_head->next;
	temp1 = head;
	while (temp1 != NULL){
		temp2->random = corresponding.find(temp1->random)->second;
		temp1 = temp1->next;
		temp2 = temp2->next;
	}
	return result_head->next;

}

int main(){
	struct node *node1 = create_node(1);
	struct node *node2 = create_node(2);
	struct node *node3 = create_node(3);
	struct node *node4 = create_node(4);
	struct node *node5 = create_node(5);
	struct node *node6 = create_node(6);
	node1->next = node2;
	node1->random = node3;
	node2->next = node3;
	node2->random = node5;
	node3->next = node4;
	node3->random = node1;
	node4->next = node5;
	node4->random = node6;
	node5->next = node6;
	node5->random = node2;
	node6->next = NULL;
	node6->random = node4;
	struct node* result_head = clone_hash_impl1(node1);
	while (result_head != NULL){
		cout <<"Data : "<< result_head->data << " ";
		if (result_head->random == NULL)
			cout << -1 << endl;
		else
			cout <<"Random :"<< result_head->random->data << endl;
		result_head = result_head->next;
	}
	_getch();
}