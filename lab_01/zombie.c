#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main(void)
{
pid_t pid;
if((pid=fork())<0)
	printf("\t fork error\n");
else
{
if(pid==0)
	printf("child process id is %d\n", getpid());
else
{
	sleep(5);
	printf("****parent\n");
	system("ps -axj | tail");
}
}
exit(0);
}
