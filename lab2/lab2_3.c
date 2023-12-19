#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>

typedef struct {
    int row;
    int column;
} Data;

enum Status{
    SUCCESS = 0,
    ERROR_OF_MEMORY = -1,
    ERROR_OF_FILE = -2,
	ERROR = -3
};

int FindSubstring(Data** info, int** res, const char* substring, int count, ...){
    va_list args;
    va_start(args, count);

    int capacity = 1;
    *info = (Data*)malloc(sizeof(Data) * capacity);
    if (*info == NULL){
        return ERROR_OF_MEMORY;
    }

    *res = (int*)malloc(sizeof(int) * count);
    if (*res == NULL){
        free(*info);
        return ERROR_OF_MEMORY;
    }

    int id_info = 0;
    for (int i = 0; i < count; i++){
        const char* file = va_arg(args, const char*);

        FILE* fptr = fopen(file, "r");
        if (fptr == NULL){
            (*res)[i] = ERROR_OF_FILE;
            continue;
        }
        
        char* line = NULL;
        size_t len = 0;
        int cnt_all = 0;
		int count = 0;
        int line_number = 1;

        while (getline(&line, &len, fptr) != -1){
            char* line_ptr = line;
            int line_len = strlen(line);
            int pattern_len = strlen(substring);

            for (int i = 0; i < line_len; i++){
                if (line_ptr[i] == substring[0]){
                    bool match = 1;
                    
                    for (int j = 1; j < pattern_len && match; j++){
                        if (i + j >= line_len || line_ptr[i + j] != substring[j]){
                            match = 0;
                        }
                    }

                    if (match) {
                        id_info += 1;
                        cnt_all += 1;
                        count += 1;

                        if (id_info > capacity){
                            capacity *= 2;
                            Data* tmp;
                            tmp = (Data*)realloc(*info, sizeof(Data) * capacity);
                            if (tmp == NULL) {
                                free(info);
                                return ERROR_OF_MEMORY;
                            }
                            *info = tmp;
                        }

                        (*info)[id_info - 1].row = line_number;
                        (*info)[id_info - 1].column = i + 1;
                    }
                }
            }

            line_number += 1;
        }
        free(line);
        fclose(fptr);
        (*res)[i] = count;
    }

    va_end(args);

    return SUCCESS;
}

int main(){
    int number = 3;
    Data* info;
    int* res;

    int status = FindSubstring(&info, &res, "111", number, "file1.txt", "file2.txt", "file3.txt");
    if (status != SUCCESS){
		switch(status){
			case ERROR_OF_MEMORY:
				printf("Error of memory\n");
				break;
			case ERROR_OF_FILE:
				printf("Error of file\n");
				break;
			default:
				break;
		}
        return status;
    }

    int last = 0;
    for (int i = 0; i < number; i++){
        printf("Number substrings in the file №%d: %d\n", i + 1, res[i]);
        if (res[i] != ERROR_OF_FILE){
            for (int j = last; j < last + res[i]; j++){
                printf("%d %d\n", info[j].row, info[j].column);
            }
            last += res[i];
        }
        else {
            printf("Error of file\n");
			return ERROR_OF_FILE;
        }
    }

    free(res);
    free(info);

    return 0;
}
