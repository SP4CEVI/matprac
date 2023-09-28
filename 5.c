#include <stdio.h>
#include <stdlib.h>
#include <math.h>


unsigned long long fact(int k, int n) {
    if (n == 0) {
        return 1;
    } else {
        return (k * n) * fact(k, n - 1);
    }
}


double sum_a(double x, double epsilon) {
    double sum = 1.0;
    double current_value = 1.0;
    int n = 1;

    while (fabs(current_value) > epsilon) {
        //printf("%d\n", fact(1, n));
        current_value = pow(x, n) / fact(1, n);
        sum += current_value;
        n++;
    }

    return sum;
}


double sum_b(double x, double epsilon) {
    double sum = 1.0;
    double current_value = 1.0;
    int n = 1;

    while (n < 20) {
        current_value = pow(-1, n) * pow(x, 2 * n) / fact(2, n);
        //printf("%d\n", fact(2, n));
        if (fabs(current_value) < epsilon){
            return sum;
        }
        sum += current_value;
        n++;
    }

    return sum;
}


double sum_c(double x, double epsilon) {
    double sum = 1.0;
    double current_value = 1.0;
    int n = 1;

    while (n < 20) {
        current_value = pow(3, 3 * n) * fact(1, n) * pow(x, 2 * n) / fact(3, n);
        if (fabs(current_value) < epsilon){
            return sum;
        }
        sum += current_value;
        n++;
    }

    return sum;
}


double sum_d(double x, double epsilon) {
    double sum = 1.0;
    double current_value = 1.0;
    int n = 1;

    while (n < 20) {
        current_value = pow(-1, n) * fact(1, fact(1, 2 * n - 1)) * pow(x, 2 * n) / fact(1, fact(2, n));
        printf("%d\n", fact(1, fact(2, n)));
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

    double x = 0.0;
    double epsilon = atof(argv[1]);

    printf("Enter mean of x: ");
    scanf("%lf", &x);

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