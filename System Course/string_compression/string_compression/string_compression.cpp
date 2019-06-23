#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
void compress(char *str)
{
	int k, i, j = 0, count = 0;
	for (i = 0; i < strlen(str); i++, j++)
	{
		str[j] = str[i];
		count = 1;
		while (str[i] == str[i + 1])
		{
			count += 1;
			i += 1;
		}
		if (count != 1)
		{
			char* temp = (char *)calloc(100, sizeof(char));
			sprintf(temp, "%d", count);
			for (k = 0; temp[k] != '\0'; k++)
			{
				j += 1;
				str[j] = temp[k];
			}
		}
	}
	str[j] = '\0';
	puts("after compression : ");
	puts(str);

}

int main()
{
	char *str = (char *)malloc(100 * sizeof(char));
	strcpy(str, "abc");
	puts("given string:");
	puts(str);
	compress(str);
	strcpy(str, "aaaabbccc");
	puts("given string:");
	puts(str);
	compress(str);
	strcpy(str, "aaaaaaaaaaaaabccc");
	puts("given string:");
	puts(str);
	compress(str);
	getchar();
	return 0;
}