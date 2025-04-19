#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5000
#define HALF_SIZE (SIZE / 2)

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

void mergeSortedArrays(int arr1[], int size1, int arr2[], int size2, int merged[]) {
    int i = 0, j = 0, k = 0;

    while (i < size1 && j < size2) {
        if (arr1[i] < arr2[j]) {
            merged[k++] = arr1[i++];
        } else {
            merged[k++] = arr2[j++];
        }
    }
    while (i < size1) {
        merged[k++] = arr1[i++];
    }
    while (j < size2) {
        merged[k++] = arr2[j++];
    }
}

void saveToFile(const char *filename, int arr[], int size) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d\n", arr[i]);
    }
    fclose(file);
}

int compareFiles(const char *file1, const char *file2) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    if (!f1 || !f2) {
        printf("Error opening files for comparison.\n");
        return 0;
    }
    
    int num1, num2;
    while (fscanf(f1, "%d", &num1) == 1 && fscanf(f2, "%d", &num2) == 1) {
        if (num1 != num2) {
            fclose(f1);
            fclose(f2);
            return 0; // Files are different
        }
    }
    
    int end1 = fscanf(f1, "%d", &num1);
    int end2 = fscanf(f2, "%d", &num2);
    
    fclose(f1);
    fclose(f2);
    
    return end1 == end2; // Ensure both files reached EOF together
}

int main() {
    int arr[SIZE], arr1[HALF_SIZE], arr2[HALF_SIZE], merged[SIZE];
    clock_t start, end;
    double elapsed_time1, elapsed_time2, elapsed_merge;

    srand(time(NULL));

    generateRandomArray(arr, SIZE);

    // Copy first and second halves
    for (int i = 0; i < HALF_SIZE; i++) {
        arr1[i] = arr[i];
        arr2[i] = arr[i + HALF_SIZE];
    }

    // Sort entire array normally for reference
    int reference_arr[SIZE];
    for (int i = 0; i < SIZE; i++) {
        reference_arr[i] = arr[i];
    }
    
    start = clock();
    bubbleSort(reference_arr, SIZE);
    end = clock();
    elapsed_time1 = ((double)(end - start)) / CLOCKS_PER_SEC;
    saveToFile("sorted_full.txt", reference_arr, SIZE);

    // Sort both halves separately
    start = clock();
    bubbleSort(arr1, HALF_SIZE);
    bubbleSort(arr2, HALF_SIZE);
    end = clock();
    elapsed_time2 = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Merge the sorted halves
    start = clock();
    mergeSortedArrays(arr1, HALF_SIZE, arr2, HALF_SIZE, merged);
    end = clock();
    elapsed_merge = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    saveToFile("sorted_output.txt", merged, SIZE);

    // Compare the two output files
    int identical = compareFiles("sorted_full.txt", "sorted_output.txt");

    // Print results
    printf("\nSorted array with original method:\n");
    printf("Time taken for full sorting: %.5f seconds\n", elapsed_time1);

    printf("\nSorted array using split-then-merge method:\n");
    printf("Time taken for sorting halves: %.5f seconds\n", elapsed_time2);
    printf("Time taken for merging: %.5f seconds\n", elapsed_merge);
    printf("Total time (split-then-merge): %.5f seconds\n", elapsed_time2 + elapsed_merge);

    if (identical) {
        printf("\nThe two sorted outputs are IDENTICAL.\n");
    } else {
        printf("\nThe two sorted outputs are DIFFERENT.\n");
    }

    return 0;
}
