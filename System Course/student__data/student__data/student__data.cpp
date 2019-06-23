#include "stdafx.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>
#include<ctype.h>
#define column_length 16
struct ele
{
	int flag;
	char data[10];
	char formula[20];
};
struct ele **sheet;
int convertToInt(char c[10])
{
	int i = 0;
	int j = 0;
	while (j<strlen(c))
	{
		i = (i * 10) + (c[j] - '0');
		j++;
	}
	return i;
}

void print(int row_length)
{
	int i, j;
	for (i = 0; i < column_length; i++)
	{
		printf("_______________________________________________\n");
		for (j = 0; j < row_length; j++)
		{
			printf("| %s |", sheet[i][j].data);
		}
		printf("\n");
	}
}
void getTopperSubjectWise(int row_length)
{
	print(row_length);
	int a, b;
	int i, j;
	for (i = 2; i<row_length; i++)
	{
		a = i;
		b = 1;
		for (j = 1; j<column_length; j++){
			if (convertToInt(sheet[i][j].data)<convertToInt(sheet[a][b].data))
				b = j;
		}
		a = row_length;
		b = column_length;
		printf("In subject report of %s, %s is the topper with %s marks\n", sheet[0][b].data, sheet[a][1].data, sheet[a - 1][b - 1].data);
	}
}
void getLeastSubjectWise(int row_length)
{
	print(row_length);
	int a, b;
	int i, j;
	for (i = 2; i<row_length; i++)
	{
		a = i;
		b = 1;
		for (j = 1; j<column_length; j++){
			if (convertToInt(sheet[i][j].data)>convertToInt(sheet[a][b].data))
				b = j;
		}
		printf("In subject report of %s, %s is the topper with %s marks\n", sheet[0][b].data, sheet[a][1].data, sheet[a][b - 1].data);
	}
}
void Average(int row_length)
{
	print(row_length);
	int i, j;
	float sum = 0.0;
	for (i = 1; i<column_length; i++)
		for (j = 2; j<row_length; j++)
			sum += convertToInt(sheet[i][j].data);
	int total = column_length*(row_length - 2);
	sum /= total;
	printf("The average score of the class %f ", sum);
}

void getLeastOverall(int row_length)
{
	print(row_length);
	int a, b;
	a = 1;
	b = 2;
	int i, j;
	int sum = 0;
	int min_sum = 0;
	for (i = 1; i < column_length; i++)
	{
		sum = 0;
		for (j = 2; j < row_length; j++)
		{
			sum += convertToInt(sheet[i][j].data);
		}
		if (sum < min_sum)
		{
			sum = min_sum;
			a = i;
			b = j;
		}
	}
	printf("The overall least performer of the class %s with %s marks", sheet[a][1].data, sheet[a][b - 1].data);
}
void getTopperOverall(int row_length)
{
	print(row_length);
	int a, b;
	a = 1;
	b = 2;
	int i, j;
	int sum = 0;
	int max_sum = 0;
	for (i = 1; i < column_length; i++)
	{
		sum = 0;
		for (j = 2; j < row_length; j++)
		{
			sum += convertToInt(sheet[i][j].data);
		}
		if (sum > max_sum)
		{
			sum = max_sum;
			a = i;
			b = j;
		}
	}
	printf("The overall topper of the class DINKY with %s marks", sheet[a][1].data, sheet[a][b].data);
}

int no_of_comma(char header[50])
{
	int i = 0, comma = 0;
	while (i<strlen(header))
	{
		if (header[i] == ',')
			comma++;
		i++;
	}
	return comma + 1;
}
struct ele** importdata(char **list_Of_commands, int cmd, char cd[100], char filename[10], FILE *fp)
{
	int p = 0;
	int k;
	k = strlen(list_Of_commands[cmd]);
	while (cd[k] == ' ')
		k++;
	while (cd[k] != '.')
	{
		filename[p] = cd[k];
		p++;
		k++;
	}
	char dataToBeRead[100];
	filename[p] = '.';
	filename[p + 1] = 'c';
	filename[p + 2] = 's';
	filename[p + 3] = 'v';
	k = 0;
	char temp[50];
	p = 0;
	fopen_s(&fp, filename, "r");
	if (fp == NULL)
	{
		printf("file doesn't exists");
		return NULL;
	}
	int i = 0;
	char header[50];
	fgets(header, 150, fp);
	int row_length = no_of_comma(header);
	while (fgets(dataToBeRead, 150, fp) != NULL && i < 16)
	{
		int j;
		k = 0;
		i++;
		for (j = 0; j < row_length; j++)
		{
			p = 0;
			while (dataToBeRead[k] != ',' && dataToBeRead[k] != '\n')
			{

				temp[p] = dataToBeRead[k];
				p++;
				k++;
			}
			k++;
			temp[p] = '\0';
			strcpy_s(sheet[i][j].data, 100, temp);
			sheet[i][j].data[p] = '\0';
			printf("%s ", sheet[i][j].data);
		}

	}
	fclose(fp);
	return sheet;
}

int main()
{
	int i;
	FILE *fp = NULL;
	char **list_Of_commands = (char **)calloc(5, sizeof(char *));
	for (i = 0; i < 5; i++)
		list_Of_commands[i] = (char *)calloc(10, sizeof(char));
	list_Of_commands[0] = "IMPORT";
	list_Of_commands[1] = "PRINT";
	list_Of_commands[2] = "GETTOPPEROVERALL";
	list_Of_commands[3] = "GETLEASTOVERALL";
	list_Of_commands[4] = "GETTOPPERSUBJECTWISE";
	list_Of_commands[5] = "GETLEASTSUBJECTWISE";
	list_Of_commands[6] = "AVERAGE";
	char filename[20] = " ";
	int j;
	sheet = (struct ele**)calloc(50, sizeof(struct ele*));
	for (i = 0; i < 50; i++)
	{
		sheet[i] = (struct ele*)calloc(50, sizeof(struct ele));
		for (j = 0; j < 50; j++)
		{
			strcpy_s(sheet[i][j].data, " ");
			strcpy_s(sheet[i][j].formula, " ");
			sheet[i][j].flag = 0;
		}
	}
	char cd[100];
	printf(">");
	while (gets(cd))
	{
		_strupr_s(cd);
		if ((!strcmp(cd, "EXIT")) || (!strcmp(cd, "exit")))
		{
			break;
			return 0;
		}
		else
		{
			int i, k;
			for (i = 0; i < 7; i++)
			{
				k = 0;
				while (cd[k] != '\0' && cd[k] == list_Of_commands[i][k])
					k++;
				if (k == strlen(list_Of_commands[i]))
					break;
			}
			if (i == 7){
				printf("Invalid command format. Press Ctrl+C to exit!");
				exit(0);
			}
			else
			{
				int cmd = i;
				int k;
				if (cmd == 0)
				{
					FILE *fp = NULL;
					sheet = importdata(list_Of_commands, cmd, cd, filename, fp);
				}
				else if (cmd == 1)
				{
					print(5);
				}
				else if (cmd == 2)
				{
					getTopperOverall(5);
				}
				else if (cmd == 3)
				{
					getLeastOverall(5);
				}
				else if (cmd == 4)
				{
					getTopperSubjectWise(5);
				}
				else if (cmd == 5)
				{
					getLeastSubjectWise(5);
				}
				else if (cmd == 5)
				{
					Average(5);
				}
			}

			printf(">");
		}
	}
	_getch();
	return 0;
}