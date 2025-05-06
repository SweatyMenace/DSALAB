import java.util.Scanner;

class Student {
    String name;
    int idno;
    String branch;
    double cgpa;
    Student prev, next;

    public Student(String name, int idno, String branch, double cgpa) {
        this.name = name;
        this.idno = idno;
        this.branch = branch;
        this.cgpa = cgpa;
        this.prev = null;
        this.next = null;
    }
}

class DLL {
    private Student head;

    public void addStudent(String name, int idno, String branch, double cgpa) {
        Student newStudent = new Student(name, idno, branch, cgpa);
        if (head == null) {
            head = newStudent;
        } else if (idno < head.idno) {
            newStudent.next = head;
            head.prev = newStudent;
            head = newStudent;
        } else {
            Student current = head;
            while (current.next != null && current.next.idno < idno) {
                current = current.next;
            }
            newStudent.next = current.next;
            if (current.next != null) {
                current.next.prev = newStudent;
            }
            current.next = newStudent;
            newStudent.prev = current;
        }
    }

    public void deleteStudent(int idno) {
        if (head == null) return;
        Student current = head;
        while (current != null && current.idno != idno) {
            current = current.next;
        }
        if (current == null) return;
        if (current.prev != null) {
            current.prev.next = current.next;
        } else {
            head = current.next;
        }
        if (current.next != null) {
            current.next.prev = current.prev;
        }
    }

    public void searchStudent(int idno) {
        Student current = head;
        while (current != null && current.idno != idno) {
            current = current.next;
        }
        if (current == null) {
            System.out.println("No student found with ID " + idno);
        } else {
            System.out.println("Student details are:");
            System.out.println("Name: " + current.name);
            System.out.println("IDNO: " + current.idno);
            System.out.println("Branch: " + current.branch);
            System.out.println("CGPA: " + current.cgpa);
        }
    }

    public void displayAll() {
        Student current = head;
        System.out.println("All Students' details are:");
        System.out.println("Name\tIDNO\tBRANCH\tCGPA");
        System.out.println("==========================");
        while (current != null) {
            System.out.println(current.name + "\t" + current.idno + "\t" + current.branch + "\t" + current.cgpa);
            current = current.next;
        }
    }

    public void bestPerformer() {
        if (head == null) {
            System.out.println("No students in list.");
            return;
        }
        Student current = head;
        Student best = head;
        while (current != null) {
            if (current.cgpa > best.cgpa) {
                best = current;
            }
            current = current.next;
        }
        System.out.println("Best performer details:");
        System.out.println("Name: " + best.name);
        System.out.println("IDNO: " + best.idno);
        System.out.println("Branch: " + best.branch);
        System.out.println("CGPA: " + best.cgpa);
    }
}

public class Doubly {
    public static void main(String[] args) {
        DLL list = new DLL();
        Scanner scanner = new Scanner(System.in);
        int choice;
        do {
            System.out.println("Options: 1. Add student 2. Delete student 3. Search Student 4. Display all 5. Best performer 6. Exit");
            System.out.println("Enter your choice: ");
            choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline
            switch (choice) {
                case 1: 
                    System.out.println("Enter name, idno, branch & cgpa: ");
                    String name = scanner.next();
                    int idno = scanner.nextInt();
                    String branch = scanner.next();
                    double cgpa = scanner.nextDouble();
                    list.addStudent(name, idno, branch, cgpa);
                    System.out.println("Addition Success!");
                    break;
                case 2:
                    System.out.println("Enter IDNO of student to delete: ");
                    idno = scanner.nextInt();
                    list.deleteStudent(idno);
                    System.out.println("Deletion Success!");
                    break;
                case 3:
                    System.out.println("Enter IDNO of student to search: ");
                    idno = scanner.nextInt();
                    list.searchStudent(idno);
                    break;
                case 4:
                    list.displayAll();
                    break;
                case 5:
                    list.bestPerformer();
                    break;
                case 6:
                    System.out.println("Bye Bye!");
                    break;
                default:
                    System.out.println("Invalid choice. Please choose again.");
            }
        } while (choice != 6);
        scanner.close();
    }
}
