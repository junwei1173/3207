#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5000

void generateRandomArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000; 
    }
}

void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n"); 
        }
    }
}

int main() {
    int arr[SIZE];
    clock_t start, end;
    double elapsed_time;

    srand(time(NULL));

    generateRandomArray(arr, SIZE);
    start = clock();
    
    bubbleSort(arr, SIZE);

    end = clock();
 
    elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nSorted array with 5000 integers:\n");
    printArray(arr, SIZE);

    printf("\nTime taken to sort the array: %.5f seconds\n", elapsed_time);

    return 0;
}
