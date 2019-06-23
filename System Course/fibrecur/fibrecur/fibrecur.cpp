// fibrecur.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
int fib_recur(int n, int arr[10])
{
	if (n == 0 || n == 1)
		arr[n] = n;
	else
	{
		if (arr[n - 2] != 0 && arr[n - 1] != 0)
			arr[n] = arr[n - 2] + arr[n - 1];
		else if (arr[n - 1] != 0 && arr[n - 2] == 0)
			arr[n] = arr[n - 1] + fib_recur(n - 2,arr);
		else if (arr[n - 1] == 0 && arr[n - 2] != 0)
			arr[n] = arr[n - 2] + fib_recur(n - 1,arr);
		else if (arr[n - 1] == 0 && arr[n - 2] == 0)
			arr[n] = fib_recur(n - 1,arr) + fib_recur(n - 2,arr);
	}
	return arr[n];
};

int _tmain(int argc, _TCHAR* argv[])
{
	int n;
	printf("Enter n\n");
	scanf_s("%d", &n);
	if (n < 0){ printf("undefined"); 
	return 0;
	}
	int arr[10];
	for (int i = 0; i < n; i++)
		arr[i] = 0;
	printf("The nth number %d ",fib_recur(n,arr));
	_getch();
	return 0;
}

