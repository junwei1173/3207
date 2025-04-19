#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5

void generateRandomArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100; // Smaller range for easier verification
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
    }
    printf("\n");
}

int main() {
    int arr[SIZE];
    srand(time(NULL));

    // Generate the random array
    generateRandomArray(arr, SIZE);

    // Print the unsorted array
    printf("Unsorted array:\n");
    printArray(arr, SIZE);

    // Record the start time
    clock_t start = clock();

    // Perform the bubble sort
    bubbleSort(arr, SIZE);

    // Record the end time
    clock_t end = clock();

    // Calculate the elapsed time in seconds
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;

    // Print the sorted array
    printf("\nSorted array:\n");
    printArray(arr, SIZE);

    // Print the elapsed time
    printf("\nTotal elapsed time for sorting: %.6f seconds\n", elapsed_time);

    return 0;
}
