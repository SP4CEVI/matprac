#include <stdio.h>
#include <math.h>

typedef enum {
    ROOT_SUCCESS,
    ROOT_FAILURE
} RootStatus;

double bisection(double a, double b, double epsilon, double (*function)(double)) {
    if (function(a) * function(b) > 0) {
        printf("No root exists in the given interval.\n");
        return NAN;
    }

    double c = (a + b) / 2;

    while (fabs(a - b) > epsilon) {
        if (function(c) == 0) {
            return c;
        } 
        else if (function(a) * function(c) < 0) {
            b = c;
        } 
        else {
            a = c;
        }

        c = (a + b) / 2;
    }

    return c;
}

double squareRootFunction(double x) {
    return x * x - 4;
}

int main() {
    double a = 0.0;
    double b = 5.0;
    double epsilon = 0.0001;

    RootStatus status;
    double root = bisection(a, b, epsilon, squareRootFunction);
    if (!isnan(root)) {
        printf("The root of the equation x^2 - 4 = 0 is %.4f\n", root);
        status = ROOT_SUCCESS;
    }
    else {
        status = ROOT_FAILURE;
    }

    if (status == ROOT_FAILURE) {
        printf("Failed to find the root\n");
    }

    return 0;
}