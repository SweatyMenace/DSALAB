#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
    char name[50];
    int idno;
    char branch[5];
    float cgpa;
    struct student *prev;
    struct student *next;
} Student;

Student* insert_sorted(Student* head, char name[], int idno, char branch[], float cgpa) {
    Student* new_node = (Student*) malloc(sizeof(Student));
    strcpy(new_node->name, name);
    new_node->idno = idno;
    strcpy(new_node->branch, branch);
    new_node->cgpa = cgpa;
    new_node->prev = new_node->next = NULL;

    if (head == NULL) {
        head = new_node;
    } else if (idno < head->idno) {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    } else {
        Student *current = head;
        while (current->next != NULL && current->next->idno < idno) {
            current = current->next;
        }
        new_node->next = current->next;
        if (current->next != NULL) {
            current->next->prev = new_node;
        }
        current->next = new_node;
        new_node->prev = current;
    }
    return head;
}

Student* delete_student(Student* head, int idno) {
    if (head == NULL) {
        return head;
    }
    Student *current = head;
    while (current != NULL && current->idno != idno) {
        current = current->next;
    }
    if (current == NULL) {
        return head;
    }
    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        head = current->next;
    }
    if (current->next != NULL) {
        current->next->prev = current->prev;
    }
    free(current);
    return head;
}

void display_all(Student* head) {
    Student *current = head;
    printf("All Students' details are:\n");
    printf("Name\tIDNO\tBRANCH\tCGPA\n");
    printf("==========================\n");
    while (current != NULL) {
        printf("%s\t%d\t%s\t%.2f\n", current->name, current->idno, current->branch, current->cgpa);
        current = current->next;
    }
}

void search_student(Student* head, int idno) {
    Student *current = head;
    while (current != NULL && current->idno != idno) {
        current = current->next;
    }
    if (current == NULL) {
        printf("No student found with ID %d.\n", idno);
    } else {
        printf("Student details are:\n");
        printf("Name: %s\nIDNO: %d\nBranch: %s\nCGPA: %.2f\n", current->name, current->idno, current->branch, current->cgpa);
    }
}

void best_performer(Student* head) {
    if (head == NULL) {
        printf("No students in list.\n");
        return;
    }
    Student *current = head;
    Student *best = head;
    while (current != NULL) {
        if (current->cgpa > best->cgpa) {
            best = current;
        }
        current = current->next;
    }
    printf("Best performer details:\n");
    printf("Name: %s\nIDNO: %d\nBranch: %s\nCGPA: %.2f\n", best->name, best->idno, best->branch, best->cgpa);
}

int main() {
    Student *head = NULL;
    int choice, idno;
    char name[50], branch[5];
    float cgpa;

    do {
        printf("Options: 1. Add student 2. Delete student 3. Search Student 4. Display all 5. Best performer 6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("Enter name, idno, branch & cgpa: ");
                scanf("%s %d %s %f", name, &idno, branch, &cgpa);
                head = insert_sorted(head, name, idno, branch, cgpa);
                printf("Addition Success!\n");
                break;
            case 2:
                printf("Enter IDNO of student to delete: ");
                scanf("%d", &idno);
                head = delete_student(head, idno);
                printf("Deletion Success!\n");
                break;
            case 3:
                printf("Enter IDNO of student to search: ");
                scanf("%d", &idno);
                search_student(head, idno);
                break;
            case 4:
                display_all(head);
                break;
            case 5:
                best_performer(head);
                break;
            case 6:
                printf("Bye Bye!\n");
                break;
            default:
                printf("Invalid choice. Please choose again.\n");
        }
    } while (choice != 6);

    return 0;
}
