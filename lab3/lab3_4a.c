#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    SUCCESS,
    ERROR
} Status;

typedef struct {
    char* data;
    int length;
} String;

Status createString(String* str, const char* value) {
    if (str == NULL || value == NULL) {
        return ERROR;
    }

    str->length = strlen(value);
    str->data = (char*)malloc((str->length + 1) * sizeof(char));
    if (str->data == NULL) {
        return ERROR;
    }

    strcpy(str->data, value);
    return SUCCESS;
}

Status deleteString(String* str) {
    if (str == NULL) {
        return ERROR;
    }

    free(str->data);
    str->data = NULL;
    str->length = 0;
    return SUCCESS;
}

int compareStrings(const String* str1, const String* str2) {
    if (str1 == NULL || str2 == NULL) {
        return ERROR;
    }

    if (str1->length < str2->length) {
        return -1;
    } else if (str1->length > str2->length) {
        return 1;
    } else {
        return strcmp(str1->data, str2->data);
    }
}

int areStringsEqual(const String* str1, const String* str2) {
    if (str1 == NULL || str2 == NULL) {
        return ERROR;
    }

    return strcmp(str1->data, str2->data) == 0;
}

Status copyString(String* dest, const String* src) {
    if (dest == NULL || src == NULL) {
        return ERROR;
    }

    dest->length = src->length;
    dest->data = (char*)realloc(dest->data, (dest->length + 1) * sizeof(char));
    if (dest->data == NULL) {
        return ERROR;
    }

    strcpy(dest->data, src->data);
    return SUCCESS;
}

Status copyOfString(const String* str, String* copy) {
    if (str == NULL || copy == NULL) {
        return ERROR;
    }

    copy->length = str->length;
    copy->data = (char*)malloc((copy->length + 1) * sizeof(char));
    if (copy->data == NULL) {
        return ERROR;
    }

    strcpy(copy->data, str->data);
    return SUCCESS;
}

Status concatStrings(String* str1, const String* str2) {
    if (str1 == NULL || str2 == NULL) {
        return ERROR;
    }

    str1->length += str2->length;
    str1->data = (char*)realloc(str1->data, (str1->length + 1) * sizeof(char));
    if (str1->data == NULL) {
        return ERROR;
    }

    strcat(str1->data, str2->data);
    return SUCCESS;
}

int main() {
    String hello;
    Status status = createString(&hello, "Hello");
    if (status == SUCCESS) {
        printf("String 1: %s\n", hello.data);

        String world;
        status = createString(&world, " world!");
        if (status == SUCCESS) {
            printf("String 2: %s\n", world.data);

            printf("\nCompare strings:\n");
            int comparison = compareStrings(&hello, &world);
            if (comparison < 0) {
                printf("String 1 is less than string 2\n");
            } else if (comparison > 0) {
                printf("String 1 is greater than string 2\n");
            } else {
                printf("String 1 is equal to string 2\n");
            }

            printf("\nAre strings equal: %s\n", areStringsEqual(&hello, &world) ? "Yes" : "No");

            printf("\nCopy string 2 to string 1\n");
            status = copyString(&hello, &world);
            if (status == SUCCESS) {
                printf("String 1: %s\n", hello.data);

                String copy;
                status = copyOfString(&hello, &copy);
                if (status == SUCCESS) {
                    printf("\nCopy string 1 to a new string\n");
                    printf("Copied string: %s\n", copy.data);

                    printf("\nConcatenate strings\n");

                    status = concatStrings(&hello, &world);
                    if (status == SUCCESS) {
                        printf("Concatenated string: %s\n", hello.data);
                    } else {
                        printf("String concatenation failed\n");
                    }

                    deleteString(&copy);
                } else {
                    printf("String copy failed\n");
                }
            } else {
                printf("String copy failed\n");
            }

            deleteString(&world);
        } else {
            printf("String creation failed\n");
        }

        deleteString(&hello);
    } else {
        printf("String creation failed\n");
    }

    return 0;
}
