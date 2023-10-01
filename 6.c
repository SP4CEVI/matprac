#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double integ_a(long double x, long double epsilon) {
    long double res = 0.0;

    for (x = epsilon; x <= 1.0; x += epsilon){
        res += log(1 + x) / x * epsilon;
    }
    return res;
}


double integ_b(long double x, long double epsilon) {
    long double res = 0.0;

    for (x = epsilon; x <= 1.0; x += epsilon){
        res += powl(expl(1), -powl(x, 2) / 2) * epsilon;
    }
    return res;
}


double integ_c(long double x, long double epsilon) {
    long double res = 0.0;

    for (x = epsilon; x <= 1.0; x += epsilon){
        res += log(1 / (1 - x)) * epsilon;
    }
    return res;
}


double integ_d(long double x, long double epsilon) {
    long double res = 0.0;

    for (x = epsilon; x <= 1.0; x += epsilon){
        res += powl(x, x) * epsilon;
    }
    return res;
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Incorrect number of arguments.\n");
        return 1;
    }

    double x = 2.0;
    long double epsilon = atof(argv[1]);

    double result_1 = integ_a(x, epsilon);
    double result_2 = integ_b(x, epsilon);
    double result_3 = integ_c(x, epsilon);
    double result_4 = integ_d(x, epsilon);

    printf("Integral 1: %lf\n", result_1);
    printf("Integral 2: %lf\n", result_2);
    printf("Integral 3: %lf\n", result_3);
    printf("Integral 4: %lf\n", result_4);
    

    return 0;
}