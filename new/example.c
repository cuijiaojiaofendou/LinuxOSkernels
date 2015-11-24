#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>

int bss_var;
int data_var0 = 0;

int main(int argc, char *argv[])
{
	printf("blow are address of types of process's mem\n");
	printf("Text location\n");\
	printf("\tAddress of main(CodeSegment):%p\n", main);
	printf("------------------------------------------\n");

	int stack_var0 = 2;
	printf("Stack Location\n");
	printf("\tInitial end of stack:%p\n", &stack_var0);
	
	int stack_var1 = 3;
	printf("\tnew end of stack:%p\n", &stack_var1);
	
	printf("------------------------------------------\n");
	printf("Data Location\n");
	printf("\tAddress of data_var(Data Segment):%p\n", &data_var0);
	
	static int data_var1 = 4;
	printf("\tNew end of data_var(Data Segment):%p\n", &data_var1);
	
	printf("------------------------------------------\n");
	printf("BSS Location\n");
	printf("\tAddress of bss_var:%p\n", &bss_var);
	
	printf("------------------------------------------\n");
	char *b = sbrk((ptrdiff_t)0);
	printf("Heap Location\n");
	printf("\tInitial end of heap:%p\n", b);
	
	brk(b+4);
	b = sbrk((ptrdiff_t)0);
	printf("\tNew end of Heap:%p\n", b); 
	return 0;
}
