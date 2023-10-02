#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double integ_a(double x){
    if (x == 0.0){
        return 1.0;
    }
    return log(1 + x) / x;
}

double integ_b(double x) {
    return exp(-pow(x, 2) / 2);
}


double integ_c(double x) {
    if (x <= 0.0 || x >= 1.0){
        return 0.0;
    }
    return log(1 / (1 - x));
}


double integ_d(double x) {
    if (x <= 0.0){
        return 0.0;
    }
    return pow(x, x);
}


double trapezoidal(double a, double b, double epsilon, double (*func)(double)){
    double h = (b - a);
    double result = (func(a) + func(b)) / 2.0;
    double integral = result * h;
    double previous_integral = 0.0;

    while(fabs(integral - previous_integral) > epsilon){
        previous_integral = integral;
        result = 0.0;
        h /= 2.0;
        int num = (int)((b- a) / h);
        for (int i = 1; i <= num; i++){
            double x = a + i * h;
            if (x > b){
                x = b;
            }
            result += func(x);
        }
        integral = (integral / 2.0) + (result * h / 2.0);
    }
    return integral;
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Incorrect number of arguments.\n");
        return 1;
    }

    double a = 0.0;
    double b = 1.0;
    double epsilon = atof(argv[1]);

    double result_a = trapezoidal(a, b, epsilon, integ_a);
    double result_b = trapezoidal(a, b, epsilon, integ_b);
    double result_c = trapezoidal(a + epsilon, b - epsilon, epsilon, integ_c);
    double result_d = trapezoidal(a, b, epsilon, integ_d);

    printf("Integral 1: %lf\n", result_a);
    printf("Integral 2: %lf\n", result_b);
    printf("Integral 3: %lf\n", result_c);
    printf("Integral 4: %lf\n", result_d);
    

    return 0;
}
