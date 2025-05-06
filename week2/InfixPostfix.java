// Java Program for Infix to Postfix Conversion and Evaluation
import java.util.*;

class Stack {
    private int top;
    private char[] items = new char[100];

    Stack() { top = -1; }
    boolean isEmpty() { return top == -1; }
    void push(char c) { items[++top] = c; }
    char pop() { return items[top--]; }
    char peek() { return items[top]; }
}

public class InfixPostfix {
    static int precedence(char op) {
        switch (op) {
            case '+': case '-': return 1;
            case '*': case '/': return 2;
            default: return 0;
        }
    }

    static String infixToPostfix(String infix) {
        Stack s = new Stack();
        StringBuilder postfix = new StringBuilder();
        for (char c : infix.toCharArray()) {
            if (Character.isDigit(c)) postfix.append(c);
            else if (c == '(') s.push(c);
            else if (c == ')') {
                while (!s.isEmpty() && s.peek() != '(') postfix.append(s.pop());
                s.pop();
            } else {
                while (!s.isEmpty() && precedence(s.peek()) >= precedence(c)) postfix.append(s.pop());
                s.push(c);
            }
        }
        while (!s.isEmpty()) postfix.append(s.pop());
        return postfix.toString();
    }

    static int evaluatePostfix(String postfix) {
        Stack stack = new Stack();
        for (char c : postfix.toCharArray()) {
            if (Character.isDigit(c)) stack.push((char) (c - '0'));
            else {
                int val2 = stack.pop();
                int val1 = stack.pop();
                switch (c) {
                    case '+': stack.push((char)(val1 + val2)); break;
                    case '-': stack.push((char)(val1 - val2)); break;
                    case '*': stack.push((char)(val1 * val2)); break;
                    case '/': stack.push((char)(val1 / val2)); break;
                }
            }
        }
        return stack.pop();
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the infix expression: ");
        String infix = sc.next();
        String postfix = infixToPostfix(infix);
        System.out.println("Postfix expression is: " + postfix);
        System.out.println("Result of the evaluation: " + evaluatePostfix(postfix));
    }
}
