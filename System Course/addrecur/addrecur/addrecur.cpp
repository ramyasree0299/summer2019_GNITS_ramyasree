// addrecur.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
int sum_recur(int arr[10], int n)
{
	if (n == 0) return 0;
	return arr[n - 1] + sum_recur(arr, n - 1);
}

int _tmain(int argc, _TCHAR* argv[])
{
	int n;
	printf("Enter the number of the elements in the array\n");
	scanf_s("%d", &n);
	int arr[10];
	printf("Enter the elements in the array\n");
	for (int i = 0; i < n; i++)
		scanf_s("%d", &arr[i]);
	printf("The sum of numbers\n");
	printf("%d",sum_recur(arr, n));
	_getch();
}

