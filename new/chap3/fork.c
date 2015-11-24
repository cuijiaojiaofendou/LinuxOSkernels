#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
int main(int argc,char *argv[])
{
	pid_t pid;
	char cmd;
	char *arg_psa[]={"ps","-a",NULL};
	char *arg_psx[]={"ps","-x",NULL};
	while(1)
	{
		printf("输入a执行'ps -a'命令\n");
		printf("输入q执行'ps -x'命令\n");
		printf("输入q退出\n");
		cmd=getchar();
		getchar();
		if((pid=fork())<0)
		{
			perror("fork error:");
			return -1;
		}
		//进程创建成功
		if(pid==0)
		{
			switch(cmd)
			{
				case'a':execve("/bin/ps",arg_psa,NULL);
					 break;
				case'x':execve("/bin/ps",arg_psx,NULL);
					 break;
				case'q':break;
				default:perror("wrong cmd\n");
					break;	
			}
			exit(0);
		}
		else if(pid>0)//父进程
		{
			if(cmd=='q')
			break;
		}
	}//退出循环
	while(waitpid(-1,NULL,WNOHANG)>0)//父进程等待回收子进程
	return 0;
}
