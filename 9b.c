#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int find_closest(int num, int arr[], int size) {
    int minDiff = abs(arr[0] - num);
    int closest = arr[0];
    
    for (int i = 1; i < size; i++) {
        int diff = abs(arr[i] - num);
        if (diff < minDiff) {
            minDiff = diff;
            closest = arr[i];
        }
    }
    
    return closest;
}

int* generate_array(int size, int minValue, int maxValue) {
    int* arr = (int*)malloc(size * sizeof(int));
    
    for (int i = 0; i < size; i++) {
        arr[i] = minValue + rand() % (maxValue - minValue + 1);
    }
    
    return arr;
}

int* apply_operation(int arrA[], int arrB[], int size) {
    int* arrC = (int*)malloc(size * sizeof(int));
    
    for (int i = 0; i < size; i++) {
        int closest = find_closest(arrA[i], arrB, size);
        arrC[i] = arrA[i] + closest;
    }
    
    return arrC;
}

void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL));
    
    int size = 100 + rand() % 9901;
    
    int* arrA = generate_array(size, -1000, 1000);
    int* arrB = generate_array(size, -1000, 1000);
    
    int* arrC = apply_operation(arrA, arrB, size);
    
    printf("Array A: ");
    print_array(arrA, size);
    
    printf("Array B: ");
    print_array(arrB, size);
    
    printf("Array C: ");
    print_array(arrC, size);
    
    free(arrA);
    free(arrB);
    free(arrC);
    
    return 0;
}