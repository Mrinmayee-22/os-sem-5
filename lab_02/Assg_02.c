#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>

void bubbleSortAscending(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void bubbleSortDescending(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            if (arr[j] < arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void forksort(int arr[], int n)
{
if (fork() == 0) 
{
bubbleSortAscending(arr, n);
printf("Child process: \n");
} 
else {
bubbleSortDescending(arr, n);
printf("Parent process: \n");
}
for(int i=0; i<n; i++)
{
printf("%d ", arr[i]);
}
printf("\n");
}

int main()
{
int n;
printf("Enter the size of the array: ");
scanf("%d", &n);
int arr[n];
for(int i = 0; i<n; i++)
{
printf("Enter a number: ");
scanf("%d", &arr[i]);
}

printf("Original array: \n");
for(int i=0; i<n; i++)
{
printf("%d ", arr[i]);
}
printf("\n");
forksort(arr, n);

return 0;
}
