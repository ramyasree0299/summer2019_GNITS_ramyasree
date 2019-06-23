// b-trees.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#define PAGE_SIZE 32
#pragma pack(32)
#define NO_OF_VALUES 3
#include<conio.h>
struct leaf_page
{
	char pageType;
	char unused[4];
	int sid[3];
	char name[3][5];
};
struct Non_leaf_page
{
	char pageType;
	char unused[3];
	int children[4];
	int value[3];
};

int min(int arr[10])
{
	int i;
	int min = 99;
	for (i = 0; i<NO_OF_VALUES; i++)
		if (min>arr[i])
			min = arr[i];
	return min;
}
int main()
{
	struct leaf_page lp[4];
	int i = 0;
	int k = 0;
	FILE *fp;
	fp = fopen("btrees.txt", "r");
	fread(lp, sizeof(struct leaf_page), 4, fp);
	struct Non_leaf_page parent;
	printf("Parent Details\n");
	printf("The parent values\n");
	int j;
	for (j = 1; j<4; j++)
	{
		parent.value[j - 1] = min(lp[j].sid);
		printf(" %d ", parent.value[j - 1]);
	}
	printf("\nThe chilren values\n");
	for (i = 1; i <= 4; i++){
		parent.children[i - 1] = (i - 1)*PAGE_SIZE;
		printf(" %d ", parent.children[i - 1]);
	}
	_getch();
	fclose(fp);
	return 0;
}


