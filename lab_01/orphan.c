#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
int pid = fork();
if(pid>0)
{
printf("parent process id: %d\n", getpid());
printf("child process id: %d\n", pid);
}
else if(pid == 0)
{
sleep(5);
printf("\nchild process id: %d\n", getpid());
printf("parent process id: %d\n", getppid());
}
return 0;
}
