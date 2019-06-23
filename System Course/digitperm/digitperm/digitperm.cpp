// digitperm.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
void nperm(int holder[10],int arr[10],int index, int k)
{
	int i,j;
	if (index != k)
	{
		for (i = 0; i < k; i++)
		{
			for (j = 0; j < index; j++)
			{
				if (holder[j] == arr[i])
					break;
			}
			if (j == index){
				holder[index] = arr[i];
				nperm(holder, arr, index + 1, k);
			}
		}
	}
	else if (index == k)
	{
		for (int j = 0; j < k; j++)
			printf("%d", holder[j]);
		printf("\n");
	}
}

int main()
{
	int n;
	printf("Enter n\n");
	scanf_s("%d", &n);
	int arr[10];
	printf("Enter the elements\n");
	for (int i = 0; i < n; i++)
		scanf_s("%d", &arr[i]);
	int holder[10];
	printf("The possible permutations\n");
	nperm(holder,arr,0,n);
	_getch();
	return 0;
}

