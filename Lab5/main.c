#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int arr[], int size) {
    int i, j, temp;
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void prettyPrintArray(int arr[], int size) {
    int i;
    printf("[");
    for (i = 0; i < size - 1; i++) { printf("%i, ", arr[i]); }
    if (size >= 1) { printf("%i]\n", arr[size-1]);}
}

int main() {
    int arrSize = 0, i;
    int *arr;
    printf("Bubble Sort!\nHow many numbers would you like to sort?:\n");
    scanf("%d", &arrSize);
    arr = (int *) malloc(arrSize * sizeof(int));
    for (i = 0; i < arrSize; i++) {
        int buff = 0;
        printf("Enter element #%d:\n", i);
        scanf("%d", &buff);
        arr[i] = buff;
    }
    prettyPrintArray(arr, arrSize);
    printf("Sorting array...\n");
    bubbleSort(arr, arrSize);
    printf("Sorted: \n");
    prettyPrintArray(arr, arrSize);
    return 0;
}