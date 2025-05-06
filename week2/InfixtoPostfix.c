// C Program for Infix to Postfix Conversion and Evaluation
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAX 100

// Stack structure with array implementation
typedef struct {
    int top;
    char items[MAX];
} Stack;

// Initialize stack
void initialize(Stack *s) {
    s->top = -1;
}

// Check if stack is empty
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Push operation
void push(Stack *s, char item) {
    s->items[++s->top] = item;
}

// Pop operation
char pop(Stack *s) {
    return s->items[s->top--];
}

// Peek operation
char peek(Stack *s) {
    return s->items[s->top];
}

// Function to check precedence of operators
int precedence(char op) {
    switch(op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        default: return 0;
    }
}

// Function to convert infix to postfix
void infixToPostfix(char infix[], char postfix[]) {
    Stack s;
    initialize(&s);
    int i = 0, j = 0;
    while (infix[i] != '\0') {
        if (isdigit(infix[i])) {
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            push(&s, infix[i]);
        } else if (infix[i] == ')') {
            while (!isEmpty(&s) && peek(&s) != '(')
                postfix[j++] = pop(&s);
            pop(&s); // Remove '(' from stack
        } else {
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(infix[i]))
                postfix[j++] = pop(&s);
            push(&s, infix[i]);
        }
        i++;
    }
    while (!isEmpty(&s))
        postfix[j++] = pop(&s);
    postfix[j] = '\0';
}

// Function to evaluate postfix expression
int evaluatePostfix(char postfix[]) {
    Stack s;
    initialize(&s);
    int i = 0;
    while (postfix[i] != '\0') {
        if (isdigit(postfix[i])) {
            push(&s, postfix[i] - '0'); // Convert char to int
        } else {
            int val2 = pop(&s);
            int val1 = pop(&s);
            switch (postfix[i]) {
                case '+': push(&s, val1 + val2); break;
                case '-': push(&s, val1 - val2); break;
                case '*': push(&s, val1 * val2); break;
                case '/': push(&s, val1 / val2); break;
            }
        }
        i++;
    }
    return pop(&s);
}

int main() {
    char infix[MAX], postfix[MAX];
    printf("Enter the infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix expression is: %s\n", postfix);
    printf("Result of the evaluation: %d\n", evaluatePostfix(postfix));
    return 0;
}