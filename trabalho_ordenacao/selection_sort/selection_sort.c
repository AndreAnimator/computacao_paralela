#include <stdio.h>

void selectionSort(int array[], int size){
    int i, j, min, aux;

    for(i = 0; i < size-1; i++){
        min = i;

        for(j = i+1; j < size; j++){
            if(array[j] < array[min])
                min = j;
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