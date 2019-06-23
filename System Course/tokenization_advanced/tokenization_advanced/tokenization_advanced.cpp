// tokenization_advanced.cpp : Defines the entry point for the console application.
//


#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX_MEMORY_SIZE 100
#define MAX_SIZE 100
enum commands{ MOV1 = 1, MOV2, ADD, SUB, MUL, JUMP, IF, EQ, LT, GT, LTEQ, GTEQ, PRINT, READ };
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
struct Intermediate_table
{
	int ins_no;
	int op_code;
	int parameters[10];
	int param_count;
	struct Intermediate_table *next;
};
struct Label_table
{
	char label_name[10];
	int address;
	struct Label_table *next;
};
struct tables
{
	struct Intermediate_table *intermediate_table;
	struct Label_table *label_table;
	struct symbol_table *table_head;
};
struct stack_element
{
	char label_name[10];
	int address;
};
struct stack
{
	struct stack_element stk[MAX_SIZE];
	int top;
}s;

struct symbol_table* createSTNode(char name, int address, int size)
{
	struct symbol_table * temp = (struct symbol_table *)malloc(sizeof(struct symbol_table));
	temp->name = name;
	temp->address = address;
	temp->size = size;
	temp->next = NULL;
	return temp;
}
struct Intermediate_table* createITNode(int ins_no, int op_code, int parameters[10], int param_count)
{
	struct Intermediate_table * temp = (struct Intermediate_table *)malloc(sizeof(struct Intermediate_table));
	temp->ins_no = ins_no;
	temp->op_code = op_code;
	int i = 0;
	for (i = 0; i<param_count; i++)
		temp->parameters[i] = parameters[i];
	temp->param_count = param_count;
	return temp;
}

struct Label_table* createLTNode(char label_name[10], int address)
{
	struct Label_table * temp = (struct Label_table *)malloc(sizeof(struct Label_table));
	strcpy(temp->label_name, label_name);
	temp->address = address;
	return temp;
}

void push(struct stack_element num)
{
	if (s.top == (MAX_SIZE - 1))
	{
		printf("Stack is Full\n");
		return;
	}
	else
	{
		s.top = s.top + 1;
		s.stk[s.top] = num;
	}
	return;
}
struct stack_element pop()
{
	struct stack_element num;
	if (s.top == -1)
	{
		printf("Stack is Empty\n");
		return num;
	}
	else
	{
		num = s.stk[s.top];
		s.top = s.top - 1;
	}
	return num;
}

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

struct Intermediate_table * read(char arguments[30], struct Intermediate_table *intermediate_head, int ins_no, char *filename)
{
	FILE *fp = fopen(filename, "a");
	fprintf(fp, "%d 0%d\n", READ, arguments[0] - 'A' + 1);
	int parameters[10];
	parameters[0] = arguments[0] - 'A' + 1;
	struct Intermediate_table *temp = createITNode(ins_no, READ, parameters, 1);
	if (intermediate_head == NULL)
		intermediate_head = temp;
	else
	{
		struct Intermediate_table *t = intermediate_head;
		while (t->next != NULL)
			t = t->next;
		t->next = temp;
	}
	fclose(fp);
	return temp;
}

struct Intermediate_table * add(char arguments[30], struct Intermediate_table *intermediate_head, int ins_no, char *filename)
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
	int parameters[10];
	parameters[0] = registers[0][0] - 'A' + 1;
	parameters[1] = registers[1][0] - 'A' + 1;
	parameters[2] = registers[2][0] - 'A' + 1;
	struct Intermediate_table *temp = createITNode(ins_no, ADD, parameters, 3);
	if (intermediate_head == NULL)
		intermediate_head = temp;
	else
	{
		struct Intermediate_table *t = intermediate_head;
		while (t->next != NULL)
			t = t->next;
		t->next = temp;
	}
	fclose(fp);
	return temp;
	fclose(fp);
}

struct Intermediate_table * sub(char arguments[30], struct Intermediate_table *intermediate_head, int ins_no, char *filename)
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
	int parameters[10];
	parameters[0] = registers[0][0] - 'A' + 1;
	parameters[1] = registers[1][0] - 'A' + 1;
	parameters[2] = registers[2][0] - 'A' + 1;
	struct Intermediate_table *temp = createITNode(ins_no, SUB, parameters, 3);
	if (intermediate_head == NULL)
		intermediate_head = temp;
	else
	{
		struct Intermediate_table *t = intermediate_head;
		while (t->next != NULL)
			t = t->next;
		t->next = temp;
	}
	fclose(fp);
	return temp;
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
		for (i = memory.next_index; i<MAX_MEMORY_SIZE; i++)
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
	temp = createSTNode(name, address, size);
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

struct Intermediate_table * mov(char arguments[30], struct Intermediate_table *intermediate_head, int ins_no, char *filename)
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
	int parameters[10];
	struct Intermediate_table *temp;
	if (k == 1)
	{
		fprintf(fp, "0%d 0%d 0%d\n", 1, mem_reg[0][0] - 'A' + 1, mem_reg[1][0] - 'A');
		parameters[0] = mem_reg[0][0] - 'A' + 1;
		parameters[1] = mem_reg[1][0] - 'A';
		temp = createITNode(ins_no, MOV1, parameters, 2);
	}
	else if (k == 0)
	{
		fprintf(fp, "0%d 0%d 0%d\n", 2, mem_reg[0][0] - 'A', mem_reg[1][0] - 'A' + 1);
		parameters[0] = mem_reg[0][0] - 'A';
		parameters[1] = mem_reg[1][0] - 'A' + 1;
		temp = createITNode(ins_no, MOV2, parameters, 2);
	}
	if (intermediate_head == NULL)
		intermediate_head = temp;
	else
	{
		struct Intermediate_table *t = intermediate_head;
		while (t->next != NULL)
			t = t->next;
		t->next = temp;
	}
	fclose(fp);
	return temp;
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
		for (i = memory.next_index; i<MAX_MEMORY_SIZE; i++)
			if (memory.address[i] == -1)
				break;
		memory.address[i] = 1;
		address = i;
		memory.next_index = i + 1;
	}
	temp = createSTNode(name, address, size);
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

struct Label_table *label(char arguments[30], struct Label_table *label_head, int ins_no, char *filename)
{
	int a;
	for (a = 0; a < strlen(arguments); a++)
		if (arguments[a] == ':')
			break;
	char label[10];
	int j = 0;
	if (a != strlen(arguments) && stricmp(arguments, "START:") != 0)
	{
		while (j<strlen(arguments) && j != ':')
		{
			label[j] = arguments[j];
			j++;
		}
	}
	struct Label_table *temp = createLTNode(label, ins_no + 1);
	if (label_head == NULL)
		label_head = temp;
	else
	{
		struct Label_table *t = label_head;
		while (t->next != NULL)
			t = t->next;
		t->next = temp;
	}
}
int getArgumentsCode(char argument1[10], char argument2[10], char argument3[10])
{
	int count = 0;
	if (strcmp(argument1, "") != 0)
		count++;
	if (strcmp(argument2, "") != 0)
		count++;
	if (strcmp(argument3, "") != 0)
		count++;
	return count;
}
int getCode(char argument[10])
{
	if (stricmp(argument, "EQ"))
		return EQ;
	if (stricmp(argument, "LT"))
		return LT;
	if (stricmp(argument, "GT"))
		return GT;
	if (stricmp(argument, "LTEQ"))
		return LTEQ;
	if (stricmp(argument, "GTEQ"))
		return GTEQ;
}
struct Intermediate_table * if_data(char command[30], struct Intermediate_table *intermediate_head, int ins_no, char *filename)
{
	struct stack_element element;
	//write the code to divide the parameters
	char argument1[10];
	char argument2[10];
	char argument3[10];
	char operation[10];
	strcpy(argument1, "");
	strcpy(argument2, "");
	strcpy(argument3, "");
	sscanf(command, "%s %s %s %s", operation, argument1, argument2, argument3);
	strcpy(element.label_name, "IF");
	element.address = ins_no;
	push(element);
	//rest of the code.
	int parameters[10];
	int c = getArgumentsCode(argument1, argument2, argument3);
	FILE *fp = fopen(filename, "a");
	struct Intermediate_table *temp;
	if (c == 1)
	{
		//fprintf(fp, "0%d 0%d \n",IF, argument1[0] - 'A' + 1);
		parameters[0] = argument1[0] - 'A' + 1;
		temp = createITNode(ins_no, IF, parameters, 1);
	}
	else{
		//fprintf(fp, "0%d 0%d 0%d 0%d\n",IF, argument1[0] - 'A' + 1, argument3[0] - 'A'+1,getCode(argument2[0]));
		parameters[0] = argument1[0] - 'A' + 1;
		parameters[2] = getCode(argument2);
		parameters[1] = argument3[0] - 'A' + 1;
		temp = createITNode(ins_no, IF, parameters, 3);
	}
	if (intermediate_head == NULL)
		intermediate_head = temp;
	else
	{
		struct Intermediate_table *t = intermediate_head;
		while (t->next != NULL)
			t = t->next;
		t->next = temp;
	}
	fclose(fp);
	return temp;
}
int stripandsendopcode(char arguments[50], struct Label_table *label_table)
{
	int i = 0;
	char label[30];
	while (i<strlen(arguments) && arguments[i] != ':')
	{
		label[i] = arguments[i];
		i++;
	}
	struct Label_table *temp = label_table;
	while (temp != NULL && stricmp(label, temp->label_name))
		temp = temp->next;
	return temp->address;
}
struct Intermediate_table * else_data(char arguments[30], struct Intermediate_table *intermediate_head, struct Label_table *label_head, int ins_no, char *filename)
{
	struct stack_element element;
	struct Label_table *temp = createLTNode("ELSE", ins_no + 1);
	if (label_head == NULL)
		label_head = temp;
	else
	{
		struct Label_table *t = label_head;
		while (t->next != NULL)
			t = t->next;
		t->next = temp;
	}

	strcpy(element.label_name, "ELSE");
	element.address = ins_no;
	push(element);
	int parameters[1];
	struct Intermediate_table *temp1;
	temp1 = createITNode(ins_no, JUMP, parameters, 0);
	if (intermediate_head == NULL)
		intermediate_head = temp1;
	else
	{
		struct Intermediate_table *t = intermediate_head;
		while (t->next != NULL)
			t = t->next;
		t->next = temp1;
	}
	return intermediate_head;
}
struct Intermediate_table * jump(char arguments[30], struct Intermediate_table *intermediate_head, struct Label_table *label_table, int ins_no, char *filename)
{
	int c = stripandsendopcode(arguments, label_table);
	int parameters[1];
	parameters[0] = c;
	struct Intermediate_table *temp;
	temp = createITNode(ins_no, JUMP, parameters, 1);
	if (intermediate_head == NULL)
		intermediate_head = temp;
	else
	{
		struct Intermediate_table *t = intermediate_head;
		while (t->next != NULL)
			t = t->next;
		t->next = temp;
	}
	return temp;
}
/*
struct Intermediate_table * end_if(char arguments[30],struct Intermediate_table *intermediate_head,struct Label_table *label_head,int ins_no,char *filename)
{
int c = stripandsendopcode(arguments,label_head);
int parameters[1];
parameters[0]=c;
struct Label_table *temp;
temp = createLTNode("ENDIF",ins_no+1);
if(label_head==NULL)
label_head=temp;
else
{
struct Label_table *t = label_head;
while (t->next != NULL)
t = t->next;
t->next = temp;
}
temp = 	label_head;
char t;
while(1)
{
struct stack_element t=pop(s);
if(strcmp(t.label_name,"IF")!=0)
c= findOpCode();//struck here
}
return temp;
}*/
struct table* parse(char cmd[35], struct tables *table, int count)
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
	{
		table->table_head = data(arguments, table->table_head);
	}
	if (_stricmp(command, "print") == 0)
	{
		print(arguments, table->table_head, filename);
	}
	if (_stricmp(command, "mov") == 0)
	{
		table->intermediate_table = mov(arguments, table->intermediate_table, count, filename);
	}
	if (_stricmp(command, "read") == 0)
	{
		table->intermediate_table = read(arguments, table->intermediate_table, count, filename);
	}
	if (_stricmp(command, "add") == 0)
	{
		table->intermediate_table = add(arguments, table->intermediate_table, count, filename);
	}
	if (_stricmp(command, "sub") == 0)
	{
		table->intermediate_table = sub(arguments, table->intermediate_table, count, filename);
	}
	if (_stricmp(command, "const") == 0)
	{
		table->table_head = constant(arguments, table->table_head);
	}
	if (_stricmp(command, "if") == 0)
	{
		table->intermediate_table = if_data(cmd, table->intermediate_table, count, filename);
	}
	if (_stricmp(command, "else") == 0)
	{
		table->intermediate_table = else_data(arguments, table->intermediate_table, table->label_table, count, filename);
	}
	if (_stricmp(command, "jump") == 0)
	{
		table->intermediate_table = jump(arguments, table->intermediate_table, table->label_table, count, filename);
	}
	if (_stricmp(command, "endif") == 0)
	{
		//table->intermediate_table = endif(arguments,table->intermediate_table,table->label_table,count,filename);
	}
	else{
		table->label_table = label(arguments, table->label_table, count, filename);
	}
	return table;
}
int main()
{
	struct tables *table;
	table->table_head = NULL;
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
	int symbol_table_count = 0;
	struct tables *table_head;
	int count = 0;
	while (!feof(fp))
	{
		fgets(num, 100, fp);
		count++;
		table_head = parse(num, table, count);
		printf("%s ", num);
	}
	fclose(fp1);
	FILE *fp2 = fopen("output.txt", "r");
	if (fp2 == NULL)
	{
		printf("Error opening the file\n");
		return 0;
	}
	_getch();
	return 0;
}

