import java.util.Scanner;

public class SearchComparison 
{
    static final int SIZE = 10000;

    public static void initializeArray(float[] a) 
    {
        for (int i = 0; i < a.length; i++) 
        {
            a[i] = i;
        }
    }

    public static int linearSearch(float[] a, float key, int[] iterations) 
    {
        for (int i = 0; i < a.length; i++) 
        {
            iterations[0]++;
            if (a[i] == key) 
            {
                return i;
            }
        }
        return -1;
    }

    public static int binarySearch(float[] a, float key, int[] iterations) 
    {
        int left = 0, right = a.length - 1;
        while (left <= right) 
        {
            iterations[0]++;
            int mid = left + (right - left) / 2;
            if (a[mid] == key) 
            {
                return mid;
            }
            if (a[mid] < key) 
            {
                left = mid + 1;
            } 
            else 
            {
                right = mid - 1;
            }
        }
        return -1;
    }

    public static void performSearch(float[] a, float key) 
    {
        int[] iterations = {0};
        long startTime, endTime;
        double timeTaken;

        System.out.println("\nINPUT: " + (int) key);
        
        // Linear Search
        startTime = System.nanoTime();
        int linearResult = linearSearch(a, key, iterations);
        endTime = System.nanoTime();
        timeTaken = (endTime - startTime) / 1000.0;
        System.out.printf("    Linear Search:\n        Position = %d\n        Time = %.2f microsecs\n        Iterations = %d\n", 
                          linearResult, timeTaken, iterations[0]);

        // Binary Search
        iterations[0] = 0;
        startTime = System.nanoTime();
        int binaryResult = binarySearch(a, key, iterations);
        endTime = System.nanoTime();
        timeTaken = (endTime - startTime) / 1000.0;
        System.out.printf("    Binary Search:\n        Position = %d\n        Time = %.2f microsecs\n        Iterations = %d\n", 
                          binaryResult, timeTaken, iterations[0]);
    }

    public static void main(String[] args) 
    {
        float[] a = new float[SIZE];
        initializeArray(a);

        Scanner scanner = new Scanner(System.in);
        
        for (int i = 0; i < 3; i++) 
        {
            System.out.print("\nEnter the search key value: ");
            float key = scanner.nextFloat();
            performSearch(a, key);
        }
        scanner.close();
    }
}