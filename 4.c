#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum Instructions {
    fl_d,
    fl_i,
    fl_s,
    fl_a,
    fl_nd,
    fl_ni,
    fl_ns,
    fl_na
};


char *Names_of_commands[] = {
    "-d",
    "-i",
    "-s",
    "-a",
    "-nd",
    "-ni",
    "-ns",
    "-na"
};



int strcmp(const char *str1, const char *str2) {
    while ('\0' != *str1 && (*str1 == *str2)) {
        str1 += 1;
        str2 += 1;
    }

    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

void flag_d(FILE* input_file, FILE* output_file) {
    if(input_file != NULL){
        int c;
        while ((c = fgetc(input_file)) != EOF) {
            if (!isdigit(c)) {
                fputc(c, output_file);
            }
        }
    }
}

void flag_i(FILE* input_file, FILE* output_file) {
    if (input_file != NULL){
        char line[256];
        while (fgets(line, sizeof(line), input_file)) {
            int count = 0;
            for (int i = 0; line[i] != '\0'; i++) {
                if (isalpha(line[i])) {
                    count++;
                }
            }
            fprintf(output_file, "%s %d\n", line, count);
        }
    }
}

void flag_s(FILE* input_file, FILE* output_file) {
    if (input_file != NULL){
        char line[256];
        while (fgets(line, sizeof(line), input_file)) {
            int count = 0;
            for (int i = 0; line[i] != '\0'; i++) {
                if (!isalpha(line[i]) && !isdigit(line[i]) && !isspace(line[i])) {
                    count++;
                }
            }
            fprintf(output_file, "%s %d\n", line, count);
        }
    }
}

void flag_a(FILE* input_file, FILE* output_file) {
    if (input_file != NULL){
        int c;
        while ((c = fgetc(input_file)) != EOF) {
            if (!isdigit(c)) {
                fprintf(output_file, "%02X", c);
            } else {
                fputc(c, output_file);
            }
        }
    }
}

void out_name(const char* filename, char* new_filename) {
    const char* prefix = "out_";
    
    int i = 0;
    while (prefix[i] != '\0') {
        new_filename[i] = prefix[i];
        i++;
    }

    int j = 0;
    while (filename[j] != '\0') {
        new_filename[i] = filename[j];
        i++;
        j++;
    }

    new_filename[i] = '\0';
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Incorrect number of arguments\n");
        return 1;
    }

    for (int i = fl_d; i <= fl_na; i++){
        if (strcmp(argv[1], Names_of_commands[i]) == 0){
            FILE* input_file = fopen(argv[2], "r");
            if (input_file == NULL) {
                printf("Failed to open input file\n");
                return 1;
            }
            char sd[64] = "";

            switch (i){
                case fl_d:
                    out_name(argv[2], sd);
                    FILE* file_d = fopen(sd, "w");
                    if (file_d == NULL) {
                        printf("Failed to open input file\n");
                        return 1;
                    }
                    flag_d(input_file, file_d);
                    fclose(file_d);
                    break;
                case fl_nd:
                    if (argc < 4){
                        printf("Missing output file path\n");
                        return 1;
                    }
                    FILE* file_nd = fopen(argv[3], "w");
                    if (file_nd == NULL) {
                        printf("Failed to open input file\n");
                        return 0;
                    }
                    flag_d(input_file, file_nd);
                    fclose(file_nd);
                    break;
                case fl_i:
                    out_name(argv[2], sd);
                    FILE* file_i = fopen(sd, "w");
                    if (file_i == NULL) {
                        printf("Failed to open input file\n");
                        return 0;
                    }
                    flag_i(input_file, file_i);
                    fclose(file_i);
                    break;
                case fl_ni:
                    if (argc < 4){
                        printf("Missing output file path\n");
                        return 1;
                    }
                    FILE* file_ni = fopen(argv[3], "w");
                    if (file_ni == NULL) {
                        printf("Failed to open input file\n");
                        return 0;
                    }
                    flag_i(input_file, file_ni);
                    fclose(file_ni);
                    break;
                case fl_s:
                    out_name(argv[2], sd);
                    FILE* file_s = fopen(sd, "w");
                    if (file_s == NULL) {
                        printf("Failed to open input file\n");
                        return 0;
                    }
                    flag_s(input_file, file_s);
                    fclose(file_s);
                    break;
                case fl_ns:
                    if (argc < 4){
                        printf("Missing output file path\n");
                        return 1;
                    }
                    FILE* file_ns = fopen(argv[3], "w");
                    if (file_ns == NULL) {
                        printf("Failed to open input file\n");
                        return 0;
                    }
                    flag_s(input_file, file_ns);
                    fclose(file_ns);
                    break;
                case fl_a:
                    out_name(argv[2], sd);
                    FILE* file_a = fopen(sd, "w");
                    if (file_a == NULL) {
                        printf("Failed to open input file\n");
                        return 0;
                    }
                    flag_a(input_file, file_a);
                    fclose(file_a);
                    break;
                case fl_na:
                    if (argc < 4){
                        printf("Missing output file path\n");
                        return 1;
                    }
                    FILE* file_na = fopen(argv[3], "w");
                    if (file_na == NULL) {
                        printf("Failed to open input file\n");
                        return 0;
                    }
                    flag_a(input_file, file_na);
                    fclose(file_na);
                    break;
            }
            fclose(input_file);
        }
    }
/*    char* flag = argv[1];
    char* input_file_path = argv[2];
    char output_file_path[256];

    FILE* input_file = fopen(input_file_path, "r");
    if (input_file == NULL) {
        printf("Failed to open input file\n");
        return 0;
    }

    FILE* output_file;

    if (flag[1] == 'd') {
        if (argc < 4) {
            printf("Missing output file path\n");
            fclose(input_file);
            return 0;
        }
        strcpy(output_file_path, argv[3]);
        output_file = fopen(output_file_path, "w");
        flag_d(input_file, output_file);
    } else if (flag[1] == 'i') {
        sprintf(output_file_path, "out_%s", input_file_path);
        output_file = fopen(output_file_path, "w");
        flag_i(input_file, output_file);
    } else if (flag[1] == 's') {
        sprintf(output_file_path, "out_%s", input_file_path);
        output_file = fopen(output_file_path, "w");
        flag_s(input_file, output_file);
    } else if (flag[1] == 'a') {
        sprintf(output_file_path, "out_%s", input_file_path);
        output_file = fopen(output_file_path, "w");
        flag_a(input_file, output_file);
    } else {
        printf("Invalid flag\n");
        fclose(input_file);
        return 0;
    }

    fclose(input_file);
    fclose(output_file);

    printf("Output file generated: %s\n", output_file_path);
*/
    return 0;
}