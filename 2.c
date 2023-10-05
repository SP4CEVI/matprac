#include <stdio.h>
#include <stdlib.h>
#include <math.h>


unsigned long long fact(int n) {
    if (n == 0) {
        return 1;
    } 
    return (n) * fact(n - 1);
}


double e_sum(double epsilon){
    double sum = 1.0;
    double term = 1.0;
    int n = 1;

    while (term > epsilon) {
        term = term / n;
        sum += term;
        n++;
    }

    return sum;
}


double e_equation(double epsilon){
    double x = 1.0;
    while (fabs(log(x) - 1.0) > epsilon) {
        x += epsilon;
    }
    return x;
}


double e_limit(double epsilon){
    double e = 1.0;
    double prev_e = 0.0;
    int n = 1;

    while (fabs(e - prev_e) > epsilon) {
        prev_e = e;

        e = pow((1 + (1.0 / n)), n);
        
        n++;
    }

    return e;
}


double pi_sum(double epsilon){
    double sum = 0.0;
    double term = 1.0;
    int n = 1;
    while (fabs(term) > epsilon){
        term = 1.0 / (2.0 * n - 1.0);
        if (n % 2 == 0){
            sum -= term;
        }
        else{
            sum += term;
        }
        n++;
    }
    return 4.0 * sum;
}


double pi_equation(double epsilon){
    long double res = 0;
    long double term = 0;
    int n = 1;
    res = pow(-1, n - 1) / (2 * n -1);

    while (fabs(res) > epsilon) {
        term += res;
        n++;
        res = pow(-1, n - 1) / (2 * n -1);
    }
    return 4 * term;
}


double pi_limit(double epsilon){
    double pi = 1.0;
    double prev_pi = 0.0;
    int n = 1;

    while (fabs(pi - prev_pi) > epsilon) {
        prev_pi = pi;

        double numerator = pow(2, n) * fact(n);
        double denominator = n * pow(fact(2 * n), 2);

        pi = pow(numerator, 4) / denominator;

        n++;
    }

    return pi;
}


double ln2_sum(double epsilon){
    long double res = 0.0;
    long double term = 0.0;
    int n = 1;
    res = pow(-1, n - 1) / n;

    while (fabs(res) > epsilon) {
        term += res;
        n++;
        res = pow(-1, n - 1) / n;
    }
    return term;
}


double ln2_equation(double epsilon){
    double res = 0.0;
    while (fabs(exp(res) - 2) > epsilon) {
        res += epsilon;
    }
    return res;
}


double ln2_limit(double epsilon){
    double term = 0.0;
    double n = 1.0;
    while (1) {
        term = n * (pow(2.0, 1.0 / n) - 1.0);
        if (fabs(term - log(2.0)) < epsilon) {
            return term;
        }
        n++;
    }
}


double sqrt2_sum(double epsilon) {
    double sum = 1.0;
    double term = 0.0;
    int n = 2;
    term = pow(2, pow(2, -n));

    while (fabs(term) > epsilon + 1) {
        sum *= term;
        n++;
        term = pow(2, pow(2, -n));
    }

    return sum;
}


double sqrt2_equation(double epsilon) {
    double res = epsilon;
    while (pow(res, 2) - 2 < epsilon) {
        res += epsilon;
    }
    return res;
}


double sqrt2_limit(double epsilon) {
    double res = 0;
    double term = 0;
    int n = 1;

    while (n) {
        term = term - (pow(term, 2) / 2) + 1;
        n++;
        if (fabs(term - res) < epsilon) {
            return term;
        }
        res = term;
    }
}


double gamma_sum(double epsilon) {
    double sum = 0.0;
    double prev_sum;
    int n = 1;

    do {
        prev_sum = sum;
        sum += 1.0 / n;
        n++;
    } while (fabs(sum - prev_sum) > epsilon);
    
    double gamma = sum - log(n);
    return gamma;
}


double gamma_equation(double epsilon) {
    double res = 0.0;
    double limit = 1.0;
    int n = 2;

    while (fabs(limit - limit * (1 - 1.0 / n)) > epsilon) {
        limit *= 1 - 1.0 / n;
        n++;
    }
    limit *= log(n);

    while (res <= log(limit)) {
        res += epsilon;
    }

    return res;
}


double gamma_limit(double epsilon) {
    double res = 0.0;
    double term = 0.0;
    int n = 1;

    while (n) {
        term += 1.0 / n;
        n++;
        if (fabs(term - res) < epsilon) {
            return term - log(n);
        }
        res = term;
    }
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Incorrect number of arguments\n");
        return 1;
    }

    double epsilon = atof(argv[1]);

    double e = e_sum(epsilon);
    printf("e (Sum): %.6f\n", e);

    double e_eq = e_equation(epsilon);
    printf("e (Equation): %.6f\n", e_eq);

    double e_lim = e_limit(epsilon);
    printf("e (Limit): %.6f\n", e_lim);

    double pi = pi_sum(epsilon);
    printf("pi (Sum): %.6f\n", pi);

    double pi_eq = pi_equation(epsilon);
    printf("pi (Equation): %.6f\n", pi_eq);

    double pi_lim = pi_limit(epsilon);
    printf("pi (Limit): %.6f\n", pi_lim);

    double ln2 = ln2_sum(epsilon);
    printf("ln(2) (Sum): %.6f\n", ln2);

    double ln2_eq = ln2_equation(epsilon);
    printf("ln(2) (Equation): %.6f\n", ln2_eq);

    double ln2_lim = ln2_limit(epsilon);
    printf("ln(2) (Limit): %.6f\n", ln2_lim);

    double sqrt2 = sqrt2_sum(epsilon);
    printf("sqrt(2) (Sum): %.6f\n", sqrt2);

    double sqrt2_eqn = sqrt2_equation(epsilon);
    printf("sqrt(2) (Equation): %.6f\n", sqrt2_eqn);

    double sqrt2_lim = sqrt2_limit(epsilon);
    printf("sqrt(2) (Limit): %.6f\n", sqrt2_lim);

    double gamma = gamma_sum(epsilon);
    printf("gamma (Sum): %.6f\n", gamma);

    double gamma_eq = gamma_equation(epsilon);
    printf("gamma (Equation): %.6f\n", gamma_eq);

    double gamma_lim = gamma_limit(epsilon);
    printf("gamma (Limit): %.6f\n", gamma_lim);

    return 0;
}