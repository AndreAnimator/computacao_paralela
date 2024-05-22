#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000

void selectionSort(int array[], int size){
    int i, j, min, aux;

    for(i = 0; i < size-1; i++){
        min = i;

        for(j = i+1; j < size; j++){
            if(array[j] < array[min])
                min = j;
        }
        
        if (min != i) {
            aux = array[i];
            array[i] = array[min];
            array[min] = aux;
        }
    }
}

int main(){
    int array[SIZE];
    
    srand(time(NULL));

    for(int i = 0; i < SIZE; i++){
        array[i] = rand()%SIZE;
    }

    clock_t start = clock();
    selectionSort(array, SIZE);
    clock_t finish = clock();

    double time_spent = (double)(finish - start)/CLOCKS_PER_SEC;
	printf("Time spent: %f\n", time_spent);
    return 0;
}