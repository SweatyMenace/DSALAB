#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100  // Define the maximum size of the stack

typedef struct {
    char id[15];
    char name[20];
    char dob[15];
    float cgpa;
} Student;

Student stack[MAX];  // Stack to store student records
int top = -1;  // Stack pointer

// Function to push a student record onto the stack
void push(Student s) {
    if (top >= MAX - 1) {
        printf("Stack Overflow! Cannot push more records.\n");
        return;
    }
    stack[++top] = s;

}

// Function to pop a student record from the stack
Student pop() {
    if (top < 0) {
        printf("Stack Underflow! No records to pop.\n");
        exit(1);
    }
    return stack[top--];
}

// Function to read student records from a file and push them onto the stack
void readFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening input file.\n");
        exit(1);
    }
    
    Student s;
    while (fscanf(file, "%s %s %s %f", s.id, s.name, s.dob, &s.cgpa) == 4) {
        push(s);
    }
    fclose(file);
}

// Function to write student records to a file and display them
void writeToFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening output file.\n");
        exit(1);
    }
    
    printf("ID\t\tNAME\tDOB\t\tCGPA\n");
    printf("==========================================\n");
    fprintf(file, "ID\t\tNAME\tDOB\t\tCGPA\n");
    fprintf(file, "==========================================\n");
    
    while (top >= 0) {
        Student s = pop();
        printf("%s\t%s\t%s\t%.2f\n", s.id, s.name, s.dob, s.cgpa);
        fprintf(file, "%s\t%s\t%s\t%.2f\n", s.id, s.name, s.dob, s.cgpa);
    }
    fclose(file);
}

int main() {
    readFromFile("studentin.dat");
    writeToFile("studentout.dat");
    return 0;
}
