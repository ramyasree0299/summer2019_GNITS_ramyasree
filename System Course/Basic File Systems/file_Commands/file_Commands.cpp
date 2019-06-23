// file_Commands.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
struct metadata
{
	char filename[16];
	int offset;
	int size;
};
void copyfrom(char **list_Of_commands, char cd[50], int cmd, struct metadata metaData[10], int *count, char *source, char *destination)
{
	FILE *sfp = fopen(source, "w");
	FILE *dfp = fopen(destination, "rb");
	if (sfp == NULL)printf("Source file reading error\n");
	if (dfp == NULL)printf("destination file reading error\n");
	char num[100];
	int i = 0;
	while ((fread(num, 16, 1, dfp))!= 0)
	{
		if (strcmp(num, source) == 0)
			break;
		fseek(dfp,1032, SEEK_CUR);
	}
	printf("%d ", ftell(dfp));
	fseek(dfp, 8, SEEK_CUR);
	char c;
	for (int i = 0; i < 1024; i++)
	{
		if (fread(&c, 1, 1, dfp) != -1)
			fprintf(sfp,"%c",c);
		printf("%c ", c);
	}
	fclose(sfp);
	fclose(dfp);
}
void copyto(char **list_Of_commands, char cd[50], int cmd, struct metadata metaData[10], int *count,char *source,char *destination)
{
	FILE *sfp = fopen(source, "r");
	FILE *dfp = fopen(destination, "rb+");
	if (sfp == NULL)printf("Source file reading error\n");
	if (dfp == NULL)printf("destination file reading error\n");
	char num[100];
	strcpy(metaData[*count].filename, source);
	metaData[*count].filename[16] = '\0';
	metaData[*count].offset = metaData[*count - 1].offset + 1024;
	metaData[*count].size = metaData[*count].offset + 1024;
	fseek(dfp, metaData[*count].offset, SEEK_CUR);
	printf("filename : %s\noffset :  %d \nsize : %d\n", metaData[*count].filename, metaData[*count].offset, metaData[*count].size);
	if (fwrite(metaData[*count].filename, 1, 16, dfp) == -1 || fwrite(&metaData[*count].offset, 4, 1, dfp) ==-1|| fwrite(&metaData[*count].size, 4, 1, dfp)==-1)
	{
		printf("Error writing in file\n");
		return ;
	}
	int i = 0;
	char c;
	for (int i = 0; i < 1024; i++)
	{
		fscanf(sfp, "%c", &c);
		fwrite(&c, 1, 1, dfp);
	}
	*count = *count + 1;
	fclose(sfp);
	fclose(dfp);
}
void format(char **list_Of_commands, char cd[50], int cmd)
{
	FILE *fp;
	char n = ' ';
	fp = fopen("hardDisk.hdd", "wb");
	if (fp == NULL)
	{
		printf("Error opening a file\n");
		return;
	}
	fwrite(&n,1,1,fp);
	fclose(fp);
	printf("file format successful\n");
}
void list(char **list_Of_commands, char cd[50], int cmd, struct metadata metaData[10],int *count)
{
	FILE *dfp;
	dfp = fopen("hardDisk.hdd", "rb+");
	if (dfp)
	{
		int i = 0;
		char num[50];
		while (feof(dfp))
		{
			fseek(dfp, i, SEEK_SET);
			printf("postion : %d", ftell(dfp));
			if (fread(num, 16, 1, dfp) != -1)
				printf("%s\n", num);
			i += 1024;
		}
		return;
	}
	printf("Error reading file\n");
	return;
	
}
int main()
{
	FILE *fp = NULL;
	char **list_Of_commands = (char **)calloc(5, sizeof(char *));
	for (int i = 0; i < 5; i++)
		list_Of_commands[i] = (char *)calloc(10, sizeof(char));
	list_Of_commands[0] = "LS";
	list_Of_commands[1] = "FORMAT";
	list_Of_commands[2] = "COPYTO";
	list_Of_commands[3] = "COPYFROM";
	struct metadata metaData[10];
	int count = 1;
	strcpy(metaData[0].filename, "");
	metaData[0].offset = -1024;
	metaData[0].size = 0;
	char cd[100];
	printf(">");
	while (gets_s(cd))
	{
		_strupr(cd);
		if ((!strcmp(cd, "EXIT")) || (!strcmp(cd, "exit")))
		{
			break;
			return 0;
		}
		else
		{
			int i, k;
			for (i = 0; i < 4; i++)
			{
				k = 0;
				while (cd[k] != '\0' && cd[k] == list_Of_commands[i][k])
					k++;
				if (k == strlen(list_Of_commands[i]))
					break;
			}
			if (i == 4){
				printf("Invalid command format. Press Ctrl+C to exit!");
				exit(0);
			}
			else
			{
				int cmd = i;
				int k;
				if (cmd == 0)
				{
					printf("Inside the list\n");
					list(list_Of_commands, cd, cmd,metaData,&count);
				}
				else if (cmd == 1)
				{
					format(list_Of_commands, cd, cmd);
				}
				else if (cmd == 2)
				{
					char *source = (char *)calloc(16, sizeof(char));
					char *destination = (char *)calloc(16, sizeof(char));
					int i = 0;
					int k;
					char filename[16];
					k = strlen(list_Of_commands[cmd]);
					while (cd[k] == ' ')
						k++;
					int p = 0;
					while (i < 2)
					{
						while (cd[k] != '.')
						{
							if (cd[k] != ' ')
							filename[p] = cd[k];
							p++;
							k++;
						}
						filename[p] = '\0';
						if (i == 0){
							strcat(filename, ".txt");
							strcpy(source, filename);
							printf("%s\n", source);
						}
						i++;
	
					}
					strcpy(destination,"hardDisk.hdd");
					copyto(list_Of_commands, cd, cmd, metaData, &count,source,destination);
				}
				else if (cmd == 3)
				{
					char *source = (char *)calloc(16, sizeof(char));
					char *destination = (char *)calloc(16, sizeof(char));
					int i = 0;
					int k;
					char filename[16];
					k = strlen(list_Of_commands[cmd]);
					while (cd[k] == ' ')
						k++;
					int p = 0;
					while (i < 2)
					{
						while (cd[k] != '.')
						{
							if (cd[k] != ' ')
								filename[p] = cd[k];
							p++;
							k++;
						}
						filename[p] = '\0';
						if (i == 0){
							strcat(filename, ".txt");
							strcpy(source, filename);
							printf("%s\n", source);
						}
						i++;
					}
					strcpy(destination,"hardDisk.hdd");
					copyfrom(list_Of_commands, cd, cmd, metaData, &count, source, destination);
				}
			}

			printf(">");
		}
	}
	return 0;
}