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
    struct Node* newNode = createNode(val);
    if (head == NULL) return newNode;

    struct Node* temp;
    for (temp = head; temp->next != NULL; temp = temp->next);
    temp->next = newNode;
    return head;
}

struct Node* insertPos(struct Node* head, int val, int pos) {
    if (pos < 1) return head;
    if (pos == 1) return insertAtBeginning(head, val);

    struct Node* temp = head;
    for (int i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Position out of bounds\n");
        return head;
    }
    struct Node* newNode = createNode(val);
    newNode->next = temp->next;
    temp->next = newNode;
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
    struct Node* temp;
    for (temp = head; temp->next->next != NULL; temp = temp->next);
    free(temp->next);
    temp->next = NULL;
    return head;
}

struct Node* deletePos(struct Node* head, int pos) {
    if (head == NULL || pos < 1) return head;
    if (pos == 1) return deleteBeg(head);

    struct Node* temp = head;
    for (int i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL) {
        printf("Position out of bounds\n");
        return head;
    }
    struct Node* toDelete = temp->next;
    temp->next = toDelete->next;
    free(toDelete);
    return head;
}

int countNodes(struct Node* head) {
    int count = 0;
    for (struct Node* temp = head; temp != NULL; temp = temp->next) {
        count++;
    }
    return count;
}

int searchNodePos(struct Node* head, int key) {
    int pos = 1;
    for (struct Node* temp = head; temp != NULL; temp = temp->next, pos++) {
        if (temp->data == key) return pos;
    }
    return -1;
}

int searchIndex(struct Node* head, int key) {
    int idx = 0;
    for (struct Node* temp = head; temp != NULL; temp = temp->next, idx++) {
        if (temp->data == key) return idx;
    }
    return -1;
}

void display(struct Node* head) {
    for (struct Node* temp = head; temp != NULL; temp = temp->next) {
        printf("%d -> ", temp->data);
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = NULL;
    int choice, val, pos, res;

    for (;;) {
        printf("\n--- LINKED LIST ---\n");
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