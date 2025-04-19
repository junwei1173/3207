#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000  // Adjust matrix size as needed

// Function to allocate memory for a matrix
int **allocateMatrix() {
    int **matrix = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
        matrix[i] = (int *)malloc(N * sizeof(int));
    return matrix;
}

// Function to free allocated matrix memory
void freeMatrix(int **matrix) {
    for (int i = 0; i < N; i++)
        free(matrix[i]);
    free(matrix);
}

// Function to initialize a matrix with random values
void fillMatrix(int **matrix) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            matrix[i][j] = rand() % 10;
}

// Function to measure time in seconds
double getTimeElapsed(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

// Matrix multiplication with (i, j, k) order
void multiply_ijk(int **A, int **B, int **C) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
        }

    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Time for ijk: %.6f seconds\n", getTimeElapsed(start, end));
}

// Matrix multiplication with (i, k, j) order
void multiply_ikj(int **A, int **B, int **C) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int i = 0; i < N; i++)
        for (int k = 0; k < N; k++)
            for (int j = 0; j < N; j++)
                C[i][j] += A[i][k] * B[k][j];

    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Time for ikj: %.6f seconds\n", getTimeElapsed(start, end));
}

// Matrix multiplication with (j, i, k) order
void multiply_jik(int **A, int **B, int **C) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int j = 0; j < N; j++)
        for (int i = 0; i < N; i++) {
            C[i][j] = 0;
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];
        }

    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Time for jik: %.6f seconds\n", getTimeElapsed(start, end));
}

// Matrix multiplication with (j, k, i) order
void multiply_jki(int **A, int **B, int **C) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int j = 0; j < N; j++)
        for (int k = 0; k < N; k++)
            for (int i = 0; i < N; i++)
                C[i][j] += A[i][k] * B[k][j];

    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Time for jki: %.6f seconds\n", getTimeElapsed(start, end));
}

// Matrix multiplication with (k, i, j) order
void multiply_kij(int **A, int **B, int **C) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int k = 0; k < N; k++)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                C[i][j] += A[i][k] * B[k][j];

    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Time for kij: %.6f seconds\n", getTimeElapsed(start, end));
}

// Matrix multiplication with (k, j, i) order
void multiply_kji(int **A, int **B, int **C) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (int k = 0; k < N; k++)
        for (int j = 0; j < N; j++)
            for (int i = 0; i < N; i++)
                C[i][j] += A[i][k] * B[k][j];

    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("Time for kji: %.6f seconds\n", getTimeElapsed(start, end));
}

// Main function
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <loop-order>\n", argv[0]);
        return 1;
    }

    int **A = allocateMatrix();
    int **B = allocateMatrix();
    int **C = allocateMatrix();
    
    srand(time(NULL));
    fillMatrix(A);
    fillMatrix(B);

    // Choose the multiplication order based on command-line argument
    char order = argv[1][0];

    switch (order) {
        case '1': multiply_ijk(A, B, C); break;
        case '2': multiply_ikj(A, B, C); break;
        case '3': multiply_jik(A, B, C); break;
        case '4': multiply_jki(A, B, C); break;
        case '5': multiply_kij(A, B, C); break;
        case '6': multiply_kji(A, B, C); break;
        default:
            printf("Invalid order. Use 1-6 to select loop ordering.\n");
            return 1;
    }

    freeMatrix(A);
    freeMatrix(B);
    freeMatrix(C);

    return 0;
}
