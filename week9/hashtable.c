#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 7
#define EMPTY 0
#define OCCUPIED 1
#define DELETED 2

typedef struct {
    char key[100];
    int state;
} HashEntry;

HashEntry hashTable[MAX_SIZE];

int calculateHash(const char *str) {
    int sumAlpha = 0, sumDigits = 0, sumSymbols = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i])) {
            sumAlpha += str[i];
        } else if (isdigit(str[i])) {
            sumDigits += str[i];
        } else {
            sumSymbols += str[i];
        }
    }
    return (sumAlpha + 3 * sumDigits + 5 * sumSymbols + 7) % MAX_SIZE;
}

void initializeHashTable() {
    for (int i = 0; i < MAX_SIZE; i++) {
        hashTable[i].state = EMPTY;
    }
}

void addLinear(const char *key) {
    int hash = calculateHash(key);
    int index = hash;
    while (hashTable[index].state == OCCUPIED) {
        if (strcmp(hashTable[index].key, key) == 0) {
            printf("Key %s already exists at index %d\n", key, index);
            return;
        }
        index = (index + 1) % MAX_SIZE;
        if (index == hash) {
            printf("Hash table is full!\n");
            return;
        }
    }
    strcpy(hashTable[index].key, key);
    hashTable[index].state = OCCUPIED;
    printf("Key %s added at index %d\n", key, index);
}

void addQuadratic(const char *key) {
    int hash = calculateHash(key);
    int index = hash, i = 1;
    while (hashTable[index].state == OCCUPIED) {
        if (strcmp(hashTable[index].key, key) == 0) {
            printf("Key %s already exists at index %d\n", key, index);
            return;
        }
        printf("Collision detected @index %d for key:%s,Occupied by: %s\n", index, key, hashTable[index].key);
        index = (hash + i * i) % MAX_SIZE;
        i++;
        if (i == MAX_SIZE) {
            printf("Hash table is full!\n");
            return;
        }
    }
    strcpy(hashTable[index].key, key);
    hashTable[index].state = OCCUPIED;
    printf("Key %s added at index %d\n", key, index);
}

void search(const char *key) {
    int hash = calculateHash(key);
    int index = hash, i = 1;
    while (hashTable[index].state != EMPTY) {
        if (hashTable[index].state == OCCUPIED && strcmp(hashTable[index].key, key) == 0) {
            printf("Key found!!\n");
            return;
        }
        index = (hash + i * i) % MAX_SIZE; 
        i++;
        if (i == MAX_SIZE) break;
    }
    printf("Key not Found!!\n");
}

void deleteKey(const char *key) {
    int hash = calculateHash(key);
    int index = hash, i = 1;
    while (hashTable[index].state != EMPTY) {
        if (hashTable[index].state == OCCUPIED && strcmp(hashTable[index].key, key) == 0) {
            hashTable[index].state = DELETED;
            printf("Deleted %s\n", key);
            return;
        }
        index = (hash + i * i) % MAX_SIZE; 
        i++;
        if (i == MAX_SIZE) break;
    }
    printf("Key not Found!!\n");
}

void displayHashTable() {
    printf("\n--- Full Hash Table ---\n");
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("%d: ", i);
        if (hashTable[i].state == EMPTY) {
            printf("EMPTY\n");
        } else if (hashTable[i].state == DELETED) {
            printf("DELETED\n");
        } else {
            printf("%s\n", hashTable[i].key);
        }
    }
}

void main() {
    int choice, probingType;
    char key[100];

    initializeHashTable();

    printf("Choose probing strategy: \n1. Linear Probing \n2. Quadratic Probing: \n");
    scanf("%d", &probingType);

    do {
        printf("\nEnter your choice: \n1. Add \n2. Search \n3. Delete \n4. Display \n5. Exit:\n:");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter the string to add:");
                scanf("%s", key);
                if (probingType == 1) {
                    addLinear(key);
                } else {
                    addQuadratic(key);
                }
                break;
            case 2:
                printf("Enter the string to search:");
                scanf("%s", key);
                search(key);
                break;
            case 3:
                printf("Enter the string to delete:");
                scanf("%s", key);
                deleteKey(key);
                break;
            case 4:
                displayHashTable();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);
}