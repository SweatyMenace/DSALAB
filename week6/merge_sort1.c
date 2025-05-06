#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define the Student structure
typedef struct {
    char name[50];
    int id;
    float salary;
} Student;

// Function to compare two students based on their names (alphabetically)
int compare(const void *a, const void *b) {
    return strcmp(((Student*)a)->name, ((Student*)b)->name);
}

// Merge function for merge sort
void merge(Student arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // Create temporary arrays
    Student L[n1], R[n2];
    
    // Copy data into temporary arrays
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    // Merge the temporary arrays back into arr[]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (compare(&L[i], &R[j]) <= 0) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    // Print the partially sorted array after every merge
    printf("Partially sorted names after merge:\n");
    for (int i = left; i <= right; i++) {
        printf("%s\n", arr[i].name);
    }
    printf("\n");
}

// Recursive Merge Sort function
void mergeSort(Student arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        // Sort the first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Function to generate random student records
void generateRandomStudentRecords(Student arr[], int n) {
    char *names[] = {"Alpha", "Beta", "Gamma", "Delta", "Elvis", "Roser", "George", "Hamilton", "Ivy", "Jacklin"};
    for (int i = 0; i < n; i++) {
        int randomNameIndex = rand() % 10; // Select a random name
        strcpy(arr[i].name, names[randomNameIndex]);
        arr[i].id = 1000 + rand() % 9000;  // Random ID between 1000 and 9999
        arr[i].salary = 30000 + (rand() % 50000);  // Random salary between 30000 and 80000
    }
}

// Function to print all student records
void printStudentRecords(Student arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Name: %s, ID: %d, Salary: %.2f\n", arr[i].name, arr[i].id, arr[i].salary);
    }
    printf("\n");
}

int main() {
    srand(time(0)); // Seed for random number generation
    
    int n = 7;
    Student students[n];
    
    // Generate random student records
    generateRandomStudentRecords(students, n);
    
    // Display unsorted records
    printf("Unsorted student records:\n");
    printStudentRecords(students, n);
    
    // Record the start time
    clock_t start = clock();
    
    // Sort the student records using mergeSort
    mergeSort(students, 0, n - 1);
    
    // Record the end time
    clock_t end = clock();
    
    // Display sorted records
    printf("Sorted student records (by name):\n");
    printStudentRecords(students, n);
    
    // Calculate and display the time taken for sorting
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken to sort the records: %.6f seconds\n", time_taken);
    
    return 0;
}
