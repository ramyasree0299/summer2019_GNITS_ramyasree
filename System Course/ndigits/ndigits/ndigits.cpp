// ndigits.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
void ndigits(int holder[10],int index,int k)
{
	int i,j=0;
	if (index != k)
	{
		for (i = 0; i <= 9; i++)
		{
			holder[index] = i;
			ndigits(holder, index + 1,k);
		}
	}
	else if (index==k)
	{
		j = 0;
		while (holder[j] == 0)j++;
		while (j < k)
		{
			printf("%d", holder[j]);
			j++;
		}
		printf("\n");
	}
}

int main()
{
	int i,k;
	printf("k :\n");
	scanf_s("%d", &k);
	int holder[5];
	for (i = 0; i < k; i++)
		holder[i] = 0;
	ndigits(holder, 0, k - 1);
	_getch();
	return 0;
	
}

