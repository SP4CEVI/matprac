#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

enum Status{
    SUCCESS,
    ERROR_OF_MEMORY,
    ERROR
};

typedef struct {
    char* data;
    int length;
} String;

typedef struct {
    String city;
    String street;
    int houseNumber;
    String building;
    int apartmentNumber;
    String recipientIndex;
} Address;

enum Status createString(String* str, const char* value) {
    if (str == NULL || value == NULL) {
        return ERROR;
    }

    str->length = strlen(value);
    str->data = (char*)malloc((str->length + 1) * sizeof(char));
    if (str->data == NULL) {
        return ERROR_OF_MEMORY;
    }

    strcpy(str->data, value);
    return SUCCESS;
}

enum Status deleteString(String* str) {
    if (str == NULL) {
        return ERROR;
    }

    free(str->data);
    str->data = NULL;
    str->length = 0;
    return SUCCESS;
}

typedef struct {
    Address recipient;
    double weight;
    String id;
    String creationTime;
    String creationDate;
    String deliveryTime;
} Mail;

typedef struct {
    Address* department;
    Mail* mails;
    int mailCount;
    Mail* deliveredMails;
    int deliveredMailCount;
    Mail* undeliveredMails;
    int undeliveredMailCount;
} Post;


void printAddress(Address* address) {
    printf("City: %s\n", address->city.data);
    printf("Street: %s\n", address->street.data);
    printf("House number: %d\n", address->houseNumber);
    printf("Building: %s\n", address->building.data);
    printf("Apartment number: %d\n", address->apartmentNumber);
    printf("Recipient index: %s\n", address->recipientIndex.data);
}

void printMail(Mail* mail) {
    printf("Recipient:\n");
    printAddress(&mail->recipient);
    printf("Weight: %.2f\n", mail->weight);
    printf("Id: %s\n", mail->id.data);
    printf("Creation time: %s %s\n", mail->creationDate.data, mail->creationTime.data);

    if (strlen(mail->deliveryTime.data) > 0) {
        printf("Delivery time: %s\n", mail->deliveryTime.data);
    } else {
        printf("Delivery time: Not delivered\n");
    }

    printf("\n");
}

Post createPost() {
    Post post;
    post.department = (Address*)malloc(sizeof(Address));
    if(post.department == NULL){
        return;
    }
    post.mailCount = 0;
    post.mails = NULL;
    return post;
}

void deletePost(Post* post) {
    if (post == NULL) {
        return;
    }

    deleteString(&post->department->city);
    deleteString(&post->department->street);
    deleteString(&post->department->building);
    deleteString(&post->department->recipientIndex);
    free(post->department);

    for (int i = 0; i < post->mailCount; i++) {
        deleteString(&post->mails[i].recipient.city);
        deleteString(&post->mails[i].recipient.street);
        deleteString(&post->mails[i].recipient.building);
        deleteString(&post->mails[i].recipient.recipientIndex);
        deleteString(&post->mails[i].id);
        deleteString(&post->mails[i].creationDate);
        deleteString(&post->mails[i].creationTime);
        deleteString(&post->mails[i].deliveryTime);
    }

    free(post->mails);
    post->mails = NULL;
    post->mailCount = 0;
}

int checkAllDigits(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}

bool checkDate(const char* date) {
    int day, month, year;
    int result = sscanf(date, "%d:%d:%d", &day, &month, &year);
    if (result != 6) {
        return false;
    }
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900) {
        return false;
    }
    return true;
}

bool checkTime(const char* time) {
    int hour, min, sec;
    int result = sscanf(time, "%d:%d:%d", &hour, &min, &sec);
    if (result != 6) {
        return false;
    }
    if (hour < 0 || hour > 23 || min < 0 || min > 59 || sec < 0 || sec > 59) {
        return false;
    }
    return true;
}

bool checkDateTimeFormat(const char* datetime) {
    int day, month, year, hour, min, sec;
    int result = sscanf(datetime, "%d:%d:%d %d:%d:%d", &day, &month, &year, &hour, &min, &sec);
    if (result != 6) {
        return false;
    }
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || hour < 0 || hour > 23 || min < 0 || min > 59 || sec < 0 || sec > 59) {
        return false;
    }
    return true;
}


int compareMail(const void* a, const void* b) {
    const Mail* mail1 = (const Mail*)a;
    const Mail* mail2 = (const Mail*)b;
    
    int indexComparison = strcmp(mail1->recipient.recipientIndex.data, mail2->recipient.recipientIndex.data);
    if (indexComparison != 0) {
        return indexComparison;
    }
    
    return strcmp(mail1->id.data, mail2->id.data);
}

enum Status addMail(Post* post) {
    Mail mail;
    String city, street, building, recipientIndex;
    createString(&city, "");
    createString(&street, "");
    createString(&building, "");
    createString(&recipientIndex, "");

    printf("Enter recipient's address:\n");
    printf("City: ");
    char temp[100];
    char temp1[100];
    scanf("%s", temp);
    if (strlen(temp) == 0) {
        printf("Invalid input. City cannot be empty.\n");
        return ERROR;
    }
    createString(&city, temp);

    printf("Street: ");
    scanf("%s", temp);
    if (strlen(temp) == 0) {
        printf("Invalid input. Street cannot be empty.\n");
        return ERROR;
    }
    createString(&street, temp); 

    printf("House number: ");
    if (scanf("%d", &(mail.recipient.houseNumber)) != 1 || mail.recipient.houseNumber <= 0) {
        printf("Invalid input. House number must be a positive integer.\n");
        return ERROR;
    }

    printf("Building: ");
    scanf("%s", temp);
    createString(&building, temp);

    printf("Apartment number: ");
    if (scanf("%d", &(mail.recipient.apartmentNumber)) != 1 || mail.recipient.apartmentNumber <= 0) {
        printf("Invalid input. Apartment number must be a positive integer.\n");
        return ERROR;
    }

    printf("Recipient index: ");
    scanf("%s", temp);
    if (strlen(temp) != 6 || !checkAllDigits(temp)) {
        printf("Invalid input. Recipient index must be a 6-digit number.\n");
        return ERROR;
    }
    createString(&recipientIndex, temp);

    mail.recipient.city = city;
    mail.recipient.street = street;
    mail.recipient.building = building;
    mail.recipient.recipientIndex = recipientIndex;

    printf("Enter mail details:\n");
    printf("Weight: ");
    if (scanf("%lf", &(mail.weight)) != 1 || mail.weight < 0) {
        printf("Invalid input. Weight must be a non-negative number.\n");
        return ERROR;
    }

    printf("Id: ");
    scanf("%s", temp);
    if (strlen(temp) != 14 || !checkAllDigits(temp)) {
        printf("Invalid input. Id must be a 14-digit number.\n");
        return ERROR;
    }
    createString(&(mail.id), temp);

    printf("Creation time (dd:MM:yyyy hh:mm:ss): ");
    scanf("%s %s", temp, temp1);
    createString(&(mail.creationDate), temp);
    createString(&(mail.creationTime), temp1);

    while (getchar() != '\n');

    printf("Delivery time (dd:MM:yyyy hh:mm:ss): ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = '\0';
    if (!checkDateTimeFormat(temp)) {
        printf("Invalid input. Please enter the time in the format dd:MM:yyyy hh:mm:ss\n");
        return ERROR;
    }
    createString(&(mail.deliveryTime), temp);
    
    if (strlen(mail.deliveryTime.data) > 0) {
        post->deliveredMailCount++;
        Mail* newDeliveredMails = (Mail*)realloc(post->deliveredMails, post->deliveredMailCount * sizeof(Mail));
        if (newDeliveredMails == NULL) {
            return ERROR_OF_MEMORY;
        }
        post->deliveredMails = newDeliveredMails;
        post->deliveredMails[post->deliveredMailCount - 1] = mail;
    } else {
        post->undeliveredMailCount++;
        Mail* newDeliveredMails = (Mail*)realloc(post->undeliveredMails, post->undeliveredMailCount * sizeof(Mail));
        if (newDeliveredMails == NULL) {
            return ERROR_OF_MEMORY;
        }
        post->undeliveredMails = newDeliveredMails;

        post->undeliveredMails[post->undeliveredMailCount - 1] = mail;
    }
    
    post->mailCount++;
    Mail* newDeliveredMails = (Mail*)realloc(post->undeliveredMails, post->undeliveredMailCount * sizeof(Mail));
    if (newDeliveredMails == NULL) {
        return ERROR_OF_MEMORY;
    }
    post->mails = newDeliveredMails;
    post->mails[post->mailCount - 1] = mail;

    return SUCCESS;
}


void removeMail(Post* post, const char* id) {
    int removalIndex = -1;
    int deliveryIndex = -1;
    int undeliveryIndex = -1;
    
    for (int i = 0; i < post->mailCount; i++) {
        if (strcmp(post->mails[i].id.data, id) == 0) {
            removalIndex = i;
            break;
        }
    }

    if (removalIndex != -1) {
        if (strlen(post->mails[removalIndex].deliveryTime.data) > 0) {
            for (int i = 0; i < post->deliveredMailCount; i++) {
                if (strcmp(post->deliveredMails[i].id.data, id) == 0) {
                    deliveryIndex = i;
                    break;
                }
            }
            
            if (deliveryIndex != -1) {
                for (int i = deliveryIndex; i < post->deliveredMailCount - 1; i++) {
                    post->deliveredMails[i] = post->deliveredMails[i + 1];
                }
                
                post->deliveredMailCount--;
                Mail* newDeliveredMails = (Mail*)realloc(post->deliveredMails, post->deliveredMailCount * sizeof(Mail));
                if (newDeliveredMails == NULL) {
                    printf("Error of memory.\n");
                    return ERROR_OF_MEMORY;
                }
                post->deliveredMails = newDeliveredMails;
            }
        } else {
            for (int i = 0; i < post->undeliveredMailCount; i++) {
                if (strcmp(post->undeliveredMails[i].id.data, id) == 0) {
                    undeliveryIndex = i;
                    break;
                }
            }
            
            if (undeliveryIndex != -1) {
                for (int i = undeliveryIndex; i < post->undeliveredMailCount - 1; i++) {
                    post->undeliveredMails[i] = post->undeliveredMails[i + 1];
                }
                
                post->undeliveredMailCount--;
                Mail* newDeliveredMails = (Mail*)realloc(post->deliveredMails, post->deliveredMailCount * sizeof(Mail));
                if (newDeliveredMails == NULL) {
                    printf("Error of memory.\n");
                    return ERROR_OF_MEMORY;
                }
                post->undeliveredMails = newDeliveredMails;
            }
        }
        
        deleteString(&post->mails[removalIndex].recipient.city);
        deleteString(&post->mails[removalIndex].recipient.street);
        deleteString(&post->mails[removalIndex].recipient.building);
        deleteString(&post->mails[removalIndex].recipient.recipientIndex);
        deleteString(&post->mails[removalIndex].id);
        deleteString(&post->mails[removalIndex].creationTime);
        deleteString(&post->mails[removalIndex].deliveryTime);
        deleteString(&post->mails[removalIndex].creationDate);
        
        for (int i = removalIndex; i < post->mailCount - 1; i++) {
            post->mails[i] = post->mails[i + 1];
        }

        post->mailCount--;
        Mail* newDeliveredMails = (Mail*)realloc(post->deliveredMails, post->deliveredMailCount * sizeof(Mail));
        if (newDeliveredMails == NULL) {
            printf("Error of memory.\n");
            return ERROR_OF_MEMORY;
        }
        post->mails = newDeliveredMails;
    }
}


Mail* findMailById(Post* post, const char* id) {
    for (int i = 0; i < post->mailCount; i++) {
        if (strcmp(post->mails[i].id.data, id) == 0) {
            return &(post->mails[i]);
        }
    }
    
    for (int i = 0; i < post->deliveredMailCount; i++) {
        if (strcmp(post->deliveredMails[i].id.data, id) == 0) {
            return &(post->deliveredMails[i]);
        }
    }
    
    for (int i = 0; i < post->undeliveredMailCount; i++) {
        if (strcmp(post->undeliveredMails[i].id.data, id) == 0) {
            return &(post->undeliveredMails[i]);
        }
    }

    return NULL;
}


int compareDeliveredMail(const void* a, const void* b) {
    const Mail* mail1 = (const Mail*)a;
    const Mail* mail2 = (const Mail*)b;
    
    return strcmp(mail1->creationTime.data, mail2->creationTime.data);
}

int compareUndeliveredMail(const void* a, const void* b) {
    const Mail* mail1 = (const Mail*)a;
    const Mail* mail2 = (const Mail*)b;
    
    return strcmp(mail1->creationTime.data, mail2->creationTime.data);
}

void searchAllDelivered(Post* post) {
    printf("Delivered mails:\n");
    qsort(post->deliveredMails, post->deliveredMailCount, sizeof(Mail), compareDeliveredMail);
    for (int i = 0; i < post->deliveredMailCount; i++) {
        printMail(&post->deliveredMails[i]);
    }
    printf("\n");
}

void searchAllUndelivered(Post* post) {
    printf("Undelivered mails:\n");
    qsort(post->undeliveredMails, post->undeliveredMailCount, sizeof(Mail), compareUndeliveredMail);
    for (int i = 0; i < post->undeliveredMailCount; i++) {
        printMail(&post->undeliveredMails[i]);
    }
    printf("\n");
}

int main() {
    Post post = createPost();

    int option;
    char id[15];

    do {
        printf("Select an option:\n");
        printf("1. Add mail\n");
        printf("2. Remove mail\n");
        printf("3. Search mail by id\n");
        printf("4. Search delivered mail\n");
        printf("5. Search undelivered mail\n");
        printf("6. Exit\n");
        printf("Option: ");
        scanf("%d", &option);
        printf("\n");

        switch (option) {

            case 1:
                addMail(&post);
                break;
            case 2:
                printf("Enter id of mail to remove: ");
                scanf("%s", id);
                removeMail(&post, id);
                break;
            case 3:
                printf("Enter id of mail to search: ");
                scanf("%s", id);
                Mail* foundMail = findMailById(&post, id);
                if (foundMail != NULL) {
                    printf("Mail found:\n");
                    printMail(foundMail);
                } else {
                    printf("Mail not found.\n");
                }
                break;
            case 4:
                searchAllDelivered(&post);
                break;
            case 5:
                searchAllUndelivered(&post);
                break;
            case 6:
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
        printf("\n");
    } while (option != 6);

    deletePost(&post);

    return 0;
}
