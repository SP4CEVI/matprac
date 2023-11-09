#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef enum {
    SUCCESS,
    INCORRECT_BASE,
    NUMBER_IS_ZERO,
    ERROR
} ErrorCode;

void dumpSignedInt(int *ptr) {
    unsigned char *bytePtr = (unsigned char *)ptr;

    for (int i = sizeof(int) - 1; i >= 0; --i) {
        for (int j = 7; j >= 0; --j) {
            printf("%d", (bytePtr[i] >> j) & 1);
        }
        printf(" ");
    }
}

ErrorCode intToBinOctHex(const int number, const int r) {
    if (r < 1 || r > 5){
        return INCORRECT_BASE;
    }
    
    if (number == 0) {
        return NUMBER_IS_ZERO;
    } 
    else if (number < 0) {
        printf("-");
        intToBinOctHex(-1 * number, r);
        return SUCCESS;
    }

    unsigned char *bytePtr = (unsigned char *)&number;
    if (bytePtr == NULL){
        return ERROR;
    }
    int bitsRead = 0;
    if (32 % r != 0){
        bitsRead = r - (32 % r);
    }
    int zeroFlag = 0;
    int digit = 0;
    for (int i = sizeof(int) - 1; i >= 0; --i) {
        for (int j = 7; j >= 0; --j) {
            ++bitsRead;
            digit = digit | (bytePtr[i] >> j & 1) << (r - bitsRead);
            if (bitsRead == r) {
                if (digit != 0 || zeroFlag != 0) 
                {
                    zeroFlag = 1;
                    char out = (digit < 10) ? (char)(digit + '0') : (char)(digit - 10 + 'A');
                    printf("%c", out);
                }
                bitsRead = 0;
                digit = 0;
            }
        }
    }
    return SUCCESS;
}

int main() {
    int number = -1001;
    int r = 11;

    switch (intToBinOctHex(number, r)) {
        case INCORRECT_BASE:
            printf("Wrong r. r must be between 1 and 5/\n");
            return 1;
        case NUMBER_IS_ZERO:
            printf("0\n");
            break;
        default:
            break;
    }
    return 0;
}