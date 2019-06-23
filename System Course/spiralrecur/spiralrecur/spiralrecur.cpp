// spiralrecur.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
void spiralRecursive(int lr, int lc, int hr, int hc, int **arr, int direction, int depth){
	int itr1;
	if (lr>hr || lc > hc)
		return;
	if (direction == 0){
		for (itr1 = lc; itr1 <= hc; itr1++)
			printf("%d ", arr[lr][itr1]);
		spiralRecursive(lr + 1, hc, hr, hc, arr, 1, depth);
	}
	else if (direction == 1){
		for (itr1 = lr; itr1 <= hr; itr1++)
			printf("%d ", arr[itr1][hc]);
		spiralRecursive(hr, hc - 1, hr, hc - 1, arr, 2, depth);
	}
	else if (direction == 2){
		for (itr1 = hc; itr1 >= depth; itr1--)
			printf("%d ", arr[hr][itr1]);
		spiralRecursive(hr - 1, depth, hr - 1, hc, arr, 3, depth);
	}
	else{
		for (itr1 = lr; itr1 >= depth + 1; itr1--)
			printf("%d ", arr[itr1][depth]);
		depth = depth + 1;
		spiralRecursive(depth, depth, hr, hc, arr, 0, depth);
	}
}
int main()
{
	int m;
	int n;
	printf("Enter the row and column size of the matrix\n");
	scanf_s("%d %d", &m, &n);
	int **matrix = (int **)calloc(m, sizeof(int *));
	int i, j;
	for (i = 0; i < m; i++)
		matrix[i] = (int *)calloc(n, sizeof(int));
	printf("Enter the matrix");
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			scanf_s("%d", &matrix[i][j]);
	spiralRecursive(0, 0, m - 1, n - 1, matrix, 0, 0);
	_getch();
	return 0;
}

