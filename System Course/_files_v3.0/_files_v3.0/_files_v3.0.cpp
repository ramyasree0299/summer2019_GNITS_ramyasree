#include "stdafx.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
/*#define DISK_SIZE (100*1024*1024)
#define BLOCK_SIZE (16*1024)
#define BLOCKS(size) ((size/BLOCK_SIZE)+(!!(size%BLOCK_SIZE)))
#define START_FILE_OFFSET (2*BLOCK_SIZE+1)
#define ARRAY_OFFSET (BLOCK_SIZE+1)
#define META_OFFSET (12+1)
#define CHECKER (0x444E524D)
#define FILES (32)*/
#define META_DATA_SIZE 32
#define DISK_SIZE 100000000
#define NO_OF_FILES 32
#define config_blocksize 16000
#define NO_OF_BLOCKS 6400

struct MetaData
{
	char name[20];
	int size;
	int blocks;
	int start_block[100];
};
struct InitData
{
	int magic_number;
	int block_size;
	int no_of_blocks;
	int no_of_empty_blocks;
	int no_of_files;
	char ByteVector[NO_OF_BLOCKS];
	struct MetaData metadata[NO_OF_FILES];
};
void read_block(void *buffer, int block_number)
{
	FILE *hard_disk = fopen("hardDisk.hdd", "rb");
	if (hard_disk == NULL)
	{
		printf("Error\n");
		return;
	}
	fseek(hard_disk, block_number*config_blocksize, SEEK_CUR);
	fread(buffer, 1, config_blocksize, hard_disk);
	fclose(hard_disk);
}
void write_block(void *buffer, int block_number)
{
	FILE *hard_disk = fopen("hardDisk.hdd", "rb+");//ptogram has triggered a breakpoint
	if (hard_disk == NULL)
	{
		printf("Error occured\n");
		return;
	}
	fseek(hard_disk, block_number*config_blocksize, SEEK_SET);
	fwrite(buffer, 1, config_blocksize, hard_disk);
	fclose(hard_disk);
}

void mount(char *filename)
{
	//filename is harddisk
	int block_size = config_blocksize;
	//int no_of_blocks = (DISK_SIZE / config_blocksize) + 1;
	struct InitData *initdata = (struct InitData *)malloc(sizeof(struct InitData));
	initdata->magic_number = 0x444E524D;//bug here access vioaltion error
	initdata->block_size = block_size;
	initdata->no_of_blocks = NO_OF_BLOCKS;
	initdata->no_of_empty_blocks = NO_OF_BLOCKS;
	initdata->no_of_files = 0;
	for (int i = 0; i < NO_OF_BLOCKS; i++)
		initdata->ByteVector[i] = '0';
	for (int i = 0; i < NO_OF_FILES; i++)
	{
		strcpy(initdata->metadata[i].name, "\0");
		initdata->metadata[i].size = 0;
		initdata->metadata[i].blocks = 0;
		for (int j = 0; j < 100; j++)
			initdata->metadata[i].start_block[j] = 0;
	}
	
	write_block((void *)initdata, 0);
}

int calculate_size(char *filename)
{
	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Error reading a file\n");
		return 0;
	}
	int i=0;
	char c;
	while (fread(&c, 1, 1, fp) != -1 && !feof(fp))
		i++;
	return i;
}
void copyfromFS(char *filename)
{
	void *initdata_buffer = malloc(config_blocksize);
	read_block(initdata_buffer, 0);
	struct InitData *initdata = (struct InitData *)malloc(sizeof(struct InitData));
	//access to the buffer code comes here
	memcpy(initdata, initdata_buffer, sizeof(struct InitData));
	FILE *sfp = fopen(filename, "r");
	char *initData = (char *)malloc(36 * sizeof(char));
	int filesize = calculate_size(filename);
	int start_block;
	int no_of_blocks_req = 0;
	if (filesize!=0)
	no_of_blocks_req = (config_blocksize / filesize) + 1;
	else
	{
		printf("Filesize is zero");
		return;
	}
	int i;
	for (i = 0; i < NO_OF_BLOCKS; i++)
	{
		if (initdata->ByteVector[i] == '0')
			break;
	}
	if (i < NO_OF_BLOCKS)
		start_block = i;
	else {
		printf("No blocks are free to copy from file system\n");
		return;
	}
	initdata->ByteVector[start_block] = '1';
	int count = 1;
	int block[NO_OF_BLOCKS];
	block[0] = start_block;
	int k = 1;
	int l;
	for (int i = 0; i < NO_OF_BLOCKS; i++)
	{
		if (initdata->ByteVector[i] == '0')
		{
			block[k] = i;
			k++;
			count++;
		}
		if (count == no_of_blocks_req)
		{
			l = k;
			k = 0;
			for (k = 0; k < l; k++)
				initdata->ByteVector[block[k]] = '1';
			break;
		}
	}
	if (count != no_of_blocks_req)
	{
		initdata->ByteVector[start_block] = '0';
		printf("sufficient blocks not found\n");
		return;
	}
	void *buffer = malloc(config_blocksize);
	initdata->no_of_empty_blocks = initdata->no_of_empty_blocks - l;
	initdata->no_of_files = initdata->no_of_files + 1;
	//memcpy(buffer, initdata, sizeof(struct InitData));
	strcpy(initdata->metadata[initdata->no_of_files].name, filename);
	initdata->metadata[initdata->no_of_files].size = filesize;
	initdata->metadata[initdata->no_of_files].blocks = no_of_blocks_req;
	for (int i = 0; i < l; i++)
	{
		initdata->metadata[initdata->no_of_files].start_block[i] = block[i];
	}
	write_block(initdata, 0);
	k = 0;
	//file contents arrray created
	i = 0;
	int buffer_size;
	void *fileBuffer;
	char *file_char_buffer = (char *)malloc(filesize*sizeof(char));
	//write code for writing file data in the disk
	while (i < no_of_blocks_req)
	{
		if (filesize > config_blocksize)
			buffer_size = config_blocksize;
		else buffer_size = filesize;
		fileBuffer = malloc(buffer_size);
		fread(file_char_buffer, buffer_size, 1, sfp);
		write_block(file_char_buffer, i);
		filesize -= buffer_size;
		i++;
	}

	fclose(sfp);
}

void copytofs(char *filename)
{
	int i;
	struct InitData *initdata=(struct InitData*)malloc(sizeof(struct InitData));
	read_block(initdata, 0);
	if (initdata)
		printf("error reading initdata_buffer in operation copytofs\n");
	for (i = 0; i < initdata->no_of_files; i++)
	{
		if (strcmp(filename, initdata->metadata[i].name) == 0)
			break;
	}
	int index = i;
	printf("%d %d %d %d", initdata->block_size, initdata->no_of_blocks, initdata->no_of_empty_blocks, initdata->no_of_files);
	int filesize = calculate_size(initdata->metadata[index].name);
	FILE *fp = fopen(filename, "w");
	if (fp == NULL)
	{
		printf("file not found");
		return ;
	}
	int buffer_size;
	char *file_char_buffer = (char *)malloc(filesize*sizeof(char));
	while (i < initdata->no_of_blocks)
	{
		if (filesize > config_blocksize)
			buffer_size = config_blocksize;
		else buffer_size = filesize;
		read_block(file_char_buffer, i);
		fwrite(file_char_buffer, buffer_size, 1, fp);
		filesize -= buffer_size;
		i++;
	}
	fclose(fp);
}
void format()
{
	FILE *fp;
	unsigned int n = 0x444E524D;
	fp = fopen("hardDisk.hdd", "rb");
	if (fp == NULL)
	{
		printf("Error opening a file\n");
		return;
	}
	void *buffer = malloc(config_blocksize);
	read_block(buffer, 0);
	unsigned int temp;
	memcpy(&temp, buffer, 4);
	if (temp == n)
	{
		fwrite(&n, 1, 1, fp);
		fclose(fp);
		printf("file format successful\n");
	}
	else printf("Failed to format\n");

}
void list()
{
	void *initdata_buffer = malloc(config_blocksize);
	read_block(initdata_buffer, 0);
	if (initdata_buffer)
		printf("error reading initdata_buffer in operation list\n");
	struct InitData *initdata = (struct InitData *)malloc(sizeof(struct InitData));
	//access to the buffer code comes here
	memcpy(initdata, initdata_buffer, sizeof(struct InitData));
	for (int i = 0; i < initdata->no_of_files; i++)
	{
		printf("%s ", initdata->metadata[i].name);
	}

}
void debug()
{
	void *initdata_buffer = malloc(config_blocksize);
	read_block(initdata_buffer, 0);
	if (initdata_buffer)
		printf("error reading initdata_buffer in operation debug\n");
	struct InitData *initdata = (struct InitData *)malloc(sizeof(struct InitData));
	//access to the buffer code comes here
	memcpy(initdata, initdata_buffer, sizeof(struct InitData));//loaded data from the disk.
	printf("The total block size is\n", initdata->block_size);
	printf("The total number of blocks\n", initdata->no_of_blocks);
	printf("The total number available blocks\n", NO_OF_FILES - initdata->no_of_empty_blocks);
	printf("The total number empty blocks\n", initdata->no_of_empty_blocks);
	for (int i = 0; i < initdata->no_of_files; i++)
		printf("%s ", initdata->metadata[i].name);
}
void delete_data()
{
	//R:to be written 
}
void exit_command()
{
	exit(0);
}
int main()
{
	printf(">");
	while (1)
	{
		char command[100];
		fgets(command, 100, stdin);
		char operation[50], argument1[20], argument2[20];
		sscanf(command, "%s %s %s", operation, argument1, argument2);
		if (_stricmp(operation, "mount") == 0)
		{
			mount(argument1);
		}
		else if (_stricmp(operation, "copytofs") == 0)
		{
			copytofs(argument1);
		}
		else if (_stricmp(operation, "copyfromfs") == 0)
		{
			copyfromFS(argument1);
		}
		else if (_stricmp(operation, "format") == 0)
		{
			list();
		}
		else if (_stricmp(operation, "ls") == 0)
		{

		}
		else if (_stricmp(operation, "delete") == 0)
		{
			delete_data();
		}
		else if (_stricmp(operation, "debug") == 0)
		{
			debug();
		}
		else if (_stricmp(operation, "unmount") == 0)
		{

		}
		else if (_stricmp(operation, "exit") == 0)
		{
			exit(0);
		}
		printf(">");
	}
return 0;
}


