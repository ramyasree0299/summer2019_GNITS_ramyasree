#define MAX_MEMORY_SIZE 100
struct symbol_table
{
	char name;
	int size;
	int address;
	struct symbol_table* next;
};
struct Memory
{
	int address[MAX_MEMORY_SIZE];
	int next_index;
}memory;
enum commands{ MOV1 = 1, MOV2, ADD, SUB, MUL, JMP, IF, EQ, LT, GT, LTEQ, GTEQ, PRINT, READ };
void print(char arguments[50], struct symbol_table *table_head, char *filename);
void read(char arguments[30], struct symbol_table *table_head, char *filename);
void add(char arguments[30], struct symbol_table *table_head, char *filename);
void sub(char arguments[30], struct symbol_table *table_head, char *filename);
struct symbol_table* data(char arguments[50], struct symbol_table *table_head);
void mov(char arguments[50], struct symbol_table *table_head, char *filename);
struct symbol_table* constant(char arguments[50], struct symbol_table *table_head);
