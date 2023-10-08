#include <stdio.h>
#include <math.h>
#include <stdlib.h>


enum Instructions {
    fl_q,
    fl_m,
    fl_t
};


char *Names_of_commands[] = {
    "-q",
    "-m",
    "-t"
};



int strcmp(const char *str1, const char *str2) {
    while ('\0' != *str1 && (*str1 == *str2)) {
        str1 += 1;
        str2 += 1;
    }

    return *(unsigned char *)str1 - *(unsigned char *)str2;
}


double* flag_q(double epsilon, double a, double b, double c, double* result){
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0){
        return NULL;
    }
    else if(discriminant == 0){
        double* roots = (double*)malloc(2 * sizeof(double));
        if (roots == NULL) {
            return NULL;
        }
        roots[0] = -b / (2 * a);
        roots[1] = roots[0];
        return roots;
    }
    else{
        double* roots = (double*)malloc(2 * sizeof(double));
        if (roots == NULL) {
            return NULL;
        }
        roots[0] = (-b + sqrt(discriminant)) / (2 * a);
        roots[1] = (-b - sqrt(discriminant)) / (2 * a);
        return roots;
    }
}


int flag_m(int a, int b) {
    if (a == 0 || b == 0){
        return -1;
    } 
    if (a % b == 0){
        return 0;
    } 
    return 1;
}


int flag_t(double epsilon, double a, double b, double c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 1;
    }

    if (fabs(a * a + b * b - c * c) < epsilon || fabs(a * a + c * c - b * b) < epsilon || fabs(b * b + c * c - a * a) < epsilon) {
        return 0;
    }

    return 1;
}


int main(int argc, char* argv[]){
    if (argc < 4){
        printf("Incorrect number of flags\n");
        return 0;
    }

    int result;
    double massive[6];
    for (int i = fl_q; i <= fl_t; i++){
        if (!strcmp(argv[1], Names_of_commands[i])){
            switch (i){
                case fl_q:
                    if (argc != 6){
                        printf("Incorrect number of flags\n");
                        return 1;
                    }
                    double epsilon = atof(argv[2]);
                    double coefficients[] = { atof(argv[3]), atof(argv[4]), atof(argv[5]) };
                    int num_permutations = 6;
                    double permutations[][3] = {
                        { coefficients[0], coefficients[1], coefficients[2] },
                        { coefficients[0], coefficients[2], coefficients[1] },
                        { coefficients[1], coefficients[0], coefficients[2] },
                        { coefficients[1], coefficients[2], coefficients[0] },
                        { coefficients[2], coefficients[0], coefficients[1] },
                        { coefficients[2], coefficients[1], coefficients[0] }
                    };

                    int unique_permutations = 0;
                    double** roots = (double**)malloc(num_permutations * sizeof(double*));
                    if (roots == NULL){
                        printf("Error of memory\n");
                    }
                    for (int j = 0; j < num_permutations; j++) {
                        roots[j] = flag_q(epsilon, permutations[j][0], permutations[j][1], permutations[j][2], massive);
                        if (roots[j] != NULL) {
                            unique_permutations++;
                        }
                    }

                    printf("%d unique permutation(s) found:\n", unique_permutations);

                    for (int j = 0; j < num_permutations; j++) {
                        if (roots[j] != NULL) {
                            printf("The equation %d\n", j + 1);
                            for (int k = 0; k < 2; k++) {
                                printf("Root %d: %.*f\n", k + 1, (int)(-log10(epsilon)), roots[j][k]);
                            }
                
                            free(roots[j]);
                        }
                    }
                    
                    free(roots);
                    
                    return 0;

                case fl_m:
                    result = flag_m(atoi(argv[2]), atoi(argv[3]));
                    if (result == 0){
                        printf("Multiple\n");
                    }
                    else if (result == -1){
                        printf("Wrong number\n");
                    }
                    else{
                        printf("Not multiple\n");
                    }
                    return 0;
                
                case fl_t:
                    if (argc != 6){
                        printf("Incorrect number of arguments\n");
                        break;;
                    }
                    result = flag_t(atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]));
                    if (result == 0){
                        printf("Can be\n");
                    }
                    else{
                        printf("Can't be\n");
                    }
                    return 0;
            }
        }
    }
    printf("%s", "Wrong flag\n");
    return 0;
}
