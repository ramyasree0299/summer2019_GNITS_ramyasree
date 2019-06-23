#include "stdafx.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

void op_push(char ch, char *stack, int top)
{
	top = top + 1;
	stack[top] = ch;
}

void var_push(int ch, int *stack, int top)
{
	top++;
	stack[top] = ch;
}


int ifOperator(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		return 1;
	else
		return 0;
}

int Prec(char ch)
{
	switch (ch)
	{
	case '+':
	case '-':
		return 1;

	case '*':
	case '/':
		return 2;

	case '^':
		return 3;
	}
	return -1;
}

char op_peek(char *stack, int op_top)
{
	return stack[op_top];
}


int var_peek(int *stack, int top)
{
	return stack[top];
}


int operation(int a, int b, char op)
{
	int val = 0;
	switch (op)
	{
	case '*':
		val = b * a;
		break;

	case '/':
		val = b / a;
		break;
	case '+':
		val = b + a;
		break;
	case '-':
		val = b - a;
		break;
	}
	return val;
}


int var_pop(int *stack, int top)
{
	int item;
	item = stack[top];
	return item;
}

int getValue(char *s)
{
	
	int i = 0, j, res = 0;
	for (i = 0; i < strlen(s); i++)
	{
		if (!isdigit(s[i]))
		{
			break;
		}
	}
	if (i == strlen(s))
	{
		for (j = 0; j < strlen(s); j++)
		{
			res = (res * 10) + s[j] - '0';
		}
		return res;
	}

}

char op_pop(char *stack, int top)
{
	return stack[top];
}


int evalinfix(char *infix, int *var_stack, int var_top, char op_stack[20], int op_top)
{
	int result = 0;
	int i = 0, a, b;
	for (i = 0; i < strlen(infix);)
	{
		if (ifOperator(infix[i]))
		{
			while (op_top >= 0 && Prec(infix[i]) <= Prec(op_peek(op_stack, op_top)))
			{
				a = var_pop(var_stack, var_top);
				var_top--;
				b = var_pop(var_stack, var_top);
				var_top--;
				var_push(operation(a, b, op_pop(op_stack, op_top)), var_stack, var_top);
				op_top--;
				var_top++;
			}
			op_push(infix[i], op_stack, op_top);
			op_top++;
			i++;
		}
		else if (infix[i] == '(')
		{
			op_push('(', op_stack, op_top);
			op_top++;
			i++;
		}
		else if (infix[i] == ')')
		{
			while (op_top>0 && op_peek(op_stack, op_top) != '(')
			{
				a = var_pop(var_stack, var_top);
				var_top--;
				b = var_pop(var_stack, var_top);
				var_top--;
				var_push(operation(a, b, op_pop(op_stack, op_top)), var_stack, var_top);
				op_top--;
				var_top++;//exp[++k] = pop(stack);
			}
			if (op_top > 0 && op_peek(op_stack, op_top) != '(')
				return -1;
			else
			{
				op_pop(op_stack, op_top);
				op_top--;
			}i++;
		}
		else
		{
			char pos = 0, s[10];
			while (!ifOperator(infix[i]) && infix[i] != '\0' && infix[i] != '(' && infix[i] != ')')
			{
				s[pos++] = infix[i];
				i++;
				s[pos] = '\0';
			}
			var_push(getValue(s), var_stack, var_top);
			var_top++;

		}
	}
	while (op_top > -1)
	{
		a = var_pop(var_stack, var_top);
		var_top--;
		b = var_pop(var_stack, var_top);
		var_top--;
		var_push(operation(a, b, op_pop(op_stack, op_top)), var_stack, var_top);
		op_top--;
		var_top++;
	}
	return var_stack[var_top];
}

int getRes(char *forum)
{
	int var_top = -1;
	int op_top = -1;
	int var_stack[100];
	char op_stack[100];
	int res = evalinfix(forum, var_stack, var_top, op_stack, op_top);
	if (res != -1)
		return res;
}