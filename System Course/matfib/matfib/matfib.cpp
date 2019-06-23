// matfib.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
int ** multiply(int** a, int** b)
{
	int i, j, k;
	int **c =(int **)calloc(2,sizeof(int*));
	for (int i = 0; i < 2; i++)
		c[i] = (int *)calloc(2,sizeof(int));
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 2; j++)
		{
			c[i][j] = 0;
			for (k = 0; k < 2; k++)
				c[i][j] += a[i][k] *b[k][j];
		}
	}
	return c;
}
int ** matrix(int **a, int n)
{
	if (n == 2)
	{
		int **t = multiply(a, a);
		return t;
	}
	return multiply(a, matrix(a, n - 1));
}
int main()
{
	int n;
	printf("n:\n");
	scanf_s("%d", &n);
	int **a = (int **)calloc(2, sizeof(int*));
	for (int i = 0; i < 2; i++)
		a[i] = (int *)calloc(2, sizeof(int));
	a[0][0]	= 0;
	a[0][1] = 1;
	a[1][0] = 1;
	a[1][1] = 1;
	if (n == 1)
	{
		printf("1");
		return 0;
	}
	int **t=matrix(a, n);
	int xn[2];
	xn[0] = 0;
	xn[1] = t[0][1] + t[1][1];
	printf("The fibanocci number at %d is %d ",n,xn[1]);
	_getch();
	return 0;
}

