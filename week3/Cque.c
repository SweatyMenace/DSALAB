#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_SIZE 10

typedef struct {
    char id[20];
    char name[50];
    char dob[11];
    double cgpa;
} Student;

typedef struct {
    Student queue[QUEUE_SIZE];
    int front, rear, size;
} CircularQueue;

void initQueue(CircularQueue *cq) {
    cq->front = 0;
    cq->rear = QUEUE_SIZE - 1;
    cq->size = 0;
}

int isFull(CircularQueue *cq) {
    return cq->size == QUEUE_SIZE;
}

int isEmpty(CircularQueue *cq) {
    return cq->size == 0;
}

void enqueue(CircularQueue *cq, Student student) {
    if (isFull(cq)) {
        printf("Queue is full\n");
        return;
    }
    cq->rear = (cq->rear + 1) % QUEUE_SIZE;
    cq->queue[cq->rear] = student;
    cq->size++;
}

Student dequeue(CircularQueue *cq) {
    Student s = {0}; // Default empty student
    if (isEmpty(cq)) {
        printf("Queue is empty\n");
        return s;
    }
    s = cq->queue[cq->front];
    cq->front = (cq->front + 1) % QUEUE_SIZE;
    cq->size--;
    return s;
}

void displayQueue(CircularQueue *cq) {
    int i, index;
    for (i = 0; i < cq->size; i++) {
        index = (cq->front + i) % QUEUE_SIZE;
        printf("%s %s %s %.2f\n", cq->queue[index].id, cq->queue[index].name, cq->queue[index].dob, cq->queue[index].cgpa);
    }
}

void displayLowCGPA(CircularQueue *cq, double threshold) {
    printf("NAME\n");
    int i, index;
    for (i = 0; i < cq->size; i++) {
        index = (cq->front + i) % QUEUE_SIZE;
        if (cq->queue[index].cgpa < threshold) {
            printf("%s\n", cq->queue[index].name);
        }
    }
}

int main() {
    CircularQueue cq;
    initQueue(&cq);
    Student temp;

    FILE *file = fopen("studentin.dat", "r");
    if (file == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    while (fscanf(file, "%s %s %s %lf", temp.id, temp.name, temp.dob, &temp.cgpa) == 4) {
        enqueue(&cq, temp);
    }
    fclose(file);

    FILE *outfile = fopen("studentout.dat", "w");
    if (outfile == NULL) {
        perror("Failed to open file for output");
        return EXIT_FAILURE;
    }

    while (!isEmpty(&cq)) {
        temp = dequeue(&cq);
        fprintf(outfile, "%s %s %s %.2f\n", temp.id, temp.name, temp.dob, temp.cgpa);
        printf("%s %s %s %.2f\n", temp.id, temp.name, temp.dob, temp.cgpa);
    }
    fclose(outfile);

    // Re-enqueue for demo purposes (would normally refill from source)
    enqueue(&cq, (Student){"2021A7PS001", "AAAA", "1/1/2000", 7.50});
    enqueue(&cq, (Student){"2021A7PS004", "DDDD", "4/1/2000", 8.75});

    // Display names of students with CGPA less than 9
    displayLowCGPA(&cq, 9.0);

    return EXIT_SUCCESS;
}