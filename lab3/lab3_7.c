#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>

enum Status {
    SUCCESS = 0,
    WRONG_INPUT = -1,
    ERROR_OF_FILE = -2,
    ERROR_OF_MEMORY = -3,
    EMPTY = -4,
    ZERO_UNDO = -5,
    ERROR = -2
};

enum options {
    NAME = 1,
    LAST_NAME = 2,
    MIDDLE_NAME = 3,
    SALARY = 4,
    GENDER = 5,
    BIRTH_DATE = 6,
};

enum Action {
    ADD = 'A',
    DELETE = 'D',
    CHANGE = 'C',
};

void PrintErrors(int choice) {
    switch (choice) {
        case WRONG_INPUT:
            printf("\nWrong input\n");
            break;
        case ERROR_OF_MEMORY:
            printf("\nError of memory\n");
            break;
        case ERROR_OF_FILE:
            printf("\nError of file\n");
            break;
        case EMPTY:
            printf("\nEmpty list.\n");
            break;
        case ZERO_UNDO:
            printf("\nNothing to undo.\n");
            break;
        default:
            break;
    }
}

typedef struct Liver {
    char name[BUFSIZ];
    char middle_name[BUFSIZ];
    char last_name[BUFSIZ];
    int day;
    int month;
    int year;
    char gender;
    double salary;
    struct Liver *next;
} Liver;

typedef struct UndoNode {
    int cnt;
    char action;
    char name[BUFSIZ];
    char middle_name[BUFSIZ];
    char last_name[BUFSIZ];
    int day;
    int month;
    int year;
    char gender;
    double salary;
    struct Liver* prev_state;
    struct UndoNode *next;
} UndoNode;

Liver *InsertSorted(Liver *head, Liver *new){
    Liver *curr = head;
    Liver *previous = NULL;

    while (curr != NULL && curr->year < new->year){
        previous = curr;
        curr = curr->next;
    }

    if (previous == NULL){
        new->next = head;
        head = new;
    } 
    else{
        previous->next = new;
        new->next = curr;
    }

    return head;
}

int Find(Liver *head){
    char name[BUFSIZ];
    char sur[BUFSIZ];
    char mid[BUFSIZ];
    int d, m, y;
    char gen;
    double sal;
    if (scanf("%s %s %s %d %d %d %c %lf", sur, name, mid, &d, &m, &y, &gen, &sal) != 8){
        while (getchar() != '\n'){
            return WRONG_INPUT;
        }
    }

    Liver *curr = head;
    while (curr != NULL){
        if (strcmp(curr->name, name) == 0 && strcmp(curr->middle_name, mid) == 0 && strcmp(curr->last_name, sur) == 0 
        && curr->day == d && curr->month == m && curr->year == y && curr->gender == gen && fabs(curr->salary - sal) < 1e-6){
            return 1;
        }
        curr = curr->next;
    }
    return 0;
}

void DeleteUndoLiver(Liver** head, UndoNode *node){
    Liver *current = *head;
    Liver *previous = NULL;

    while (current != NULL){
        if (strcmp(current->name, node->name) == 0 && strcmp(current->middle_name, node->middle_name) == 0 && strcmp(current->last_name, node->last_name) == 0 
        && current->year == node->year && current->day == node->day && current->month == node->month && fabs(current->salary - node->salary) < 1e-6){
            if (previous == NULL){
                *head = current->next;
            } 
            else{
                previous->next = current->next;
            }
            free(current);
        }
        previous = current;
        current = current->next;
    }
}

int AddUndoLiver(Liver **head, Liver **prev_state, UndoNode* node){
    Liver *new = (Liver *)malloc(sizeof(Liver));
    if (!new){
        return ERROR_OF_MEMORY;
    }

    strcpy(new->name, node->name);
    strcpy(new->middle_name, node->middle_name);
    strcpy(new->last_name, node->last_name);
    new->day = node->day;
    new->month = node->month;
    new->year = node->year;
    new->gender = node->gender;
    new->salary = node->salary;

    new->next = NULL;
    *head = InsertSorted(*head, new);

    if (*prev_state != NULL){
        *prev_state = (Liver *)malloc(sizeof(Liver));
        if (!*prev_state){
            free(new);
            return ERROR_OF_MEMORY;
        }
        memcpy(*prev_state, new, sizeof(Liver));
    }

    return SUCCESS;
}

UndoNode *AddUndo(UndoNode *undo_head, char action, const Liver *data, Liver* prev) {
    UndoNode *new = (UndoNode *)malloc(sizeof(UndoNode));
    if (!new){
        exit(EXIT_FAILURE);
    }

    new->action = action;
    strcpy(new->name, data->name);
    strcpy(new->middle_name, data->middle_name);
    strcpy(new->last_name, data->last_name);
    new->day = data->day;
    new->month = data->month;
    new->year = data->year;
    new->gender = data->gender;
    new->salary = data->salary;
    new->next = undo_head;

    if (prev != NULL){
        new->prev_state = prev;
    }

    free(prev);
    return new;
}

int AddLiver(Liver **head, Liver **prev_state, UndoNode** undo_head) {
    char name[BUFSIZ];
    char sur[BUFSIZ];
    char mid[BUFSIZ];
    int d, m, y;
    char gen;
    double sal;
    if (scanf("%s %s %s %d %d %d %c %lf", name, sur, mid, &d, &m, &y, &gen, &sal) != 8 || m > 12 || d > 31 ||
        m < 1 || d < 1 || y < 1 || (tolower(gen) != 'w' && tolower(gen) != 'm') || fabs(sal - 1e-6) < 0.0) {
        while (getchar() != '\n'){
            return WRONG_INPUT;
        }
    }

    Liver *new = (Liver *)malloc(sizeof(Liver));
    if (!new) {
        return ERROR_OF_MEMORY;
    }

    strcpy(new->name, name);
    strcpy(new->middle_name, mid);
    strcpy(new->last_name, sur);
    new->day = d;
    new->month = m;
    new->year = y;
    new->gender = gen;
    new->salary = sal;

    *undo_head = AddUndo(*undo_head, ADD, new, NULL);
    (*undo_head)->cnt += 1;

    new->next = NULL;
    *head = InsertSorted(*head, new);

    if (*prev_state != NULL){
        *prev_state = (Liver *)malloc(sizeof(Liver));
        if (!*prev_state) {
            free(new);
            return ERROR_OF_MEMORY;
        }
        memcpy(*prev_state, new, sizeof(Liver));
    }

    return SUCCESS;
}

int DeleteLiver(Liver **head, UndoNode **undo_head) {
    printf("Enter liver's parameters: ");

    char name[BUFSIZ];
    char sur[BUFSIZ];
    char mid[BUFSIZ];
    int d, m, y;
    char gen;
    double sal;

    if (scanf("%s %s %s %d %d %d %c %lf", sur, name, mid, &d, &m, &y, &gen, &sal) != 8){
        while (getchar() != '\n'){
            return WRONG_INPUT;
        }
    }

    Liver *current = *head;
    Liver *previous = NULL;

    while (current != NULL){
        if (strcmp(current->name, name) == 0 && strcmp(current->middle_name, mid) == 0 &&
            strcmp(current->last_name, sur) == 0 && current->year == y && current->day == d &&
            current->month == m && fabs(current->salary - sal) < 1e-6){
                
            *undo_head = AddUndo(*undo_head, DELETE, current, NULL);
            (*undo_head)->cnt += 1;

            if (!previous){
                *head = current->next;
            } 
            else{
                previous->next = current->next;
            }
            free(current);
            return 1;
        }
        previous = current;
        current = current->next;
    }

    return 0;
}

int LoadInfo(const char *filename, Liver **head){
    FILE *file = fopen(filename, "r");
    if (file == NULL){
        perror("Error opening file");
        return ERROR_OF_FILE;
    }

    *head = NULL;
    Liver *curr = NULL;

    char line[BUFSIZ];
    while (fgets(line, sizeof(line), file) != NULL){
        Liver *new = (Liver *)malloc(sizeof(Liver));
        if (!new){
            fclose(file);
            return ERROR_OF_MEMORY;
        }

        if (sscanf(line, "%s %s %s %d %d %d %c %lf", new->last_name, new->name, new->middle_name, &new->day, &new->month, &new->year, &new->gender, &new->salary) != 8 ||
            new->salary < 1e-6 || new->day < 1 || new->day > 31 || new->month < 1 || new->month > 12 || (tolower(new->gender) != 'w' && tolower(new->gender) != 'm')) {
            fclose(file);
            free(new);
            return ERROR_OF_FILE;
        }

        new->next = NULL;
        *head = InsertSorted(*head, new);
        curr = new;
    }

    fclose(file);
    return SUCCESS;
}

void PrintAll(Liver *head, FILE *file){
    Liver *curr = head;
    while (curr != NULL){
        fprintf(file, "%s %s %s %d %d %d %c %.2lf\n", curr->last_name, curr->name, curr->middle_name, curr->day, curr->month, curr->year, curr->gender, curr->salary);
        curr = curr->next;
    }
}

int ChangeUndoLiver(Liver **head, UndoNode* node, Liver* prev_node){
    Liver *current = *head;
    while (current != NULL){
        if (strcmp(current->name, node->name) == 0 && strcmp(current->middle_name, node->middle_name) == 0 && strcmp(current->last_name, node->last_name) == 0 && 
            current->year == node->year && current->day == node->day && current->month == node->month && fabs(current->salary - node->salary) < 1e-6){
            strcpy(current->name, prev_node->name);
            strcpy(current->middle_name, prev_node->middle_name);
            strcpy(current->last_name, prev_node->last_name);
            current->day = prev_node->day;
            current->month = prev_node->month;
            current->year = prev_node->year;
            current->gender = prev_node->gender;
            current->salary = prev_node->salary;
            break;
        }
        current = current->next;
    }

    return SUCCESS;
}

int ChangeLiver(Liver **head, int *oper, UndoNode** undo_head) {
    char name[BUFSIZ];
    char sur[BUFSIZ];
    char mid[BUFSIZ];
    int d, m, y;
    char gen;
    double sal;

    if (scanf("%s %s %s %d %d %d %c %lf", sur, name, mid, &d, &m, &y, &gen, &sal) != 8){
        while (getchar() != '\n'){
            return WRONG_INPUT;
        }
    }

    Liver *current = *head;

    bool flag = true;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && strcmp(current->middle_name, mid) == 0 && strcmp(current->last_name, sur) == 0 && current->year == y && 
            current->day == d && current->month == m && fabs(current->salary - sal) < 1e-6){
            char buf[BUFSIZ];
            int day1, month1, year1;
            char gender;
            double salary;
            while (flag){
                printf("\nChoose operation:\n");
                printf("1. Change name\n");
                printf("2. Change last name\n");
                printf("3. Change middle name\n");
                printf("4. Change salary\n");
                printf("5. Change gender\n");
                printf("6. Change date of birth\n");
                printf("0. Exit\n");
                printf("Enter number of operation: ");
                int choice;
                scanf("%d", &choice);
                printf("Enter the change: ");
                switch (choice) {
                    case NAME:
                        scanf("%s", buf);
                        strcpy(current->name, buf);
                        break;
                    case LAST_NAME:
                        scanf("%s", buf);
                        strcpy(current->last_name, buf);
                        break;
                    case MIDDLE_NAME:
                        scanf("%s", buf);
                        strcpy(current->middle_name, buf);
                        break;
                    case SALARY:
                        if (scanf("%lf", &salary) != 1){
                            return WRONG_INPUT;
                        } 
                        else{
                            current->salary = salary;
                        }
                        break;
                    case GENDER:
                        if (tolower(current->gender) == 'm'){
                            current->gender = 'w';
                            printf("\nSuccessfuly changed\n");
                        } 
                        else{
                            current->gender = 'm';
                            printf("\nSuccessfuly changed\n");
                        }
                        break;
                    case BIRTH_DATE:
                        if (scanf("%d %d %d", &day1, &month1, &year1) != 3){
                            return WRONG_INPUT;
                        } 
                        else{
                            current->day = day1;
                            current->month = month1;
                            current->year = year1;
                        }
                        break;
                    case 0:
                        flag = false;
                        break;
                    default:
                        printf("\nWrong input\n");
                        break;
                }
            }
            
            (*oper) += 1;

            Liver* prev_liver = (Liver*)malloc(sizeof(Liver));
            if(!prev_liver){
                return ERROR_OF_MEMORY;
            }

            strcpy(prev_liver->name, name);
            strcpy(prev_liver->middle_name, mid);
            strcpy(prev_liver->last_name, sur);
            prev_liver->day = d;
            prev_liver->month = m;
            prev_liver->year = y;
            prev_liver->salary = sal;
            prev_liver->gender = gen;

            *undo_head = AddUndo(*undo_head, CHANGE, current, prev_liver);
            (*undo_head)->cnt += 1;

            return 1;
        }
        current = current->next;
    }
    
    return 0;
}

int DoUndo(UndoNode **undo_head, Liver **head){
    if (undo_head == NULL || (*undo_head)->action == '-'){
        return EMPTY;
    }

    UndoNode *last_undo = *undo_head;
    *undo_head = (*undo_head)->next;

    Liver *prev_state = NULL;
    int status;
    switch (last_undo->action){
        case ADD:
            DeleteUndoLiver(head, last_undo);
            break;
        case DELETE:
            prev_state = *head;
            if ((status = AddUndoLiver(head, &prev_state, last_undo)) != SUCCESS){
                PrintErrors(status);
            }
            break;
        case CHANGE:
            if ((status = ChangeUndoLiver(head, last_undo, last_undo->prev_state)) != SUCCESS) {
                PrintErrors(status);
            }
            break;
        default:
            break;
    }

    free(last_undo);

    return SUCCESS;
}

void FreeUndoList(UndoNode *head){
    while (head != NULL){
        UndoNode *temp = head;
        head = head->next;

        if (temp->prev_state != NULL){
            free(temp->prev_state);
        }

        free(temp);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Wrong input. It should be <input file>\n");
        return WRONG_INPUT;
    }

    Liver *head = NULL;
    Liver *prev_state = NULL;
    UndoNode *undo_head = (UndoNode*)malloc(sizeof(UndoNode));
    if(!undo_head){
        printf("Error of memory\n");
        return ERROR_OF_MEMORY;
    }
    undo_head->cnt = 0;
    undo_head->action = '-';

    int status;
    if ((status = LoadInfo(argv[1], &head)) != SUCCESS){
        PrintErrors(status);
        return status;
    }

    char filename[256];
    bool flag = true;
    int choice = -1;
    int cnt_oper = 0;
    int cnt_undo = 0;
    while (flag) {
        printf("\nChoose your action:\n");
        printf("1. Print livers\n");
        printf("2. Add liver\n");
        printf("3. Find liver\n");
        printf("4. Save data to a file\n");
        printf("5. Undo\n");
        printf("6. Delete liver\n");
        printf("7. Change liver's info\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1){
            choice = -1;
        }

        switch (choice){
            case 1:
                if (head == NULL){
                    printf("\nEmpty list.\n");
                } 
                else{
                    PrintAll(head, stdout);
                }
                break;
            case 2:
                prev_state = head;
                printf("\nEnter the liver info in format <Surname> <Name> <Middle name> <birth day(dd mm yyyy)> <gender> <salary>: ");
                if ((status = AddLiver(&head, &prev_state, &undo_head)) != SUCCESS){
                    PrintErrors(status);
                    prev_state = NULL;
                } 
                else{
                    cnt_oper += 1;
                }
                break;
            case 3:
                if (head == NULL){
                    printf("\nEmpty list.\n");
                } 
                else{
                    printf("Enter paramteres of a liver in format <Surname> <Name> <Middle name> <birth day(dd mm yyyy)> <gender> <salary>: ");
                    if ((status = Find(head)) < 0){
                        PrintErrors(status);
                    } 
                    else{
                        printf("%s\n", (status == 1) ? "Found." : "Not found.");
                    }
                }
                break;
            case 4:
                printf("Enter filename: ");
                if (scanf("%255s", filename) != 1){
                    printf("Wrong input\n");
                } 
                else{
                    FILE *file = fopen(filename, "w");
                    if (file == NULL){
                        printf("Error of file\n");
                        break;
                    }
                    PrintAll(head, file);
                    fclose(file);
                }
                break;
            case 5:
                cnt_undo = cnt_oper / 2;
                if (cnt_undo == 0){
                    printf("\nNothing to undo.\n");
                } 
                else{
                    while (cnt_undo != 0){
                        if ((status = DoUndo(&undo_head, &head)) != SUCCESS){
                            PrintErrors(status);
                            break;
                        } 
                        else{
                            printf("Success\n");
                            cnt_undo -= 1;
                        }
                    }
                    cnt_oper = 0;
                }
                break;
            case 6:
                if (head == NULL){
                    printf("\nEmpty list.\n");
                } 
                else{
                    if ((status = DeleteLiver(&head, &undo_head)) < 0){
                        PrintErrors(status);
                    } 
                    else{
                        cnt_oper += 1;
                        printf("%s\n", (status == 1) ? "Deleted." : "Liver not found.");
                    }
                }
                break;
            case 7:
                if (head == NULL){
                    printf("\nEmpty list.\n");
                } 
                else{
                    printf("Enter paramteres of a liver in format <Surname> <Name> <Middle name> <birth day(dd mm yyyy)> <gender> <salary>: ");
                    if ((status = ChangeLiver(&head, &cnt_oper, &undo_head)) < 0){
                        PrintErrors(status);
                    } 
                    else{
                        printf("%s\n", (status == 1) ? "Changed." : "Liver not found.");
                    }
                }
                break;
            case 0:
                flag = false;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    if (prev_state != NULL){
        free(prev_state);
    }

    while (head != NULL){
        Liver *tmp = head;
        head = head->next;
        free(tmp);
    }

    FreeUndoList(undo_head);

    return 0;
}
