// tokenization.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX_MEMORY_SIZE 100
enum commands{ MOV1 = 1, MOV2, ADD, SUB, MUL, JMP, IF, EQ, LT, GT, LTEQ, GTEQ, PRINT, READ };
struct symbol_table
{
	char name;
	int size;
	int address;
	struct symbol_table* next;
};
struct Memory
{
	int address[MAX_MEMORY_SIZE];
	int next_index;
}memory;
void print(char arguments[50], struct symbol_table *table_head, char *filename)
{
	struct symbol_table *temp = table_head;
	char name = arguments[0];
	if (temp == NULL)
	{
		printf("Symbol table is empty\n");
		return;
	}
	else
	{
		while (temp != NULL && temp->name != name)
			temp = temp->next;
		//write code to access here
	}
	FILE *fp = fopen(filename, "a");
	fprintf(fp, "%d 0%d\n", PRINT, name - 'A' + 1);
	fclose(fp);
}
struct symbol_table* createNode(char name, int address, int size)
{
	struct symbol_table * temp = (struct symbol_table *)malloc(sizeof(struct symbol_table));
	temp->name = name;
	temp->address = address;
	temp->size = size;
	temp->next = NULL;
	return temp;
}
void read(char arguments[30], struct symbol_table *table_head, char *filename)
{
	FILE *fp = fopen(filename, "a");
	fprintf(fp, "%d 0%d\n", READ, arguments[0] - 'A' + 1);
	fclose(fp);
}
void add(char arguments[30], struct symbol_table *table_head, char *filename)
{
	int i = 0;
	char **registers = (char **)calloc(4, sizeof(char *));
	for (i = 0; i<3; i++)
		registers[i] = (char *)calloc(10, sizeof(char));
	int j = 0;
	int k = 0;
	i = 0;
	while (i<strlen(arguments))
	{
		k = 0;
		while (arguments[i] != ',' && arguments[i] != '\0')
		{
			registers[j][k] = arguments[i];
			i++;
			k++;
		}
		registers[j][k] = '\0';
		i++;
		j++;
	}

	FILE *fp = fopen(filename, "a");
	fprintf(fp, "0%d 0%d 0%d 0%d\n", ADD, registers[0][0] - 'A' + 1, registers[1][0] - 'A' + 1, registers[2][0] - 'A' + 1);
	fclose(fp);
}
void sub(char arguments[30], struct symbol_table *table_head, char *filename)
{
	int i = 0;
	char **registers = (char **)calloc(4, sizeof(char *));
	for (i = 0; i<3; i++)
		registers[i] = (char *)calloc(10, sizeof(char));
	int j = 0;
	int k = 0;
	i = 0;
	while (i<strlen(arguments))
	{
		k = 0;
		while (arguments[i] != ',' && arguments[i] != '\0')
		{
			registers[j][k] = arguments[i];
			i++;
			k++;
		}
		registers[j][k] = '\0';
		i++;
		j++;
	}
	FILE *fp = fopen(filename, "a");
	fprintf(fp, "0%d 0%d 0%d 0%d\n", SUB, registers[0][0] - 'A' + 1, registers[1][0] - 'A' + 1, registers[2][0] - 'A' + 1);
	fclose(fp);
}

struct symbol_table* data(char arguments[50], struct symbol_table *table_head)
{
	struct symbol_table *temp;
	int size;
	int no_of_memory_required = 0;
	char name = arguments[0];
	int address;
	if (strlen(arguments) == 1)
	{
		int i = 0;
		size = 4;
		no_of_memory_required = size / 4;
		for (int i = memory.next_index; i<MAX_MEMORY_SIZE; i++)
			if (memory.address[i] == -1)
				break;
		memory.address[i] = 1;
		address = i;
		memory.next_index = i + 1;
	}
	else if (strlen(arguments) > 1)
	{
		int i = 2;
		int a = 0;
		while (i < strlen(arguments) && isdigit(arguments[i]))
		{
			a += (a * 10) + (arguments[i] - '0');
			i++;
		}
		size = 4 * a;
		no_of_memory_required = a;
		int j = 0;
		int count = 0;
		for (j = 0; j < MAX_MEMORY_SIZE; j++)
		{
			if (memory.address[j] != -1)//assuming the blocks of memory is contigous
				count++;
			if (count == no_of_memory_required)
				break;
		}
		if (j != MAX_MEMORY_SIZE)
		{
			for (j = 0; j < MAX_MEMORY_SIZE; j++)
			{
				if (memory.address[j] == -1)
					if (j == 0)
						address = j;
				memory.address[j] = 1;
			}
			memory.next_index = j + 1;
		}
		else
		{
			printf("Failed reading address\n");
			return NULL;
		}
	}
	temp = createNode(name, address, size);
	if (table_head == NULL)
		table_head = temp;
	else
	{
		struct symbol_table *t = table_head;
		while (t->next != NULL)
			t = t->next;
		t->next = temp;

	}
	return table_head;
}
void mov(char arguments[50], struct symbol_table *table_head, char *filename)
{
	int i = 0;
	char **mem_reg = (char **)calloc(4, sizeof(char *));
	for (i = 0; i<3; i++)
		mem_reg[i] = (char *)calloc(10, sizeof(char));
	int j = 0;
	int k = 0;
	i = 0;
	while (i<strlen(arguments))
	{
		k = 0;
		while (arguments[i] != ',' && arguments[i] != '\0')
		{
			mem_reg[j][k] = arguments[i];
			i++;
			k++;
		}
		mem_reg[j][k] = '\0';
		i++;
		j++;
	}
	FILE *fp = fopen(filename, "a");
	for (i = 0; i<j; i++)
		for (k = 0; k<strlen(mem_reg[i]); k++)
			if (mem_reg[i][k] == 'X')
				break;
	if (k == 2)
		fprintf(fp, "0%d 0%d 0%d\n", 1, mem_reg[0][0] - 'A' + 1, mem_reg[1][0] - 'A');
	else if (k == 1)
		fprintf(fp, "0%d 0%d 0%d\n", 2, mem_reg[0][0] - 'A', mem_reg[1][0] - 'A' + 1);
	fclose(fp);
}
struct symbol_table *constant(char arguments[50], struct symbol_table *table_head)
{
	struct symbol_table *temp;
	int size;
	int no_of_memory_required = 0;
	char name = arguments[0];
	int address;
	if (strlen(arguments) == 1)
	{
		int i = 0;
		size = 0;
		for (int i = memory.next_index; i<MAX_MEMORY_SIZE; i++)
			if (memory.address[i] == -1)
				break;
		memory.address[i] = 1;
		address = i;
		memory.next_index = i + 1;
	}
	temp = createNode(name, address, size);
	if (table_head == NULL)
		table_head = temp;
	else
	{
		struct symbol_table *t = table_head;
		while (t->next != NULL)
			t = t->next;
		t->next = temp;

	}
	return table_head;
}
struct symbol_table* parse(char cmd[35],struct symbol_table *table_head)
{
	int i = 0;
	int j = 0;
	int k = 0;
	for (i = 0; i < MAX_MEMORY_SIZE; i++)
		memory.address[i] = -1;
	memory.next_index = 0;
	char command[10];
	char arguments[100]; 
	sscanf(cmd, "%s %s", command, arguments);
	char *filename = "output.txt";
	if (_stricmp(command, "data") == 0)
		table_head = data(arguments, table_head);
	if (_stricmp(command, "print") == 0)
		print(arguments, table_head,  filename);
	if (_stricmp(command, "mov") == 0)
		mov(arguments, table_head,  filename);
	if (_stricmp(command, "read") == 0)
		read(arguments, table_head,  filename);
	if (_stricmp(command, "add") == 0)
		add(arguments, table_head, filename);
	if (_stricmp(command, "sub") == 0)
		sub(arguments, table_head, filename);
	if (_stricmp(command, "const") == 0)
		table_head = constant(arguments, table_head);
	return table_head;
}
int main()
{
	struct symbol_table *table_head = NULL;
	FILE *fp = fopen("input.txt", "r");
	if (fp == NULL)
	{
		printf("Error opening the file\n");
		return 0;
	}
	char num[250];
	FILE *fp1 = fopen("output.txt", "w");
	fprintf(fp1, "");
	fclose(fp1);
	while (!feof(fp))
	{
		fgets(num, 100, fp);
		table_head=parse(num,table_head);
		printf("%s ", num);
	}
	fclose(fp1);
	FILE *fp2 = fopen("output.txt", "r");
	if (fp2 == NULL)
	{
		printf("Error opening the file\n");
		return 0;
	}
	printf("\nData succesfully written \nThe output file\n");
	while (!feof(fp2))
	{
		fgets(num, 100, fp2);
		printf("%s ", num);
	}
	fclose(fp2);
	_getch();
	return 0;
}

