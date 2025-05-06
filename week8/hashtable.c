#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 7

typedef struct Node {
    char key[50];
    struct Node* next;
} Node;

Node* hashTable[MAX_SIZE] ;

int calculateHashValue(const char* str) {
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

void insert(const char* key) {
    int hashIndex = calculateHashValue(key);
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->key, key);
    newNode->next = hashTable[hashIndex];
    hashTable[hashIndex] = newNode;
}

int search(const char* key) {
    int hashIndex = calculateHashValue(key);
    Node* temp = hashTable[hashIndex];
    while (temp) {
        if (strcmp(temp->key, key) == 0) {
            return hashIndex;
        }
        temp = temp->next;
    }
    return -1;
}

void deleteKey(const char* key) {
    int hashIndex = calculateHashValue(key);
    Node* temp = hashTable[hashIndex];
    Node* prev = NULL;

    while (temp) {
        if (strcmp(temp->key, key) == 0) {
            if (prev) {
                prev->next = temp->next;
            } else {
                hashTable[hashIndex] = temp->next;
            }
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

void displayHashTable() {
    for (int i = 0; i < MAX_SIZE; i++) {
        printf("[%d]:", i);
        Node* temp = hashTable[i];
        while (temp) {
            printf(" -> %s", temp->key);
            temp = temp->next;
        }
        printf("\n");
    }
}

void main() {
    printf("Hash Table Implementation\n");
    
    int choice = 0;
    int n ;
    char* keys[20];
    
    while(choice!=5)
    {
       
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter you choice:\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter keys (max 20, end with 'exit'):\n");
                for (int i = 0; i < 20; i++) {
                    keys[i] = (char*)malloc(5 * sizeof(char));
                    scanf("%s", keys[i]);
                    if (strcmp(keys[i], "exit") == 0) {
                        free(keys[i]);
                        break;
                    }
                }
                n = sizeof(keys) / sizeof(keys[0]);
                printf("Hash values:\n");
                for (int i = 0; i < n; i++) {
                    printf("Hash value for %s = %d\n", keys[i], calculateHashValue(keys[i]));
                }

                for (int i = 0; i < n; i++) {
                    insert(keys[i]);
                }
                break;
            case 2:
                printf("\nEnter a key to search: ");
                char searchKey[3] ;
                scanf("%s", searchKey);
                int searchResult = search(searchKey);
                if (searchResult != -1) {
                    printf("\nSearch: %s found at index %d\n", searchKey, searchResult);
                } else {
                    printf("\nSearch: %s not found\n", searchKey);
                }
                break;
            case 3:
                printf("\nEnter a key to delete: ");
                char deleteKeyStr[3];
                scanf("%s",deleteKeyStr);
                printf("\nDelete: %s\n", deleteKeyStr);
                deleteKey(deleteKeyStr);
                printf("\nHash table after deletion:\n");
                displayHashTable();
                break;
            case 4:
                displayHashTable();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
}