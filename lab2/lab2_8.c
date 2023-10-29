#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

typedef enum {
    MEMORY_SUCCESS,
    MEMORY_FAILURE
} MemoryStatus;

typedef enum {
    BASE_SUCCESS,
    BASE_FAILURE
} BaseStatus;

MemoryStatus addNumbers(char* num1, char* num2, int base, char** result) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int i, j, carry = 0;

    *result = (char*)malloc(sizeof(char) * (len1 > len2 ? len1 + 1 : len2 + 1));
    if (*result == NULL) {
        printf("Failed to allocate memory for result.\n");
        return MEMORY_FAILURE;
    }

    int index = 0;
    for (i = len1 - 1, j = len2 - 1; (i >= 0 && j >= 0) || carry; i--, j--, index++) {
        int digit1 = (i >= 0) ? (num1[i] - '0') : 0;
        int digit2 = (j >= 0) ? (num2[j] - '0') : 0;
        int sum = digit1 + digit2 + carry;

        (*result)[index] = (char)((sum % base) + '0');
        carry = sum / base;
    }

    (*result)[index] = '\0';

    for (i = 0, j = index - 1; i < j; i++, j--) {
        char temp = (*result)[i];
        (*result)[i] = (*result)[j];
        (*result)[j] = temp;
    }

    return MEMORY_SUCCESS;
}

BaseStatus sumNumbers(int base, int numCount, char** numbers, char** sum) {
    if (base < 2 || base > 36) {
        printf("Base must be between 2 and 36 inclusive.\n");
        return BASE_FAILURE;
    }

    int i;

    *sum = strdup(numbers[0]);
    if (*sum == NULL) {
        printf("Failed to allocate memory for sum.\n");
        return BASE_FAILURE;
    }

    for (i = 1; i < numCount; i++) {
        char* temp;
        MemoryStatus memoryStatus = addNumbers(*sum, numbers[i], base, &temp);
        if (memoryStatus == MEMORY_FAILURE) {
            printf("Failed to calculate sum.\n");
            free(*sum);
            return BASE_FAILURE;
        }

        free(*sum);
        *sum = temp;
    }

    return BASE_SUCCESS;
}

int main() {
    int base = 3;
    int numCount = 3;
    char* num1 = "000001234";
    char* num2 = "56780000";
    char* num3 = "0000009012";

    BaseStatus baseStatus;
    if (base < 2 || base > 36) {
        printf("Base must be between 2 and 36 inclusive.\n");
        baseStatus = BASE_FAILURE;
    } 
    else {
        char** numbers = (char**)malloc(sizeof(char*) * numCount);
        if (numbers == NULL) {
            printf("Failed to allocate memory for numbers.\n");
            return 1;
        }

        numbers[0] = num1;
        numbers[1] = num2;
        numbers[2] = num3;

        char* sum = NULL;
        BaseStatus sumStatus = sumNumbers(base, numCount, numbers, &sum);
        if (sumStatus == BASE_SUCCESS) {
            printf("Sum: %s\n", sum);
            free(sum);
        } 
        else {
            printf("Failed to calculate the sum.\n");
        }

        baseStatus = BASE_SUCCESS;
        free(numbers);
    }

    if (baseStatus == BASE_FAILURE) {
        printf("Failed to calculate the sum due to incorrect base.\n");
    }

    return 0;
}