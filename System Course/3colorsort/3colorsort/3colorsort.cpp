// 3colorsort.cpp : Defines the entry point for the console application.
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
void sum(int arr[10], int n)
{
	printf("\nElements in the array using sum method\n");
	int i = 0, sum = 0;
	for (i = 0; i<n; i++)
		sum += arr[i];
	int count2 = 0;
	for (i = 0; i<n; i++)
		if (arr[i] == 2)count2++;
	sum = sum - 2 * count2;
	n = n - count2;
	i = 0;
	while (i<n - sum)
	{
		printf("0 ");
		i++;
	}
	while (sum>0)
	{
		printf("1 ");
		sum--;
	}
	while (count2>0)
	{
		printf("2 ");
		count2--;
	}
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
	_getch();
	return 0;
}