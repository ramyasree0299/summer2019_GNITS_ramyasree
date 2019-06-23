// spiral.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
void spiral(int lr, int lc, int hr, int hc, int **matrix)
{
	while (lr < hr && lc < hc)
	{
		int i, j;
		for (i = lc; i <= hc; i++)
			printf("%d ", matrix[lr][i]);

		lr++;
		for (j = lr; j <= hr; j++)
			printf("%d ", matrix[j][hc]);
		hc--;
		for (i = hc; i >= lc; i--)
			printf("%d ", matrix[hr][i]);
		hr--;
		for (i = hr; i >= lr;i--)
			printf("%d ", matrix[i][lc]);
		lc++;
	}
}
int main()
{
	int m;
	int n;
	printf("Enter the row and column size of the matrix\n");
	scanf_s("%d %d", &m, &n);
	int **matrix = (int **)calloc(m,sizeof(int *));
	for (int i = 0; i < m; i++)
		matrix[i] = (int *)calloc(n,sizeof(int));
	printf("Enter the matrix");
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			scanf_s("%d", &matrix[i][j]);
	spiral(0, 0, m-1, n-1, matrix);
	_getch();
	return 0;
}

