// file_sort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void  sort(int arr[10])
{
	int temp;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 3 - i; j++)
		{
			if (arr[j]>arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j + 1] = temp;
			}
		}
	}
	
}
void fileDivision()
{
	FILE *fp;
	FILE *fps[10];
	int i = 0;
	fp=fopen("Numbers.txt", "r");
	if (fp == NULL) printf("file doesn't exits\n");
	char num[10];
	char append[10];
	char filename[20] = "file";
	int change = 4;
	int j;
	for (int i = 0; i < 5; i++)
	{
		j = 0;
		append[0] = (i + 1) + '0';
		append[1] = '\0';
		strcat(append, ".txt");
		append[5] = '\0';
		strcat(filename, append);
		filename[10] = '\0';
		fps[i] = fopen(filename,  "w");
		while (j < 4 && fgets(num, 10, fp) != NULL)
		{
			fprintf(fps[i], "%s", num);
			j++;
		}
		fclose(fps[i]);
		filename[change] = '\0';
	}
	printf("Files read\n");
	char t_num[50];
	char* t1_num = (char *)malloc(sizeof(char));
	for (int i = 0; i < 5; i++)
	{
		printf("\nFiles read again\n");
		j = 0;
		append[0] = (i + 1) + '0';
		append[1] = '\0';
		strcat_s(append, 50, ".txt");
		append[5] = '\0';
		strcat(filename, append);
		filename[10] = '\0';
		fps[i]=fopen(filename, "r");
		printf("file opened");
		int arr[10];
		int num1;
		while (j < 4)
		{	
			fscanf(fps[i], "%d\n", &num1);
			arr[j] = num1;
			j++;
		}
		fclose(fps[i]);
		sort(arr);
		j = 0;
		fps[i] = fopen(filename, "w");
		while (j < 4)
		{
			printf("%d\n", arr[j]);
			fprintf(fps[i], "%d\n", arr[j]);
			j++;
		}
		filename[change] = '\0';
		fclose(fps[i]);
	}
	fclose(fp);
	for (int i = 0; i < 5; i++)
	{
		j = 0;
		append[0] = (i + 1) + '0';
		append[1] = '\0';
		strcat(append,  ".txt");
		append[5] = '\0';
		strcat(filename,  append);
		filename[10] = '\0';
		fps[i]=fopen(filename, "r");
		filename[change] = '\0';
	}
	FILE *ofp;
	ofp=fopen("output.txt", "w");
	int min = 9999;
	int t_val;
	int index=-1;
	int counter = 0;
	while (counter <= 20)
	{
		for (int j = 0; j < 5; j++)
		{
			if (!feof(fps[j]))
			{
				fscanf(fps[j], "%d", &t_val);
				printf("%d\n", t_val);
				if (t_val < min)
				{
					min = t_val;
					index = j;
				}
				printf("%d\t", min);
			}
		}		
		fprintf(ofp, "%d\n", min);
		counter++;
			for (int j = 0; j < 5; j++)
			{
				if (j != index)
					fseek(fps[j], -2, SEEK_CUR);
			}
			
		}
	
	
}
int _tmain(int argc, _TCHAR* argv[])
{
	fileDivision();
	return 0;
}

