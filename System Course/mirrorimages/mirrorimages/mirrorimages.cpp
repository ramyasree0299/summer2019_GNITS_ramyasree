// ndigits.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
void ndigits(int holder[10],char mirror[10], int index, int k)
{
	int i, j = 0;
	if (index != k)
	{
		for (i = 0; i <= 9; i++)
		{
			holder[index] = i;
			ndigits(holder,mirror, index + 1, k);
		}
	}
	else if (index == k)
	{
		j = 0;
		while (holder[j] == 0)j++;
		while (j < k)
		{
			printf("%c", mirror[holder[j]]);
			j++;
		}
		printf("\n");
	}
}

int main()
{
	int i, k;
	printf("k :\n");
	scanf_s("%d", &k);
	int holder[10];
	for (i = 0; i < k; i++)
		holder[i] = 0;
	char mirror[10];
	mirror[0] = '0';
	mirror[1] = '1';
	mirror[2] = '5';
	mirror[3] = 'E';
	mirror[4] = 'h';
	mirror[5] = '2';
	mirror[6] = '9';
	mirror[7] = 'L';
	mirror[8] = '8';
	mirror[9] = '6';
	printf("0\n");
	ndigits(holder,mirror, 0, k - 1);
	_getch();
	return 0;
}

