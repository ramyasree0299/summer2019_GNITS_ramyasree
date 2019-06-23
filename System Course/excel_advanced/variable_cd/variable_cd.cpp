#include "stdafx.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>
#define _CRT_SECURE_NO_WARNINGS

struct ele
{
	int flag;
	int data;
	char formula[20];
};
int isOperator(char c)
{
	if (c == '*' || c == '+' || c == '-' || c == '%' || c == '^' || c == '/')
		return 1;
	return 0;
}
char *insert(int start, char * forum, char *num)
{
	int i = 0;
	if (strlen(num) <= 2)
	{
		while (i < strlen(num))
		{
			forum[start + i] = num[i];
			i++;
		}
		if (strlen(num) == 1)
			while (start + i <= strlen(forum))
			{
				forum[start + i] = forum[start + i + 1];
				i++;
			}
	}
	else if (strlen(num) <= strlen(forum))
	{
		forum[start] = num[0];
		forum[start + 1] = num[1];
		start += 2;
		int length = strlen(forum);
		int nlength = strlen(num) - 2;
		int i;
		for (i = length - 1; i >= start; i--)
			forum[i + nlength] = forum[i];
		i = 0;
		for (i = 0; i < nlength; i++)
			forum[start + i] = num[2 + i];
		forum[length + nlength] = '\0';

	}
	printf("Insert  :%s \n", forum);
	return forum;
}
char* getInfixExp(struct ele sheet[10][10], char forum[10000])
{
	int k = 0;
	char *num = (char*)malloc(100 * sizeof(char));
	forum[strlen(forum)] = '\0';
	int n;
	while (k < strlen(forum))
	{
		if (isalpha(forum[k]) == 1)
		{
			if (sheet[forum[k] - 'A'][forum[k + 1] - '0' - 1].flag == 0){
				_itoa_s(sheet[forum[k] - 'A'][forum[k + 1] - '0' - 1].data, num, 100, 10);
			}
			else if (sheet[forum[k] - 'A'][forum[k + 1] - '0' - 1].flag == 1){
				strcpy_s(num, 100, getInfixExp(sheet, sheet[forum[k] - 'A'][forum[k + 1] - '0' - 1].formula));
			}
			int i = 0;
			forum = insert(k, forum, num);
		}
		else
			k++;
	}
	printf("getInfix : %s\n", forum);
	return forum;
}

int alldigits(char temp[20])
{
	int length = strlen(temp);
	int i = 0;
	while (i < length && isdigit(temp[i]))i++;
	int j = 0;
	if (i == length)
	{
		i = 0;
		while (i < length)
		{
			j = (j * 10) + (temp[i] - '0');
			i++;
		}
	}
	return j;
}
int DetectCycle(struct ele sheet[10][10], char param[2], char temp[50], int index)
{
	int j;
	for (j = 0; j < index; j += 2)
		if (param[0] == temp[j] && param[1] == temp[j + 1])
			break;
	if (j != index)
		return 1;
	else if (j == index && sheet[param[0] - 'A'][param[1] - '0' - 1].flag == 1)
	{
		temp[index] = param[0];
		temp[index + 1] = param[1];
		int k = 0, t;
		char t1[100];
		strcpy_s(t1, 100,sheet[param[0] - 'A'][param[1] - '0' - 1].formula);
		while (k < strlen(t1))
		{
			if (isalpha(t1[k]) == 1)
			{
				param[0] = t1[k];
				param[1] = t1[k + 1];
				return DetectCycle(sheet, param, temp, index + 2);
			}
			k += 2;
		}
	}
}
void validateCode(struct ele sheet[10][10], char* param, int flag)
{
	if (flag == 0)return;
	else if (flag == 1)
	{//checking recursion
		char forum[100];
		strcpy_s(forum,100, sheet[param[0] - 'A'][param[1] - '0' - 1].formula);
		int k = 0;
		while (k < strlen(forum))
		{
			if (isalpha(forum[k]) == 1 && forum[k] == param[0] && forum[k + 1] == param[1])
			{
				printf("Recursion caught!! Please press any key twice to exit\n");
				return;
			}
			else k++;
		}
	}

}

void get(struct ele sheet[10][10], char **list_Of_commands, int cmd, char cd[100])
{
	char param[2];
	int p = 0;
	int k;
	k = strlen(list_Of_commands[cmd]);
	while (cd[k] == ' ')
		k++;
	while (cd[k] != '\0')
	{
		param[p] = cd[k];
		p++;
		k++;
	}
	char temp[50];
	if (sheet[param[0] - 'A'][param[1] - '0' - 1].flag == 0)
	{
		printf("%d\n", sheet[param[0] - 'A'][param[1] - '0' - 1].data);
	}
	else
		if (sheet[param[0] - 'A'][param[1] - '0' - 1].flag == 1 && DetectCycle(sheet, param, temp, 0)==0)
		{

			char temp[20];
			char forum[100];
			strcpy_s(forum, 20, sheet[param[0] - 'A'][param[1] - '0' - 1].formula);
			int k = 0;
			char* num = (char *)malloc(20 * sizeof(char));
			char op = ' ';
			num = getInfixExp(sheet, forum);
			//sheet[param[0] - 'A'][param[1] - '0' - 1].data = getRes(num);
			printf("%d\n", sheet[param[0] - 'A'][param[1] - '0' - 1].data);
		}
		else {
			printf("Dead Lock found\n");
			_getch();
			exit(0);
		}
}
void set(struct ele sheet[10][10], char **list_Of_commands, int cmd, char cd[100])
{
	char param[10];
	int p = 0;
	int k;
	k = strlen(list_Of_commands[cmd]);
	while (cd[k] == ' ')
		k++;

	while (cd[k] != '=')
	{
		param[p] = cd[k];
		p++;
		k++;
	}
	k++;
	int n = k;
	p = 0;
	int form_flag = 0;
	while (cd[k] != '\0')
	{
		if (!(isdigit(cd[k])))
			form_flag = 1;
		sheet[param[0] - 'A'][param[1] - '0' - 1].formula[p] = cd[k];
		k++;
		p++;
	}
	sheet[param[0] - 'A'][param[1] - '0' - 1].formula[p] = '\0';
	if (form_flag == 0)
	{
		sheet[param[0] - 'A'][param[1] - '0' - 1].flag = 0;
		int num = 0;
		while (cd[n] != '\0')
		{
			num = (num * 10) + (cd[n] - '0');
			n++;
		}
		sheet[param[0] - 'A'][param[1] - '0' - 1].data = num;
	}
	else sheet[param[0] - 'A'][param[1] - '0' - 1].flag = 1;
	validateCode(sheet, param, form_flag);
}
void print(struct ele sheet[10][10])
{
	int i;
	int j;
	for (i = 0; i < 10; i++)
	{
		printf("_______________________________________________\n");
		for (j = 0; j < 10; j++)
		{
			printf("| %d |", sheet[i][j].data);
		}
		printf("\n");
	}
}
void exportdata(struct ele sheet[10][10], char **list_Of_commands, int cmd, char cd[100], char filename[10], FILE *fp)
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
	filename[p] = '\0';
	filename[p] = '.';
	filename[p + 1] = 'c';
	filename[p + 2] = 's';
	filename[p + 3] = 'v';
	fopen_s(&fp, filename, "w");
	if (fp == NULL)printf("failed to open file");
	int i, j;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			if (sheet[i][j].flag == 0)
				fprintf(fp, "%d,", sheet[i][j].data);
			else fprintf(fp, "%s,", sheet[i][j].formula);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}
void importdata(struct ele sheet[10][10], char **list_Of_commands, int cmd, char cd[100], char filename[10], FILE *fp)
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
	char temp[10];
	p = 0;
	fopen_s(&fp, filename, "r");
	if (fp == NULL)printf("file doesn't exists");
	int i = 0;
	int j;
	while (fgets(dataToBeRead, 50, fp) != NULL && i < 10)
	{
		printf("%s\n", dataToBeRead);
		for (j = 0; j < 10; j++)
		{
			p = 0;
			k = 0;
			while (dataToBeRead[k] != ',' && dataToBeRead[k] != '\n')
			{
				temp[p] = dataToBeRead[k];
				p++;
				k++;
			}
			k++;
			temp[p] = '\0';
			int n;
			if ((n = alldigits(temp)) != 0)
				sheet[i][j].data = n;
			else
				strcpy_s(sheet[i][j].formula, 20, temp);
			j++;
		}
	}
	fclose(fp);
}
void save(struct ele sheet[10][10], char filename[10], FILE *fp)
{
	int i, j;
	if (strcmp(filename, " "))
	{
		//printf("%d", strcmp(filename, " "));
		fopen_s(&fp, filename, "w");
		if (fp == NULL)printf("failed to open file");
		for (i = 0; i < 10; i++)
		{
			for (j = 0; j < 10; j++)
			{
				if (sheet[i][j].flag == 0)
					fprintf(fp, "%d,", sheet[i][j].data);
				else fprintf(fp, "%s,", sheet[i][j].formula);
			}
			fprintf(fp, "\n");
		}
		fclose(fp);
	}
	else
	{
		printf("file not selected");
	}
}
int main()
{
	int i;
	FILE *fp = NULL;
	char **list_Of_commands = (char **)calloc(5, sizeof(char *));
	for (i = 0; i < 5; i++)
		list_Of_commands[i] = (char *)calloc(10, sizeof(char));
	list_Of_commands[0] = "GET";
	list_Of_commands[1] = "SET";
	list_Of_commands[2] = "PRINT";
	list_Of_commands[3] = "EXPORT";
	list_Of_commands[4] = "IMPORT";
	list_Of_commands[5] = "SAVE";
	char filename[20] = " ";
	struct ele sheet[10][10];
	int j;
	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++)
		{
			sheet[i][j].data = 0;
			strcpy_s(sheet[i][j].formula, 20, " ");
			sheet[i][j].flag = 0;
		}
	char cd[100];
	printf(">");
	while (gets_s(cd))
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
			for (i = 0; i < 6; i++)
			{
				k = 0;
				while (cd[k] != '\0' && cd[k] == list_Of_commands[i][k])
					k++;
				if (k == strlen(list_Of_commands[i]))
					break;
			}
			if (i == 6){
				printf("Invalid command format. Press Ctrl+C to exit!");
				exit(0);
			}
			else
			{
				int cmd = i;
				int k;
				//return 0; //comment this
				if (cmd == 0)
				{
					get(sheet, list_Of_commands, cmd, cd);
				}
				else if (cmd == 1)
				{
					set(sheet, list_Of_commands, cmd, cd);
				}
				else if (cmd == 2)
				{
					print(sheet);
				}
				else if (cmd == 3)
				{
					exportdata(sheet, list_Of_commands, cmd, cd, filename, fp);
				}
				else if (cmd == 4)
				{

					importdata(sheet, list_Of_commands, cmd, cd, filename, fp);
				}
				else if (cmd == 5)
				{
					save(sheet, filename, fp);
				}
			}

			printf(">");
		}
	}
	_getch();
	return 0;
}

