#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

typedef struct Node {
    char* str;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct {
    Node* root;
} BST;

// Utility to create a new node
Node* createNode(const char* str) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->str = strdup(str);
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert function
Node* insertNode(Node* root, const char* str) {
    if (root == NULL) return createNode(str);
    if (strcmp(str, root->str) < 0)
        root->left = insertNode(root->left, str);
    else
        root->right = insertNode(root->right, str);
    return root;
}

// Search function
int searchNode(Node* root, const char* str) {
    if (root == NULL) return 0;
    if (strcmp(str, root->str) == 0) return 1;
    if (strcmp(str, root->str) < 0)
        return searchNode(root->left, str);
    else
        return searchNode(root->right, str);
}

// Find max in left subtree
Node* findMax(Node* root) {
    while (root->right != NULL) root = root->right;
    return root;
}

// Delete function
Node* deleteNode(Node* root, const char* str) {
    if (root == NULL) return NULL;
    if (strcmp(str, root->str) < 0)
        root->left = deleteNode(root->left, str);
    else if (strcmp(str, root->str) > 0)
        root->right = deleteNode(root->right, str);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root->str);
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root->str);
            free(root);
            return temp;
        }
        Node* temp = findMax(root->left);
        free(root->str);
        root->str = strdup(temp->str);
        root->left = deleteNode(root->left, temp->str);
    }
    return root;
}

// Traversals
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%s ", root->str);
        inorder(root->right);
    }
}

void preorder(Node* root) {
    if (root != NULL) {
        printf("%s ", root->str);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%s ", root->str);
    }
}

// Wrappers for printing
void printInorder(BST* bst) {
    printf("\nINORDER: ");
    inorder(bst->root);
    printf("\n");
}

void printPreorder(BST* bst) {
    printf("\nPREORDER: ");
    preorder(bst->root);
    printf("\n");
}

void printPostorder(BST* bst) {
    printf("\nPOSTORDER: ");
    postorder(bst->root);
    printf("\n");
}

// Free all nodes
void freeTree(Node* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root->str);
        free(root);
    }
}

int main() {
    BST bst = {NULL};
    int choice;
    char data[MAX_LEN];

    do {
        printf("\nBST Operations\n============\n");
        printf("1.Insert Node\t\t2.Search\n");
        printf("3.Delete Node\t\t4.Pre-order Traversal\n");
        printf("5.In-order Traversal\t6.Post-order Traversal\n");
        printf("0.Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1:
                printf("Enter the string to insert: ");
                fgets(data, MAX_LEN, stdin);
                data[strcspn(data, "\n")] = 0; // remove newline
                bst.root = insertNode(bst.root, data);
                printf("Current Tree’s Inorder Traversal:");
                printInorder(&bst);
                break;
            case 2:
                printf("Enter data to search: ");
                fgets(data, MAX_LEN, stdin);
                data[strcspn(data, "\n")] = 0;
                if (searchNode(bst.root, data)) {
                    printf("Element found: %s\n", data);
                } else {
                    printf("Element not found!\n");
                }
                break;
            case 3:
                printf("Enter the string to delete: ");
                fgets(data, MAX_LEN, stdin);
                data[strcspn(data, "\n")] = 0;
                if (searchNode(bst.root, data)) {
                    bst.root = deleteNode(bst.root, data);
                    printf("Deleted successfully.\n");
                } else {
                    printf("Data not found in tree!\n");
                }
                break;
            case 4:
                printPreorder(&bst);
                break;
            case 5:
                printInorder(&bst);
                break;
            case 6:
                printPostorder(&bst);
                break;
            case 0:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);

    freeTree(bst.root);
    return 0;
}
