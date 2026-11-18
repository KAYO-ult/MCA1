#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = val;
    newNode->next = NULL;
    return newNode;
}

struct Node* insertAtBeginning(struct Node* head, int val) {
    struct Node* newNode = createNode(val);
    newNode->next = head;
    return newNode;
}

struct Node* insertEnd(struct Node* head, int val) {
    if (head == NULL) return createNode(val);
    head->next = insertEnd(head->next, val);
    return head;
}

struct Node* insertPos(struct Node* head, int val, int pos) {
    if (pos < 1) {
        printf("Position out of bounds\n");
        return head;
    }
    if (pos == 1) {
        struct Node* newNode = createNode(val);
        newNode->next = head;
        return newNode;
    }
    if (head == NULL) {
        printf("Position out of bounds\n");
        return NULL;
    }
    head->next = insertPos(head->next, val, pos - 1);
    return head;
}

struct Node* deleteBeg(struct Node* head) {
    if (head == NULL) return NULL;
    struct Node* temp = head;
    head = head->next;
    free(temp);
    return head;
}

struct Node* deleteEnd(struct Node* head) {
    if (head == NULL) return NULL;
    if (head->next == NULL) {
        free(head);
        return NULL;
    }
    head->next = deleteEnd(head->next);
    return head;
}

struct Node* deletePos(struct Node* head, int pos) {
    if (head == NULL || pos < 1) {
        printf("Position out of bounds\n");
        return head;
    }
    if (pos == 1) {
        struct Node* temp = head->next;
        free(head);
        return temp;
    }
    head->next = deletePos(head->next, pos - 1);
    return head;
}

int countNodes(struct Node* head) {
    if (head == NULL) return 0;
    return 1 + countNodes(head->next);
}

int searchNodePos(struct Node* head, int key) {
    if (head == NULL) return -1;
    if (head->data == key) return 1;
    int res = searchNodePos(head->next, key);
    return (res == -1) ? -1 : 1 + res;
}

int searchIndex(struct Node* head, int key) {
    if (head == NULL) return -1;
    if (head->data == key) return 0;
    int res = searchIndex(head->next, key);
    return (res == -1) ? -1 : 1 + res;
}

void display(struct Node* head) {
    if (head == NULL) {
        printf("NULL\n");
        return;
    }
    printf("%d -> ", head->data);
    display(head->next);
}

int main() {
    struct Node* head = NULL;
    int choice, val, pos, res;

    while (1) {
        printf("\n--- RECURSIVE LINKED LIST ---\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert Anywhere (Position)\n");
        printf("4. Delete at Beginning\n");
        printf("5. Delete at End\n");
        printf("6. Delete Anywhere (Position)\n");
        printf("7. Count Number of Nodes\n");
        printf("8. Search Element (1-based Node Number)\n");
        printf("9. Search Element (0-based Index)\n");
        printf("10. Display\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 0) break;

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                head = insertAtBeginning(head, val); // Fixed function call
                break;
            case 2:
                printf("Enter value: ");
                scanf("%d", &val);
                head = insertEnd(head, val);
                break;
            case 3:
                printf("Enter value and 1-based position: ");
                scanf("%d %d", &val, &pos);
                head = insertPos(head, val, pos);
                break;
            case 4:
                head = deleteBeg(head);
                break;
            case 5:
                head = deleteEnd(head);
                break;
            case 6:
                printf("Enter 1-based position to delete: ");
                scanf("%d", &pos);
                head = deletePos(head, pos);
                break;
            case 7:
                printf("Total Nodes: %d\n", countNodes(head));
                break;
            case 8:
                printf("Enter element to search: ");
                scanf("%d", &val);
                res = searchNodePos(head, val);
                if (res == -1) printf("Element not found\n");
                else printf("Element %d is at Node #%d\n", val, res);
                break;
            case 9:
                printf("Enter element to search: ");
                scanf("%d", &val);
                res = searchIndex(head, val);
                if (res == -1) printf("Element not found\n");
                else printf("Element %d is at Index %d\n", val, res);
                break;
            case 10:
                display(head);
                break;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}