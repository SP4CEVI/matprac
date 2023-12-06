#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Status{
    SUCCESS = 0,
    ERROR_OF_MEMORY = -1,
    ERROR = -2
};

enum Compare_Status{
    SIMILAR = 0,
    FIRST_IS_BIGGER = 1,
    FIRST_IS_SMALLER = -1
};

typedef struct{
    char * data;
    int length;
} String, *String_ptr;

String_ptr CreateString(const char * data){
    String_ptr string = (String_ptr)malloc(sizeof(String));
    if (!string){
        return NULL;
    } 
    string->length = strlen(data);
    string->data = (char*)malloc((string->length + 1) * sizeof(char));
    if (!(string->data)) {
        free(string);
        return NULL;
    }
    strcpy(string->data, data);
    return string;
}

void DeleteString(String_ptr string){
    if (!string){
        return;
    } 

    if (string->data){
        free(string->data);
    }

    free(string);
}

int CompareStrings(const String_ptr first, const String_ptr second){
    if (first->length > second->length){
        return FIRST_IS_BIGGER;
    } 
    else if (first->length < second->length){
        return FIRST_IS_SMALLER;
    } 

    int length = first->length;
    for (int i = 0; i < length; i++){
        if ((first->data)[i] > (second->data)[i]){
            return FIRST_IS_BIGGER;
        } 
        else if ((first->data)[i] < (second->data)[i]){
            return FIRST_IS_SMALLER;
        } 
    }
    return SIMILAR;
}

int AreStringsEqual(const String_ptr first, const String_ptr second){
    if (first->length != second->length){
        return ERROR;
    } 

    int length = first->length;
    for (int i = 0; i < length; i++){
        if ((first->data)[i] != (second->data)[i]){
            return ERROR;
        } 
    }
    return SUCCESS;
}

void CopyString(const String_ptr first, String_ptr second){
    second->length = first->length;
    strcpy(second->data, first->data);
    return;
}

String_ptr Dublicate(const String_ptr string){
    String_ptr new = CreateString(string->data);
    if (!new){
        return NULL;
    } 
    return new;
}

int DynamicCopy(String_ptr new, const String_ptr string){
    if (!new){
        return ERROR;
    }
    new->length = string->length;
    new->data = (char*)malloc((new->length) * sizeof(char));
    if (!(new->data)){
        return ERROR_OF_MEMORY;
    } 
    memcpy(new->data, string->data, string->length);
    return SUCCESS;
}

String_ptr ConcatString(const String_ptr first, const String_ptr second){
    char * data = (char*)malloc(((first->length) + (second->length) + 1) * sizeof(char));
    if (!data){
        return NULL;
    } 

    memcpy(data, first->data, first->length);
    memcpy(data + first->length, second->data, second->length);

    String_ptr string = CreateString(data);
    if (!string){
        free(data);
        return NULL;
    }
    free(data);
    return string;
}

int main(){
    String_ptr first = CreateString("abcd ef");
    if (!first){
        printf("Error of memory\n");
        return ERROR_OF_MEMORY;
    }
    printf("Your string: %s , length: %d\n\n", first->data, first->length);

    String_ptr second = CreateString("12345");
    if (!second){
        DeleteString(first);
        printf("Error of memory\n");
        return ERROR_OF_MEMORY;
    }
    printf("Your string: %s , length: %d\n\n", second->data, second->length);

    switch(CompareStrings(first, second)){
        case 0:
            printf("Strings are equal\n\n");
            break;
        case 1:
            printf("\"%s\" are bigger than \"%s\"\n\n", first->data, second->data);
            break;
        case -1:
            printf("\"%s\" are bigger than \"%s\"\n\n", second->data, first->data);
            break;
    }

    String_ptr new = ConcatString(first, second);
    if (!new){
        DeleteString(first);
        DeleteString(second);
        printf("Error of memory\n");
        return ERROR_OF_MEMORY;
    }
    printf("Concatenated string is: %s, lengths: %d\n\n", new->data, new->length);

    switch(AreStringsEqual(first, second)){
        case 0:
            printf("Strings \"%s\" and \"%s\" are equal\n\n", first->data, second->data);
            break;
        case -2:
            printf("Strings \"%s\" and \"%s\" are different\n\n", first->data, second->data);
            break;
    }
    
    CopyString(first, second);
    printf("Result of copy first to seond string is: %s %s\n\n", first->data, second->data);

    String_ptr third = Dublicate(first);
    if (!third){
        DeleteString(first);
        DeleteString(second);
        DeleteString(new);
        printf("Error of memory\n");
        return ERROR_OF_MEMORY;
    }
    printf("Result of dublication first to third string is: %s\n\n", third->data);

    String_ptr fourth = (String_ptr)malloc(sizeof(String));
    if (!fourth){
        DeleteString(first);
        DeleteString(second);
        DeleteString(new);
        DeleteString(third);
        printf("Error of memory\n");
        return ERROR_OF_MEMORY;
    }
    int result = DynamicCopy(fourth, first);
    if (result == ERROR_OF_MEMORY){
        DeleteString(first);
        DeleteString(second);
        DeleteString(new);
        DeleteString(third);
        DeleteString(fourth);
        printf("Error of memory\n");
        return ERROR_OF_MEMORY;
    }
    printf("Result of dynamic copy first string is: %s\n\n", fourth->data);

    DeleteString(first);
    DeleteString(second);
    DeleteString(new);
    DeleteString(third);
    DeleteString(fourth);

    return SUCCESS;
}