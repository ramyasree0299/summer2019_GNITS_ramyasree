// puzzle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
int verify(char puzzle[10][10],int m,int n,int i, int j, char str[10])
{
	printf("%d %d\n", i, j);
	int k;
	int length = strlen(str);
	char end = str[strlen(str) - 1];
	//direction1-forward
	int count = 0;
	if (j+length-1<=m-1 && puzzle[i][j + length-1] == end)
	{
		
		k = 0;
		while (k<length && puzzle[i][j + k] == str[k])
			k++;
		if (k == length)count++;
	}
	if (j-length+1>=0 && puzzle[i][j - length+1] == end)
	{
		k = 0;
		while (k<length && puzzle[i][j - k] == str[k])
			k++;
		if (k == length)count++;
	}
	if (i + length-1 <= n - 1 && puzzle[i + length-1][j] == end)
	{
		k = 0;
		while (k<length && puzzle[i+k][j] == str[k])
			k++;
		if (k == length)count++;
	}
	if (i- length+1 >= 0 && puzzle[i - length+1][j] == end)
	{
		k = 0;
		while (k<length && puzzle[i-k][j] == str[k])
			k++;
		if (k == length)count++;
	}
	if (i + length - 1 <= n - 1 && j + length - 1 <= m - 1)
	{
		k = 0;
		while (k<length && puzzle[i+k][j+k]==str[k])
			k++;
		if (k == length)count++;
	}
	if (j - length + 1 >= 0 && i - length + 1 >= 0)
	{
		k = 0;
		while (k<length && puzzle[i - k][j - k] == str[k])
			k++;
		if (k == length)count++;
	}
	if (i - length + 1 >= 0 && j + length - 1 <= m - 1)
	{
		k = 0;
		while (k<length && puzzle[i - k][j + k] == str[k])
			k++;
		if (k == length)count++;
	}
	if (j - length + 1 >= 0 && i + length - 1 <= n - 1)
	{
		k = 0;
		while (k<length && puzzle[i + k][j - k] == str[k])
			k++;
		if (k == length)count++;
	}
	return count;
}
int solve_puzzle(char puzzle[10][10], char str[10], int m, int n)
{
	int temp;
	char start = str[0];
	int count = 0;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if (puzzle[i][j] == start){
				temp = verify(puzzle, m, n, i, j, str);
				if (temp>= 1)
					count += temp;
			}
	printf("%d", count);
	return count;
}
int main()
{
	int m,n, i, j;
	printf("m:\n");
	scanf_s("%d", &m);
	printf("n:\n");
	scanf_s("%d", &n); 
		char puzzle[10][10];
	printf("Enter puzzle\n");
	for (i = 0; i < m; i++)
	for (j = 0; j < n; j++)
	scanf(" %c", &puzzle[i][j]);
	char str[100] = "hear";
	printf("The number of strings %d", solve_puzzle(puzzle, str, m, n));
	_getch();
	return 0;
}

