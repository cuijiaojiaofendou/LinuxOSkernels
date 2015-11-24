// =====================================================================================
// 
//       Filename:  1.c
//
//    Description:  系统调用和内核函数
//
//        Version:  1.0
//        Created:  2015年06月15日 16时41分25秒
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Striver (CuiJiaojiao), cuijiaojiao@xiyoulinux.org
//        Company:  Class 1204 of Software Engineering
// 
// =====================================================================================

#include <syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int main(void){
	long id1, id2;

	//直接调用内核函数
	id1 = syscall(SYS_getpid);
	printf("syscall(SYS_getpid) = %ld\n", id1);

	//调用系统调用
	id2 = getpid();
	printf("getpid() = %ld\n", id2);

	return 0;
}
