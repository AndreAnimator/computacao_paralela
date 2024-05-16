/*
Sugestão: tentar implementar bubble sort par e impar:

rank = process_id();
A = initial_value();
for (i = 0; i < N; i++)
{
    if (i % 2 == 0)
    { // even phase
        if (rank % 2 == 0)
        { // even process
            recv(B, rank + 1); send(A, rank + 1);
            A = min(A,B);
        } else
        { // odd process
            send(A, rank - 1); recv(B, rank - 1);
            A = max(A,B);
        }
    }
    else if (rank > 0 && rank < N - 1)
    { // odd phase
        if (rank % 2 == 0)
        { // even process
            recv(B, rank - 1); send(A, rank - 1);
            A = max(A,B);
        } else
        { // odd process
            send(A, rank + 1); recv(B, rank + 1);
            A = min(A,B);
        }
    }
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define NUM_THREADS 2
#define ARRAY_MAX_SIZE 50
double step;
static long num_steps = 100000;

void swap(int* arr, int i, int j)
{
	int temp = arr[i];
	arr[i] = arr[j];
	arr[j] = temp;
}

void bubbleSort(int arr[], int n)
{
	int i, j;
	for(i = 0; i < n - 1; i++)
        #pragma omp parallel for default(none),shared(arr, i, n)
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1])
				swap(arr, j, j + 1);
/*
    for (i = 0; i < n; i++)
    {
        if (i % 2 == 0)
        { // even phase
            if (rank % 2 == 0)
            { // even process
                recv(B, rank + 1); send(A, rank + 1);
                A = min(A,B);
            } else
            { // odd process
                send(A, rank - 1); recv(B, rank - 1);
                A = max(A,B);
            }
        }
        else if (rank > 0 && rank < n-1)
        { // odd phase
            if (rank % 2 == 0)
            { // even process
                recv(B, rank - 1); send(A, rank - 1);
                A = max(A,B);
            } else
            { // odd process
                send(A, rank + 1); recv(B, rank + 1);
                A = min(A,B);
            }
        }
    }*/
}

void printArray(int arr[], int size)
{
	int i;
	for(i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

int main()
{
    int arr[ARRAY_MAX_SIZE];
    for(int i = 0; i < ARRAY_MAX_SIZE; i++)
    {
        arr[i] = rand()%ARRAY_MAX_SIZE;
    }
    int N = sizeof(arr) / sizeof(arr[0]);
    printf("tamanho do vetor: %d\n", N);
    clock_t start = clock();
    //#pragma omp parallel
    //{
    bubbleSort(arr, N);
    //}

    clock_t finish = clock();
    printf("Sorted array: ");
    printArray(arr, N);
    double time_spent = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("Time spent: %f\n", time_spent);
	return 0;
}