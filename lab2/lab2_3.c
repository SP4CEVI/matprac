#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>

enum Status {
    SUCCESS,
    ERROR_FILE_OPEN,
    SUBSTRING_NOT_FOUND
};

char* my_strstr(const char* haystack, const char* needle) {
    if (*needle == '\0') {
        return (char*)haystack;
    }
    
    while (*haystack) {
        const char* h = haystack;
        const char* n = needle;
        
        while (*h && *n && (*h == *n)) {
            h++;
            n++;
        }
        
        if (*n == '\0') {
            return (char*)haystack;
        }
        
        haystack++;
    }
    
    return NULL;
}

enum Status find_substring_in_files(const char* substring, int count, ...) {
    va_list files;
    va_start(files, count);

    enum Status status = SUCCESS;

    for (int i = 0; i < count; i++) {
        const char* filename = va_arg(files, const char*);

        FILE* file = fopen(filename, "r");
        if (!file) {
            printf("Failed to open file: %s\n", filename);
            status = ERROR_FILE_OPEN;
            continue;
        }

        char* line = NULL;
        size_t line_size = 0;
        ssize_t read;

        int line_number = 1;
        int found = 0;

        while ((read = getline(&line, &line_size, file)) != -1) {
            char* position = line;

            while ((position = my_strstr(position, substring)) != NULL) {
                int column_number = position - line + 1;

                printf("File: %s, Line: %d, Char: %d\n", filename, line_number, column_number);

                position++;
                found = 1;
            }

            line_number++;
        }

        if (!found) {
            printf("Substring not found in file: %s\n", filename);
            status = SUBSTRING_NOT_FOUND;
        }

        fclose(file);
    }

    va_end(files);

    return status;
}

int main() {
    enum Status result = find_substring_in_files("h", 3, "file1.txt", "file2.txt", "file3.txt");
    printf("Search completed successfully\n");
    return 0;
}
