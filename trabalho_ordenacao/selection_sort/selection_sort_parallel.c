#include <stdio.h>
#include <omp.h>

void selectionSort(int array[], int size){
    int i, j, min, min_local, aux;

    for(i = 0; i < size-1; i++){
        min = i;
        #pragma omp parallel default(shared) private(j, min_local)
        {   
            printf("%d\n",omp_get_num_threads());
            min_local = i;
            #pragma omp for
            for(j = i+1; j < size; j++){
                if(array[j] < array[min_local]){
                    min_local = j;
                }
            }
            #pragma omp barrierçu99
            if(array[min_local] < array[min]) {
                min = min_local;
            }
        }

        aux = array[i];
        array[i] = array[j];
        array[j] = aux;
    }
}

int main(){
    int array[5] = {2, 9, 8, 56, 24};
    selectionSort(array, 5);
    for(int i = 0; i < 5; i++){
        printf("%d ", array[i]);
    }
}