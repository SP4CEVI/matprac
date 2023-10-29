#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void ascii_to_base(int asciiCode, int base, char result[]) {
    int index = 0;
    int remainder;
    int quotient = asciiCode;

    if (quotient == 0) {
        result[index++] = '0';
    } 
    else {
        while (quotient > 0) {
            remainder = quotient % base;
            if (remainder < 10) {
                result[index++] = remainder + '0';
            } 
            else {
                result[index++] = remainder - 10 + 'A';
            }
            quotient /= base;
        }
    }

    result[index] = '\0';
    int i, j;
    for (i = 0, j = index - 1; i < j; i++, j--) {
        char temp = result[i];
        result[i] = result[j];
        result[j] = temp;
    }
}

enum Instructions {
    fl_r,
    fl_a
};


char *Names_of_commands[] = {
    "-r",
    "-a"
};


int strcmp(const char *str1, const char *str2) {
    while ('\0' != *str1 && (*str1 == *str2)) {
        str1 += 1;
        str2 += 1;
    }

    return *(unsigned char *)str1 - *(unsigned char *)str2;
}


void flag_r(char* output_file, char* file1, char* file2) {
    FILE* fp_output = fopen(output_file, "w");
    if (fp_output == NULL) {
        printf("Error of open output file.\n");
        return;
    }
    
    FILE* fp_file1 = fopen(file1, "r");
    if (fp_file1 == NULL) {
        printf("Error of open: %s\n", file1);
        fclose(fp_output);
        return;
    }
    
    FILE* fp_file2 = fopen(file2, "r");
    if (fp_file2 == NULL) {
        printf("Error of open: %s\n", file2);
        fclose(fp_output);
        fclose(fp_file1);
        return;
    }
    
    char buffer[256];
    int odd_file1 = 0;
    int odd_file2 = 0;
    
    while (1) {
        if (odd_file1 && fgets(buffer, sizeof(buffer), fp_file1) != NULL) {
            fprintf(fp_output, "%s", buffer);
            odd_file1 = 0;
            continue;
        }
        
        if (!odd_file1 && fgets(buffer, sizeof(buffer), fp_file1) == NULL) {
            if (odd_file2 && fgets(buffer, sizeof(buffer), fp_file2) != NULL) {
                fprintf(fp_output, "%s", buffer);
                odd_file2 = 0;
            } 
            else {
                break;
            }
        } 
        else {
            fprintf(fp_output, "%s", buffer);
            odd_file1 = 1;
        }
        
        if (odd_file2 && fgets(buffer, sizeof(buffer), fp_file2) != NULL) {
            fprintf(fp_output, " %s", buffer);
            odd_file2 = 0;
        } 
        else {
            odd_file2 = 1;
        }
    }
    
    fclose(fp_output);
    fclose(fp_file1);
    fclose(fp_file2);
}


void flag_a(char* output_file, char* file) {
    FILE* fp_output = fopen(output_file, "w");
    if (fp_output == NULL) {
        printf("Error of open output file.\n");
        return;
    }
    
    FILE* fp_file = fopen(file, "r");
    if (fp_file == NULL) {
        printf("Error of open: %s\n", file);
        fclose(fp_output);
        return;
    }
    
    char buffer[256];
    int word_counter = 0;
    
    while (fgets(buffer, sizeof(buffer), fp_file) != NULL) {
        char* token = strtok(buffer, " \t\n");
        
        while (token != NULL) {
            if (word_counter % 10 == 9) {
                for (int i = 0; i < strlen(token); i++) {
                    if (isalpha(token[i])) {
                        token[i] = tolower(token[i]);
                    }
                }
                
                int decimalNumber = atoi(token);
                char result[256];
                ascii_to_base(decimalNumber, 4, result);
                fprintf(fp_output, "%s ", result);
            } else if ((word_counter % 2 == 1) && (word_counter % 10 != 9)) {
                for (int i = 0; i < strlen(token); i++) {
                    if (isalpha(token[i])) {
                        token[i] = tolower(token[i]);
                    }
                }
                
                fprintf(fp_output, "%s ", token);
            } else if ((word_counter % 5 == 4) && (word_counter % 10 != 9)) {
                for (int i = 0; i < strlen(token); i++) {
                    if (isalpha(token[i])) {
                        int asciiCode = token[i];
                        char result[256];
                        ascii_to_base(asciiCode, 8, result);
                        
                        fprintf(fp_output, "%s", result);
                    } else {
                        fprintf(fp_output, "%c", token[i]);
                    }
                }
                fprintf(fp_output, " ");
            } else {
                fprintf(fp_output, "%s ", token);
            }
            
            token = strtok(NULL, " \t\n");
            word_counter++;
        }
    }
    
    fclose(fp_output);
    fclose(fp_file);
}

int main(int argc, char** argv) {
    if (argc < 4) {
        printf("Wrong number of arguments\n");
        return 3;
    }
    
    char* flag = argv[1];
    
    if (strcmp(flag, "-r") == 0) {
        if (argc != 5) {
            printf("Wrong number of arguments for -r.\n");
            return 4;
        }
        
        char* output_file = argv[4];
        char* file1 = argv[2];
        char* file2 = argv[3];
        
        flag_r(output_file, file1, file2);
    } 
    else if (strcmp(flag, "-a") == 0) {
        if (argc != 4) {
            printf("Wrong number of arguments for -a.\n");
            return 5;
        }
        
        char* output_file = argv[3];
        char* file = argv[2];
        
        flag_a(output_file, file);
    } 
    else {
        printf("Wrong flag: %s\n", flag);
        return 6;
    }
    return 0;
}
