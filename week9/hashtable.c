#include <stdio.h>

#include <string.h>

#include <ctype.h>



#define MAX_SIZE 7

#define EMPTY "EMPTY"

#define DELETED "DELETED"



typedef enum {EMPTY_SLOT, OCCUPIED, DELETED_SLOT} Status;



typedef struct {

    char key[100];

    Status status;

} HashTableEntry;



HashTableEntry table[MAX_SIZE];



int isSymbol(char ch) {

    return !isalnum(ch);

}



int computeHash(const char *str) {

    int sumAlpha = 0, sumDigits = 0, sumSymbols = 0;

    for (int i = 0; str[i]; ++i) {

        if (isalpha(str[i]))

            sumAlpha += str[i];

        else if (isdigit(str[i]))

            sumDigits += str[i];

        else if (isSymbol(str[i]))

            sumSymbols += str[i];

    }

    return (sumAlpha + 3 * sumDigits + 5 * sumSymbols + 7) % MAX_SIZE;

}



void displayTable() {

    printf("\n--- Full Hash Table ---\n");

    for (int i = 0; i < MAX_SIZE; ++i) {

        if (table[i].status == EMPTY_SLOT)

            printf("%d: %s\n", i, EMPTY);

        else if (table[i].status == DELETED_SLOT)

            printf("%d: %s\n", i, DELETED);

        else

            printf("%d: %s\n", i, table[i].key);

    }

}



int insertLinear(const char *key) {

    int hash = computeHash(key);

    for (int i = 0; i < MAX_SIZE; ++i) {

        int idx = (hash + i) % MAX_SIZE;

        if (table[idx].status == EMPTY_SLOT || table[idx].status == DELETED_SLOT) {

            strcpy(table[idx].key, key);

            table[idx].status = OCCUPIED;

            printf("Key %s added at index %d\n", key, idx);

            return 1;

        }

    }

    printf("Hash table full! Cannot insert %s\n", key);

    return 0;

}



int insertQuadratic(const char *key) {

    int hash = computeHash(key);

    for (int i = 0; i < MAX_SIZE; ++i) {

        int idx = (hash + i*i) % MAX_SIZE;

        if (table[idx].status == EMPTY_SLOT || table[idx].status == DELETED_SLOT) {

            strcpy(table[idx].key, key);

            table[idx].status = OCCUPIED;

            printf("Key %s added at index %d\n", key, idx);

            return 1;

        } else {

            printf("Collision detected @index %d for key:%s, Occupied by: %s\n", idx, key, table[idx].key);

        }

    }

    printf("Hash table full! Cannot insert %s\n", key);

    return 0;

}



int search(const char *key, int useQuadratic) {

    int hash = computeHash(key);

    for (int i = 0; i < MAX_SIZE; ++i) {

        int idx = useQuadratic ? (hash + i*i) % MAX_SIZE : (hash + i) % MAX_SIZE;

        if (table[idx].status == EMPTY_SLOT)

            break;

        if (table[idx].status == OCCUPIED && strcmp(table[idx].key, key) == 0) {

            printf("Key found!!\n");

            return idx;

        }

    }

    printf("Key not Found!!\n");

    return -1;

}



void deleteKey(const char *key, int useQuadratic) {

    int idx = search(key, useQuadratic);

    if (idx != -1) {

        table[idx].status = DELETED_SLOT;

        printf("Deleted %s\n", key);

    }

}



void initTable() {

    for (int i = 0; i < MAX_SIZE; ++i)

        table[i].status = EMPTY_SLOT;

}



int main() {

    int choice, strategy;

    char key[100];

    initTable();



    printf("Choose probing strategy: 1. Linear  2. Quadratic :: ");

    scanf("%d", &strategy);



    while (1) {

        printf("\nEnter your choice: 1.Add 2.Search 3.Delete 4.Display 5.Exit::");

        scanf("%d", &choice);

        getchar(); // to consume newline



        switch (choice) {

            case 1:

                printf("Enter the string to add: ");

                fgets(key, sizeof(key), stdin);

                key[strcspn(key, "\n")] = '\0';  // remove newline

                strategy == 1 ? insertLinear(key) : insertQuadratic(key);

                break;

            case 2:

                printf("Enter the string to search: ");

                fgets(key, sizeof(key), stdin);

                key[strcspn(key, "\n")] = '\0';

                search(key, strategy == 2);

                break;

            case 3:

                printf("Enter the string to delete: ");

                fgets(key, sizeof(key), stdin);

                key[strcspn(key, "\n")] = '\0';

                deleteKey(key, strategy == 2);

                break;

            case 4:

                displayTable();

                break;

            case 5:

                return 0;

            default:

                printf("Invalid choice!\n");

        }

    }

}
