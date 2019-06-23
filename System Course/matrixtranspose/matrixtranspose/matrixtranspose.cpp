#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int main()
{
	int m, n;
	printf("M:\n");
	scanf_s("%d", &m);
	printf("N:\n");
	scanf_s("%d", &n);
	int i, j;
	int mat[10][10];
	int trans[10][10];
	printf("Enter the matrix\n");
	for (i = 0; i<m; i++)
		for (j = 0; j<n; j++)
			scanf_s("%d", &mat[i][j]);
	for (i = 0; i<n; i++)
		for (j = 0; j<m; j++)
			trans[i][j] = mat[j][i];
	printf("The matrix\n");
	for (i = 0; i<m; i++){
		for (j = 0; j<n; j++){
			printf("%d\t", mat[i][j]);
		}
		printf("\n");
	}
	printf("The transpose\n");
	for (i = 0; i<n; i++){
		for (j = 0; j<m; j++){
			printf("%d\t", trans[i][j]);
		}
		printf("\n");
	}
	_getch();
	return 0;
}