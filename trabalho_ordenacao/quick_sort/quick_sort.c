#include<stdio.h>
#include<omp.h>
#include<math.h>
#include <stdlib.h>

#define ARRAY_MAX_SIZE 50

int arr[ARRAY_MAX_SIZE];


void swap(int* a, int* b)
{
	int t = *a;
	*a = *b;
	*b = t;
}

int partition (int arr[], int low, int high)
{
	int pivot = arr[high];
	int i = (low - 1);
	for(int j = low; j <= high- 1; j++)
	{
		if (arr[j] <= pivot)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);

        //As I capture each task,  its going to look at the value of  arr , low, pi at that point and
        // it will create a private values for that variables and its going to initialize it the current values.
        //So each task will be execute its own copy.

		#pragma omp task firstprivate(arr,low,pi)
		{
			quickSort(arr,low, pi - 1);

		}

		#pragma omp task firstprivate(arr, high,pi)
		{
			quickSort(arr, pi + 1, high);
		}
	}
}

void printArray(int arr[], int size)
{
	int i;
	for (i=0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

int main()
{


	double start_time, run_time;
	for(int i = 0; i < ARRAY_MAX_SIZE; i++)
    {
       arr[i] = rand()%ARRAY_MAX_SIZE;
    }
	int n = sizeof(arr)/sizeof(arr[0]);

    omp_set_num_threads(8);
    start_time = omp_get_wtime();

    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int nthrds = omp_get_num_threads();
        printf("Thread is %d\n",id);
        
        #pragma omp single nowait
        quickSort(arr, 0, n-1);
    }

	quickSort(arr,0,n-1);
	run_time = omp_get_wtime() - start_time;
	printf("\n Execution time was %lf seconds\n ",run_time);
	printf("Sorted array: \n");
	printArray(arr, n);
    printf("\n");
	return 0;
}