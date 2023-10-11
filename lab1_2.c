#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


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
    double a = 0;
    double b = 100;
    double c;
    while (fabs(b - a) > epsilon) {
        c = (a + b) / 2.0;
        double f = log(c);
        
        if (fabs(f - 1) < epsilon) {
            return c;
        } else if (f < 1) {
            a = c;
        } else {
            b = c;
        }
    }
    
    return (a + b) / 2.0;
}


double e_limit(double epsilon){
    double e = 0.0;
    double prev_e = 0.0;
    int n = 1;

    while (n){
        e = pow((1 + (1.0 / n)), n);
        n++;
        if(1.0 / n < epsilon){
            return e;
        }
    }
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
    double res = 0;
    double term = 0;
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
    double res = 0.0;
    double res_midl = 1.0;
    int sign = 1;
    int n = 1;
    
    while (fabs(res_midl) >= epsilon) {
        res += res_midl;
        sign *= -1;
        n += 2;
        res_midl = sign * (1.0 / n);
    }
    
    return res * 4.0;
}


double ln2_sum(double epsilon){
    double res = 0.0;
    double term = 0.0;
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
    double term = 1.0;
    int n = 1;
    double prev = 0.0;
    while (fabs(term - prev) >= epsilon ) {
        term = prev;
        prev += 1 / (n * pow(2.0, n));;
        n++;
    }
    return term;
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
    double a = 0;
    double b = 100;
    double c;
    while (fabs(b - a) > epsilon) {
        c = (a + b) / 2.0;
        double f = pow(c, 2);
        
        if (fabs(f - 2) < epsilon) {
            return c;
        } else if (f < 2) {
            a = c;
        } else {
            b = c;
        }
    }
    
    return (a + b) / 2.0;
}


double sqrt2_limit(double epsilon) {
    double res = 0;
    double term = 0;
    int n = 1;

    while (n){
        term = term - (pow(term, 2) / 2) + 1;
        n++;
        if(fabs(term - res) < epsilon){
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
    double term = 1.0;
    int n = 2;
    int l = 1;
    while (1.0 / l * exp(1) > epsilon) {
        l += 1;
    }
    bool *simple = malloc((l + 1) * sizeof(bool));
    if (simple == NULL) {
        printf("Error of memory\n");
        return 1;
    }
    for (int i = 2; i <= l; i++) {
        simple[i] = true;
    }
    for (int p = 2; p * p <= l; p++) {
        if (simple[p] == true) {
            for (int i = p * p; i <= l; i += p) {
                simple[i] = false;
            }
        }
    }

    for (int i = 2; i <= l; i++) {
        if (simple[i]) {
            term *= (i - 1) * 1.0 / i;
        }
    }
    free(simple);
    return -logl(term * logl(l));

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
    if (epsilon <= 0.0){
        printf("Wrong epsilon\n");
        return 1;
    }
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
