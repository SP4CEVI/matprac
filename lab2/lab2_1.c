#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

enum Status {
    GOOD
};

int length(char* str) {
   int len = 0;
   while (*str != '\0') {
      str += 1;
      len += 1;
   }
   return len;
}

void my_strcat(char* dest, const char* src) {
    while (*dest != '\0') {
        dest += 1;
    }
    
    while (*src != '\0') {
        *dest = *src;
        dest += 1;
        src += 1;
    }
    *dest = '\0';
}

enum Status my_len(char* str, int* len) {
   char* ptr = str;
   while (*ptr != '\0') {
      *len += 1;
      ptr += 1;
   }
   return GOOD;
}

enum Status reverse(char* str, char* rts) {
   rts[length(str)] = '\0';
   for (int i = 0; i != length(str); i++) {
      rts[length(str) - i - 1] = str[i];
   }
   return GOOD;
}

enum Status my_upper(char* str, char* up) {
   up[length(str)] = '\0';
   for (int i = 0; i != length(str); i++) {
      if (i % 2) {
         up[i] = toupper(str[i]);
      } 
      else {
         up[i] = str[i];
      }
   }
   return GOOD;
}

enum Status formatted(char* str, char* form) {
   form[length(str)] = '\0';
   int len = 0;

   for (int i = 0; i != length(str); i++) {
      if (isdigit(str[i])) {
         len += 1;
         form[len - 1] = str[i];
      }
   }

   for (int i = 0; i != length(str); i++) {
      if (isalpha(str[i])) {
         len += 1;
         form[len - 1] = str[i];
      }
   }

   for (int i = 0; i != length(str); i++) {
      if (!isalpha(str[i]) && !isdigit(str[i])) {
         len += 1;
         form[len - 1] = str[i];
      }
   }

   return GOOD;
}

enum Status concatenated(char** str, char* ret, const int n, int len, int seed) {
   srand(seed);
   int indices[n];
   int index;
   int dupl;
   int random = rand() % n;

   for (int i = 0; i < n; i++) {
      if (random == i) {
         my_strcat(ret, str[2]);
      } 
      else {
         do {
            index = rand() % (n - 1);
            dupl = 0;
            for (int j = 0; j < i + 1; j++) {
               if (indices[j] == index) {
                  dupl = 1;
                  break;
               }
            }
         } while (dupl);
         indices[i + 1] = index;
         my_strcat(ret, str[index + 4]);
      }
   }
   
   return GOOD;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Invalid number of arguments\n");
        return 1;
    }
    int len = 0;
    char* rev;
    char* upper;
    char* forma;
    int seed;
    int l;
    int n = 1;
    char* con;
    if ((argv[1][0] == '-') && (length(argv[1]) == 2)) {
        switch (argv[1][1]) {
            case 'l':
                my_len(argv[2], &len);
                printf("%d\n", len);
                break;
            case 'r':
                if ((rev = (char*)malloc(sizeof(char) * length(argv[2]) + 1)) == NULL) {
                    printf("Error of memory\n");
                    return 2;
                }

                reverse(argv[2], rev);
                printf("%s\n", rev);

                free(rev);
                break;
            case 'u':
                if ((upper = (char*)malloc(sizeof(char) * length(argv[2]) + 1)) == NULL) {
                    printf("Error of memory\n");
                    return 3;
                }

                my_upper(argv[2], upper);
                printf("%s\n", upper);

                free(upper);
                break;
            case 'n':
                if ((forma = (char*)malloc(sizeof(char) * length(argv[2]) + 1)) == NULL) {
                    printf("Error of memory\n");
                    return 4;
                }

                formatted(argv[2], forma);
                printf("%s\n", forma);

                free(forma);
                break;
            case 'c':
                if (argc < 4) {
                    printf("Invalid number of arguments\n");
                    return 5;
                }
                seed = atoi(argv[3]);
                if (seed < 0) {
                    seed *= -1;
                }

                l = length(argv[2]);
                for (int i = 4; i < argc; i++) {
                    n += 1;
                    l += length(argv[i]);
                }

                if ((con = (char*)malloc(sizeof(char) * l + 1)) == NULL) {
                    printf("Error of memory\n");
                    return 6;
                }

                concatenated(argv, con, n, l, seed);
                printf("%s\n", con);

                free(con);
                break;
            default:
                printf("Invalid flag\n");
                return 7;
        }
    } 
    else {
        printf("Invalid flag\n");
        return 8;
    }

    return 0;
}