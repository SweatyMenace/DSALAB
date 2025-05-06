#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 10

// Structure to store student records
typedef struct {
    char name[50];
    int id;
    float cgpa;
} Student;

int main() {
    Student students[SIZE];
    srand(time(0));
    
    // Generating random student records
    const char *names[] = {"Sharthak", "Ravi", "Anil", "Sreyansh", "Ivy", "Jui", "Gaurav", "Harish", "Imon", "Zubair"};
    for (int i = 0; i < SIZE; i++) {
        strcpy(students[i].name, names[rand() % 10]);
        students[i].id = rand() % 1000 + 1;
        students[i].cgpa = (float)(rand() % 401) / 100; // Random CGPA between 0.00 and 4.00
    }
    
    printf("Unsorted Student Records:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%s (ID: %d, CGPA: %.2f)\n", students[i].name, students[i].id, students[i].cgpa);
    }
    
    clock_t start = clock();
    
    // QuickSort without function
    int stack[SIZE], top = -1;
    int low = 0, high = SIZE - 1;
    stack[++top] = low;
    stack[++top] = high;
    
    while (top >= 0) {
        high = stack[top--];
        low = stack[top--];
        
        float pivot = students[high].cgpa;
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (students[j].cgpa <= pivot) {
                i++;
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
        Student temp = students[i + 1];
        students[i + 1] = students[high];
        students[high] = temp;
        int pi = i + 1;
        
        // Display intermediate stage
        printf("\nAfter partition step:\n");
        for (int k = 0; k < SIZE; k++) {
            printf("%s (ID: %d, CGPA: %.2f)\n", students[k].name, students[k].id, students[k].cgpa);
        }
        
        if (pi - 1 > low) {
            stack[++top] = low;
            stack[++top] = pi - 1;
        }
        if (pi + 1 < high) {
            stack[++top] = pi + 1;
            stack[++top] = high;
        }
    }
    
    clock_t end = clock();
    
    printf("\nSorted Student Records (by CGPA):\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%s (ID: %d, CGPA: %.2f)\n", students[i].name, students[i].id, students[i].cgpa);
    }
    
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTime taken to sort: %f seconds\n", time_taken);
    
    return 0;
}

