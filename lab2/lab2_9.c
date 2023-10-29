#include <stdio.h>
#include <stdarg.h>
#include <math.h>

typedef enum {
    SUCCESS,
    FAILURE
} Status;

Status num_has_end(int base, int count, ...) {
    va_list numbers;
    va_start(numbers, count);

    for (int i = 0; i < count; i += 1) {
        double number = va_arg(numbers, double);
        double n = number;

        if (number < 0.0 || number > 1.0) {
            printf("Number must be in the range [0, 1]\n");
            va_end(numbers);
            return FAILURE;
        } 
        else {
            int flag = 0;
            for (int i = 0; i < 10; i++) {
                double fractional_part = fmod(number, 1.0);
                number *= base;

                if (fractional_part == 0 && !flag) {
                    flag = 1;
                    printf("The fraction %f has a finite representation in the system. It is %f\n", n, number);
                } 
                else if (fractional_part == 1 && !flag) {
                    flag = 1;
                    printf("The fraction %f does not have a finite representation in the system . It is %f\n",n, number);
                }
            }
            if (!flag) {
                printf("The fraction %f does not have a finite representation in the system. It is %f\n", n, number);
            }
        }
    }

    va_end(numbers);
    return SUCCESS;
}

int main() {
    Status status = num_has_end(2, 3, 0.00985, 0.772, 0.500);

    if (status == FAILURE) {
        printf("Failed to convert numbers.\n");
    }

    return 0;
}