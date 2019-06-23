// file_sort_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void fileDivision()
{
	FILE *fp;
	fp = fopen("input.txt", "r");
	int num;
	bool *bitvector = (bool *)calloc(1000003, sizeof(bool));
	int i, j = 0, k, limit;
	int max_range = 10000000;
	int start_range = 0, end_range = 1000000;
	while (end_range != max_range)
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d", &num);
			if (num>=start_range && num<=end_range)
			bitvector[num - start_range] = 1;
		}
		for (int i = start_range; i < end_range; i++)
		{
			if (bitvector[i - start_range] == 1)
				printf("%d ", i);
		}
		start_range = end_range;
		end_range += end_range - start_range;

	}
}
int main()
{
	fileDivision();
	return 0;
}

