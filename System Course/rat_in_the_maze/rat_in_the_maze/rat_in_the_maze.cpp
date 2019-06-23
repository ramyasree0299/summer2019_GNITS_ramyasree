// rat_in_the_maze.cpp : Defines the entry point for the console application.
//




#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
struct Maze_block
{
	int path;
	int visited;
};
void find_path(struct Maze_block  maze[20][20], int row_size, int column_size, int row, int column, int* count, int endi, int endj, int solution[20][20])
{
	if (row == endi && column == endj)
	{
		printf("Path exists\n");
		*count = *count + 1;
		return;
	}
	if (column + 1 < row_size && maze && maze[row][column + 1].path == 1 && maze[row][column + 1].visited == 0)
	{
		printf("%d %d\n", row, column + 1);
		solution[row][column + 1] = 1;
		maze[row][column + 1].visited = 1;
		find_path(maze, row_size, column_size, row, column + 1, count, endi, endj, solution);
	}
	if (row + 1 <column_size && maze[row + 1][column].path == 1 && maze[row + 1][column].visited == 0)
	{
		printf("%d %d\n", row + 1, column);
		solution[row + 1][column] = 1;
		maze[row + 1][column].visited = 1;
		find_path(maze, row_size, column_size, row + 1, column, count, endi, endj, solution);
	}
	if (column - 1 >= 0 && maze[row][column - 1].path == 1 && maze[row][column - 1].visited == 0)
	{
		printf("%d %d\n", row, column - 1);
		solution[row][column - 1] = 1;
		maze[row][column - 1].visited = 1;
		find_path(maze, row_size, column_size, row, column - 1, count, endi, endj, solution);
	}
	if (row - 1 >= 0 && maze[row - 1][column].path == 1 && maze[row - 1][column].visited == 0)
	{
		printf("%d %d\n", row - 1, column);
		solution[row - 1][column] = 1;
		maze[row - 1][column].visited = 1;
		find_path(maze, row_size, column_size, row - 1, column, count, endi, endj, solution);
	}
}
void solve(struct Maze_block maze[20][20], int si, int sj, int ei, int ej, int m, int n, int solution[20][20])
{
	int count = 0;
	find_path(maze, m, n, si, sj, &count, ei, ej, solution);
	if (count == 0)
		printf("Path doesn't exists");
	return;
}
int main()
{
	struct Maze_block maze[20][20];
	int row_size, column_size;
	printf("Enter the row and column sizes\n");
	scanf_s("%d %d", &row_size, &column_size);
	int ei, ej, si, sj;
	printf("Enter start index i ,start index j,end index i,end index j\n");
	scanf_s("%d %d %d %d", &si, &sj, &ei, &ej);
	printf("enter the maze\n");
	int i, j;
	for (i = 0; i < row_size; i++)
		for (j = 0; j < column_size; j++)
		{
			scanf_s("%d", &maze[i][j].path);
			maze[i][j].visited = 0;
		}
	int solution[20][20];
	for (i = 0; i < row_size; i++)
		for (j = 0; j < column_size; j++)
			solution[i][j] = 0;
	printf("the path\n");
	solve(maze, si, sj, ei, ej, row_size, column_size, solution);
	_getch();
	return 0;
}

