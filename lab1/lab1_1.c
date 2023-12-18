#include <stdio.h>
#include <stdlib.h>
#include <math.h>


enum ERRORS {
    FLAG = 1,
    OK,
    WRONG_NUMBER,
    BAD,
    ERRORS_OF_MEMORY,
    ONE
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
    "No solutions\n",
    "Error of memory\n",
    "Not composite not simple\n"
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


enum ERRORS flag_h(unsigned int value, unsigned int** result){
    if ((value < 1) || (value > 100)){
        return WRONG_NUMBER;
    }
    for (int i = 1; i <= 100; i++){
        if (i % value == 0){
            unsigned int* temp = (unsigned int*)realloc(*result, sizeof(unsigned int) * ((*result)[0] + 2));
            if (temp == NULL){
                return ERRORS_OF_MEMORY;
            }
            *result = temp;
            (*result)[(*result)[0] + 1] = i;
            (*result)[0] += 1;
        }
    }
    if ((*result)[0]){
        return OK;
    }
    return BAD;
}


enum ERRORS flag_p(unsigned int value){
    if (value < 1){
        return WRONG_NUMBER;
    }

    if (value == 1){
        return ONE;
    }

    if (value == 2){
        return OK;
    }

    for (int i = 3; i < sqrtl(value); i += 2){
        if (value % i == 0){
            return BAD;
        }
    }
    return OK;
}


enum ERRORS flag_s(int value, unsigned int** result){
    if (value <= 0){
        return WRONG_NUMBER;
    }
    while (value > 0) {
        unsigned int* temp = (unsigned int*)realloc(*result, sizeof(unsigned int) * ((*result)[0] + 2));
        if (temp == NULL){
            return ERRORS_OF_MEMORY;
        }
        (*result) = temp;
        (*result)[(*result)[0] + 1] = value % 10;
        (*result)[0] += 1;
        value = (value - (value % 10)) / 10;
    }
    return OK;
}


enum ERRORS flag_e(unsigned int value, unsigned int** result){
    if (value < 1 || value > 10){
        return WRONG_NUMBER;
    }
    unsigned int* temp = (unsigned int*)realloc(*result, sizeof(unsigned int) * 10 * value + 1);
    if (temp == NULL){
        return ERRORS_OF_MEMORY;
    }
    (*result) = temp;    
    (*result)[0] = 0;
    for (int i = 1; i <= 10; i++){
        for (int j = 1; j <= value; j++){
            (*result)[(*result)[0] + 1] = i * j;
            (*result)[0] += 1;
        }
    }
    return OK;
}


enum ERRORS flag_a(unsigned int value, unsigned int** result){
    if (value < 1){
        return WRONG_NUMBER;
    }

    unsigned int sum = (value * (value + 1)) / 2;

    *result = (unsigned int*)malloc(sizeof(unsigned int) * 2);
    if (result == NULL){
        return ERRORS_OF_MEMORY;
    }
    (*result)[0] = sum;

    if ((*result)[0]){
        return OK;
    }
    return BAD;
}


enum ERRORS flag_f(unsigned int value, unsigned int** result){
    if (value < 1){
        return WRONG_NUMBER;
    }
    *result = (unsigned int*)malloc(sizeof(unsigned int) * 2);
    if (result == NULL){
        return ERRORS_OF_MEMORY;
    }
    (*result)[0] = 1;
    for (int i = 2; i <= value; i++){
        (*result)[0] *= i;
    }
    if ((*result)[0]){
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
    if (result == NULL){
        printf("Error of memory\n");
    }
    result[0] = 0;

    for (int i = fl_h; i <= fl_f; i++){
        if (!strcmp(argv[2], Names_of_commands[i])){
            switch (i){
                case fl_h:
                    switch (flag_h(value, &result)){
                        case OK:
                            for (int j = 1; j <= result[0]; j++){
                                printf("%d ", result[j]);
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
                        case ERRORS_OF_MEMORY:
                            printf("%s", phrases_of_output[ERRORS_OF_MEMORY - 1]);
                            free(result);
                            return 0;
                    }
                case fl_p:
                    switch (flag_p(value)){
                        case OK:
                            printf("The number is simple\n");
                            return 0;
                        case BAD:
                            printf("Composite number");
                            return 0;
                        case WRONG_NUMBER:
                            printf("%s", phrases_of_output[WRONG_NUMBER - 1]);
                            return 0;
                        case ONE:
                            printf("%s", phrases_of_output[ONE - 1]);
                            return 0;
                    }
                case fl_s:
                    switch (flag_s(value, &result)){
                        case OK:
                            for (int j = result[0]; j != 0; j -= 1){
                                printf("%d ", result[j]);
                            }
                            printf("\n");
                            free(result);
                            return 0;
                        case ERRORS_OF_MEMORY:
                            printf("%s", phrases_of_output[ERRORS_OF_MEMORY - 1]);
                            free(result);
                            return 0;
                        case WRONG_NUMBER:
                            printf("%s", phrases_of_output[WRONG_NUMBER - 1]);
                            free(result);
                            return 0;
                    }
                case fl_e:
                    switch (flag_e(value, &result)){
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
                        case ERRORS_OF_MEMORY:
                            printf("%s", phrases_of_output[ERRORS_OF_MEMORY - 1]);
                            free(result);
                            return 0;
                    }
                case fl_a:
                    switch (flag_a(value, &result)){
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
                        case ERRORS_OF_MEMORY:
                            printf("%s", phrases_of_output[ERRORS_OF_MEMORY - 1]);
                            free(result);
                            return 0;
                    }
                case fl_f:
                    switch (flag_f(value, &result)){
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
                        case ERRORS_OF_MEMORY:
                            printf("%s", phrases_of_output[ERRORS_OF_MEMORY - 1]);
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
