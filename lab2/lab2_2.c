#include <stdio.h>
#include <stdarg.h>
#include <math.h>

typedef enum {
    POWER_SUCCESS,
    POWER_FAILURE
} PowerStatus;

double averageGeo(int n, ...) {
    va_list args;
    va_start(args, n);
    
    double product = 1.0;
    for (int i = 0; i < n; i++) {
        double num = va_arg(args, double);
        product *= num;
    }
    
    va_end(args);
    
    return pow(product, 1.0 / n);
}

PowerStatus power(double x, int n, double* result) {
    if (n < 0) {
        return POWER_FAILURE;
    } else {
        *result = pow(x, n);
        return POWER_SUCCESS;
    }
}

int main() {
    double avg = averageGeo(3, 2.0, 4.0, 8.0);
    printf("Average geometric: %lf\n", avg);

    double result;
    PowerStatus status = power(2.0, 5, &result);
    if (status == POWER_SUCCESS) {
        printf("Result: %lf\n", result); 
    } else {
        printf("Failed to calculate the power\n");
    }
    
    return 0;
}