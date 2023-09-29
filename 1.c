#include <stdio.h>
#include <stdlib.h>
#include <math.h>


enum ERRORS {
    FLAG = 1,
    OK,
    WRONG_NUMBER,
    BAD
};


enum Instructions {
    fl_h,
    fl_p,
    fl_s,
    fl_e,
    fl_a,
    fl_f
};

char *phrases_of_output[] = {
    "Wrong flag\n",
    "Wrong means\n",
    "Without errors\n",
    "No solutions\n"
};

char *Names_of_commands[] = {
    "-h",
    "-p",
    "-s",
    "-e",
    "-a",
    "-f"
};

int strcmp(const char *str1, const char *str2) {
    while ('\0' != *str1 && (*str1 == *str2)) {
        str1 += 1;
        str2 += 1;
    }

    return *(unsigned char *)str1 - *(unsigned char *)str2;
}


enum ERRORS flag_h(unsigned int value, unsigned int* result){
    if ((value < 1) || (value > 100)){
        return WRONG_NUMBER;
    }
    for (int i = 1; i <= 100; i++){
        if (i % value == 0){
            result = (unsigned int*)realloc(result, sizeof(unsigned int) * (result[0] + 2));
            result[result[0] + 1] = i;
            result[0] += 1;
        }
    }
    if (result[0]){
        return OK;
    }
    return BAD;
}


enum ERRORS flag_p(unsigned int value, unsigned int* result){
    if (value < 2){
        return WRONG_NUMBER;
    }
    for (int i = 2; i < sqrtl(value); i++){
        if (value % i == 0 && i != value){
            return OK;
        }
    }
    return BAD;
}


enum ERRORS flag_s(unsigned int value, unsigned int* result){
    while (value > 0) {
        result[result[0] + 1] = value % 10;
        result[0] += 1;
        result = (unsigned int*)realloc(result, sizeof(unsigned int) * (result[0] + 2));
        value = (value - (value % 10)) / 10;
    }
    return OK;
}


enum ERRORS flag_e(unsigned int value, unsigned int* result){
    if (value < 1 || value > 10){
        return WRONG_NUMBER;
    }
    for (int i = 1; i <= 10; i++){
        for (int j = 1; j <= value; j++){
            result = (unsigned int*)realloc(result, sizeof(unsigned int) * (result[0] + 2));
            result[result[0] + 1] = pow(i, j);
            result[0] += 1;
        }
    }
    return OK;
}


enum ERRORS flag_a(unsigned int value, unsigned int* result){
    if (value < 1){
        return WRONG_NUMBER;
    }
    for (int i = 1; i <= value; i++){
        result[0] += i;
    }
    if (result[0]){
        return OK;
    }
    return BAD;
}


enum ERRORS flag_f(unsigned int value, unsigned int* result){
    if (value < 1){
        return WRONG_NUMBER;
    }
    result[0] = 1;
    for (int i = 2; i <= value; i++){
        result[0] *= i;
    }
    if (result[0]){
        return OK;
    }
    return BAD;
}


int main(int argc, char* argv[])
{
    if (argc != 3){
        printf("%s", phrases_of_output[FLAG - 1]);
        return 0;
    }

    unsigned int value = atoi(argv[1]);
    unsigned int* result = NULL;
    result = (unsigned int*)malloc(sizeof(unsigned int) * 2);
    result[0] = 0;

    for (int i = fl_h; i <= fl_f; i++){
        if (!strcmp(argv[2], Names_of_commands[i])){
            switch (i){
                case fl_h:
                    switch (flag_h(value, result)){
                        case OK:
                            for (int j = 1; j <= result[0]; j++){
                                printf("%d", result[j]);
                            }
                            printf("\n");
                            free(result);
                            return 0;
                        case BAD:
                            printf("%s", phrases_of_output[BAD - 1]);
                            free(result);
                            return 0;
                        case WRONG_NUMBER:
                            printf("%s", phrases_of_output[WRONG_NUMBER - 1]);
                            free(result);
                            return 0;
                    }
                case fl_p:
                    switch (flag_p(value, result)){
                        case OK:
                            printf("The number is simple\n");
                            free(result);
                            return 0;
                        case BAD:
                            printf("Composite number");
                            free(result);
                            return 0;
                        case WRONG_NUMBER:
                            printf("%s", phrases_of_output[WRONG_NUMBER - 1]);
                            free(result);
                            return 0;
                    }
                case fl_s:
                    switch (flag_s(value, result)){
                        case OK:
                            for (int j = result[0]; j != 0; j -= 1){
                                printf("%d", result[j]);
                            }
                            printf("\n");
                            free(result);
                            return 0;
                    }
                case fl_e:
                    switch (flag_e(value, result)){
                        case OK:
                            for (int j = 1; j <= result[0]; j++){
                                if ((j - 1) % value == 0 && j > 1){
                                    printf("\n");
                                    }
                                printf("%d ", result[j]);
                            }
                            printf("\n");
                            free(result);
                            return 0;
                        case WRONG_NUMBER:
                            printf("%s", phrases_of_output[WRONG_NUMBER - 1]);
                            free(result);
                            return 0;
                    }
                case fl_a:
                    switch (flag_a(value, result)){
                        case OK:
                            printf("%d", result[0]);
                            printf("\n");
                            free(result);
                            return 0;
                        case BAD:
                            printf("%s", phrases_of_output[BAD - 1]);
                            free(result);
                            return 0;
                        case WRONG_NUMBER:
                            printf("%s", phrases_of_output[WRONG_NUMBER - 1]);
                            free(result);
                            return 0;
                    }
                case fl_f:
                    switch (flag_f(value, result)){
                        case OK:
                            printf("%d", result[0]);
                            printf("\n");
                            free(result);
                            return 0;
                        case BAD:
                            printf("%s", phrases_of_output[BAD - 1]);
                            free(result);
                            return 0;
                        case WRONG_NUMBER:
                            printf("%s", phrases_of_output[WRONG_NUMBER - 1]);
                            free(result);
                            return 0;
                    }
            }
        }
    }
    printf("%s", phrases_of_output[FLAG - 1]);
    free(result);
    return 0;
}
