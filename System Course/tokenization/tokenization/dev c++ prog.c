#include<stdio.h>
#include<string.h>
#include<ctype.h>
struct symbol_table
{
	char name;
	char *address;
	int size;
	struct symbol_table* next;
};
enum commands{MOV1=1, MOV2, ADD, SUB, MUL, JMP, IF,EQ,LT,GT,LTEQ,GTEQ,PRINT,READ}; 
void print(char arguments[50],struct symbol_table *table_head,char *filename)
{
	struct symbol_table *temp=table_head;
	char name  = arguments[0];
	if(temp==NULL)
	{
		printf("Symbol table is empty\n");
		return ;
	}else 
	{
		while(temp!=NULL && temp->name != name)
		temp=temp->next;
		//write code to access here
	}
	FILE *fp=fopen(filename,"a");
	fprintf(fp,"%d 0%d\n",PRINT,name-'A'+1);
	fclose(fp);
}
struct symbol_table* createNode(char name,char *address,int size)
{
	struct symbol_table * temp=(struct symbol_table *)malloc(sizeof(struct symbol_table));
	temp->name =name;
	strcpy(temp->address,address);
	temp->size=size;
	temp->next=NULL;
	return temp;
}
void read(char arguments[30],struct symbol_table *table_head,char *filename)
{
	FILE *fp=fopen(filename,"a");
	fprintf(fp,"%d 0%d\n",READ,arguments[0]-'A'+1);
	fclose(fp);
}
void add(char arguments[30],struct symbol_table *table_head,char *filename)
{
	int i=0;
	char **registers = (char **)calloc(4,sizeof(char *));
	for(i=0;i<3;i++)
			registers[i]=(char *)calloc(10,sizeof(char));
	int j=0;
	int k=0;
	i=0;
	while(i<strlen(arguments))
	{
		k=0;
		while(arguments[i]!=',' && arguments[i]!='\0')
		{
			registers[j][k]=arguments[i];
			i++;
			k++;
		}
		registers[j][k]='\0';
		i++;
		j++;
	}
	
	FILE *fp=fopen(filename,"a");
	fprintf(fp,"0%d 0%d 0%d 0%d\n",ADD,registers[0][0]-'A'+1,registers[1][0]-'A'+1,registers[2][0]-'A'+1);
	fclose(fp);
}
void add(char arguments[30],struct symbol_table *table_head,char *filename)
{
	int i=0;
	char **registers = (char **)calloc(4,sizeof(char *));
	for(i=0;i<3;i++)
			registers[i]=(char *)calloc(10,sizeof(char));
	int j=0;
	int k=0;
	i=0;
	while(i<strlen(arguments))
	{
		k=0;
		while(arguments[i]!=',' && arguments[i]!='\0')
		{
			registers[j][k]=arguments[i];
			i++;
			k++;
		}
		registers[j][k]='\0';
		i++;
		j++;
	}
	
	FILE *fp=fopen(filename,"a");
	fprintf(fp,"0%d 0%d 0%d 0%d\n",ADD,registers[0][0]-'A'+1,registers[1][0]-'A'+1,registers[2][0]-'A'+1);
	fclose(fp);
}
void sub(char arguments[30],struct symbol_table *table_head,char *filename)
{
	int i=0;
	char **registers = (char **)calloc(4,sizeof(char *));
	for(i=0;i<3;i++)
			registers[i]=(char *)calloc(10,sizeof(char));
	int j=0;
	int k=0;
	i=0;
	while(i<strlen(arguments))
	{
		k=0;
		while(arguments[i]!=',' && arguments[i]!='\0')
		{
			registers[j][k]=arguments[i];
			i++;
			k++;
		}
		registers[j][k]='\0';
		i++;
		j++;
	}
	
	FILE *fp=fopen(filename,"a");
	fprintf(fp,"0%d 0%d 0%d 0%d\n",SUB,registers[0][0]-'A'+1,registers[1][0]-'A'+1,registers[2][0]-'A'+1);
	fclose(fp);
}

void data(char *arguments,struct symbol_table *table_head)
{
	struct symbol_table *temp;
	int size;
	char name=arguments[0];
	char *address=(char *)malloc(8*sizeof(char));
	if(strlen(arguments)==1)
	{
		int a;
		int *variable =&a;
    	itoa(variable,address,50);
		size=4;
	}else if(strlen(arguments)>1)
	{
		int i=2;
		int a=0;
		while(i<strlen(arguments) && isdigit(arguments[i]))
		{
			a+=(a*10)+(arguments[i]-'0');
			i++;
		}
		size=4*a;
		int *arr=(int *)calloc(size,sizeof(int));
		itoa(arr,address,50);
	}	
	temp=createNode(name,address,size);
	if(table_head==NULL)
		table_head=temp;
	else
	{
		temp=table_head;
		while(temp->next!=NULL)
		{
			struct symbol_table *t=table_head;
			while(t->next!=NULL)
			t=t->next;
			t->next=temp;
		}
	}
	printf("%s %s %d\n",name,address,size);	
} 
void mov(char arguments)
{
	int i=0;
	char **mem_reg = (char **)calloc(4,sizeof(char *));
	for(i=0;i<3;i++)
			mem_reg[i]=(char *)calloc(10,sizeof(char));
	int j=0;
	int k=0;
	i=0;
	while(i<strlen(arguments))
	{
		k=0;
		while(arguments[i]!=',' && arguments[i]!='\0')
		{
			mem_reg[j][k]=arguments[i];
			i++;
			k++;
		}
		mem_reg[j][k]='\0';
		i++;
		j++;
	}
	FILE *fp=fopen(filename,"a");
	int k;
	for(i=0;i<j;i++)
		for(k=0;k<strlen(mem_reg[i]);k++)
		if(mem_reg[i][k]=='X')
		break;
	if(k==2)
	fprintf(fp,"0%d 0%d 0%d 0%d\n",MOV1,registers[0][0]-'A'+1,registers[1][0]-'A');
		else if(k==1)
	fprintf(fp,"0%d 0%d 0%d 0%d\n",MOV2,registers[0][0]-'A',registers[1][0]-'A'+1);
	fclose(fp);
} 
void parse(char cmd[35])
{
	int i=0;
	int j=0;
	int k=0;
	struct symbol_table *table_head=NULL;
	char command[10];
	char arguments[20];
	sscanf(cmd,"%s %s",command,arguments);
	char *filename = "output.txt";
	if (_stricmp(command, "data") == 0)
			data(arguments,table_head);
		else if (_stricmp(command, "mov") == 0)
			mov(arguments);
		else if (_stricmp(command, "read") == 0)
			read(arguments,table_head,filename);
		else if (_stricmp(command, "add") == 0)
			add(arguments,table_head,filename);
		else if (_stricmp(command, "sub") == 0)
			sub(arguments,table_head,filename);
		else if (_stricmp(command, "print") == 0)
			print(arguments,table_head,filename);
		/*else if (_stricmp(command, "const") == 0)
		else if (_stricmp(command, "if") == 0)*/	
}
int main()
{
	FILE *fp = fopen("input.txt", "r");
	if(fp==NULL)
	{
		printf("Error opening the file\n");
		return 0;
	}
	char num[35];
	while (fread(num, 30,1,fp) != -1)
	{
		printf("%s ",num);
			//parse(num);
			printf("\n");
	}
	return 0;
}


