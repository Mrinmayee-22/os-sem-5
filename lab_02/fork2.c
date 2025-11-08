//odd or even number using fork

#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>

void forkexample(int num)
{
if(fork()==0)
{
if(num%2 == 0)
{
printf("Hello from Child!\n");
printf("Even number");
}
}
else
{
if(num%2 == 1)
{
printf("Hello from Parent!\n");
printf("Odd number\n");
}
}
}
int main()
{
int num;
printf("Enter a number: ");
scanf("%d", &num);
forkexample(num);
return 0;
}
