#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void find_and_swap_min_max(int arr[], int size) {
    int minIndex = 0;
    int maxIndex = 0;
    
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[minIndex]) {
            minIndex = i;
        }
        if (arr[i] > arr[maxIndex]) {
            maxIndex = i;
        }
    }
    
    swap(arr + minIndex, arr +maxIndex);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Incorrect number of arguments.\n");
        return 1;
    }
    
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    
    if (a > b){
        printf("Wrong number order\n");
        return 2;
    }

    srand(time(NULL));
    
    const int size = 10;
    int arr[size];
    printf("Massive before changes: ");
    for (int i = 0; i < size; i++) {
        arr[i] = a + rand() % (b - a + 1);
        printf("%d ", arr[i]);
    }
    
    printf("\n");
    
    find_and_swap_min_max(arr, size);
    printf("Massive after changes: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    
    printf("\n");
    
    return 0;
}