import java.io.*;
import java.util.Scanner;

class Student {
    String idNo;
    String name;
    String dob; // Date of Birth
    double cgpa;

    public Student(String idNo, String name, String dob, double cgpa) {
        this.idNo = idNo;
        this.name = name;
        this.dob = dob;
        this.cgpa = cgpa;
    }

    @Override
    public String toString() {
        return idNo + "\t" + name + "\t" + dob + "\t" + cgpa;
    }
}

class Stack {
    private Student[] students;
    private int top;
    private int capacity;

    public Stack(int size) {
        students = new Student[size];
        capacity = size;
        top = -1;
    }

    public void push(Student student) {
        if (isFull()) {
            System.out.println("Stack Overflow");
            return;
        }
        students[++top] = student;
    }

    public Student pop() {
        if (isEmpty()) {
            System.out.println("Stack Underflow");
            return null;
        }
        return students[top--];
    }

    public boolean isEmpty() {
        return top == -1;
    }

    public boolean isFull() {
        return top == capacity - 1;
    }
}

public class StudentStack {
    public static void main(String[] args) throws FileNotFoundException {
        File file = new File("studentin1.dat");
        Scanner scanner = new Scanner(file);
        Stack stack = new Stack(10); // Assume a maximum stack size of 10

        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            String[] data = line.split("\t");
            Student student = new Student(data[0], data[1], data[2], Double.parseDouble(data[3]));
            stack.push(student);
        }
        scanner.close();

        PrintWriter writer = new PrintWriter("studentout1.dat");
        writer.println("ID\tNAME\tDOB\tCGPA");
        writer.println("==========================================");

        while (!stack.isEmpty()) {
            Student student = stack.pop();
            System.out.println(student);
            writer.println(student);
        }
        writer.close();
    }
}