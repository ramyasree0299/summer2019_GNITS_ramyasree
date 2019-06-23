// 2colorsort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
void sort(int arr[10], int n)
{
	printf("\nElements in the array using sort method\n");
	int i, j, temp;
	for (i = 0; i < n - 1; i++)
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = temp;
			}
	for (i = 0; i<n; i++)
		printf("%d ", arr[i]);

}
void count(int arr[10], int n)
{
	printf("\nElements in the array using count method\n");
	int count1 = 0;
	int count0 = 0;
	int i = 0;
	for (i = 0; i<n; i++)
	{
		if (arr[i] == 1)count1++;
		else count0++;
	}
	while (count0>0)
	{
		printf("0 ");
		count0--;
	}

	while (count1>0)
	{
		printf("1 ");
		count1--;
	}
}
void sum(int arr[10], int n)
{
	printf("\nElements in the array using sum method\n");
	int i = 0, sum = 0;
	for (i = 0; i<n; i++)
		sum += arr[i];
	for (i = 0; i<n - sum; i++)
		printf("0 ");
	for (i = 0; i<sum; i++)
		printf("1 ");
}


int main()
{
	int n;
	printf("Enter size:\n");
	scanf_s("%d", &n);
	int arr[10];
	printf("\nEnter the elements of the array\n");
	int i;
	for (i = 0; i<n; i++)
		scanf_s("%d", &arr[i]);
	sort(arr, n);
	sum(arr, n);
	count(arr, n);
	_getch();
	return 0;
}
