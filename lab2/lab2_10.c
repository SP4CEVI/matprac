#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

enum Error {
    OK,
    ERROR_MEMORY
};

long long int factorial(int n) {
    if (n <= 1)
        return 1;
    else
        return n * factorial(n - 1);
}

int Coeff(int n, int k) {
    if (k > n || n < 0 || k < 0) {
        return 0;
    }
    return factorial(n) / (factorial(k) * factorial(n - k));
}

enum Error polynom(double epsilon, double a, double** result, int n, ...) {
    *result = (double*)malloc((n + 1) * sizeof(double));
    if (*result == NULL) {
        return ERROR_MEMORY;
    }

    for (int i = 0; i <= n; i++) {
        (*result)[i] = 0.0;
    }

    va_list args;
    va_start(args, n);

    for (int i = 0; i <= n; i++) {
        double coeff = va_arg(args, double);
        double c = coeff - (*result)[i];

        for (int j = i; j <= n; j++) {
            if (j == i)
                (*result)[j] = c;
            else
                (*result)[j] += Coeff(n - i, j - i) * pow(-a, j - i) * c;
        }
    }

    va_end(args);

    return OK;
}

int main() {
    double epsilon = 0.001;
    double a = 3.0;
    double* result = NULL;

    enum Error status = polynom(epsilon, a, &result, 3, 2.0, 0.0, 1.0, 1.0);

    if (status == ERROR_MEMORY) {
        printf("Error of memory\n");
    } else if (status == OK) {
        printf("Decomposed polynomial:\n");
        for (int i = 0; i <= 3; i++) {
            printf("g%d = %.4f\n", 3 - i, result[i]);
        }
        free(result);
    }

    return 0;
}