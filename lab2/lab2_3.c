#include <stdio.h>
#include <stdarg.h>

typedef enum {
    FILE_OPEN_SUCCESS,
    FILE_OPEN_FAILURE
} FileOpenStatus;

FileOpenStatus openFile(const char* filename, FILE** file) {
    *file = fopen(filename, "r");
    if (*file == NULL) {
        return FILE_OPEN_FAILURE;
    } else {
        return FILE_OPEN_SUCCESS;
    }
}

void searchInFiles(const char* substring, ...) {
    va_list args;
    va_start(args, substring);

    const char* filename;
    FILE* file;
    int filenameIndex = 0;
    while ((filename = va_arg(args, const char*)) != NULL) {
        FileOpenStatus status = openFile(filename, &file);
        if (status == FILE_OPEN_FAILURE) {
            printf("Cannot open file: %s\n", filename);
            continue;
        }

        int lineNum = 1;
        int charNum = 1;
        char ch;
        int substringIndex = 1;

        while ((ch = fgetc(file)) != EOF) {
            if (ch == substring[substringIndex]) {
                substringIndex++;
                if (substring[substringIndex] == '\0') {
                    printf("Found at line %d, position %d in file: %s\n", lineNum, charNum - substringIndex, filename);
                    substringIndex = 1;
                }
            } else {
                substringIndex = 1;
            }

            if (ch == '\n') {
                lineNum++;
                charNum = 1;
            } else {
                charNum++;
            }
        }

        fclose(file);

        filenameIndex++;
    }

    va_end(args);
}

int main() {
    searchInFiles("hello", "file1.txt", "file2.txt", "file3.txt", NULL);
    return 0;
}
