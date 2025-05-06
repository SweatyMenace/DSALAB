import java.util.*;


public class MergeSort
{
    public static void main(String[] args)
    {
        List<Student> list = generateList(10);

        System.out.println("Unsorted Student Records:");
        printTable(list);

        long start = System.nanoTime();
        mergeSort(list, 0, list.size() - 1);
        long end = System.nanoTime();

        System.out.println("\nSorted Student Records:");
        printTable(list);
        System.out.printf("\nSorting Time: %.4f ms\n", (end - start) / 1e6);
    }

    // Merge Sort
    public static void mergeSort(List<Student> list, int l, int r) 
    {
        if (l < r) 
        {
            int m = l + (r - l) / 2;
            mergeSort(list, l, m);
            mergeSort(list, m + 1, r);
            merge(list, l, m, r);
        }
    }

    // Merge Function
    public static void merge(List<Student> list, int l, int m, int r) 
    {
        List<Student> left = new ArrayList<>(list.subList(l, m + 1));
        List<Student> right = new ArrayList<>(list.subList(m + 1, r + 1));

        int i = 0, j = 0, k = l;
        while (i < left.size() && j < right.size()) 
        {
            list.set(k++, left.get(i).name.compareTo(right.get(j).name) <= 0 ? left.get(i++) : right.get(j++));
        }
        while (i < left.size()) list.set(k++, left.get(i++));
        while (j < right.size()) list.set(k++, right.get(j++));

        // Show intermediate merge progress
        System.out.printf("\nMerged [%d-%d]:\n", l + 1, r + 1);
        printTableRange(list, l, r);
    }

    // Generate Random Student Records
    public static List<Student> generateList(int n) 
    {
        String[] names = {"Aarav", "Bhavya", "Charan", "Divya", "Esha", "Farhan", "Gautam", "Harsh", "Ishaan", "Jaya"};
        List<Student> list = new ArrayList<>();
        Random rand = new Random();

        for (int i = 0; i < n; i++) {
            String name = names[rand.nextInt(names.length)];
            String id = "2023A7PS0" + (100 + rand.nextInt(900)) + "U";
            double salary = 30000 + rand.nextDouble() * 50000;
            list.add(new Student(i + 1, name, id, salary));
        }
        return list;
    }

    // Print Table Header & Data
    public static void printTable(List<Student> list) 
    {
        System.out.println("+-------+----------+-----------------+------------+");
        System.out.println("| S No.  | Name     | ID              | Salary     |");
        System.out.println("+-------+----------+-----------------+------------+");
        for (Student s : list) System.out.println(s);
        System.out.println("+-------+----------+-----------------+------------+\n");
    }

    // Print Partial Table for Merge Steps
    public static void printTableRange(List<Student> list, int l, int r) 
    {
        System.out.println("+-------+----------+-----------------+------------+");
        System.out.println("| S No.  | Name     | ID              | Salary     |");
        System.out.println("+-------+----------+-----------------+------------+");
        for (int i = l; i <= r; i++) System.out.println(list.get(i));
        System.out.println("+-------+----------+-----------------+------------+\n");
    }
}

class Student 
{
    int recNum;
    String name, id;
    double salary;

    public Student(int recNum, String name, String id, double salary) 
    {
        this.recNum = recNum;
        this.name = name;
        this.id = id;
        this.salary = salary;
    }

    @Override
    public String toString() 
    {
        return String.format("| %-5d | %-8s | %-15s | %10.2f |", recNum, name, id, salary);
    }
}
