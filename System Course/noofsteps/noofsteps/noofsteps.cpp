// noofsteps.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
void findpath(int added, int remain, int steps,int *count,int k)
{
	for (int i = 1; i <= k; i++)
	{
		if (added + i < steps) {
			added += i;
			remain -= i;
			if (added != steps)findpath(added,remain, steps,count,k);
		}
		else if (added + i == steps){
			added += i;
			remain -= i;
			*count=*count+1;
		}
		added -= i;
	}
}

int main() {
	int steps;
	printf("Enter the number of steps\n");
	scanf_s("%d", &steps);
	printf("Maximum number of steps can be taken at a time\n");
	int k;
	scanf_s("%d", &k);
	int added = 0;
	int remain = steps;
	int count = 0;
	findpath(added, remain, steps,&count,k);
	printf("The number of ways to take %d steps are %d\n",steps,count);
	_getch();
	return 0;
}
