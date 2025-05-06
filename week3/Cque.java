import java.io.*;
import java.util.*;

class Student {
    String id;
    String name;
    String dob;
    double cgpa;

    public Student(String id, String name, String dob, double cgpa) {
        this.id = id;
        this.name = name;
        this.dob = dob;
        this.cgpa = cgpa;
    }

    @Override
    public String toString() {
        return id + " " + name + "  " + dob + " " + cgpa;
    }
}

class CircularQueue {
    private Student[] queue;
    private int front, rear, size;

    public CircularQueue(int capacity) {
        queue = new Student[capacity];
        front = 0;
        size = 0;
        rear = capacity - 1;
    }

    public void enqueue(Student student) {
        if (size == queue.length) {
            System.out.println("Queue is full");
            return;
        }
        rear = (rear + 1) % queue.length;
        queue[rear] = student;
        size++;
    }

    public Student dequeue() {
        if (size == 0) {
            System.out.println("Queue is empty");
            return null;
        }
        Student student = queue[front];
        front = (front + 1) % queue.length;
        size--;
        return student;
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public void display() {
        for (int i = 0; i < size; i++) {
            int index = (front + i) % queue.length;
            System.out.println(queue[index]);
        }
    }

    public void displayLowCGPA(double threshold) {
        System.out.println("NAME");
        for (int i = 0; i < size; i++) {
            int index = (front + i) % queue.length;
            if (queue[index].cgpa < threshold) {
                System.out.println(queue[index].name);
            }
        }
    }
}

public class Cque {
    public static void main(String[] args) {
        CircularQueue queue = new CircularQueue(10); // Adjust size as necessary

        try (BufferedReader reader = new BufferedReader(new FileReader("studentin.dat"));
             BufferedWriter writer = new BufferedWriter(new FileWriter("studentout.dat"))) {

            String line;
            while ((line = reader.readLine()) != null) {
                String[] data = line.split("\\s+");
                queue.enqueue(new Student(data[0], data[1], data[2], Double.parseDouble(data[3])));
            }

            // Dequeue and display/write operation
            while (!queue.isEmpty()) {
                Student student = queue.dequeue();
                System.out.println(student);
                writer.write(student.toString() + "\n");
            }

            // Re-enqueue for demo purposes (would normally refill from source)
            queue.enqueue(new Student("2021A7PS001", "AAAA", "1/1/2000", 7.50));
            queue.enqueue(new Student("2021A7PS004", "DDDD", "4/1/2000", 8.75));

            // Display names of students with CGPA less than 9
            queue.displayLowCGPA(9.0);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
