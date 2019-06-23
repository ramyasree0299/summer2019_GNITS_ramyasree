// apowern.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
int power(int a, int n)
{
	if (n == 0)return 1;
	else
	return a*power(a, n - 1);
}
int main()
{
	int a, n, m;
	printf("a : ");
	scanf_s("%d", &a);
	printf("n : ");
	scanf_s("%d", &n);
	int p= power(a, n);
	p = p % (1000000000 + 7);
	printf("(a^n)mod(10^9+7) = %d\n", p);
	return 0;
}

