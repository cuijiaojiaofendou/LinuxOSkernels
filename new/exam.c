/*查看进程的虚存地址*/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int i;
	unsigned char *buf;
	
	buf = (char *)malloc(sizeof(char)*1024);
	printf("My pid is:%d\n", getpid());
	
	for (i = 0; i < 60; i++){
		sleep(60);
	}

	return 0;
}
