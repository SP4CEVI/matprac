#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 100

int base_to_10(char number[], int base){
    int res = 0;
    char *ptr = number;

    if (*ptr == '-') {
        ptr++;
    }

    while (*ptr){
        if (isdigit(*ptr)) {
            res = res * base + (*ptr - '0');
        } 
        else {
            res = res * base + (*ptr - 'A' + 10);
        }
        ptr++;
    }
    return res;
}


char* ten_to_base(int number, int base){
    char buf[MAX_LENGTH];
    int res;
    char *ptr = buf + MAX_LENGTH - 1;
    *ptr = '\0';

    while (number > 0){
        res = number % base;
        if (res > 9) {
            *--ptr = res - 10 + 'A';
        } 
        else {
            *--ptr = res + '0';
        }
        number /= base;
    }
    return ptr;
}


int main() {
    int base;
    char number[MAX_LENGTH];
    char maxNumber[MAX_LENGTH] = "";
    int maxValue = 0;

    printf("Enter the base of the number system (2-36): ");
    scanf("%d", &base);

    if (!(base >= 2 && base <= 36)){
        printf("Wrong number\n");
        return 1;
    }

    printf("Enter the numbers in the number system with the base %d (to complete, enter \"Stop\"): \n", base);
    
    while (1) {
        scanf("%s", number);
        
        if (strcmp(number, "Stop") == 0) {
            break;
        }
        
        int value = base_to_10(number, base);
        int absValue = abs(value);
        
        if (absValue > abs(maxValue)) {
            maxValue = value;
        }
    }

    if (!(maxNumber[0])){
        printf("Wrong number \n");
        return 2;
    }
    
    printf("The maximum number modulo: %d\n", maxValue);
    printf("The maximum number in the number system with a base 9: %s\n", ten_to_base(maxValue, 9));
    printf("The maximum number in the number system with a base 18: %s\n", ten_to_base(maxValue, 18));
    printf("The maximum number in the number system with a base 27: %s\n", ten_to_base(maxValue, 27));
    printf("The maximum number in the number system with a base 36: %s\n", ten_to_base(maxValue, 36));
    
    return 0;
}
