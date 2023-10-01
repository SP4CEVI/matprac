#include <stdio.h>
#include <stdlib.h>
#include <math.h>


unsigned long long fact(int n) {
    if (n == 0) {
        return 1;
    }
    return (n) * fact(n - 1);
}


double sum_a(long double x, long double epsilon) {
    long double sum = 1.0;
    long double current_value = 1.0;
    int n = 1;

    while (fabs(current_value) > epsilon) {
        current_value = pow(x, n) / fact(n);
        sum += current_value;
        n++;
    }

    return sum;
}


long double sum_b(long double x, long double epsilon) {
    long double sum = 1.0;
    long double current_value = 1.0;
    int n = 1;

    while (n < 20) {
        current_value = pow(-1, n) * pow(x, 2 * n) / fact(2 * n);
        if (fabs(current_value) < epsilon){
            return sum;
        }
        sum += current_value;
        n++;
    }

    return sum;
}


long double sum_c(long double x, long double epsilon) {
    long double sum = 1.0;
    long double current_value = 1.0;
    int n = 1;

    while (n < 20) {
        current_value = pow(3, 3 * n) * pow(fact(n), 3) * pow(x, 2 * n) / fact(3 * n);
        if (fabs(current_value) < epsilon){
            return sum;
        }
        sum += current_value;
        n++;
    }

    return sum;
}


long double sum_d(long double x, long double epsilon) {
    long double sum = 1.0;
    long double current_value = 1.0;
    int n = 1;

    while (n < 20) {
        current_value = pow(-1, n) * fact(fact(2 * n - 1)) * pow(x, 2 * n) / fact(fact(2 * n));
        if (fabs(current_value) < epsilon){
            return sum;
        }
        sum += current_value;
        n++;
    }

    return sum;
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Incorrect number of arguments.\n");
        return 1;
    }

    double x = 3.0;
    long double epsilon = atof(argv[1]);

    /*printf("Enter mean of x: ");
    scanf("%lf", &x);*/

    double result_1 = sum_a(x, epsilon);
    double result_2 = sum_b(x, epsilon);
    double result_3 = sum_c(x, epsilon);
    double result_4 = sum_d(x, epsilon);

    printf("Sum 1: %lf\n", result_1);
    printf("Sum 2: %lf\n", result_2);
    printf("Sum 3: %lf\n", result_3);
    printf("Sum 4: %lf\n", result_4);
    

    return 0;
}
